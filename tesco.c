#include<stdio.h>
#include<stdlib.h>

int main(){

    float vstup = 0, hotovost = 0, ucet = 0;

    float vydavok[100];

    int pocet = 0, i, delitel;
    
    printf("\nEnter value of your bill: ");
    scanf("%f", &ucet);
    if(0 < ucet && ucet < 10000){
        printf("\nInsert money for payment: ");
    }
    else{
        printf("\nWrong input!\n");
        return 1;
    }


    do{
        scanf("%f", &vstup);
        if((vstup ==0.01f)||(vstup ==0.02f)||(vstup==0.05f)||(vstup==0.10f)||(vstup==0.20f)||(vstup==0.50f)||(vstup==1)||(vstup==2)||(vstup==5)||(vstup==10)||(vstup==20)||(vstup==50)||(vstup==100)||(vstup==200)||(vstup==500)) 
            hotovost += vstup;
        else if(vstup != 0){
            if((delitel = vstup * 100 ) % 100 == 0){
                printf("\n%.0f is not valid!\n", vstup);
            }
            else {
                printf("\n%.2f is not valid!\n", vstup); 
            }
            return 1;
            }
    }while(vstup != 0 && scanf("%f", &vstup) != EOF);
    if((delitel = hotovost * 100 ) % 100 == 0){
                printf("\nYou have inserted: %.0f\n", hotovost);
            }
            else {
                printf("\nYou have inserted: %.2f\n", hotovost);
            }
    
    if(ucet < hotovost){
    hotovost -= ucet;
    if((delitel = hotovost * 100 ) % 100 == 0){
                printf("To return: %.0f\n", hotovost);
            }
            else {
                printf("To return: %.2f\n", hotovost);
            }
    hotovost = hotovost * 100;



    while(hotovost >= 50000){

        hotovost -= 50000;

        vydavok[pocet++] = 500;

    }



    while(hotovost >= 20000){

        hotovost -= 20000;

        vydavok[pocet++] = 200;

    }



    while(hotovost >= 10000){

        hotovost -= 10000;

        vydavok[pocet++] = 100;

    }



    while(hotovost >= 5000){

        hotovost -= 5000;

        vydavok[pocet++] = 50;

    }



    while(hotovost >= 2000){

        hotovost -= 2000;

        vydavok[pocet++] = 20;

    }



    while(hotovost >= 1000){

        hotovost -= 1000;

        vydavok[pocet++] = 10;

    }



    while(hotovost >= 500){

        hotovost -= 500;

        vydavok[pocet++] = 5;

    }



    while(hotovost >= 200){

        hotovost -= 200;

        vydavok[pocet++] = 2;

    }



    while(hotovost >= 100){

        hotovost -= 100;

        vydavok[pocet++] = 1;

    }



    while(hotovost >= 50){

        hotovost -= 50;

        vydavok[pocet++] = 0.5f;

    }



    while(hotovost >= 20){

        hotovost -= 20;

        vydavok[pocet++] = 0.2f;

    }



    while(hotovost >= 10){

        hotovost -= 10;

        vydavok[pocet++] = 0.1f;

    }



    while(hotovost >= 5){

        hotovost -= 5;

        vydavok[pocet++] = 0.05f;

    }



    while(hotovost >= 2){

        hotovost -= 2;

        vydavok[pocet++] = 0.02f;

    }



    while(hotovost >= 1){

        hotovost -= 1;

        vydavok[pocet++] = 0.01f;

    }
    
    printf("Collect your payback: ");


    for(i = 0; i < pocet; i++){

        if((delitel = vydavok[i] * 100) % 100 == 0){
                printf("%.0f ", vydavok[i]);
            }
            else {
                printf("%.2f ", vydavok[i]);
            }

    }
    printf("\n");
    }

    else if(ucet > hotovost) {
    printf("Not enough money!\n");
    }
    else if(ucet == hotovost){
        printf("To return: 0 \n");
    }
    printf("\n");
}



