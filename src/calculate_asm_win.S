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

.check_dims:
	movq 8(%rcx), %r10
	cmpq 8(%rdx), %r10
	jne .check_dims_fail

	movq 16(%rcx), %rax
	cmpq 16(%rdx), %rax
	jne .check_dims_fail

	imulq %rax, %r10
	ret

.check_dims_fail:
	addq $8, %rsp
	jmp .ret_dim_err

_add_mat_w:
	call .check_dims
	testq %r10, %r10
	jz .ret_suc

	movq 0(%rcx), %r8
	movq 0(%rdx), %r9

	movq %r10, %rax
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
	andq $3, %r10
	jz .ret_suc

.add_tail:
	movsd (%r9), %xmm0
	addsd (%r8), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %r10
	jnz .add_tail
	jmp .ret_suc

_sub_mat_w:
	call .check_dims	
	testq %r10, %r10
	jz .ret_suc

	movq 0(%rcx), %r8
	movq 0(%rdx), %r9

	
	movq %r10, %rax
	shlq $2, %rax
	jz .sub_tail

.sub_vec_loop:
	vmovupd (%r8), %ymm0
	vsubpd (%r9), %ymm0, %ymm0
	vmovupd %ymm0, (%r8)
	addq $32, %r8
	addq $32, %r9
	decq %rax
	jnz .add_vec_loop

	vzeroupper
	andq $3, %r10
	jz .ret_suc

.sub_tail:
	movsd (%r8), %xmm0
	subsd (%r9), %xmm0
	movsd %xmm0, (%r8)
	addq $8, %r8
	addq $8, %r9
	decq %r10
	jnz .sub_tail
	jmp .ret_suc

.check_dims_mul:
	movq 16(%rcx), %r10
	movq 8(%rdx), %rax
	cmpq %rax, %r10
	jne .check_dims_fail

	movq 8(%rcx), %rax
	imulq 16(%rdx), %rax
	ret

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
