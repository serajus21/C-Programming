	.file	"ops.c"
	.text
	.p2align 4
	.globl	times10
	.type	times10, @function
times10:
.LFB0:
	.cfi_startproc
	leal	(%rdi,%rdi,4), %eax
	addl	%eax, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	times10, .-times10
	.p2align 4
	.globl	div10
	.type	div10, @function
div10:
.LFB1:
	.cfi_startproc
	movl	%edi, %eax
	movl	$3435973837, %edx
	imulq	%rdx, %rax
	shrq	$35, %rax
	ret
	.cfi_endproc
.LFE1:
	.size	div10, .-div10
	.p2align 4
	.globl	sum_to
	.type	sum_to, @function
sum_to:
.LFB2:
	.cfi_startproc
	testl	%edi, %edi
	jle	.L7
	leal	1(%rdi), %ecx
	xorl	%edx, %edx
	andl	$1, %edi
	movl	$1, %eax
	je	.L6
	movl	$2, %eax
	movl	$1, %edx
	cmpl	%ecx, %eax
	je	.L4
	.p2align 4
	.p2align 4
	.p2align 3
.L6:
	leal	1(%rdx,%rax,2), %edx
	addl	$2, %eax
	cmpl	%ecx, %eax
	jne	.L6
.L4:
	movl	%edx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	xorl	%edx, %edx
	movl	%edx, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	sum_to, .-sum_to
	.ident	"GCC: (GNU) 16.2.1 20261029 (Red Hat 16.2.1-3)"
	.section	.note.GNU-stack,"",@progbits
