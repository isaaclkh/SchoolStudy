#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
    if (sig == SIGALRM) puts("Time out!");
    alarm(10);
}

void keycontrol(int sig){
    if (sig == SIGINT) puts("CTRL + C pressed");
}

int main(int argc, char *argv[]){
    int i;
    struct sigaction act;

    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    act.sa_handler = keycontrol;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    for(i=0; i<3; i++){
        puts("wait...");
        sleep(100);
    }
}
