// csort.cpp – Reference: Fundamentals of Data Structures by Horowitz, Sahni
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100
#define SWAP(x, y, t)  ((t) = (x), (x) = (y), (y) = (t))

void sort(int[], int);
int main(int argc, char *argv[]) {
    int i, n;
    int list[MAX_SIZE];
    printf("Enter the number of samples: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX_SIZE) {
        printf("Improper value of n");
        exit(EXIT_FAILURE);
    }
    printf("\nUnSorted array:\n");
    for (i = 0; i < n; i++) {
        list[i] = rand() % 1000;
        printf("%d  ", list[i]);
    }
    sort(list, n);
    printf("\nSorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d  ", list[i]);
    }
    printf("\n");
}
void sort(int list[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[min])
                min = j;
        temp = list[i];
        list[i] = list[min];
        list[min] = temp;
    }
}
