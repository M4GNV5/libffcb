#ifndef _FFCB_COMMON
#define _FFCB_COMMON

#include <stdbool.h>

typedef struct ffcb ffcb_t;

extern ffcb_t *ffcb_writemem;
extern ffcb_t *ffcb_execmem;
extern size_t ffcb_unusedIndex;
bool ffcb_init();

#endif
