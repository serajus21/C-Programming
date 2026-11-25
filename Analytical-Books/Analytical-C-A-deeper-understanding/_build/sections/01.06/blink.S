; blink.S
; Blink the Uno's LED (pin 13 = port B, bit 5) in AVR assembly.
; Every instruction line below becomes one machine instruction.

        .equ  PINB, 0x03        ; I/O address of PINB
        .equ  DDRB, 0x04        ; I/O address of DDRB

        .global main
main:
        sbi   DDRB, 5           ; bit 5 of DDRB = 1: PB5 is an output
loop:
        sbi   PINB, 5           ; writing 1 to PINB bit 5 toggles PB5
        ldi   r18, 0x00         ; r20:r19:r18 = 0x186A00 = 1,600,000
        ldi   r19, 0x6A
        ldi   r20, 0x18
delay:
        subi  r18, 1            ; subtract 1 from the 24-bit count...
        sbci  r19, 0            ; ...borrowing from the middle byte
        sbci  r20, 0            ; ...and from the top byte
        brne  delay             ; until all 24 bits are 0
        rjmp  loop              ; then toggle again, forever
