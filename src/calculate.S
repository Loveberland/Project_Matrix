.section .text
.globl _add_mat
.type _add_mat, @function
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
_add_mat:
