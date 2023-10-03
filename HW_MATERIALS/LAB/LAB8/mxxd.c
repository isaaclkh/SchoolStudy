#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE * fpInput = NULL;
FILE * fpOutput = NULL;

void btt();
void ttb(char * fileName);

int main(int argc, char *argv[]){

    // Missing Or Wrong Format Of Running The Program
    if(argc < 3){
        fprintf(stderr, "MISSING INPUT : you should provide (option) <input file> <output file>\n");
        return EXIT_FAILURE;
    }

    if(argc > 4){
        fprintf(stderr, "MISSING INPUT : you should provide (option) <input file> <output file>\n");
        return EXIT_FAILURE;
    }


    // open the file differently (open with binary or text file) with the correspoinding options (no option or r option)
    if(strcmp(argv[1], "-r") == 0){ // ttb
        fpInput = fopen(argv[2], "r");
    }
    
    if(argc == 3){ // btt
        fpInput = fopen(argv[1], "rb");
        fpOutput = fopen(argv[2], "w");
    }

    // If the file does not exist or cannot open the file
    if (fpInput == NULL){
        fprintf(stderr, "WRONG INPUT FILE : error opening file\n");
        return EXIT_FAILURE;
    }

    // actual execution
    switch (argc){
        case 3:
            btt();
        break;
        case 4:
            ttb(argv[3]);
            break;
    }


    // file closing after using it
    fclose(fpInput);
    fclose(fpOutput);
}

// binary file to text file
void btt(){
    // buffer which contain buffer of the file
    char * buf = NULL;
    // size of the file
    size_t fileSize;

    // computing file size
    fseek(fpInput, 0, SEEK_END);    // file cursor at the end of the file = the offset is 0 so it will be at the end of the file (return 0 if succeed moving)
    fileSize = ftell(fpInput);      // ftell return the value of the current cursor (meaning file size because the cursor is at the end of the file)
    fseek(fpInput, 0, SEEK_SET);    // reset the cursor of the file to the beginning

    // buffer size allocating with reseting the values (different with malloc)
    buf = (char *) calloc (fileSize+1, sizeof(char));

    // read the file and put it into buffer as much as file size
    fread(buf, sizeof(char), fileSize, fpInput);

    int i = 0, j = 0;                               // loop variables (i = task to convert to binary line by line, j = task to convert as ascii at the right side) i and j are acting like the cursor (current location)
    unsigned char * p1 = (unsigned char *)buf;      // variable used to convert the ascii code as hex
    unsigned char * p2 = (unsigned char *)buf;      // variable used to convert as ascii code if it is possibles
    int lcount = 0;                                 // variable used to count lines
    int bcount = 0;                                 // variable used to count blocks

    // loop from the start until it reaches fileSize
    for (i = 0; i < fileSize; i++){
        if(i % 16 == 0) fprintf(fpOutput, "%07x0: ", lcount);           // writing the index of each line (the index is increasing by 10 as the line) : index format (expressed in length of 7 and hex and 0 comes at the end)
        fprintf(fpOutput, "%02x", (unsigned int)*(p1 + i));             // eight blocks of 4-digit hex followed by two whiespaces (char->int with format of %x meaning convert the char to int and format as hex)
        if(bcount % 2 == 1) fprintf(fpOutput, "  ");                    // put spaces after writing 2 bytes (one block = 4bytes)

        // if the converting of the ascii code as hex is done computing
        if (((i + 1) % 16 == 0) && (i > 0))                             // there is 16 values and i starts from 0 so i+1 mod 16 would result 0 and i should be greater than 0 (the last line would not be 0 because the last line could have less than 16 values)
        {
            for (j = 0; j < 16; j++)                                    // there is 16 of it so loop for 16 times (one by one)
            {
                // isprint returns 1 if it is convertable as ascii code and iscntrl returns 1 if it is convertable like '\n' so meaning 0 is not convertable
                if (isprint(*(p2 + j)) && (iscntrl(*(p2 + j)) == 0))    // meaning if the value could be convert as ascii values and the value is not control sign like '\n' // one question how about the space? isspace == 0 put or not (xxd also converts the space so i did too)
                    fprintf(fpOutput, "%c", *(p2 + j));                 // then write that correspoinding character in side the output file
                else
                    fprintf(fpOutput, ".");                             // if the value is not convertable in ascii value then put dot (.) on the file
            }
            fprintf(fpOutput, "\n");                                    // after finishing all the computation then the line is finish so put line feed in the output file
            p2 = p1 + i + 1;                                            // p2, which is used to convert as asciidoe if it is possible, should move to the next line so p2 will be at the point where p1 + i + 1;
            lcount++;                                                    // counting line increase
        }
        
        bcount++;
    }

    // to complete task of the last line of the file (task of ascii convertion at the right side)
    if ((((i + 1) % 16) <= 15) && ((i + 1) % 16 != 1)){                 // if (i+1) mod 16 is the same or smaller than 15 meaning the last line has less than 16 values and (i+1) mod 16 should not be 1 because it could be 17th value
        for (j = (i + 1) % 16 - 1; j < 16; j++)                         // put spaces (6space = 4digit hex + 2space) for the remaining part  // (i+1 mod 16-1 would be the current cursor(point) so starting from there until less than 16) // i starting from 0 so considering that thing also
        {
            fprintf(fpOutput, "  ");
            if(j % 2 == 1) fprintf(fpOutput, "  ");
        }

        for (j = 0; j < (i + 1) % 16 - 1; j++)                          // for loop from the start until the value exist
        {
            if (isprint(*(p2 + j)) && (iscntrl(*(p2 + j)) == 0))        // meaning if the value could be convert as ascii values and the value is not control sign like '\n'
                fprintf(fpOutput, "%c", *(p2 + j));                     // then write that correspoinding character in side the output file
            else
                fprintf(fpOutput, ".");                                 // if the value is not convertable in ascii value then put dot (.) on the file
        }
        fprintf(fpOutput, "\n");                                        // after finishing all the computation then the line is finish so put line feed in the output file
    }

}

// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// text file to binary file
void ttb(char * fileName){
    // strtok(': ') 이렇게 해서 index를 구분해야함
    // hex -> char
    // temp file에 저장을 하는데 만약에 text로 변환이 되면서 잘못된 것이 있다고하면 즉 뭘까? 모르겠어 hex에서 char로 변환을 할 수 없다면 이게 error인건가?
    // 그러면 error처리
    // 만약 하나씩 다 해보았는데 다 잘 변환이되었다면 rewind해서 file의 처음으로 돌아간뒤 실질적으로 output file에다 적기 시작하면됨
    // value들은 2자리씩 가지고 있음 그러면 2자리씩 받아오면서 char로 변환해야함

    FILE * tempfp;

    char * address = NULL;
    char * rightSide = NULL;
    char * middle = NULL;
    int count = 1;

    char * first = NULL;
    char * second = NULL;

    int number = 0;
    char one;
    int check;

    address = (char *)calloc(10, sizeof(char));
    middle = (char *) calloc (49, sizeof(char)); // 32 + 16 (6*8)
    rightSide = (char *) calloc (17, sizeof(char));

    first = (char *)calloc(3, sizeof(char));
    second = (char *)calloc(3, sizeof(char));

    tempfp = tmpfile();

    while(!feof(fpInput)){
        fscanf(fpInput, "%9c %48c %16c\n", address, middle, rightSide);
        // printf("address : %s, middle : %s, rightside : %s\n", address, middle, rightSide);
        // printf("%s\n", line);

        char * ptr = strtok(middle, "  ");

        while(ptr != NULL){
            memset(first, 0, sizeof(char) * 3);
            memset(second, 0, sizeof(char) * 3);

            // printf("ptr : %s\n", ptr);
            sscanf(ptr, "%2c%2c", first, second);
            if(strcmp(first, "") != 0){
                number = (int)strtol(first, NULL, 16);
                one = (char)number;
                check = (int) one;
                if(check == one) fprintf(tempfp, "%c", number);
                else{
                    fprintf(stderr, "ERROR : HAS A SYNTAX ERROR WHILE CONVERTING\n original : %2x, convert : %2x\n", one, check);
                    fclose(tempfp);
                    return;
                }
            }
            
            if(strcmp(second, "") != 0){
                number = (int)strtol(second, NULL, 16);
                one = (char)number;
                check = (int) one;
                if (check == one) fprintf(tempfp, "%c", number);
                else{
                    fprintf(stderr, "ERROR : HAS A SYNTAX ERROR WHILE CONVERTING\n original : %2x, convert : %2x\n", one, check);
                    fclose(tempfp);
                    return;
                }
            }
            
            ptr = strtok(NULL, "  ");
        }
        
    }

    rewind(fpInput);
    fpOutput = fopen(fileName, "wb");

    while(!feof(fpInput)){
        fscanf(fpInput, "%9c %48c %16c\n", address, middle, rightSide);

        char * ptr = strtok(middle, "  ");

        while(ptr != NULL){
            memset(first, 0, sizeof(char) * 3);
            memset(second, 0, sizeof(char) * 3);

            // printf("ptr : %s\n", ptr);
            sscanf(ptr, "%2c%2c", first, second);
            if(strcmp(first, "") != 0){
                number = (int)strtol(first, NULL, 16);
                one = (char)number;
                fprintf(fpOutput, "%c", number);
            }
            
            if(strcmp(second, "") != 0){
                number = (int)strtol(second, NULL, 16);
                one = (char)number;
                fprintf(fpOutput, "%c", number);
            }
            
            ptr = strtok(NULL, "  ");
        }
        
    }
}