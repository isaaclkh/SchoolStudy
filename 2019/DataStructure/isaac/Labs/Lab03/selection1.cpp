// C++ for C Coders & Data Structures
// Lecture note by idebtor@gmail.com
//
//	selection.cpp - This brute force version of Selection Sort that takes O(n^2).
/*************************************************************
    Lab03 - Understanding a better coding in C/C++
    - NMN(No magic number)
    - DRY(Don't repeat yourself)
    - malloc(), free()
    - assert()
    - rand()
    - mod operator %
    - #if macro
    - Learn about __a better coding__ after all.
***************************************************************/
#include <stdio.h>

void printList(int *list, int n)

void comparativeSort(int *list, int n) {
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min]) min = j;
		swap(list[i], list[min]); // Swap min found with the 1st data unsorted
	}
}

int main(int argc, char *argv[]) {
	int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8};
	const int N = sizeof(list)/sizeof(list[0]); // 고치는 것을 최소한으로 하면 좋다 만약에 나누는 것이 sizeof(int)라고 하면 나중에 list의 타입을 바꾸면 또 바꿔야한다. 그래서 하는 것이 list[0]으로 하면 결국에는 list의 타입으로 나누는 것이기에 list의 타입을 바꿔도 다시 바꿀 필요가 없는것이다.
    
    //nullptr

    printf("UNSORTED(%d): \n", N);
    
    printList(list, N);
	comparativeSort(list, N);

	printf("SORTED(%d): \n", N);
  
    printList(list, N);

    printf("Happy Coding~~\n");
}

void printList(int *list, int n){
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
        
    printf("\n");
}
