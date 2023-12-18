#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#define N 50
void producer(int *fileDescr);
void consumer(int *fileDescr);
void upper(char *line);

int main(int argc, char **argv){
    pid_t sender, receiver;
    int fd;
    int fileDescr[2];

    /*creazione pipe*/
    int ris=pipe(fileDescr);

    if(ris==-1){
        fprintf(stderr, "errore nella creazione della pipe!\n");
        return -1;
    }
    sender=fork();
    if(sender==-1){
        fprintf(stdout, "errore nella creazione della fork!\n");
        return -1;
    }
    if(sender>0){ //padre
        receiver=fork();
        if(receiver==0){
            consumer(fileDescr);
            
        }
    }else{
        producer(fileDescr);
        
    }
    wait((int *) 0);
    wait((int *) 0);

    return 0;
}

void consumer(int fileDescr[2]){
    char line[N],tmp[N];
    close(fileDescr[1]);

    //char buffer[100];
    //ssize_t bytes_read;
    //int n;
    while(1){
        read(fileDescr[0], line, sizeof(line));
        //close(fileDescr[0]);
        //sscanf(tmp, "%s", line);

        /*if(bytes_read==-1){
            fprintf(stdout, "errore nella lettura del file!\n");
            return -1;
        }*/
        upper(line);
        fprintf(stdout,"%s\n", line);
        fflush(stdout);

        if(strcmp(line, "end") ==0){
            close(fileDescr[0]);
            break;
            
        }
        
       
    }
    exit(0);
}

void producer(int fileDescr[2]){
    char line[N],tmp[N];
    close(fileDescr[0]);
    while(1){
        fprintf(stdout, "Stringa: ");
        fflush(stdout);
        //scanf("%s",line);
        gets(line, sizeof(line));
        //fprintf(fp,"%s", line);
        //ssize_t bytes_written;
        //sprintf(tmp,"%s", line);
        
        write(fileDescr[1],line,sizeof(line));
        

        /*if(bytes_written==-1){
            fprintf(stdout, "errore nella scrittura del file!\n");
            return -1;
            
        }*/

        if(strcmp(line, "end") ==0){
            close(fileDescr[1]);
            break;
            
        }
        sleep(1);
        
    }
    exit(0);
}

void upper(char *line){
    for(int i=0;i<strlen(line);i++){
        line[i]=toupper(line[i]);
    }
}

/*void signalHandler(){
    return;
}*/

