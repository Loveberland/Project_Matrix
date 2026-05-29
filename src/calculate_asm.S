.section .text
.globl _add_mat
.globl _sub_mat
.type _add_mat, @function
.type _sub_mat, @function
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
.section .note.GNU-stack, "", @progbits
