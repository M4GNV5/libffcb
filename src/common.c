#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "common.h"

ffcb_t *ffcb_mem = NULL;
size_t ffcb_unusedIndex;

bool ffcb_init()
{
	ffcb_mem = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	ffcb_unusedIndex = 0;

	if(ffcb_mem == NULL)
		return false;
	return true;
}
