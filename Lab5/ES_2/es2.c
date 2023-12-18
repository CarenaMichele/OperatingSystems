#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#define N 50
void parent(int *file1,int *file2);
void child(int *file1, int *file2);
void upper(char *line);

int main(int argc, char **argv){
    pid_t pid;
    int file1[2];
    int file2[2];

    /*creazione pipe*/
    int ris=pipe(file1);
    int ris2=pipe(file2);

    if(ris==-1){
        fprintf(stderr, "errore nella creazione della pipe!\n");
        return -1;
    }
    if(ris2==-1){
        fprintf(stderr, "error nella creazione della pipe!\n");
        return -1;
    }
    pid=fork();
    if(pid==-1){
        fprintf(stdout, "errore nella creazione della fork!\n");
        return -1;
    }
    if(pid>0){ //padre
        /*while(1){
            fprintf(stdout,"I'm the father (PID=%d)", getppid());
        }
        wait((int *) 0);*/ 
        parent(file1, file2);
    }else{ //figlio
        child(file1, file2);
        /*while(1){
            fprintf(stdout,"Im the child (PID=%d)", getpid());
        }*/
    }
    wait((int *) 0);
    return 0;
}

void parent(int *f1, int *f2){
    /*padre legge sulla prima pipe e scrive sulla seconda, viceversa il figlio*/
    close(f1[1]);
    close(f2[0]);
    int i=0;
    char line[N];
    while(i<=10){
        fprintf(stdout, "I'm the father (PID=%d)\n", getpid());
        sprintf(line,"X");
        write(f2[1],line, sizeof(line));
        i++;
        read(f1[0],line,sizeof(line));
    }
    sprintf(line,"end");
    write(f2[1],line, sizeof(line));
    close(f1[0]);
    close(f2[1]);
}

void child(int *f1, int *f2){
    close(f1[0]);
    close(f2[1]);
    char line[N];
    while(1){
        read(f2[0],line,sizeof(line));
        if(strcmp(line, "end")==0){
            close(f1[1]);
            close(f2[0]);
            break;
        }
        else{
            fprintf(stdout,"I'm the child (PID=%d)\n", getpid());
        }
        sprintf(line,"X");
        write(f1[1],line, sizeof(line));
    }
}
