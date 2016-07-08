#include <stdio.h>
#include <stdarg.h>

void *ffcb_create(void *func, void *arg);

void test(int *data, va_list ap)
{
	printf("*data = %d\n", *data);

	int argc = va_arg(ap, int);
	for(int i = 0; i < argc; i++)
		printf("args[%d] = %d\n", i, va_arg(ap, int));
}

typedef void (*callback_t)(int argc, ...);

int main()
{
	int a = 42;
	int b = 666;

	callback_t cb1 = ffcb_create(test, &a);
	callback_t cb2 = ffcb_create(test, &b);

	cb1(3, 7, 8, 666);
	cb2(0);
}
