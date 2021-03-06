# libffcb
Library for combining function pointer + data pointer to a single function pointer.
The returned function pointer can be called like any other C function. The called function receives three arguments:
A pointer used for returning values, the data pointer passed to `ffcb_create` and a `va_list`.
You can access all arguments passed to the function using stdarg's `va_arg`.

## Functions
ffcb library functions
```C
void *ffcb_create(void *func, void *arg);
void ffcb_delete(void *func);

void ffcb_return_int(ffcb_return_t ret, intptr_t val);
void ffcb_return_pointer(ffcb_return_t ret, void *val);
void ffcb_return_float(ffcb_return_t ret, double val);
```
Your callback function should have a prototype similar to this:
```C
//ret is for use with ffcb_return_int, ffcb_return_pointer and ffcb_return_float
//arg is the pointer passed to ffcb_create
//ap can be used with stdarg's va_arg for retrieving arguments the caller
//	 passed when calling the function pointer generated by ffcb_create
void myFunction(ffcb_return_t ret, void *arg, va_list ap);
```

## Architectures
Supported:
- x86
- x64

Planned:
- ARM
- MIPS
- ...

## Short example
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/ffcb.h"

void myFunc(ffcb_return_t ret, int *data, va_list ap)
{
	printf("data = %d\n", *data);
	free(data);
}

int main()
{
	//allocate memory used for holding data passed to myFunc
	int *data = malloc(sizeof(int));
	*data = 42;

	//create a combined function pointer
	void *func = ffcb_create(myFunc, data);

	//pass it to atexit
	//this is the important part: note that we do not pass 'data' to atexit in any way
	atexit(func);
}
```

## Long example
```C
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "src/ffcb.h"

//function pointer type
typedef double (*callback_t)(int argc, ...);

//the function we will combine with a data pointer
void myFunc(ffcb_return_t ret, int *data, va_list ap)
{
	//print data
	printf("*data = %d\n", *data);

	if(*data < 0) //called from atexit => no arguments
	{
		//free the malloc'ed memory
		free(data);
		return;
	}

	//print arguments first argument is argc, all following are of type int
	int argc = va_arg(ap, int);
	for(int i = 0; i < argc; i++)
	{
		printf("args[%d] = %d\n", i, va_arg(ap, int));
	}

	//return the value 3.1415
	ffcb_return_float(ret, 3.1415);
}

int main()
{
	//data for the two callbacks
	int a = 42;
	int *b = malloc(sizeof(int));
	*b = -666;

	//combine myFunc with &a into local variable 'func'
	callback_t func = ffcb_create(myFunc, &a);

	//print the return value of calling func
	printf("func returned %g\n", func(4, 31, 12, 13, 17));

	//invalidate the func pointer (similar to free'ing memory)
	ffcb_delete(func);

	//allocate a new callback that we pass to atexit
	void *func2 = ffcb_create(myFunc, b);
	atexit(func2);

	return 0;
}
```
