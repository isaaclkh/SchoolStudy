#include <iostream>
using namespace std;

void print_strs(int n, char *strs[]){

    switch (n) {
        case 0: case 1: case 2:
            cout << "argv[0] = " << strs[0] << endl;
            cout << "Hello World!" << endl;
            break;
            
        default:
            cout << "argv[0] = " << strs[0] << endl;
            for(int i=2; i<n; i++){
               cout << strs[i] << endl;
            }
            break;
    }
    
}
