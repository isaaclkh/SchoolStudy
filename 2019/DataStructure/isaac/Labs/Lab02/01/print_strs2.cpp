#include <iostream>
#include <vector>
using namespace std;

void print_strs(int n, char *strs[]){

    cout << "Using char arrays\n";
    
    for(int i=0; i<n; i++){
        cout << strs[i] << endl;
    }
    
    /*switch (n) {
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
    }*/
    
}

void print_strs(vector<string> v){
    
    cout << "Print argv using print_strs()" << endl;
    
    for(vector<string>::size_type i = 0; i<v.size(); ++i){
        cout << v[i] << endl;
    }
}

