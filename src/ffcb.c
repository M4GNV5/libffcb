#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct ffcb
{
	uint8_t code[32 - 2 * sizeof(void *)];
	void *func;
	void *data;
} ffcb_t;

ffcb_t *ffcb_mem = NULL;
ffcb_t *ffcb_unused = NULL;
size_t ffcb_unusedIndex;

extern void ffcb_create_code(uint8_t *code);

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

	ffcb_create_code(cb->code);
	cb->func = func;
	cb->data = arg;

	return cb;
}

void ffcb_delete(ffcb_t *func)
{
	func->data = ffcb_unused;
	ffcb_unused = func;
}
