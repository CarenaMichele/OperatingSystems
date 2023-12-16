#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define N 100
#define LUNGPUNT 10
#define LUNGVET 50
void comSystem(FILE *f1);
int main(int argc, char **argv){
    FILE *f1;
    pid_t pid;

    if(argc!=2){
        printf("error!\n");
        return 1;
    }

    f1=fopen(argv[1],"r");

    if(f1==NULL){
        printf("error opening file!\n");
        return 1;
    }

    //comSystem(f1);

    char **mat, *tmpP;

    mat=(char **)malloc(LUNGPUNT * sizeof(char*));
    for(int i=0;i<LUNGPUNT;i++){
        mat[i]=(char  *)malloc(LUNGVET *sizeof(char));
    }

    char tmp[N];
    int nString=0;
    while(fscanf(f1, "%s", tmp)!=EOF){
        if(strcmp(tmp,"end")!=0){
            strcpy(mat[nString],tmp);
            nString++;
        }
        else{
            printf("Comando: ");
            for(int j=0;j<nString;j++){
                printf("%s ", mat[j]);
            }
            printf("\n");
            tmpP=mat[nString];
            mat[nString]=NULL; //questo viene fatto perchè l'ultimo argomento di argv deve essere null terminato
            pid=fork();
            if(pid==0){
                execvp(mat[0],mat); //come primo argomento mettiamo il nome del comando unix //es. mat={"ls","-l",NULL};
            }
            else{
                sleep(3);
            }
            mat[nString]=tmpP;
            nString=0;
        }
    }    

    fclose(f1);
    return 0;
}

void comSystem(FILE *f1){
    char *str, *tmp;
    str[0]='\0';
    while(fscanf(f1,"%s",tmp)!=EOF){
        if(strcmp(tmp, "end")!=0){
            strcat(str, tmp);
            strcat(str, " ");
        }
        else{
            printf("%s\n",str);
            system(str);
            str[0]='\0';
        }   
    }
}
