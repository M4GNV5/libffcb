#include <stdint.h>

extern void ffcb_call();

void ffcb_create_code(uint8_t *code)
{
	code[0] = 0xe8; //call ffcb_call(%eip)
	*(int32_t *)(code + 1) = (uint8_t *)ffcb_call - code - 5;
	code[5] = 0xc3; //ret
}
