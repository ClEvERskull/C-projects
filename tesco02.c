#include<stdio.h>
#include<stdlib.h>

int main(){
    float vstup = 0, platene = 0;
    int pocet = 0, hotovost = 0, i;
    float vydavok[100];

    do{
        scanf("%f.2", &vstup);
        platene =+ vstup;
    }while(vstup != 0);

    hotovost = platene * 100;

    while(hotovost >= 50000){
        hotovost =- 50000;
        vydavok[++pocet] = 500;
    }

    while(hotovost >= 20000){
        hotovost =- 20000;
        vydavok[++pocet] = 200;
    }

    while(hotovost >= 10000){
        hotovost =- 10000;
        vydavok[++pocet] = 100;
    }

    while(hotovost >= 5000){
        hotovost =- 5000;
        vydavok[++pocet] = 50;
    }

    while(hotovost >= 2000){
        hotovost =- 2000;
        vydavok[++pocet] = 20;
    }

    while(hotovost >= 1000){
        hotovost =- 1000;
        vydavok[++pocet] = 10;
    }

    while(hotovost >= 500){
        hotovost =- 500;
        vydavok[++pocet] = 5;
    }

    while(hotovost >= 200){
        hotovost =- 200;
        vydavok[++pocet] = 2;
    }

    while(hotovost >= 100){
        hotovost =- 100;
        vydavok[++pocet] = 1;
    }

    while(hotovost >= 50){
        hotovost =- 50;
        vydavok[++pocet] = 0.5;
    }

    while(hotovost >= 20){
        hotovost =- 20;
        vydavok[++pocet] = 0.2;
    }

    while(hotovost >= 10){
        hotovost =- 10;
        vydavok[++pocet] = 0.1;
    }

    while(hotovost >= 5){
        hotovost =- 5;
        vydavok[++pocet] = 0.05;
    }

    while(hotovost >= 2){
        hotovost =- 2;
        vydavok[++pocet] = 0.02;
    }

    while(hotovost >= 1){
        hotovost =- 1;
        vydavok[++pocet] = 0.01;
    }

    for(i = 0; i < pocet; i++){
        printf("f.2 ", &vydavok[i]);
    }
}
