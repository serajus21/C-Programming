	.file	"avr_hello.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"hello, world\r\n"
	.section	.text.startup,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(2)
	sts 192,r24
	ldi r24,lo8(16)
	ldi r25,0
	sts 196+1,r25
	sts 196,r24
	ldi r24,lo8(8)
	sts 193,r24
	ldi r30,lo8(.LC0)
	ldi r31,hi8(.LC0)
.L3:
	ld r24,Z+
.L2:
	lds r25,192
	sbrs r25,5
	rjmp .L2
	sts 198,r24
	ldi r24,hi8(.LC0+14)
	cpi r30,lo8(.LC0+14)
	cpc r31,r24
	brne .L3
.L4:
	rjmp .L4
	.size	main, .-main
	.ident	"GCC: (Fedora 15.3.0-1.fc45) 15.3.0"
.global __do_copy_data
