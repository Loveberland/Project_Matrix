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
