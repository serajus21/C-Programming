        .equ  PINB, 0x03
        .equ  DDRB, 0x04
        .global main
main:
        sbi   DDRB, 5
        ldi   r16, 5
        sts   0x81, r16          ; TCCR1B: timer 1 counts every 1024 clocks
loop:
        lds   r24, 0x84          ; TCNT1L
        lds   r25, 0x85          ; TCNT1H
mark:
        sbi   PINB, 5
        ldi   r18, 0x00
        ldi   r19, 0x6A
        ldi   r20, 0x18
delay:
        subi  r18, 1
        sbci  r19, 0
        sbci  r20, 0
        brne  delay
        rjmp  loop
