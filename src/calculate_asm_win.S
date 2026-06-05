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

_add_mat_w:
_sub_mat_w:
_mul_mat_w:
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
