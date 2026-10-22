// funcsLib.c
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void setupMessage(char *message)
{
    printf("%s\n", message);
}

void delay(int sec)
{
    sleep(sec);
}

void digitalWrite(int pin, int state)
{
    if (state == 1)
    {
        printf("PIN: %d | State: ON\n", pin);
    }
    else
    {
        printf("PIN: %d | State: OFF\n", pin);
    }
}