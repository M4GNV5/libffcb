.global ffcb_call
ffcb_call:
	/*retrieve va_arg pointer*/
	leal 8(%esp), %eax
	pushl %eax

	/*retrieve ffcb_t pointer*/
	movl 4(%esp), %eax
	andb $0xE0, %al
	addl $24, %eax

	pushl 4(%eax)
	call *(%eax)
