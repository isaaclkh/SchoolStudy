#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MAX Value of instruction
#define MAXSIZE 255

// TYPEDEF

// enum of types of operation
typedef enum
{
    READ,   // 0
    WRITE,  // 1
    ASSIGN, // 2
    MOVE,   // 3
    LOAD,   // 4
    STORE,  // 5
    ADD,    // 6
    MINUS,  // 7
    MULT,   // 8
    MOD,    // 9
    EQ,     // 10
    LESS,   // 11
    JUMP,   // 12
    JUMPIF, // 13
    TERM,   // 14
    N_op    // 15 // size of the operation
} op;

// structure of the instruction
typedef struct
{   
    // one operator and maximum 3 of parameter
    op operator; // operation
    char r1[5]; // first parameter
    char r2[5]; // second parameter
    char r3[5]; // third parameter
} instruct;

// union of value : it could be constant number or insruction
typedef union
{
    char num[10]; // constant number
    instruct inst; // intruction
} value;


// Global variables

// memory which stores the entire file in value type
value memory[MAXSIZE]; // memory of the value

// contains correspoinding strings to each of the operation
char *const opTitle[] = {
    "READ",
    "WRITE",
    "ASSIGN",
    "MOVE",
    "LOAD",
    "STORE",
    "ADD",
    "MINUS",
    "MULT",
    "MOD",
    "EQ",
    "LESS",
    "JUMP",
    "JUMPIF",
    "TERM",
};

// contains the 1 where there is value in each line of the file
// this is used in printing values in the file
int storedAddr[255] = {0};

// compare the string of the operation and return the correspoinding operation
op getVal(char * str){
    
    // between the operation size
    for (int i = READ; i < N_op; i++){
        if (strcmp(str, opTitle[i]) == 0) return i; // if the string matches the corresponding operation then return that
    }
    
    return N_op; // if nothing is matched then return the size of ther operation
}

// convert constant number integer to ineger value (putting double quotations into the string)
int strToConstInt(char * str){

    // untile i reaches the length of the string
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '\"' || str[i] == '\n') // if there is double quotation or \n character
            str[i] = ' '; // then just make it as space
    }

    return atoi(str); // return the integer value of the string
}

// trim the string (if there is line feed then just make it as the end of the string)
char * trimString(char * str){
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '\n') str[i] = '\0'; // if there is line feed sign, just make it as the end of the string
    }

    return str; // return the trimmed string
}

//--------------------//

// read the values in the file and store into memory
void readValues(char * fileName){
    
    FILE * fp; // file pointer
    char * line = NULL; // read each line
    size_t len = 0; // intial size of the line
    ssize_t read; // size of the line which is read

    int address=0; // initial value of the address

    char * token; // string token which is splitted in the string

    fp = fopen(fileName, "r"); // open file
    
    // fpopen error
    if (fp == NULL) perror("FILE OPEN ERROR");

    // until there is stil remaining in the file while reading the line of the file one by one
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // trim the string (extract line feed = \n)
        trimString(line);

        // split the line with ": " this character, then the token will have the address
        token = strtok(line, ": ");
        // get the address
        address = atoi(token);

        // set the storedAddr[address] to 1 thant at storedAddr[address] has the value
        storedAddr[address] = 1;

        // if the address is out of range print error
        if (address > 255 || address < 0) fprintf(stderr, "Segmentation error : address is not between 0~255\n");

        // split the line with " " this character, then the token will have the value
        token = strtok(NULL, " ");
        
        // if there is nothing then just do nothing
        if(token == NULL) ;
        
        // else there is something
        else{    
            memory[address].inst.operator = getVal(token); // set the operator to the memory
            if (getVal(token) == N_op) strcpy(memory[address].num, token); // if the value is number then set in the memory num to token
            //printf("[%d] %d\n", address, memory[address].inst.operator);
        }
        
        // for 3 times
        for(int i=0; i<3; i++){
            // split the line with " " this character, then the token will have the parmeter
            token = strtok(NULL, " ");
            // if the parameter doesn't exist, break
            if(token == NULL) break;

            // set the parameter to the correspoinding memory parameter
            if (i == 0) strcpy(memory[address].inst.r1, token);
            if (i == 1) strcpy(memory[address].inst.r2, token);
            if (i == 2) strcpy(memory[address].inst.r3, token);
        }

    }

    fclose(fp); // close file
    if (line) free(line); // free the line
}

// print the value which are stored in memory (addtional function which is not related to TICO)
void printMem(){

    // until the MAXSIZE of the value
    for(int i=0; i<MAXSIZE; i++){
        
        if(storedAddr[i]){ // if there is value in the memory
            printf("[TEST] %d: ", i); // print [TEST] that to indicating printing

            // if there is nothing on the value (empty) just print line feed
            if (memory[i].inst.operator== 0 && atoi(memory[i].inst.r1) == 0 && atoi(memory[i].inst.r2) == 0 && atoi(memory[i].inst.r3) == 0)
                printf("\n");
            
            // else if the operator is in the operator (smaller than N_op and greater or equalt to READ)
            else if(memory[i].inst.operator < N_op && memory[i].inst.operator >= READ){
                if (memory[i].inst.operator== TERM) printf("%s\n", "TERM"); // if ther operator is TERM then just print TERM

                // else prin the value stored in memory
                else printf("%s %s %s %s\n", opTitle[memory[i].inst.operator], memory[i].inst.r1, memory[i].inst.r2, memory[i].inst.r3);
            }
            
            // else (meaning there the constant number only) then print the constant number
            else printf("%s\n", memory[i].num);
        }

    }
}

// convert string to constant number string (put double quotations)
char * strMakeConstNum(char * num){
    char quotation = '\"'; // double quotation
    char * newString = (char *) malloc(sizeof(char) * 5); // new string size of 5 which is the char pointer
    char * temp; // character pointer temp

    newString[0] = quotation; // put first quotation mark
    strcpy(newString+1, num); // copy the number string from the next to the first character (which is double quotation mark)
    strcat(newString, "\""); // put double quotation mark at the end

    //printf("NEWSTRING: %s\n", newString);

    // if there is line feed, extract it and put space
    for(int i=0; i<strlen(newString); i++){
        if(newString[i] == '\n') newString[i] = ' ';
    }

    strcpy(temp, newString);
    free(newString);
    return temp;
}

// convert integer to constant number string (put double quotations) : similar compuation in strMakeConstNum
char * numMakeConstNum(int num){
    char quotation = '\"';
    char * newString = (char *) malloc(sizeof(char) * 5);
    char * temp;

    newString[0] = quotation;
    sprintf(newString+1,"%d", num); // used sprintf to convert integer number to string
    strcat(newString, "\"");

    for(int i=0; i<strlen(newString); i++){
        if(newString[i] == '\n') newString[i] = ' ';
    }
    
    return newString;
}

// interpreting the value stored in memory
void interpret(){
    char temp[5]; // temporary string to store input from user
    int md, ms, mx, my, m, c, result; // parameters

    // loop until the MAXSIZE of the memory(values)
    for (int i = 0; i < MAXSIZE; i++)
    {
        // reseting the temporary string and parameters
        temp[0] = '\0';
        md = 0;
        ms = 0;
        mx = 0;
        my = 0;
        m = 0;
        c = 0;
        result = 0;

        // if the value is empty do nothing
        if (memory[i].inst.operator== 0 && atoi(memory[i].inst.r1) == 0 && atoi(memory[i].inst.r2) == 0 && atoi(memory[i].inst.r3) == 0);

        // if the value is not empty and has the operation which is in the range of the operation
        else if (memory[i].inst.operator<N_op && memory[i].inst.operator>= READ)
        {
            if (memory[i].inst.operator== TERM) return; // if the operation is TERM then terminate

            // if it is not TERM then
            else{
                switch (memory[i].inst.operator) // switch cases for each operation
                {
                    // receive a number from user and store it in memory[m].num
                    case READ:
                        // printf("READ\n");
                        printf("ENTER a number to store in %s : ", memory[i].inst.r1);
                        fgets(temp, 5, stdin);
                        m = atoi(memory[i].inst.r1);
                        strcpy(memory[m].num, strMakeConstNum(temp));
                        break;

                    // put(print) a number at memory[m].num
                    case WRITE:
                        // printf("WRITE\n");
                        m = atoi(memory[i].inst.r1);
                        printf("%d\n", strToConstInt(memory[m].num));
                        break;

                    // put a number "c" to memory[m].num
                    case ASSIGN:
                        // printf("ASSIGN\n");
                        m = atoi(memory[i].inst.r1);
                        strcpy(memory[m].num, memory[i].inst.r2);
                        break;

                    // copy the value memory[ms].num to memory[md].num
                    case MOVE:
                        // printf("MOVE\n");
                        md = atoi(memory[i].inst.r1);
                        ms = atoi(memory[i].inst.r2);
                        strcpy(memory[md].num, memory[ms].num);
                        break;

                    // read an address stored at ms (memory[ms])
                    // and put the value at the address to md
                    // memory[md].num = *memory[ms] ==> memory[md].num = memory[ms].num
                    case LOAD:
                        // printf("LOAD\n");
                        md = atoi(memory[i].inst.r1);
                        ms = atoi(memory[i].inst.r2);
                        strcpy(memory[md].num, memory[ms].num);
                        break;

                    // read an address stored at md (memory[md])
                    // and put the value at [ms] to the address
                    // memory[ms].num = *memory[md] ==> memory[ms].num = memory[md].num
                    case STORE:
                        // printf("STORE\n");
                        md = atoi(memory[i].inst.r1);
                        ms = atoi(memory[i].inst.r2);
                        strcpy(memory[ms].num, memory[md].num);
                        break;

                    // add the values at mx and my, and pu the result to md
                    case ADD:
                        // printf("ADD\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);
                        result = mx + my;
                        strcpy(memory[md].num, numMakeConstNum(result));
                        break;

                    // subtract the value at my from the value at my, and put the result to md
                    case MINUS:
                        // printf("MINUS\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);
                        result = mx - my;
                        strcpy(memory[md].num, numMakeConstNum(result));
                        break;

                    // multiply the value at mx by the value at my and put the result to md
                    case MULT:
                        // printf("MULT\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);
                        result = mx * my;
                        strcpy(memory[md].num, numMakeConstNum(result));
                        break;
                    
                    // put the value at mx modules the value at my to md
                    case MOD:
                        // printf("MOD\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);
                        result = mx % my;
                        strcpy(memory[md].num, numMakeConstNum(result));
                        break;

                    // Put 1 to md if two values at mx and my are the same. Otherwise, put 0 to md
                    case EQ:
                        // printf("EQ\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);
                        if(mx == my) strcpy(memory[md].num, "\"1\"");
                        else strcpy(memory[md].num, "\"0\"");
                        break;

                    // Put 1 to md if the value at mx is less than the value at my. Otherwise, put 0 to md
                    case LESS:
                        // printf("LESS\n");
                        md = atoi(memory[i].inst.r1);
                        mx = strToConstInt(memory[atoi(memory[i].inst.r2)].num);
                        my = strToConstInt(memory[atoi(memory[i].inst.r3)].num);

                        if(mx < my) strcpy(memory[md].num, "\"1\"");
                        else strcpy(memory[md].num, "\"0\"");
                        break;

                    // execute the instruction at m for the next turn
                    // since i is the address, change i
                    case JUMP:
                        // printf("JUMP\n");
                        m = atoi(memory[i].inst.r1);
                        i = m-1; // because after finishing i++ will be done so m minus one
                        break;

                    // execute the instruction at m for the next turn, if the value at c is not zero
                    case JUMPIF:
                        // printf("JUMPIF\n");
                        m = atoi(memory[i].inst.r1);
                        c = atoi(memory[i].inst.r2);
                        if(strToConstInt(memory[c].num) != 0) i = m-1; // because after finishing i++ will be done so m minus one
                        break;
                    
                    default:
                        printf("DEFAULT\n"); // THIS IS ERROR, THIS WILL NEVER COME OUT
                        return;
                        break;
                }
            }
        }

        // else, while interpreting the values, it stopped at constant number : meaning error
        else fprintf(stderr, "WARNING! : CHECK YOUR TEXT (REACHED AT ADDRESS WHICH HAS CONSTANT VALUE)");
    }
}

int main(int argc, char *argv[])
{
    // if there is no given file name then it is error
    if (argc < 2){
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // read the values written in file and store in memory
    readValues(argv[1]);
    
    // you can print the value stored in memory before interpreting
    printMem();

    // interpret the values stored in memory
    interpret();

    // // you can print the value stored in memory after interpreting
    printMem();

    return 0;
}