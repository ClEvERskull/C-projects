#include<stdio.h>

int main(){
    int farmers, i;
    long int celkovo = 0;
    scanf("%d ", &farmers);
    if(farmers < 0 || farmers > 20){
        printf("Wrong input!\n");
        return 1;
    }
    int farma, zvierata, ekologickost;
    for(i = 0; i < farmers; i++){
        scanf("%d ", &farma);
        scanf("%d ", &zvierata);
        scanf("%d ", &ekologickost);
        if((farma >= 0 && farma <= 10000) && (zvierata >= 0 && zvierata <= 10000) && (ekologickost >= 0 && ekologickost <= 10000)){
            celkovo += ekologickost * farma * (zvierata / zvierata);
        }
        else{
            printf("Wrong input!\n");
            return 1;
        }
    }
    printf("Total donation: %ld\n", celkovo);
    return 0;
}
