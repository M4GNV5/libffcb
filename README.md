#libffcb
Library for combining function pointer + data pointer to a single function pointer.
The returned function pointer can be called like any other C function and receives two arguments:
the data pointer passed to `ffcb_create` and a `va_list`.
You can access all arguments passed to the function using stdarg's `va_arg`.

##Architectures
Supported:
- x86
- x64

Planned:
- ARM
- MIPS
- ...

##Example code
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ffcb.h"

typedef void (*callback_t)(int argc, ...);

void myFunc(int *data, va_list ap)
{
	//print data
	printf("*data = %d\n", *data);

	if(*data < 0) //called from atexit => no arguments
	{
		free(data);
		return;
	}

	//print arguments
	int argc = va_arg(ap, int);
	for(int i = 0; i < argc; i++)
	{
		printf("args[%d] = %d\n", i, va_arg(ap, int));
	}
}

int main()
{
	int a = 42;
	int *b = malloc(sizeof(int));
	*b = -666;

	callback_t func = ffcb_create(myFunc, &a);
	func(4, 31, 12, 13, 17);

	void *func2 = ffcb_create(myFunc, b);
	atexit(func2);
}
```
