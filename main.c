#include <stdio.h>
#include <stdarg.h>

void *ffcb_create(void *func, void *arg);

void test(int *data, va_list ap)
{
	printf("*data = %d\n", *data);
}

int main()
{
	int a = 42;
	int b = 666;

	void (*cb1)() = ffcb_create(test, &a);
	void (*cb2)() = ffcb_create(test, &b);

	cb1();
	cb2();
}
