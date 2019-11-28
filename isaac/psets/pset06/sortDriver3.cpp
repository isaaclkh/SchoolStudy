/*
 On my honour, I pledge that I have neither received nor provided improper assistance
 in the completion of this assignment.
 Signed:  임건호  Section:  01  Student Number:  21800612
 
* Lecture Note by idebtor@gmail.com
*
* This program is written to run the sort algorithms.
* It takes the number of data samples to sort from the user.
* Then, the int array is created and filled with random numbers.
* User may selection one of sort functions to be used. Then
* execution time and its output is displayed.
*
* History:
* 02/10/19:		Created in C++
*
* Before Compilation, you must have some files (static library and
* include file) ready as shown below:
*   include/nowic.h
*		include/sort.h
*		lib/libnowic.a        (nowic.lib for Visual Studio)
* 	lib/sort.a            (sort.lib for Visual Studio)
* Compilation:
*	g++ selection.cpp insertion.cpp quicksort.cpp bubble.cpp
*       sortDriver.cpp -I../include -L../lib -lnowic -lsort -o sort
*/

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include "nowic.h"
using namespace std;

void printList(int *list, int n, int max_print, int per_line);
void randomize(int list[], int size);
void profiling(void (*sortFunc)(int*, int), int* list, int n, bool random=true);
void bubbleSort(int *list, int n);
void insertionSort(int *list, int n);
void quickSort(int *list, int n);
void selectionSort(int *list, int n);

// sortDriver to test sort functions or algorithms.
int main(int argc, char *argv[]) {
	int N = 0;						// default sample size
	int keyin;
	int *list = nullptr;				// input and output buffer
	int max_print = 10;				// default max_print(=front_part+last_part)
	int per_line = max_print / 2;	// default samples per line to print
	clock_t start;
	char randomized = 'N';
	char option_char;
	char option_str[512];
	char algorithm_list[4][20] = {"Bubble", "Insertion", "Quicksort", "Selection"};
	enum algorithm_enum { BUBBLE, INSERTION, QUICKSORT, SELECTION };
	int  algorithm_chosen = SELECTION;  // default algorithm chosen
    const int STARTING_SAMPLES = 500;
    void (*fp[]) (int *, int) = {bubbleSort, insertionSort, quickSort, selectionSort};
    int size = N;
    int* copyList = new(nothrow) int[N];
    int j = N - 1;
	DPRINT(cout << ">main...N=" << N << endl;)

	// Use setvbuf() to prevent the output from buffered on console.
	setvbuf(stdout, NULL, _IONBF, 0);

	do {
		sprintf(option_str, "[sort=%s N=%d randomized=%c max_print=%d per_line=%d]",
			algorithm_list[algorithm_chosen], N, randomized, max_print, per_line);
		cout << "\n\tOPTIONS: " << option_str << "\n"
			"\tn - number of samples size and initialize\n"
			"\tr - randomize(shuffle) samples\n"
			"\ta - algorithm to run\n"
			"\ts - sort()\n"
			"\tm - max samples to display at front or rear\n"
			"\td - max samples to display per line\n";

		option_char = GetChar("\tCommand(q to quit): ");
		DPRINT(cout << "option_char = " << option_char << endl;);

		switch (option_char) {
        
        case 'a': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			switch (GetChar("\tEnter b for bubble, i for insertion, s for selection, q for quick sort: ")) {
			case 'b': algorithm_chosen = BUBBLE; 		break;
			case 'i': algorithm_chosen = INSERTION; 	break;
			case 'q': algorithm_chosen = QUICKSORT; 	break;
			case 's': algorithm_chosen = SELECTION; 	break;
			default: { cout << "\tNo such an algorithm available. Try it again.\n"; break; } }

			//////////////
			break;

		case 'n': DPRINT(cout << "case = " << option_char;);
			keyin = GetInt("\tEnter input sample size: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}

			// set N with the new keyin value
			// before allocating the new list, free the old list if not nullptr
			// allocate memory for new data samples
			// Fill the list with numbers from 0 to n - 1.
			// your code here
			N = keyin;
			if (list != nullptr) delete[] list;
			list = new (nothrow) int[N];
			assert(list != nullptr);
			for (int i = 0; i < N; i++) list[i] = i;

			printList(list, N, max_print, per_line);
			///////////////////////
			break;

		case 'r': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 1) {
				cout << "\tSet sample size first or larger\n";
				break;
			}
			randomize(list, N);
			randomized = 'Y';

			printList(list, N, max_print, per_line);
			break;

		case 'v': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 0) {
				cout << "\tSet sample size first\n";
				break;
			}
            
            copy_n(list, N, copyList);
            fp[algorithm_chosen](copyList, N);
                
            for(int i=0; i<N; i++){
                swap(copyList[i], copyList[size-1]);
                size--;
            }
            
			//cout << "your code here" << endl;

			randomized = 'N';
			printList(copyList, N, max_print, per_line);
            delete[] copyList;
			break;
                
		case 'p':
                if(N <= STARTING_SAMPLES){
                    cout << "\tSet sample size first or change the sample size larger than 500 to profile" << endl;
                    break;
                }

                cout << "\n\tinsertionSort(): already sorted - best case." << endl;
                profiling(fp[algorithm_chosen], list, N, false);

                cout << "\n\tinsertionSort(): randomized - average case." << endl;
                profiling(fp[algorithm_chosen], list, N);

                cout << "\n\tinsertionSort(): sorted reversed - worst case." << endl;
                
                
                for (int i = 0; i < N; i++) list[i] = j--;
                profiling(fp[algorithm_chosen], list, N, false);

			break;
                
		case 's': DPRINT(cout << "case = " << option_char << endl;);
			if (N <= 0) {
				cout << "\tSet sample size first\n";
				break;
			}
			cout << "\tThe clock ticks and " << algorithm_list[algorithm_chosen] << " begins...\n";
			start = clock();
            
            fp[algorithm_chosen](list, N);
			//cout << "your one-line code here: use a function pointer" << endl;
			printList(list, N, max_print, per_line);
			randomized = 'N';
			//////////////////

			cout << "\tDuration: " << (clock() - start)/(double)CLOCKS_PER_SEC << " seconds\n";
			break;

		case 'm': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			keyin = GetInt("\tEnter max sample size to display: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}
			max_print = keyin;
			printList(list, N, max_print, per_line);

			////////////////
			break;
		case 'd': DPRINT(cout << "case = " << option_char << endl;);
			// your code here
			keyin = GetInt("\tEnter max sample per line to display: ");
			if (keyin < 1) {
				cout << "\tExpecting a number larger than 0";
				break;
			}
			per_line = keyin;
			printList(list, N, max_print, per_line);

			////////////////
			break;
                
		default:
			break;
		}
	} while (option_char != 'q');

	if (list != nullptr) delete[] list;
	// system("pause");
	DPRINT(cout << ">main" << endl;)
	return EXIT_SUCCESS;
}
