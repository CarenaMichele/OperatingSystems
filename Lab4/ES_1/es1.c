#include <stdio.h>
int main(int argc, char **argv){
    int n;

    while(fscanf(stdin, "%d", &n)==1){
        if(n%2==0)
            fprintf(stdout, "%d\n", n);
        else
            fprintf(stderr, "%d\n", n);
    }
    
    return 0;
}
