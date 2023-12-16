#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
static void father(pid_t pid);
static void child();
static void signalHandler();
int main(){
    pid_t pid;

    if (signal(SIGUSR1, signalHandler)==SIG_ERR){
        fprintf(stderr, "Signal Handler error\n");
        return 1;
    }
    pid=fork();
    if(pid==0){ //padre
     child();
    }else{ //figlio
     father(pid);
    }
    return 0;
}

static void father(pid_t pid){
    fprintf (stdout, "Father Running: pid=%d, childPid=%d\n",getpid (), pid);
    while(1){
        sleep(2);
        kill(pid, SIGUSR1);
        pause();
        fprintf(stdout, "Father woke up!\n");
    }
    return;
}

static void child(){
    fprintf (stdout, "Child Running: pid=%d, fatherPid=%d\n",getpid (), getppid());
    while(1){
        pause();
        fprintf(stdout, "Child woke up!\n");
        sleep(2);
        kill(getppid(), SIGUSR1);
    }
    return;
}

static void signalHandler(){
    return;
}
