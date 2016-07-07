#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../common.h"

typedef struct ffcb
{
	uint8_t code[16];
	void *func;
	void *data;
} ffcb_t;

extern void ffcb_call();

void *ffcb_create(void *func, void *arg)
{
	if(ffcb_execmem == NULL && !ffcb_init())
		return NULL;

	size_t index = ffcb_unusedIndex++;
	ffcb_t *cb = &ffcb_writemem[index];
	ffcb_t *cbExec = &ffcb_execmem[index];

	cb->code[0] = 0xe8; //call
	*(int32_t *)(cb->code + 1) = (uint8_t *)&ffcb_call - cbExec->code - 5;
	cb->code[5] = 0xc3; //ret
	cb->func = func;
	cb->data = arg;

	return cbExec;
}
