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

_trans_mat_w:

#ifndef _WIN32
.size	_trans_mat_w, . - _trans_mat_w
.section	.note.GNU-stack, "", @progbits
#endif
