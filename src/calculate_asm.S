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
 * %r8 = pointer into a->data
 * %r9 = pointer into b->data
 * %r11 = loop counter
 * %xmm0 = current element scratch
 */

.check_dims:
	movq 8(%rdi), %rcx
	cmpq 8(%rsi), %rcx
	jne .check_dims_fail

	movq 16(%rdi), %rax
	cmpq 16(%rsi), %rax
	jne check_dims_fail

	imulq %rax, %rcx
	ret

.check_dims_fail:
	addq $8, %rsp
	jmp .ret_dim_err

_add_mat:
	call .check_dims
	testq %rcx, %rcx
	jz .ret_suc

	movq 0(%rdi), %r8
	movq 0(%rsi), %r9

	movq %rcx, %rax
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
	andq $3, %rcx
	jz  .ret_suc

.add_tail:
	movsd (%r9), %xmm0
	addsd (%r8), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %rcx
	jnz .add_tail
	jmp .ret_suc

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
	vmovupd (%r8), %ymm0
	vsubpd (%r9), %ymm0, %ymm0
	vmovupd %ymm0, (%r8)
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .sub_vec_loop

	vzeroupper
	andq $3, %rcx
	jz .ret_suc

.sub_tail:
	movsd (%r8), %xmm0
	subsd (%r9), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %rcx
	jnz .sub_tail

.ret_suc:
	xorq %rax, %rax
	ret

.ret_dim_err:
	movq $-1, %rax
	ret

.size _add_mat, . - _add_mat
.size _sub_mat, . - _sub_mat
.section .note.GNU-stack, "", @progbits