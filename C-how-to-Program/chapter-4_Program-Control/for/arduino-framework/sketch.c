// sketch.c

#include <stdio.h>
#include "funcsLib.h"

void digitalWrite(int pin, int state)
{
    if (state == 1)
    {
        printf("PIN : %d | STATUS: ON\n", pin);
    }
    else
    {
        printf("PIN : %d | STATUS: OFF\n", pin);
    }
}

void delay(int milisecs)
{
    printf("Waiting %d ms ... \n", milisecs);
}

/*
#include <time.h>
void delay(int milisecs)
{
    struct timespec ts;
    
    // Convert milliseconds to seconds and nanoseconds
    ts.tv_sec = milisecs / 1000;
    ts.tv_nsec = (milisecs % 1000) * 1000000;
    
    // Pause execution
    nanosleep(&ts, NULL);
}
*/