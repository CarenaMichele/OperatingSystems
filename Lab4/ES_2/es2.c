#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> /*fornisce dichiarazioni per funzioni e costanti per manipolazione di file e descrittori di file*/
#include <sys/types.h>
#define N 12
void child (int fd, int j);
int main(int argc, char **argv){
    int n, c, v;
    if(argc!=2){
        printf("errore!\n");
        return -1;
    }
    /*creo file e scrivo 12 interi*/

    //int fd= creat(argv[1],0666);
    int fd= open(argv[1], O_RDWR | O_CREAT, 0666);
    if(fd==-1){
        perror("open");
        return -1;
    }

    int data[N];
    for(int i=0;i<N;i++){
        data[i]=rand()%20;
        fprintf(stdout, "%d ",data[i]);
    }
    fprintf(stdout, "\n");

    size_t data_size=sizeof(data); /*calcola la dim totale in byte dei dati */
    ssize_t bytes_written= write(fd, data, data_size); /*ssize_t è usato anche per verificare se c'è un errore o no*/

    if(bytes_written==-1){
        perror("write");
        close(fd);
        return -1;
    }
    fprintf(stdout, "%ld\n", bytes_written);
    close(fd);

    /*apro file e leggo gli interi a partire dall'ultimo*/

    fd=open(argv[1], O_RDONLY);
    if(fd==-1){
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
    }
    fprintf(stdout, "File before ordering:  ");
    for(int i=N;i>0;i--){
        lseek(fd,-i*sizeof(int),SEEK_END);
        c=read(fd, &v, sizeof(int));
        fprintf(stdout, "%d ", v);
    }
    fprintf(stdout, "\n");

    close(fd);

    /*comunicazione tra padre e figlio*/
    fd=open(argv[1], O_RDWR);

    fprintf(stdout,"Ordinamento concorrente:\n ");
    for (int i=0; i<N-1; i++) {
        for (int j=0; j<N-1-i; j++) {
            if(fork()>0){ //father 
                wait((int *) 0);
            }
            else{ //child 
                child(fd, j);
                exit(0);
            }
        }
    }
    close(fd);

    fd=open(argv[1], O_RDONLY);
    if(fd==-1){
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
    }
    fprintf(stdout, "File after ordering:  ");
    for(int i=0;i<N;i++){
        lseek(fd,i*sizeof(int),SEEK_SET);
        c=read(fd, &v, sizeof(int));
        fprintf(stdout, "%d ", v);
    }
    fprintf(stdout, "\n");

    close(fd);

    return 0;
}

void child (int fd, int j){
    int c1, c2, v1, v2;
    lseek(fd, j*sizeof(int), SEEK_SET);
    c1= read(fd,&v1,sizeof(int));
    c2= read(fd,&v2,sizeof(int));

    if(v1>v2){
        lseek(fd,j*sizeof(int), SEEK_SET);
        c1= write(fd, &v2, sizeof(int));
        c2= write(fd, &v1, sizeof(int));
    }

    return;
}
