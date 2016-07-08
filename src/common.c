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
	size_t pageSize = getpagesize();
	char tmpfname[] = "/tmp/ffcbXXXXXX";
	int fd = mkstemp (tmpfname);
	if(!fd)
		return false;

	unlink (tmpfname);
	ftruncate (fd, pageSize);

	ffcb_mem = mmap(NULL, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
	ffcb_unusedIndex = 0;

	if(ffcb_mem == NULL)
		return false;
	return true;
}
