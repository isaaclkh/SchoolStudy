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
    its.it_iterval.tv_nsec = 0;

    its.it_value.tv_sec = 5;
    its.it_value.tv_nsec = 0;

    timer_settime(timerID, 0, &its, NULL);
}

int createTimer(timer t *_timerID, int sec, int msec){
    struct sigevent te;
    struct itimerspec its;
    struct sigaction sa;

    //Set up signal handler
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGRTMIN, &sa, NULL) == -1){
        printf("sigaction error\n");
        exit(1);
    }

    //Set and enable alarm
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = SIGRTMIN;
    te.sigev_value.sival_ptr = _timerID;

    timer_create(CLOCK_REALTIME, &te, _timerID);

    its.it_interval.tv_sec = sec;
    its.it_interval.tv_nsec = msec*1000000;
    its.it_value.tv_sec = sec;
    its.it_value.tv_nsec = msec*1000000;

    timer_settime(*_timerID, 0, &its, NULL);

    return 0;
}

int main(){
    struct sigaction act;

    createTimer(&timerID, 3, 0);

    act.sa_handler = keycontrol;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    for(int i = 0; i < 10; i++){
        puts("wait...");
        slee(100);
    }

    return 0;
}