// http-server.c
// A small HTTP server written with raw POSIX sockets (Linux/macOS).
// Compile: gcc -Wall -Wextra -Wpedantic -std=c17 http-server.c -o http-server
// Run:     ./http-server
// Open:    http://127.0.0.1:8080

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10
#define REQUEST_BUFFER_SIZE 4096

/*
 * send() is allowed to send fewer bytes than we request. This helper keeps
 * calling send() until the complete HTTP header or body has been sent.
 */
static int send_all(int socket_fd, const char *data, size_t length)
{
    size_t total_sent = 0;

    while (total_sent < length) {
        ssize_t sent = send(socket_fd, data + total_sent, length - total_sent, 0);

        if (sent < 0) {
            perror("send");
            return -1;
        }

        if (sent == 0) {
            fputs("send: connection closed before the response was complete\n", stderr);
            return -1;
        }

        total_sent += (size_t)sent;
    }

    return 0;
}

/*
 * This is the closest raw-C equivalent of Node's request handler:
 *
 *   http.createServer((req, res) => { ... })
 *
 * For this first version, every request receives the same HTML page.
 */
static void handle_client(int client_fd)
{
    char request[REQUEST_BUFFER_SIZE + 1];
    const char body[] =
        "<!doctype html>\n"
        "<html>\n"
        "  <head><title>Raw C HTTP Server</title></head>\n"
        "  <body><h1>Hello from raw C!</h1></body>\n"
        "</html>\n";
    char response_header[256];

    ssize_t received = recv(client_fd, request, REQUEST_BUFFER_SIZE, 0);
    if (received < 0) {
        perror("recv");
        return;
    }

    if (received == 0) {
        return; // The client disconnected without sending a request.
    }

    request[received] = '\0';
    printf("\n--- Request received ---\n%s\n", request);

    int header_length = snprintf(
        response_header,
        sizeof response_header,
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        strlen(body));

    if (header_length < 0 || (size_t)header_length >= sizeof response_header) {
        fputs("Could not create the HTTP response header\n", stderr);
        return;
    }

    if (send_all(client_fd, response_header, (size_t)header_length) == 0) {
        send_all(client_fd, body, strlen(body));
    }
}

int main(void)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return 1;
    }

    /* Lets us restart the program without waiting for an old socket to expire. */
    int reuse_address = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &reuse_address, sizeof reuse_address) < 0) {
        perror("setsockopt");
        close(server_fd);
        return 1;
    }

    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    /* Loopback means this server is reachable only from this computer. */
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) != 1) {
        fputs("inet_pton: could not create the loopback address\n", stderr);
        close(server_fd);
        return 1;
    }

    if (bind(server_fd, (struct sockaddr *)&server_address,
             sizeof server_address) < 0) {
        perror("bind");
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen");
        close(server_fd);
        return 1;
    }

    /* Avoid terminating if a browser disconnects while we are sending. */
    signal(SIGPIPE, SIG_IGN);

    printf("Server running at http://127.0.0.1:%d\n", PORT);
    puts("Press Ctrl+C to stop it.");

    for (;;) {
        struct sockaddr_in client_address;
        socklen_t client_address_length = sizeof client_address;
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address,
                               &client_address_length);

        if (client_fd < 0) {
            if (errno == EINTR) {
                continue;
            }

            perror("accept");
            continue;
        }

        handle_client(client_fd);
        close(client_fd); // "Connection: close" means this request is finished.
    }
}
