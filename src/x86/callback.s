.global ffcb_call
.type ffcb_call, %function
ffcb_call:
	/*retrieve va_arg pointer*/
	leal 8(%esp), %eax
	pushl %eax

	/*retrieve ffcb_t pointer*/
	movl 4(%esp), %eax
	andb $0xE0, %al
	pushl 28(%eax)
	pushl %eax

	call *24(%eax)
	addl $12, %esp

	/*check returnType*/
	movl (%esp), %eax
	andb $0xE0, %al
	cmpb $0, 15(%eax)
	je .done
	cmpb $1, 15(%eax)
	je .retInt

/*.retFloat:*/
	fldl 16(%eax)
	jmp .done

.retInt:
	movl 16(%eax), %eax

.done:
	ret

.global ffcb_return_int
.type ffcb_return_int, %function
ffcb_return_int:
	movl 4(%esp), %eax
	movb $1, 15(%eax)
	movl 8(%esp), %edx
	movl %edx, 16(%eax)
	ret

.global ffcb_return_pointer
.type ffcb_return_pointer, %function
ffcb_return_pointer:
	movl 4(%esp), %eax
	movb $1, 15(%eax)
	movl 8(%esp), %edx
	movl %edx, 16(%eax)
	ret

.global ffcb_return_float
.type ffcb_return_float, %function
ffcb_return_float:
	movl 4(%esp), %eax
	movb $2, 15(%eax)
	movl 8(%esp), %edx
	movl %edx, 16(%eax)
	movl 12(%esp), %edx
	movl %edx, 20(%eax)
	ret
