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

#ifdef __amd64__
	cb->code[0] = 0x48; //movabs (absolute)ffcb_call, %rax
	cb->code[1] = 0xb8;
	*(void **)(cb->code + 2) = (void *)ffcb_call;
	cb->code[10] = 0xff; //call *%rax
	cb->code[11] = 0xd0;
	cb->code[12] = 0xc3; //ret
#else
#ifdef __i386__
	cb->code[0] = 0xe8; //call ffcb_call(%eip)
	*(int32_t *)(cb->code + 1) = (uint8_t *)ffcb_call - cb->code - 5;
	cb->code[5] = 0xc3; //ret
#else
#error Architecture not supported, this file is only for amd64 and i386
#endif
#endif

	cb->func = func;
	cb->data = arg;

	return cb;
}

void ffcb_delete(ffcb_t *func)
{
	func->data = ffcb_unused;
	ffcb_unused = func;
}
