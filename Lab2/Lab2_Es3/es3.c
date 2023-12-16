#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    printf("P1, PID=%d\n", getpid());
    pid=fork();
    if(pid==0){
        P2();
    }
    else{
        P1();
        wait((int *)0);
    }
    printf("P9, PID=%d\n", getpid());
    return 0;
}

void P1(){
    pid_t pid;
    printf("P2, PID=%d\n", getpid());
    pid=fork();
    if(pid==0){
        printf("P5, PID=%d\n", getpid());
        exit(0);
    }
    else{
        printf("P4, PID=%d\n", getpid());
        wait((int *)0);
    }
    printf("P7, PID=%d\n", getpid());
}

void P2(){
    pid_t pid;
    printf("P3, PID=%d\n", getpid());
    pid=fork();
    if(pid==0){
        printf("P6, PID=%d\n", getpid());
        exit(0);
    }
    else{
        wait((int *)0);
    }
    printf("P8, PID=%d\n", getpid());
    exit(0);
}