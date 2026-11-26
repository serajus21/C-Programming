	.file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"hello, world"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 16.2.1 20261029 (Red Hat 16.2.1-3)"
	.section	.note.GNU-stack,"",@progbits
