/**
* Author:		Youngsup Kim
* Description:	This program is written to run and test some recursion algorithms.
*
* On my honour, I pledge that I have neither received nor provided improper
* assistance in the completion of this assignment. Signed: ____YOUR NAME______
*
* To build this program:
*  g++ recursionDriver.cpp recursion.cpp binsearch.cpp quicksort.cpp
*      -I../include -L../lib -lnowic -o recursion
*
* History:
* 2018/02/10	Created
* 2019/02/02	C++ Conversion
*/

/*On my honour, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
Signed: __임건호__ Section: __01__ Student Number: ___21800612___*/

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#include <iostream>
#include <cassert>
using namespace std;

#include "nowic.h"

long long factorial(int N);
long long fibonacci(int N);
int gcd(int a, int b);
int bunnyEars(int a);
int funnyEars(int a);
int triangle(int a);
int sumDigits(int n);
int count8(int n);
long long powerN(int base, int n);
void quickSort(int *lsit, int N);
int binary_search(int *list, int key, int size);

int main(int argc, char *argv[]) {
	int option;
	int N, K, count;

	// Use setvbuf() to prevent the output from buffered on console.
	setvbuf(stdout, NULL, _IONBF, 0);

	while(1) {
		cout << "\n\tRecursive Algorithms:\n"
			"\t1. Factorial\n"
			"\t2. GCD(Great Common Divisor)\n"
			"\t3. Fibonacci\n"
			"\t4. Bunny Ears\n"
			"\t5. Funny Ears\n"
			"\t6. Triangle\n"
			"\t7. Sum of digits\n"
			"\t8. Count 8\n"
			"\t9. Power N\n"
			"\t10. Recursive Binary Search\n";

		switch (option = GetInt("\tCommand(0 to quit): ")) {
		case 0: 
			cout << "Happy Coding~~\n";
			exit(EXIT_SUCCESS);

		case 1:
			cout << "\tFactorial Examples:\n";
			cout << "\tfactorial(1) = 1\n";
			cout << "\tfactorial(2) = 2\n";
			cout << "\tfactorial(3) = 6\n";
			cout << "\tfactorial(8) = 40320\n";
			cout << "\tfactorial(12) = 479001600\n";

			while (1) {
				N = GetInt("\tEnter a number to compute N factorial(0 to quit): ");
				if (N <= 0) break;
				cout << "\tfactorial(" << N << ") = " << factorial(N) << endl;
			}
			break;
		case 2:
			cout << "\tGCD Examples:\n";
			cout << "\tgcd(27, 9) = 9\n";
			cout << "\tgcd(111, 259) = 37\n";

			while (1) {
				int x = GetInt("\tEnter 1st number to compute GCD(0 to quit): ");
				if (x == 0) break;
				int y = GetInt("\tEnter 2nd number to compute GCD(0 to quit): ");
				if (y == 0) break;
				cout << "\tgcd(" << x << ", " << y << ") = " << gcd(x, y) << endl;
			}
			break;

		case 3:
			cout << "\tFibonacci Examples:\n";
			cout << "\tfibonacci(0) = 0\n";
			cout << "\tfibonacci(1) = 1\n";
			cout << "\tfibonacci(2) = 1\n";
			cout << "\tfibonacci(3) = 2\n";
			cout << "\tfibonacci(4) = 3\n";
			cout << "\tfibonacci(5) = 5\n";
			cout << "\tfibonacci(6) = 8\n";
			while (1) {
				N = GetInt("\tEnter a number to compute N fibonacci(0 to quit): ");
				if (N <= 0) break;
				cout << "\tfibonacci(" << N << ") = " << fibonacci(N) << endl;
			}
			break;
		case 4:
			cout << "\tbunnyEars(0) = 0\n";
			cout << "\tbunnyEars(1) = 2\n";
			cout << "\tbunnyEars(2) = 4\n";
			cout << "\tbunnyEars(3) = 6\n";
			cout << "\tbunnyEars(234) = 468\n";
			while (1) {
				N = GetInt("\tEnter a number of Bunnies(0 to quit): ");
				if (N <= 0) break;
				cout << "\tbunnyEars(" << N << ") = " << bunnyEars(N) << endl;
			}
			break;
		case 5:
            cout << "\tfunnyEars(0) = 0\n";
            cout << "\tfunnyEars(1) = 2\n";
            cout << "\tfunnyEars(2) = 5\n";
            cout << "\tfunnyEars(4) = 10\n";
            cout << "\tfunnyEars(9) = 22\n";
            while (1) {
                N = GetInt("\tEnter a number of Funnies(0 to quit): ");
                if (N <= 0) break;
                cout << "\tfunnyEars(" << N << ") = " << funnyEars(N) << endl;
            }
			break;
		case 6:
            cout << "\ttriangle(0) = 0\n";
            cout << "\ttriangle(1) = 1\n";
            cout << "\ttriangle(2) = 3\n";
            cout << "\ttrinalge(3) = 6\n";
            cout << "\ttriangle(4) = 10\n";
            cout << "\tfunnyEars(7) = 28\n";
            while (1) {
                N = GetInt("\tEnter a row number for Triangle(0 to quit): ");
                if (N <= 0) break;
                cout << "\ttriangle(" << N << ") = " << triangle(N) << endl;
            }
            break;
		case 7:
			cout << "\tsumDigits(126) = 9\n";
            cout << "\tsumDigits(12) = 3\n";
            cout << "\tsumDigits(1) = 1\n";
            cout << "\tsumDigits(10110) = 3\n";
            cout << "\tsumDigits(235) = 10\n";
            while (1) {
                N = GetInt("\tEnter a number to sum digits(0 to quit): ");
                if (N <= 0) break;
                cout << "\ttriangle(" << N << ") = " << sumDigits(N) << endl;
            }
            break;
		case 8:
			cout << "\tcount8(818) = 2\n";
            cout << "\tcount8(8) = 1\n";
            cout << "\tcount8(123) = 0\n";
            cout << "\tcount8(881238) = 3\n";
            cout << "\tcount8(48581) = 2\n";
            cout << "\tcount8(888586198) = 5\n";
            cout << "\tcount8(99899) = 1\n";
            while (1) {
                N = GetInt("\tEnter a number to count 8(0 to quit): ");
                if (N <= 0) break;
                cout << "\tcount8(" << N << ") = " << count8(N) << endl;
            }
			break;
		case 9:
			cout << "\tpowerN(2, 5) = 32\n";
            cout << "\tpowerN(3, 1) = 3\n";
            cout << "\tpowerN(3, 2) = 9\n";
            cout << "\tpowerN(3, 3) = 27\n";
            cout << "\tpowerN(10, 2) = 100\n";
            cout << "\tpowerN(10, 3) = 1000\n";
            while (1) {
                N = GetInt("\tEnter a base number(0 to quit): ");
                if (N <= 0) break;
                K = GetInt("\tEnter a power number(0 to quit): ");
                if (K <= 0) break;
                cout << "\tpowerN(" << N << ") = " << powerN(N, K) << endl;
            }
            break;

		case 10:   
			cout << "\tRecursive Binary Search\n ";
			while (1) {
				N = GetInt("\tEnter a list size to generate(0 to quit) : ");
				if (N <= 0) break;

				int *list = new (nothrow) int[N];
				assert(list != NULL);

				for (int i = 0; i < N; i++)
					list[i] = rand() % N;

				quickSort(list, N);
                cout << "\t";
				for (int i = 0; i < N; i++)
					cout << list[i] << " ";
				cout << endl;

				int key = GetInt("\tEnter a number to search: ");
				int index = binary_search(list, key, N);

                if(key == list[index])
                    cout << "\t" <<key << " is @[" << index << "]" << endl;
                
                else{
                    count = 0;
                    if(index==-1){
                        for(int i=0; i < N; i++){
                            if(key>list[i]) count++;
                        }
                    cout << "\t" << key << " is not @[" << count << "]" << endl;
                    }
                }
				/*cout << "index=" << index << endl;
				cout << "your code here to replace the line above.\n";*/

				delete[] list;
			}
		default:
			break;
		}
	};   

	cout << "\n\tHappy Coding~~\n";
	return EXIT_SUCCESS;
}


/*int count(int n){
    int n=0;
    
    if(n%10==8){
        n++;
        return n + count(n/10);
    }
    
    if(n/10 == 0){
        if(n == 8) return 1;
        else return 0;
    }
    
    
}*/
