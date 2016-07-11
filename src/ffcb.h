#ifndef _FFCB_H
#define _FFCB_H

#include <stdint.h>

typedef void ffcb_return_t;

void *ffcb_create(void *func, void *arg);
void ffcb_delete(void *func);

void ffcb_return_int(ffcb_return_t *func, intptr_t val);
void ffcb_return_pointer(ffcb_return_t *func, void *val);
void ffcb_return_float(ffcb_return_t *func, double value);

#endif
