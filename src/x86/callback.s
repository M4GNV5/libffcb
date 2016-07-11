.global ffcb_call
.type ffcb_call, %function
ffcb_call:
	subl $12, %esp
	movl %esp, %edx

	/*retrieve va_arg pointer*/
	leal 20(%esp), %eax
	pushl %eax

	/*retrieve ffcb_t pointer*/
	movl 16(%esp), %eax
	andb $0xE0, %al
	pushl 28(%eax)

	/*push ffcb_return_t pointer*/
	push %edx

	call *24(%eax)
	addl $12, %esp

	/*check returnType*/
	cmpb $0, (%esp)
	je .done
	cmpb $1, (%esp)
	je .retInt

/*.retFloat:*/
	fldl 4(%esp)
	jmp .done

.retInt:
	movl 4(%esp), %eax

.done:
	addl $12, %esp
	ret

.global ffcb_return_int
.type ffcb_return_int, %function
ffcb_return_int:
	movl 4(%esp), %eax
	movb $1, (%eax)
	movl 8(%esp), %edx
	movl %edx, 4(%eax)
	ret

.global ffcb_return_pointer
.type ffcb_return_pointer, %function
ffcb_return_pointer:
	movl 4(%esp), %eax
	movb $1, (%eax)
	movl 8(%esp), %edx
	movl %edx, 4(%eax)
	ret

.global ffcb_return_float
.type ffcb_return_float, %function
ffcb_return_float:
	movl 4(%esp), %eax
	movb $2, (%eax)
	movl 8(%esp), %edx
	movl %edx, 4(%eax)
	movl 12(%esp), %edx
	movl %edx, 8(%eax)
	ret
