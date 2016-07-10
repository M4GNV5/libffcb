#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct ffcb
{
	uint8_t code[16];
	void *func;
	void *data;
} ffcb_t;

ffcb_t *ffcb_mem = NULL;
ffcb_t *ffcb_unused = NULL;
size_t ffcb_unusedIndex;

extern void ffcb_call();

void *ffcb_create(void *func, void *arg)
{
	if(ffcb_mem == NULL)
	{
		ffcb_mem = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if(ffcb_mem == NULL) //mmap failed
			return NULL;

		ffcb_unusedIndex = 0;
	}

	ffcb_t *cb;
	if(ffcb_unused == NULL)
	{
		cb = &ffcb_mem[ffcb_unusedIndex++];
	}
	else
	{
		cb = ffcb_unused;
		ffcb_unused = ffcb_unused->data;
	}

	cb->code[0] = 0xe8; //call
	*(int32_t *)(cb->code + 1) = (uint8_t *)&ffcb_call - cb->code - 5;
	cb->code[5] = 0xc3; //ret
	cb->func = func;
	cb->data = arg;

	return cb;
}

void ffcb_delete(ffcb_t *func)
{
	func->data = ffcb_unused;
	ffcb_unused = func;
}
