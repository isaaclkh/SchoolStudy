#include <stdio.h>
#include <string.h>

int main()
{
    int md = 100;
    int ms = 50;
    int *address = &md; // Get the address stored at md
    *address = ms;            // Store the value at ms to the address
    printf("%d %d", md, ms);
    return 0;
}

// READ,       // 0
// WRITE,  // 1
// ASSIGN, // 2
// MOVE,   // 3
// LOAD,   // 4
// STORE,  // 5
// ADD,    // 6
// MINUS,  // 7
// MULT,   // 8
// MOD,    // 9
// EQ,     // 10
// LESS,   // 11
// JUMP,   // 12
// JUMPIF, // 13
// TERM,   // 14
// N_op    // 15