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
// Lab 5:
//  - Duplicate `hello4.cpp` and name it `hello5.cpp`
//  - Define the following function below `main()` and declare the function prototype above the `main()`.
//   ```
// It prints two dimensional array of characters or an array of strings.
// Each string is terminated by a \0 and n is the number of strings.
// void print_strs(int n, char *strs[]) {
//     your code here
// }
//  ```
//  - Modify the code such that it uses `print_strs()` and works like `hello4x`.
//

#include <iostream>
using namespace std;

void print_strs(int n, char *strs[]);

int main(int argc, char *argv[]) {

  print_strs(argc, argv);

}

void print_strs(int n, char *strs[]){

  if(n>1){
    cout << "argv[0] = C:\\GitHub\\nowicx\\labs\\lab01\\hello4x.exe" << endl;

    for(int i=1; i<n; i++)
      cout << "Hello " << strs[i] << endl;
  }


  else {
    cout << "argv[0] = C:\\GitHub\\nowicx\\labs\\lab01\\hello4x.exe" << endl;
    cout << "Hello World!" << endl;
  }

}
