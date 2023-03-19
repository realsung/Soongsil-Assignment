#include <stdio.h>

int main(){
    for(unsigned int i=100; i<999999; i++){
        for(unsigned int j=100; j<999999; j++){
            if(i*j<=16){
                printf("%d %d\n",i, j);
            }
        }
    }
}