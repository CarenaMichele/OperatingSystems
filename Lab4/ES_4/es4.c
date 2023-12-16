#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#define N 50
void producer(pid_t pidR);
void consumer(pid_t pidS);
void upper(char *line);
void signalHandler();

int main(int argc, char **argv){
    pid_t sender, receiver;
    int fd;

    if (signal(SIGUSR1, signalHandler)==SIG_ERR){
        fprintf(stderr, "Signal Handler error\n");
        return 1;
    }

    sender=fork();

    if(sender>0){ //padre
        //fprintf(stdout,"processo padre con pid= %d\n", getpid());
        receiver=fork();
        if(receiver==0){
            //fprintf(stdout, "sono il secondo figlio con pid=%d\n", getpid());
            consumer(sender);
        }
    }else{
        //fprintf(stdout, "sono il primo figlio con pid=%d\n", getpid());
        producer(receiver);
    }
    wait((int *) 0);
    wait((int *) 0);

    return 0;
}

void producer(pid_t pidR){
    FILE *fp;
    char line[N];

    while(1){
        fp=fopen("input.txt","w");

        if(fp==NULL){
            fprintf(stderr, "errore nell'apertura del file!\n");
            return -1;
        }

        fprintf(stdout, "Stringa: ");
        fflush(stdout);
        gets(line, sizeof(line)); //fgets restituisce anche \n quindi dava errore quando scrivevo stringa end perchè prendeva anche \n
        //fprintf(stdout, "%s", line);

        fprintf(fp,"%s", line);
        fclose(fp);
        kill(pidR, SIGUSR1);
        
        if(strcmp(line, "end")==0){
            break;
        }
        pause();
        
    }
    fflush(stdout);
    exit(0);
}

void consumer(pid_t pidS){
    FILE *fp;
    char line[N], strMaiusc[N];

    while(1){
        pause();

        fp=fopen("input.txt", "r");

        if(fp==NULL){
            fprintf(stderr, "errore nell'apertura del file\n");
            return -1;
        }
        fgets(line, sizeof(line), fp);
        fclose(fp);
        if(strcmp(line, "end")==0){
            break;
        }
        //fprintf(stdout, "%s", line);
        upper(line);
        fprintf(stdout,"%s", line);
        fflush(stdout);
        fprintf(stdout,"\n");
        

        sleep(1);
        kill(pidS,SIGUSR1);

    }
    fflush(stdout);
    exit(0);
}

void upper(char *line){
    for(int i=0;i<strlen(line);i++){
        line[i]=toupper(line[i]);
    }
}

void signalHandler(){
    return;
}

