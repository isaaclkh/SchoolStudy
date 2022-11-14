#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

sigset_t mask;
timer_t timerID;

//timer handler
void timerHandler(){
    printf("time-out\n");
}

void keycontrol(int sig){
    struct itimerspec its;
    
    if(sig == SIGINT) printf("CTRL + C pressed!\n");
    its.it_iterval.tv_sec = 0;
}
