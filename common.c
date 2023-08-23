#include<stdio.h>

short int gcd(const short int a, const short int b){
      int cislo1,cislo2;
    if(a == 0 || b == 0 || a > 1000 || a < -1000 || b > 1000 || b < -1000)
        return -1;
    else{
        if(a < 0)
             cislo1 = a * (-1);
        else
            cislo1 = a;
        if(b < 0)
             cislo2 = b * (-1);
        else 
             cislo2 = b;
        if(cislo1 > cislo2){
            int i = cislo2;
            while(i != 1){
                if(cislo2 % i == 0 && cislo1 % i == 0)
                    return i;
                else 
                    i--;
            }
        }
        
        else {
            int i = cislo1;
            while(1){
                if(cislo2 % i == 0 && cislo1 % i == 0)
                    return i;
                else 
                    i--;
            }
        }
    }
}

long int lcm(const int a, const int b){
    int i,j;
    if(a > 1000 || a < 0 || b > 1000 || b < 0)
        return -1;
    else {
        while(1){
            if(a > b){
                for(i = 1; i <= a; i++){
                    for(j = 0; j <= b; j++){
                        if((a * i) == (b * j)){
                            int cislo = a*i;
                            return cislo;
                        }
                    }

                }
            }

            else if(a == b){
                return a;
            }
        }
    }
}

int main(){
printf("%d\n", gcd(16,12));
printf("%d\n", gcd(-21,-35));
printf("%d\n", gcd(2,0));
printf("%ld\n", lcm(3,4));
printf("%ld\n", lcm(16,12));
printf("%ld\n", lcm(6,0));
}
