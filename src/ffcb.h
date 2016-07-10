#ifndef _FFCB_H
#define _FFCB_H

#include <stdint.h>
#include <stdarg.h>

void *ffcb_create(void *func, void *arg);
void ffcb_delete(void *func);

void ffcb_return_int(void *func, intptr_t val);
void ffcb_return_pointer(void *func, void *val);
void ffcb_return_float(void *func, double value);

#endif
