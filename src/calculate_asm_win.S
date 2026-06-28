/*
 * x86_64 AT&T, Windows
 *
 * Functions:
 *	_add_mat_w(Matrix *a, Matrix *b) -> a[i][j] += b[i][j]
 *	_sub_mat_w(Matrix *a, Matrix *b) -> a[i][j] -= b[i][j]
 *	_mul_mat_w(Matrix *a, Matrix *b) -> a *= b
 *
 * Arguments:
 * 	%rcx = Matrix *a
 * 	%rdx = Matrix *b
 *
 * Return value:
 *	0 = success
 *	-1 = dimension mismatch
 */

.section	.rdata, "dr"
.align	16

.l_abs_mask:
	.quad	0x7FFFFFFFFFFFFFFF
	.quad	0x7FFFFFFFFFFFFFFF

.l_neg_mask:
	.quad	0x8000000000000000
	.quad	0x8000000000000000

.l_one:
	.double 1.0

.l_nan_val:
	.quad 0x7FF8000000000000

.section .text

.globl	_add_mat
.globl	_sub_mat
.globl	_mul_mat
.globl	_det_mat
.globl	_add_mat_w
.globl	_sub_mat_w
.globl	_mul_mat_w
.globl	_det_mat_w
#ifndef	_WIN32
.type	_add_mat_w, @function
.type	_sub_mat_w, @function
.type	_mul_mat_w, @function
.type	_det_mat_w, @function
.type	_add_mat, @function
.type	_sub_mat, @function
.type	_mul_mat, @function
.type	_det_mat, @function
#endif

.check_dims:
	movq	8(%rcx), %r10
	cmpq	8(%rdx), %r10
	jne	.check_dims_fail

	movq	16(%rcx), %rax
	cmpq	16(%rdx), %rax
	jne	.check_dims_fail

	imulq	%rax, %r10
	ret

.check_dims_fail:
	addq	$8, %rsp
	jmp	.ret_dim_err

_add_mat_w:
	call	.check_dims
	testq	%r10, %r10
	jz	.ret_suc

	movq	0(%rcx), %r8
	movq	0(%rdx), %r9

	movq	%r10, %rax
	shrq	$2, %rax
	jz	.add_tail

.add_vec_loop:
	vmovupd	(%r9), %ymm0
	vaddpd	(%r8), %ymm0, %ymm0
	vmovupd	%ymm0, (%r8)
	addq	$32, %r8
	addq	$32, %r9
	decq	%rax
	jnz	.add_vec_loop

	vzeroupper
	andq	$3, %r10
	jz	.ret_suc

.add_tail:
	movsd	(%r9), %xmm0
	addsd	(%r8), %xmm0
	movsd	%xmm0, (%r8)
	addq	$8, %r8
	addq	$8, %r9
	decq	%r10
	jnz	.add_tail
	jmp	.ret_suc

_sub_mat_w:
	call	.check_dims
	testq	%r10, %r10
	jz	.ret_suc

	movq	0(%rcx), %r8
	movq	0(%rdx), %r9

	
	movq	%r10, %rax
	shrq	$2, %rax
	jz	.sub_tail

.sub_vec_loop:
	vmovupd	(%r8), %ymm0
	vsubpd	(%r9), %ymm0, %ymm0
	vmovupd	%ymm0, (%r8)
	addq	$32, %r8
	addq	$32, %r9
	decq	%rax
	jnz	.sub_vec_loop

	vzeroupper
	andq	$3, %r10
	jz	.ret_suc

.sub_tail:
	movsd	(%r8), %xmm0
	subsd	(%r9), %xmm0
	movsd	%xmm0, (%r8)
	addq	$8, %r8
	addq	$8, %r9
	decq	%r10
	jnz	.sub_tail
	jmp	.ret_suc

.check_dims_mul:
	movq	16(%rcx), %r8
	movq	8(%rdx), %rax
	cmpq	%rax, %r8
	jne	.check_dims_fail

	movq	8(%rcx), %rax
	imulq	16(%rdx), %rax
	ret

_mul_mat_w:
	call	.check_dims_mul

	pushq	%rbp
	movq	%rsp, %rbp
	pushq	%rbx
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15
	subq	$56, %rsp

	movq	%rcx, -48(%rbp)
	movq	%rdx, -56(%rbp)

	shlq	$3, %rax
	movq	%rax, %rcx
	call	malloc
	movq	%rax, -64(%rbp)

	movq	-48(%rbp), %rcx
	movq	-56(%rbp), %rdx

	movq	8(%rcx), %r8
	movq	16(%rcx), %r9
	movq	16(%rdx), %r10
	movq	0(%rcx), %r11
	movq	0(%rdx), %r12
	movq	-64(%rbp), %r13
	
	xorq	%r14, %r14

.mul_i_loop_w:
	cmpq	%r8, %r14
	jge	.mul_i_end_w

	xorq	%r15, %r15

.mul_j_loop_w:
	cmpq	%r10, %r15
	jge	.mul_j_end_w

	vxorpd	%xmm0, %xmm0, %xmm0

	xorq	%rbx, %rbx

.mul_k_loop_w:
	cmpq	%r9, %rbx
	jge	.mul_k_end_w

	movq	%r14, %rax
	imulq	%r9, %rax
	addq	%rbx, %rax
	vmovsd	(%r11, %rax, 8), %xmm1

	movq	%rbx, %rax
	imulq	%r10, %rax
	addq	%r15, %rax
	vmulsd	(%r12, %rax, 8), %xmm1, %xmm1

	vaddsd 	%xmm1, %xmm0, %xmm0

	incq	%rbx
	jmp	.mul_k_loop_w

.mul_k_end_w:
	movq	%r14, %rax
	imulq	%r10, %rax
	addq	%r15, %rax
	vmovsd	%xmm0, (%r13, %rax, 8)

	incq 	%r15
	jmp	.mul_j_loop_w

.mul_j_end_w:
	incq 	%r14
	jmp	.mul_i_loop_w

.mul_i_end_w:
	movq 	-48(%rbp), %rcx
	movq 	0(%rcx), %rcx
	call 	free

	movq 	-48(%rbp), %rcx
	movq 	-64(%rbp), %rax
	movq 	%rax, 0(%rcx)

	movq 	-56(%rbp), %rdx
	movq 	16(%rdx), %rax
	movq 	%rax, 16(%rcx)

	xorq 	%rax, %rax
	addq 	$56, %rsp
	popq 	%r15
	popq 	%r14
	popq 	%r13
	popq 	%r12
	popq 	%rbx
	popq 	%rbp
	ret

_det_mat_w:
	pushq	%rbx
	pushq	%rbp
    	pushq	%rsi
    	pushq	%rdi
    	pushq	%r12
    	pushq   %r13
    	pushq   %r14
    	pushq   %r15

	subq	$56, %rsp

	movq	8(%rcx), %rbx
	movq	16(%rcx), %rax
	cmpq	%rax, %rbx
	jne	.l_nan_w
	testq	%rbx, %rbx
	jz	.l_nan_w

	movq    %rcx, 32(%rsp)

	movq    %rbx, %rcx
    	imulq   %rbx, %rcx
    	shlq    $3, %rcx
    	call    malloc
    	testq   %rax, %rax
    	jz      .l_nan_w
    	movq    %rax, %r12

	movq    %r12, %rcx
	movq    32(%rsp), %rdx
	movq    (%rdx), %rdx
    	movq    %rbx, %r8
    	imulq   %rbx, %r8
    	shlq    $3, %r8
    	call    memcpy

	xorq    %rbp, %rbp
	xorq    %r13, %r13

.l_k_loop_w:
	cmpq    %rbx, %r13
    	jge     .l_k_done_w

	movq    %r13, %r14

	movq    %r13, %rax
	imulq   %rbx, %rax
	addq    %r13, %rax
	movsd   (%r12, %rax, 8), %xmm1
	andpd   .l_abs_mask(%rip), %xmm1

	leaq    1(%r13), %r15

.l_pivot_loop_w:
	cmpq    %rbx, %r15
	jge     .l_pivot_done_w
	movq    %r15, %rax
	imulq   %rbx, %rax
	addq    %r13, %rax
	movsd   (%r12, %rax, 8), %xmm2
	andpd   .l_abs_mask(%rip), %xmm2
	ucomisd %xmm1, %xmm2
	jbe     .l_pivot_next_w
	movsd   %xmm2, %xmm1
	movq    %r15, %r14

.l_pivot_next_w:
	incq    %r15
	jmp     .l_pivot_loop_w

.l_pivot_done_w:
	xorpd   %xmm0, %xmm0
	ucomisd	%xmm0, %xmm1
	je      .l_zero_w

	cmpq    %r13, %r14
	je      .l_no_swap_w
	incq    %rbp

	movq    %r13, %rax
	imulq   %rbx, %rax
	leaq    (%r12, %rax, 8), %rax

	movq    %r14, %rcx
	imulq   %rbx, %rcx
	leaq    (%r12, %rcx, 8), %rcx

	xorq    %r15, %r15

.l_swap_loop_w:
	cmpq    %rbx, %r15
	jge     .l_swap_done_w
	movsd   (%rax, %r15, 8), %xmm0
	movsd   (%rcx, %r15, 8), %xmm2
	movsd   %xmm2, (%rax, %r15, 8)
	movsd   %xmm0, (%rcx, %r15, 8)

	incq    %r15
	jmp     .l_swap_loop_w

.l_swap_done_w:

.l_no_swap_w:
	movq    %r13, %rcx
	imulq   %rbx, %rcx
	leaq    (%r12, %rcx, 8), %rcx

	leaq    1(%r13), %r15

.l_elim_i_w:
	cmpq    %rbx, %r15
	jge     .l_elim_i_done_w

	movq    %r15, %rax
    	imulq   %rbx, %rax
    	leaq    (%r12, %rax, 8), %rax

	movsd   (%rax, %r13, 8), %xmm3
    	movsd   (%rcx, %r13, 8), %xmm4
    	divsd   %xmm4, %xmm3

	leaq    1(%r13), %rdx

.l_elim_j_w:
	cmpq    %rbx, %rdx
    	jge     .l_elim_j_done_w
    	movsd   (%rcx, %rdx, 8), %xmm5
    	mulsd   %xmm3, %xmm5
	movsd   (%rax, %rdx, 8), %xmm2
    	subsd   %xmm5, %xmm2
    	movsd   %xmm2, (%rax, %rdx, 8)
    	incq    %rdx
    	jmp     .l_elim_j_w

.l_elim_j_done_w:
	incq    %r15
	jmp     .l_elim_i_w

.l_elim_i_done_w:
	incq    %r13
    	jmp     .l_k_loop_w

.l_k_done_w:
	movsd   .l_one(%rip), %xmm0
	xorq    %r13, %r13

.l_diag_w:
	cmpq    %rbx, %r13
    	jge     .l_diag_done_w
    	movq    %r13, %rax
    	imulq   %rbx, %rax
    	addq    %r13, %rax
    	movsd   (%r12, %rax, 8), %xmm1
    	mulsd   %xmm1, %xmm0
    	incq    %r13
    	jmp     .l_diag_w

.l_diag_done_w:
	testq   $1, %rbp
    	jz      .l_sign_ok_w
    	xorpd	.l_neg_mask(%rip), %xmm0

.l_sign_ok_w:
	movsd   %xmm0, 40(%rsp)
	movq    %r12, %rcx
	call    free
	movsd   40(%rsp), %xmm0
    	jmp     .l_epilogue_w

.l_zero_w:
	movq    %r12, %rcx
    	call    free
    	xorpd   %xmm0, %xmm0
    	jmp	.l_epilogue_w

.l_nan_w:
	movsd   .l_nan_val(%rip), %xmm0

.l_epilogue_w:
	addq    $56, %rsp
    	popq    %r15
    	popq    %r14
    	popq    %r13
    	popq    %r12
    	popq    %rdi
    	popq    %rsi
    	popq    %rbp
    	popq	%rbx
    	ret

_add_mat:
_sub_mat:
_mul_mat:
_det_mat:

.ret_suc:
	xorq	%rax, %rax
	ret

.ret_dim_err:
	movq	$-1, %rax
	ret

#ifndef _WIN32
.size	_add_mat_w, . - _add_mat_w
.size	_sub_mat_w, . - _sub_mat_w
.size	_mul_mat_w, . - _mul_mat_w
.size	_det_mat_w, . - _det_mat_w
.section	.note.GNU-stack, "", @progbits
#endif