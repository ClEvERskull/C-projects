#include<stdio.h>
#include<math.h>

int main(){
    int pocet = 0,i = 0,student = 0,ucitel = 0,osoba = 0, dotacia = 0, peniaze = 0;
    float suma;
    scanf("%d", &pocet);
    if(pocet < 0 || pocet > 20){
        printf("Wrong input!\n");
        return 1;
    }
    for(i = 0;i < pocet; i++){
        scanf("%d", &osoba);
        if(osoba == 1){
            scanf("%f", &suma);
            if(suma < 0){
                printf("Wrong input!\n");
                return 1;
            }
            peniaze = suma * 100;
            if(peniaze >= 400)
                dotacia += 200;
            else if(peniaze >= 200)
                dotacia += 100;
            student += peniaze;
        }
        else if(osoba == 2){
            scanf("%f", &suma);
            if(suma < 0){
                printf("Wrong input!\n");
                return 1;
            }
            peniaze = suma * 100;
            ucitel += peniaze;
            if( peniaze % 360 >= 0 && peniaze % 360 < 180 ){
                dotacia += (((int)(peniaze/360) * 360) * 0.55f) + 42;
            }
            else if( peniaze % 360 > 180 && peniaze % 360 < 360){
                dotacia += (peniaze * 0.55f) + 42;
            }
        }
        else{
                printf("Wrong input!\n");
                return 1;
        }
    }
    float paid = ucitel + student - dotacia;
    paid = paid / 100;
    float dotacie = dotacia / 100;
    printf("Total: %.2f donated, %.2f paid.\n", dotacie, paid);

}
