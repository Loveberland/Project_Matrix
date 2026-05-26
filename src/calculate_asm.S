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
	movq 8(%rdi), %rax
	cmpq 8(%rsi), %rax
	jne .Ldim_error

	movq 16(%rdi), %rax
	cmpq 16(%rsi), %rax
	jne .Ldim_error

	movq 8(%rdi), %rcx
	imulq 16(%rdi), %rcx

	testq %rcx, %rcx
	jz .Lsuccess

	movq 0(%rdi), %r8
	movq 0(%rsi), %r9

	xorq %r11, %r11

.Lloop:
	cmpq %rcx, %r11
	jge .Lsuccess

	movsd (%r9, %r11, 8), %xmm0
	movsd (%r8, %r11, 8), %xmm1
	addsd %xmm0, %xmm1
	movsd %xmm1, (%r8, %r11, 8)
	incq %r11 # i++
	jmp .Lloop

.Lsuccess:
	xorq %rax, %rax
	ret

.Ldim_error:
	movq $-1, %rax
	ret

.size _add_mat, . - _add_mat
.section .note.GNU-stack, "", @progbits
