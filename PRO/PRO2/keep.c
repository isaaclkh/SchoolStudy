#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv){
    if(argc < 2){
        prerror("Invalid option : you need to enter option\n options will be\ninit, track, versions, untrack, store, restore");
        return EXIT_FAILURE;
    }
}