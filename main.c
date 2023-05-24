
#include <stdio.h>
#include "mylib.h"

int main(void){
	int a = 3, b = 5;
	printf("(initial) a=%d, b=%d\n", a, b);
	swap(&a, &b);
	printf("(swqpped) a=%d, b=%d\n", a, b);
	return 0;
}
