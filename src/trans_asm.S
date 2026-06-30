/*
 * x86-64 AT&T, Linux
 * Function: _trans_mat(Matrix *mat)
 * Argument: %rdi = Matrix *mat
 */

.section	.text
.globl	_trans_mat
.type	_trans_mat, @function

.check_dims:
	movq 	8(%rdi), %rcx
	cmpq 	16(%rdi), %rcx
	jne 	.check_dims_fail

	imulq 	16(%rdi), %rcx
	ret

.check_dims_fail:
	addq 	$8, %rsp
	jmp 	.ret_dim_err

_trans_mat:
	call	.check_dims
	testq	%rcx, %rcx
	jz 	.ret_suc

.ret_suc:
	xorq	%rax, %rax
	ret

.ret_dim_err:
	movq	$-1, %rax
	ret

.size	_trans_mat, . - _trans_mat
.section	.note.GNU-stack, "", @progbits
