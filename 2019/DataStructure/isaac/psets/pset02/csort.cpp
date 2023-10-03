/*
 On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
 Signed: ___임건호___ Student Number: ___21800612___
 */

// csort.cpp – Reference: Fundamentals of Data Structures by Horowitz, Sahni
#include <iostream>
//#include <stdlib.h>
//#include <math.h>
//#define MAX_SIZE 100
#define SWAP(x, y, t)  ((t) = (x), (x) = (y), (y) = (t))
using namespace std;

void selectionSort(int[], int); //그냥 sort라는 이름 말고 selectionSort 와 같은 이름으로 바꾸기

int main(int argc, char *argv[]) { // main function 에는 (exit_success나 exit_failure)를 return
    int i, n;
    //int list[MAX_SIZE];
    int *list;
    //MAX_SIZE 사용하지 않기 위해서는 * 포인터로 만들고(또는 그냥 array) new 해주어야한다. (+delete or delete[])
    
    if(argc == 2) {
        n = strtol(argv[1], nullptr, 10);
    }
    
    else {
            cout << "Enter the number of samples: ";
            cin >> n;
    }
    
    while(1){
            
        if (n > 1 && n < 100) break;
            
        else if(n == 0) {
            cout << "The sample number should be greater than 1 and less than 100\n(0 is not allowed)" << endl;
            exit(EXIT_FAILURE);
        }
            
        cout << "Improper value of number of samples\n";
        cout << "(Enter the number of samples more than 1 and less than 100) \n\n";
        cout << "Retry : " ;
        cin >> n;
        
        //만약에 n이 0일 때만 exit 나머지는 반복해서 물음 맞을 때까지 (while문 사용)
        //error 메세지에서는 뭐가 잘못 되었는지 무엇이 좋은 value인지 출력
    }
    
    
    list = new int(n);
    
    cout << "\nUnSorted array:\n";
    
    for (i = 0; i < n; i++) {
        list[i] = rand() % 1000;
        cout << list[i] << "  " ;
    }
    
    selectionSort(list, n);
    
    cout << "\n\nSorted array:\n";
    
    for (i = 0; i < n; i++) {
        cout <<  list[i] << "  ";
    }
    
    cout << "\n";
    
    delete (list);
    
    exit(EXIT_SUCCESS);
}

void selectionSort(int list[], int n) { // 8번째 줄 처럼 함수 이름 바꾸기
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
