.global ffcb_call
.type ffcb_call, %function
ffcb_call:
	pushq   %rbp
	movq    %rsp, %rbp		/*allow backtracing*/
	/*176 register buffer + 24 va_list*/
	subq $200, %rsp

	movq %rdi, (%rsp)
	movq %rsi, 8(%rsp)
	movq %rdx, 16(%rsp)
	movq %rcx, 24(%rsp)
	movq %r8, 32(%rsp)
	movq %r9, 40(%rsp)

	movaps %xmm0, 48(%rsp)
	movaps %xmm1, 64(%rsp)
	movaps %xmm2, 80(%rsp)
	movaps %xmm3, 96(%rsp)
	movaps %xmm4, 112(%rsp)
	movaps %xmm5, 128(%rsp)
	movaps %xmm6, 144(%rsp)
	movaps %xmm7, 160(%rsp)

	/* Create va_arg struct (see http://www.x86-64.org/documentation/abi.pdf) */
	movl $0, 176(%rsp)		/*unsigned int gp_offset;*/
	movl $48, 180(%rsp)		/*unsigned int fp_offset;*/
	leaq 224(%rsp), %rax
	movq %rax, 184(%rsp)	/*void *overflow_area;*/
	movq %rsp, 192(%rsp)	/*void *reg_area;*/

	/*retrieve ffcb_t pointer*/
	movq 208(%rsp), %rax
	andb $0xE0, %al

	movq %rax, %rdi
	movq 24(%rax), %rsi
	leaq 176(%rsp), %rdx
	call *16(%rax)

	/*check returnType*/
	movq 208(%rsp), %rax
	andb $0xE0, %al
	cmpb $0, 7(%rax)
	je .done
	cmpb $1, 7(%rax)
	je .retInt

/*.retFloat:*/
	movsd 8(%rax), %xmm0
	jmp .done

.retInt:
	movq 8(%rax), %rax

.done:
	leave
	ret

.global ffcb_return_int
.type ffcb_return_int, %function
ffcb_return_int:
	movb $1, 7(%rdi)
	movq %rsi, 8(%rdi)
	ret

.global ffcb_return_pointer
.type ffcb_return_pointer, %function
ffcb_return_pointer:
	movb $1, 7(%rdi)
	movq %rsi, 8(%rdi)
	ret

.global ffcb_return_float
.type ffcb_return_float, %function
ffcb_return_float:
	movb $2, 7(%rdi)
	movsd %xmm0, 8(%rdi)
	ret
