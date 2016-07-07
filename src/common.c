#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "common.h"

ffcb_t *ffcb_writemem = NULL;
ffcb_t *ffcb_execmem = NULL;
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

	ffcb_writemem = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	ffcb_execmem = mmap(NULL, pageSize, PROT_READ | PROT_EXEC, MAP_SHARED, fd, 0);
	ffcb_unusedIndex = 0;

	if(ffcb_writemem == NULL || ffcb_execmem == NULL)
		return false;
	return true;
}
