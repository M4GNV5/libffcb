#ifndef _FFCB_COMMON
#define _FFCB_COMMON

#include <stdbool.h>

typedef struct ffcb ffcb_t;

extern ffcb_t *ffcb_mem;
extern size_t ffcb_unusedIndex;
bool ffcb_init();

#endif
