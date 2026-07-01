/*
 * x86-64 AT&T syntax
 * Function: _trans_mat(Matrix *mat)
 */

.section	.text
.globl	_trans_mat_w

.check_dims:
	/* %rax holds total number of elements. */
	movq	8(%rdi), %rax
	imulq	16(%rdi), %rax
	ret

_trans_mat_w:
	pushq	%rdi
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rcx, %rdi
	pushq	%rbx
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15
	subq	$48, %rsp

	/* mat == NULL? */
	testq 	%rdi, %rdi
	jz	.ret_err

	/* Move matrix to -48(%rbp). */
	movq	%rdi, -48(%rbp)

	/* mat->data == NULL? */
	movq	0(%rdi), %rax
	testq	%rax, %rax
	jz	.ret_err

	call	.check_dims
	testq	%rax, %rax
	jz 	.ret_suc

	shlq	$3, %rax
	movq	%rax, %rcx
	call	malloc

	/* Save new_data pointer to stack. */
	movq	%rax, -56(%rbp);

	/* Return matrix back. */
	movq	-48(%rbp), %rdi
	/* %r8 = rows */
	movq	8(%rdi), %r8
	/* %r9 = columns */
	movq	16(%rdi), %r9
	/* %r10 = matrix */
	movq	0(%rdi), %r10
	/* %r11 = new_data */
	movq	-56(%rbp), %r11

	/* i = 0 */
	xorq	%r14, %r14

.i_loop:
	/* i < rows? */
	cmpq	%r8, %r14
	jge	.i_end

	/* j = 0 */
	xorq	%r15, %r15

.j_loop:
	/* j < columns? */
	cmpq	%r9, %r15
	jge	.j_end

	/* %xmm0 = mat->data[i * columns + j] */
	movq	%r14, %rax
	imulq	%r9, %rax
	addq	%r15, %rax
	movsd	(%r10, %rax, 8), %xmm0

	/* new_data->data[j * rows + i] = %xmm0 */
	movq	%r15, %rax
	imulq	%r8, %rax
	addq	%r14, %rax
	movsd	%xmm0, (%r11, %rax, 8)

	/* j++ */
	incq	%r15
	jmp	.j_loop

.j_end:
	/* i++ */
	incq	%r14
	jmp	.i_loop

.i_end:
	/* free old memory */
	/* %rdi = mat */
	movq	-48(%rbp), %rdi
	/* mat->data */
	movq	0(%rdi), %rcx
	call	free

	/* %rdi = mat */
	movq	-48(%rbp), %rdi

	/* mat->data = new_data */
	movq	-56(%rbp), %rax
	movq	%rax, 0(%rdi)

	/* swap rows and columns. */
	movq	8(%rdi), %r8
	movq	16(%rdi), %r9
	movq	%r8, 16(%rdi)
	movq	%r9, 8(%rdi)

.ret_suc:
	xorq	%rax, %rax
	jmp .epilogue
	
.ret_err:
	movq	$-1, %rax

.epilogue:
	addq	$48, %rsp
	popq	%r15
	popq	%r14
	popq	%r13
	popq	%r12
	popq	%rbx
	popq	%rbp
	popq	%rdi
	ret
