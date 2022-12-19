// Data Structure
// Lim Keonho 21800612
//
// Lab 2:
//  - Write a C++ code such that it prints Hello World! twice, one per line.
//  - Name the file hello2.cpp.
//  - Use an escape character \n and endl manipulator or function for a new line.
//  - Build an executable and run it.
//
// Lab 3:
//  - Duplicate `hello2.cpp` and name it `hello3.cpp`
//  - Simplify the code using `using namespace std;`
//  - Build an executable and run it.
//
// Lab 4:
//  - Duplicate `hello3.cpp` and name it `hello4.cpp`
//  - Change the main function as shown below:
//    ```
//    int main(int argc, char *argv[])
//    ```
//  - Write the code such that it prints the values of `argc` and `*argv[]`
//    just like __hello4x__ provided for you as an example.
//  - Refer to the following sample run:
//    ```
//    $ ./hello4x
//    argv[0] = C:\GitHub\nowicx\labs\lab01\hello4x.exe
//    Hello World!
//
//    $ ./hello4x john paul david
//    argv[0] = C:\GitHub\nowicx\labs\lab01\hello4x.exe
//    Hello john
//    Hello paul
//    Hello david
//    ```

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {

    if(argc>1){
      cout << "argv[0] = C:\\GitHub\\nowicx\\labs\\lab01\\hello4x.exe" << endl;

      for(int n=1; n<argc; n++)
        cout << "Hello " << argv[n] << endl;
    }


    else {
      cout << "argv[0] = C:\\GitHub\\nowicx\\labs\\lab01\\hello4x.exe" << endl;
      cout << "Hello World!" << endl;
    }
}
