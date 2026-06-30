/*
 * x86-64 AT&T, Windows
 * Function: _trans_mat(Matrix *mat)
 * Argument: %rcx = Matrix *mat
 */

.section	.text
.globl	_trans_mat_w
#ifndef _WIN32
.type	_trans_mat_w, @function
#endif

.check_dims:
	movq 	8(%rcx), %r10
	cmpq 	16(%rcx), %r10
	jne 	.check_dims_fails

	imulq 	16(%rcx), %r10
	ret

.check_dims_fails:
	movq 	$8, %rsp
	jmp	.ret_dim_err

_trans_mat_w:
	call	.check_dims
	testq 	%r10, %r10
	jz	.ret_suc

.ret_suc:
	xorq 	%rax, %rax
	ret

.ret_dim_err:
	movq 	$-1, %rax
	ret

#ifndef _WIN32
.size	_trans_mat_w, . - _trans_mat_w
.section	.note.GNU-stack, "", @progbits
#endif
