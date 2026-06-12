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

.section .text

.globl _add_mat
.globl _sub_mat
.globl _mul_mat
.globl _add_mat_w
.globl _sub_mat_w
.globl _mul_mat_w
#ifndef _WIN32
.type _add_mat_w, @function
.type _sub_mat_w, @function
.type _mul_mat_w, @function
.type _add_mat, @function
.type _sub_mat, @function
.type _mul_mat, @function
#endif

.check_dims:
	movq 8(%rcx), %r10
	cmpq 8(%rdx), %r10
	jne .check_dims_fail

	movq 16(%rcx), %rax
	cmpq 16(%rdx), %rax
	jne .check_dims_fail

	imulq %rax, %r10
	ret

.check_dims_fail:
	addq $8, %rsp
	jmp .ret_dim_err

_add_mat_w:
	call .check_dims
	testq %r10, %r10
	jz .ret_suc

	movq 0(%rcx), %r8
	movq 0(%rdx), %r9

	movq %r10, %rax
	shrq $2, %rax
	jz .add_tail

.add_vec_loop:
	vmovupd (%r9), %ymm0
	vaddpd (%r8), %ymm0, %ymm0
	vmovupd %ymm0, (%r8)
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .add_vec_loop

	vzeroupper
	andq $3, %r10
	jz .ret_suc

.add_tail:
	movsd (%r9), %xmm0
	addsd (%r8), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %r10
	jnz .add_tail
	jmp .ret_suc

_sub_mat_w:
	call .check_dims	
	testq %r10, %r10
	jz .ret_suc

	movq 0(%rcx), %r8
	movq 0(%rdx), %r9

	
	movq %r10, %rax
	shrq $2, %rax
	jz .sub_tail

.sub_vec_loop:
	vmovupd (%r8), %ymm0
	vsubpd (%r9), %ymm0, %ymm0
	vmovupd %ymm0, (%r8)
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .add_vec_loop

	vzeroupper
	andq $3, %r10
	jz .ret_suc

.sub_tail:
	movsd (%r8), %xmm0
	subsd (%r9), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %r10
	jnz .sub_tail
	jmp .ret_suc

.check_dims_mul:
	movq 16(%rcx), %r8
	movq 8(%rdx), %rax
	cmpq %rax, %r8
	jne .check_dims_fail

	movq 8(%rcx), %rax
	imulq 16(%rdx), %rax
	ret

_mul_mat_w:
	call .check_dims_mul

	pushq %rbp
	movq %rsp, %rbp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $56, %rsp

	movq %rcx, -48(%rbp)
	movq %rdx, -56(%rbp)

	shlq $3, %rax
	movq %rax, %rcx
	call malloc
	movq %rax, -64(%rbp)

	movq -48(%rbp), %rcx
	movq -56(%rbp), %rdx

	movq 8(%rcx), %r8
	movq 16(%rcx), %r9
	movq 16(%rdx), %r10
	movq 0(%rcx), %r11
	movq 0(%rdx), %r12
	movq -64(%rbp), %r13
	
	xorq %r14, %r14

.mul_i_loop_w:
	cmpq %r8, %r14
	jge .mul_i_end_w

	xorq %r15, %r15

.mul_j_loop_w:
	cmpq %r10, %r15
	jge .mul_j_end_w

	vxorpd %xmm0, %xmm0, %xmm0

	xorq %rbx, %rbx

.mul_k_loop_w:
	cmpq %r9, %rbx
	jge .mul_k_end_w

	movq %r14, %rax
	imulq %r9, %rax
	addq %rbx, %rax
	vmovsd (%r11, %rax, 8), %xmm1

	movq %rbx, %rax
	imulq %r10, %rax
	addq %r15, %rax
	vmulsd (%r12, %rax, 8), %xmm1, %xmm1

	vaddsd %xmm1, %xmm0, %xmm0

	incq %rbx
	jmp .mul_k_loop_w

.mul_k_end_w:
	movq %r14, %rax
	imulq %r10, %rax
	addq %r15, %rax
	vmovsd %xmm0, (%r13, %rax, 8)

	incq %r15
	jmp .mul_j_loop_w

.mul_j_end_w:
	incq %r14
	jmp .mul_i_loop_w

.mul_i_end_w:
	movq -48(%rbp), %rcx
	movq 0(%rcx), %rcx
	call free

	movq -48(%rbp), %rcx
	movq -64(%rbp), %rax
	movq %rax, 0(%rcx)

	movq -56(%rbp), %rdx
	movq 16(%rdx), %rax
	movq %rax, 16(%rcx)

	xorq %rax, %rax
	addq $56, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	popq %rbp
	ret

_add_mat:
_sub_mat:
_mul_mat:
.ret_suc:
	xorq %rax, %rax
	ret

.ret_dim_err:
	movq $-1, %rax
	ret

#ifndef _WIN32
.size _add_mat_w, . - _add_mat_w
.size _sub_mat_w, . - _sub_mat_w
.size _mul_mat_w, . - _mul_mat_w
.section .note.GNU-stack, "", @progbits
#endif
