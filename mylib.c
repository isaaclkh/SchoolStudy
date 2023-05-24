
#include "mylib.h"

void swap(int * a, int * b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int add(int a, int b){
	return a+b;
}

int subtract(int a, int b){
	return a-b;
}

int mult(int a, int b){
	return a*b;
}

int div(int a, int b){
	return a/b;
}
