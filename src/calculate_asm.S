/*
 * x86-64 AT&T, Linux
 *
 * Functions:
 *	_add_mat_w(Matrix *a, Matrix *b) -> a[i][j] += b[i][j]
 *	_sub_mat_w(Matrix *a, Matrix *b) -> a[i][j] -= b[i][j]
 *	_mul_mat_w(Matrix *a, Matrix *b) -> a *= b
 *
 * Arguments:
 * 	%rdi = Matrix *a
 * 	%rsi = Matrix *b
 *
 * Return value:
 *	0 = success
 *	-1 = dimension mismatch
 */

.section .rodata
.align 16

.l_abs_mask:
	.quad 0x7FFFFFFFFFFFFFFF
	.quad 0x7FFFFFFFFFFFFFFF

.l_neg_mask:
	.quad 0x8000000000000000
	.quad 0x8000000000000000

.l_one
	.double 1.0

/* IEEE-754 quiet NAN */
.l_nan_val:
	.quad 0x7FF8000000000000

.section .text
.globl _add_mat
.globl _sub_mat
.globl _mul_mat
.globl _det_mat
.globl _add_mat_w
.globl _sub_mat_w
.globl _mul_mat_w
.globl _det_mat_w
.type _add_mat, @function
.type _sub_mat, @function
.type _mul_mat, @function
.type _det_mat, @function
/*
 * %rdi = a (Matrix *)
 * %rsi = b (Matrix *)
 * %rax = return value
 * %rcx = total element count
 * %r8 = pointer into a->data(walking pointer)
 * %r9 = pointer into b->data(walking pointer)
 * %rsp = stack pointer
 * %xmm0 = use in tail_loop(1 double)
 * %ymm0 = SIMD 4 doubles
 */

/* check dimensions of matrix */
.check_dims:
	/* if rows not equal then return */
	movq 8(%rdi), %rcx
	cmpq 8(%rsi), %rcx
	jne .check_dims_fail

	/* if columns not equal then return */
	movq 16(%rdi), %rax
	cmpq 16(%rsi), %rax
	jne .check_dims_fail

	/* rows(%rcx) *= columns(%rax) */
	imulq %rax, %rcx
	ret

/* bypass .check_dims and _add_mat/_sub_mat then return to C caller*/
.check_dims_fail:
	addq $8, %rsp
	jmp .ret_dim_err

_add_mat:
	call .check_dims
	/* empty matrix */
	testq %rcx, %rcx
	jz .ret_suc

	/* load matrix to register */
	/* %r8 = a->data */
	movq 0(%rdi), %r8
	/* %r9 = b->data */
	movq 0(%rsi), %r9

	/* %rax = total elements */
	movq %rcx, %rax
	/* %rax >> 2 */
	shrq $2, %rax
	/* if elements < 4 */
	jz .add_tail

.add_vec_loop:
	/* load data from %r9 32 bytes to %ymm0 */
	/* ymm0 = {b[i + 3], b[i + 2], b[i + 1], b[i + 0]} */
	vmovupd (%r9), %ymm0
	/* 4 additions together */
	/* %ymm0 = {a + b}[i...i + 3] */
	vaddpd (%r8), %ymm0, %ymm0
	/* store data from %ymm0 to %r8 */
	vmovupd %ymm0, (%r8)
	/* i += 4 */
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .add_vec_loop

	/* clear %ymm0 */
	vzeroupper
	/* %rcx %= 4(0 - 3 elements remaining) */
	andq $3, %rcx
	/* if element doensn't reamining jump .ret_suc */
	jz  .ret_suc

.add_tail:
	movsd (%r9), %xmm0
	addsd (%r8), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %rcx
	/* loop if %rcx not equal $0 */
	jnz .add_tail
	jmp .ret_suc

/* same as _add_mat just change instrcution from add to sub */
_sub_mat:
	call .check_dims
	testq %rcx, %rcx
	jz .ret_suc

	movq 0(%rdi), %r8
	movq 0(%rsi), %r9

	movq %rcx, %rax
	shrq $2, %rax
	jz .sub_tail

.sub_vec_loop:
	/* move a to %ymm0 */
	vmovupd (%r8), %ymm0
	/* %ymm0 = a - b */
	vsubpd (%r9), %ymm0, %ymm0
	/* move %ymm0 to a */
	vmovupd %ymm0, (%r8)
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .sub_vec_loop

	vzeroupper
	andq $3, %rcx
	jz .ret_suc

.sub_tail:
	/* move a to %xmm0 */
	movsd (%r8), %xmm0
	/* %xmm0 = a - b */
	subsd (%r9), %xmm0
	/* move %xmm0 to a */
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %rcx
	jnz .sub_tail
	jmp .ret_suc

/* return -1 if a->cols != b->rows */
/* %rax keep elements amount(a->rows * b->cols) */
.check_dims_mul:
	movq 16(%rdi), %rcx
	movq 8(%rsi), %rax
	cmpq %rax, %rcx
	jne .check_dims_fail

	movq 8(%rdi), %rax
	imulq 16(%rsi), %rax
	ret

_mul_mat:
	call .check_dims_mul

	pushq %rbp
	movq %rsp, %rbp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $24, %rsp

	/* save value in matrix before call malloc */
	movq %rdi, -48(%rbp)
	movq %rsi, -56(%rbp)

	/* %rax *= 8(sizeof(double) * %rax) */
	shlq $3, %rax
	movq %rax, %rdi
	/* malloc return storage to %rax, use %rdi for bytes amount */
	call malloc@PLT
	movq %rax, -64(%rbp)

	/* move value in matrix to %rdi(a->data), %rsi(b->data) */
	movq -48(%rbp), %rdi
	movq -56(%rbp), %rsi

	movq 8(%rdi), %r8
	movq 16(%rdi), %r9
	movq 16(%rsi), %r10

	/* %r11 = a->data, %r12 = b->data */
	movq 0(%rdi), %r11
	movq 0(%rsi), %r12
	/* %r13 = result(a->data * b->data) */
	movq -64(%rbp), %r13

	/* i = 0 */
	xorq %r14, %r14

.mul_i_loop:
	/* i < a->rows */
	cmpq %r8, %r14
	jge .mul_i_end

	/* j = 0 */
	xorq %r15, %r15

.mul_j_loop:
	/* j < b->cols */
	cmpq %r10, %r15
	jge .mul_j_end

	/* %xmm0 = 0.0 */
	vxorpd %xmm0, %xmm0, %xmm0

	/* k = 0 */
	xorq %rbx, %rbx

.mul_k_loop:
	/* k < b->cols */
	cmpq %r9, %rbx
	jge .mul_k_end

	/* %rax = i */
	movq %r14, %rax
	/* %rax *= b->cols */
	imulq %r9, %rax
	/* %rax += k */
	addq %rbx, %rax
	/* %xmm1 = a->data[i][k] */
	vmovsd (%r11, %rax, 8), %xmm1

	/* %rax = i */
	movq %rbx, %rax
	/* %rax *= a->cols */
	imulq %r10, %rax
	/* %rax += j */
	addq %r15, %rax

	/* %xmm1 *= b->data[k][j] */
	vmulsd (%r12, %rax, 8), %xmm1, %xmm1
	/* %xmm0 += %xmm1(fixing error of IEEE754) */
	vaddsd %xmm1, %xmm0, %xmm0

	/* k++ */
	incq %rbx
	jmp .mul_k_loop

.mul_k_end:
	/* %rax = i */
	movq %r14, %rax
	/* %rax *= a->rows */
	imulq %r10, %rax
	/* %rax *= j */
	addq %r15, %rax
	/* keep %xmm0 in %r13 */
	vmovsd %xmm0, (%r13, %rax, 8)

	/* j++ */
	incq %r15
	jmp .mul_j_loop

.mul_j_end:
	/* i++ */
	incq %r14 
	jmp .mul_i_loop

.mul_i_end:
	/* move data(Matrix *a) in stack to %rdi */
	movq -48(%rbp), %rdi
	/* %rdi = a->data */
	movq 0(%rdi), %rdi
	/* free a->data */
	call free@PLT

	/* move data(Matrix *a) in stack to %rdi */
	movq -48(%rbp), %rdi
	/* move result in stack to %rax */
	movq -64(%rbp), %rax
	/* a->data = result */
	movq %rax, 0(%rdi)

	/* move data(Matrix *b) in stack to %rsi */
	movq -56(%rbp), %rsi
	/* %rcx = b->cols */
	movq 16(%rsi), %rcx
	/* a->cols = %rcx */
	movq %rcx, 16(%rdi)

	xorq %rax, %rax
	addq $24, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	popq %rbp
	ret

_det_mat:
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	pushq %rbp
	subq $24, %rsp

	/* %rbx = rows */
	movq 8(%rdi), %rbx
	/* %rax = cols */
	movq 16(%rdi), %rax
	/* jump if not equal */
	cmpq %rax, %rbx
	jne .l_nan
	/* jump if size = 0 */
	testq %rbx, %rbx
	jz .l_nan

	/* keep matrix to %rsp */
	movq %rdi, 8(%rsp)

	/* allocate space n^2 */
	movq %rbx, %rdi
	imulq %rbx, %rdi
	shlq $3, %rdi
	call malloc
	testq %rax, %rax
	/* if malloc fail return NAN */
	jz .l_nan
	/* %r12 = workspace */
	movq %rax, %r12

	/* copy matrix to workspace */
	movq %r12, %rdi
	movq 8(%rsp), %rsi
	movq (%rsi), %rsi
	movq %rbx, %rdx
	imulq %rbx, %rdx
	shlq $3, %rdx
	call memcpy

	/* swap_count = 0*/
	xorq %rbp, %rbp
	/* k = 0 */
	xorq %r13, %r13

.l_k_loop:
	cmpq %rbx, %r13
	jge .l_k_done

	movq %r13, %r14

	movq %r13, %rax
	imulq %rbx, %rax
	addq %r13, %rax
	movsd (%r12, %rax, 8), %xmm1
	/* %xmm1 = |A[k][k]| */
	andpd .l_abs_mask(%rip), %xmm1

	/* i = k + 1 */
	leaq 1(%r13), %r15

.l_pivot_loop:
	cmpq %rbx, %r15
	jge .l_pivot_done
	movq %r15, %rax
	imulq %rbx, %rax
	/* i * n + k */
	addq %r13, %rax
	movsd (%r12, %rax, 8), %xmm2
	/* %xmm2 = |A[i][k]| */
	andpd .l_abs_mask(%rip), %xmm2
	ucomisd %xmm1, %xmm2
	jbe .l_pivot_next
	movsd %xmm2, %xmm1
	movq %r15, %r14

.l_pivot_next:
	incq %r15
	jmp .l_pivot_loop

.l_pivot_done:
	xorpd %xmm0, %xmm0
	ucomisd %xmm0, %xmm1
	je .l_zero

	cmpq %r13, %r14
	je .l_no_swap
	incq %rbp

	movq %r13, %rax
	imulq %rbx, %rax
	/* %rax = &A[k][0] */
	leaq (%r12, %rax, 8), %rax

	movq %r14, %rcx
	imulq %rbx, %rcx
	/* %rcx = &A[max_row][0] */
	leaq (%r12, %rcx, 8), %rcx

	/* j = 0 */
	xorq %r15, %r15

.l_swap_loop:
	cmpq %rbx, %r15
	jge .l_swap_done
	movsd (%rax, %r15, 8), %xmm0
	movsd (%rcx, %r15, 8), %xmm2
	movsd %xmm2, (%rax, %r15, 8)
	movsd %xmm0, (%rcx, %r15, 8)
	incq %r15
	jmp .l_swap_loop

.l_swap_done:

.l_no_swap:
	movq %r13, %rcx
	imulq %rbx, %rcx
	leaq (%r12, %rcx, 8), %rcx

	leaq 1(%r13), %r15

.l_elim_i:
	cmpq %rbx, %r15
	jge .l_elim_i_done

	movq %r15, %rax
	imulq %rbx, %rax
	leaq (%r12, %rax, 8), %rax

	movsd (%rax, %r13, 8), %xmm3
	movsd (%rcx, %r13, 8), %xmm4
	divsd %xmm4, %xmm3

	/* j = k + 1 */
	leaq 1(%r13), %rdx

.l_elim_j:
	cmpq %rbx, %rdx
	jge .l_elim_j_done
	/* A[k][j] */
	movsd (%rcx, %rdx, 8), %xmm5
	/* factor * A[k][j] */
	mulsd %xmm3, %xmm5
	/* A[i][j] */
	movsd (%rax, %rdx, 8), %xmm6
	/* A[i][j] -= factor * A[k][j] */
	subsd %xmm5, %xmm6
	movsd %xmm6, (%rax, %rdx, 8)
	incq %rdx
	jmp .l_elim_j

.l_elim_j_done:
	/* next row i */
	incq %r15
	jmp .l_elim_i

.l_elim_i_done:
	/* k++ */
	incq %r13
	jmp .l_k_loop

.l_k_done:
	movsd .l_one(%rip), %xmm0
	/* i = 0 */
	xorq %r13, %r13

.l_diag:
	cmpq %rbx, %r13
	jge .l_diag_done
	movq %r13, %rax
	imulq %rbx, %rax
	addq %r13, %rax
	movsd (%r12, %rax, 8), %xmm1
	mulsd %xmm1, %xmm0
	incq %r13
	jmp .l_diag

.l_diag_done:
	testq $1, %rbp
	jz .l_sign_ok
	xorpd .l_neg_mask(%rip), %xmm0

.l_sign_ok:
	movsd %xmm0, (%rsp)
	movq %r12, %rdi
	call free
	movsd (%rsp), %xmm0
	jmp .l_epilogue

.l_zero:
	movq %r12, %rdi
	call free
	xorpd %xmm0, %xmm0
	jmp .l_epilogue

.l_nan:
	movsd .l_nan_val(%rip), %xmm0

.l_epilogue:
	addq $24, %rsp
	popq %rbp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	ret

_add_mat_w:
_sub_mat_w:
_mul_mat_w:
_det_mat_w:

/* ret 0 */
.ret_suc:
	xorq %rax, %rax
	ret

/* ret -1 */
.ret_dim_err:
	movq $-1, %rax
	ret

.size _add_mat, . - _add_mat
.size _sub_mat, . - _sub_mat
.size _mul_mat, . - _mul_mat
.size _det_mat, . - _det_mat
.section .note.GNU-stack, "", @progbits
