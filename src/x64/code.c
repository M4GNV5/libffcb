#include <stdint.h>

extern void ffcb_call();

void ffcb_create_code(uint8_t *code)
{
	code[0] = 0x48; //movabs (absolute)ffcb_call, %rax
	code[1] = 0xb8;
	*(void **)(code + 2) = (void *)ffcb_call;
	code[10] = 0xff; //call *%rax
	code[11] = 0xd0;
	code[12] = 0xc3; //ret
}
