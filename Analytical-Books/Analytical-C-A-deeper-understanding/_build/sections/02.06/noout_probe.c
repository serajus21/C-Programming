#include <stdio.h>
#include <avr/io.h>
#include <avr/sleep.h>
static int up(char c, FILE *f){ (void)f; while(!(UCSR0A&(1<<UDRE0))){} UDR0=c; return 0;}
static FILE u = FDEV_SETUP_STREAM(up, NULL, _FDEV_SETUP_WRITE);
int main(void){
  FILE *was = stdout;
  int n = printf("hello\n");
  UCSR0A=(1<<U2X0); UBRR0=16; UCSR0B=(1<<TXEN0); stdout=&u;
  printf("stdout was %p; printf returned %d\n", (void*)was, n);
  while(!(UCSR0A&(1<<TXC0))){} __asm__ volatile("cli"); sleep_mode(); }
