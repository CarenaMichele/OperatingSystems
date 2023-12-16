#include <stdio.h>
int main(){
    int i;
    for(i=3;i>1;i--){
        if(fork())
        printf("%d\n", i);
    }
    printf("%d\n", i);
    
    return 0;
}

