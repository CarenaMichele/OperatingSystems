#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    pid_t pid1;
    pid_t pid2;
    int n=atoi(argv[1]);
    int t=atoi(argv[2]);
    int i, counter=0;
    
    fprintf(stdout, "PID=%d; PPID=%d, counter=%d\n", getpid(), getppid(),counter);

    for(i=0;i<n;i++){
        pid1 =fork();
        if(pid1==0){
            counter++;
            fprintf(stdout, "PID=%d; PPID=%d; counter=%d\n", getpid(), getppid(), counter);
        }
        else{
            pid2=fork();
            if(pid2==0){
                counter++;
                fprintf(stdout, "PID=%d; PPID=%d; counter=%d\n", getpid(), getppid(), counter);
            }
            else{
                fprintf(stdout, "PID=%d; PPID=%d; counter=%d\n", getpid(), getppid(), counter);
                exit(0);
            }

        }
    }
    fprintf(stdout, "PID %d. Leaf. Sleep for %d secs. \n", getpid(), t);
    sleep(t);
    return 0;
}