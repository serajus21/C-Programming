	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"Enter two integers: "
.LC1:
	.string	"%d %d"
.LC2:
	.string	"Addition: %d\n"
.LC3:
	.string	"Subtraction: %d\n"
.LC4:
	.string	"Multiplication: %d\n"
.LC5:
	.string	"Division: %d\n"
	.align 8
.LC6:
	.string	"--------------------Area of Circle---------------------"
	.align 8
.LC8:
	.string	"Enter the radius of the circle: "
.LC9:
	.string	"%f"
.LC10:
	.string	"Area of the circle: %f\n"
	.align 8
.LC11:
	.string	"--------------------Area of Rectangle---------------------"
	.align 8
.LC12:
	.string	"Enter the length and width of the rectangle: "
.LC13:
	.string	"%f %f"
.LC14:
	.string	"Area of the rectangle: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leaq	-8(%rbp), %rdx
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc23_scanf
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	add
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	subtract
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	multiply
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	divide
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC6, %edi
	call	puts
	pxor	%xmm0, %xmm0
	movss	%xmm0, -12(%rbp)
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC9, %edi
	movl	$0, %eax
	call	__isoc23_scanf
	movl	-12(%rbp), %eax
	movd	%eax, %xmm0
	call	area_of_circle
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm0, %xmm2
	movq	%xmm2, %rax
	movq	%rax, %xmm0
	movl	$.LC10, %edi
	movl	$1, %eax
	call	printf
	movl	$.LC11, %edi
	call	puts
	pxor	%xmm0, %xmm0
	movss	%xmm0, -16(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -20(%rbp)
	movl	$.LC12, %edi
	movl	$0, %eax
	call	printf
	leaq	-20(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC13, %edi
	movl	$0, %eax
	call	__isoc23_scanf
	movss	-20(%rbp), %xmm0
	movl	-16(%rbp), %eax
	movaps	%xmm0, %xmm1
	movd	%eax, %xmm0
	call	area_of_rectangle
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm3
	movq	%xmm3, %rax
	movq	%rax, %xmm0
	movl	$.LC14, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 16.1.1 20260515 (Red Hat 16.1.1-2)"
	.section	.note.GNU-stack,"",@progbits
