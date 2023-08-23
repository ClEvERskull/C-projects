#include<stdio.h>
int is_prime(const int number);
int next_prime(const int prime);
long int find_A_n(const int n);
int sum_digits(const long int number);
int sum_digits_n(const int n);
int constant(const int a, const int b);


int is_prime(const int number){
    int prime = 0, loop = 1;
    if(number < 2)
        return 0;
    while(loop <= number){
        if(number % loop == 0)
            prime++;
        loop++;
    }
    if(prime == 2)
        return 1;
    else 
        return 0;
}

int next_prime(const int prime){
    if(is_prime(prime) == 0)
        return -1;
    int nmb = prime + 1;
    if(is_prime(nmb) == 0)
        nmb++;
    else if(is_prime(nmb) == 1)
        return nmb;
}

long int find_A_n(const int n){
long int a = 2;
int i = 0, n = 2;

if(n < 1)
    return 0;
while(i < n)(
    cislo = next_prime(cislo);
    i++;
)
while(1){
    i = 1;
    while(i <= a){
        if(a % cislo == n)
            return a;
        else 
            i++;
    }
    a = next_prime(a);
}
}

int sum_digits(const long int number){
    if(number < 0)
        return 0;
    long int cislo = number; 
    int hodnota = 0;
    while (cislo > 0) {
        hodnota += cislo % 10;
        cislo /= 10;
    }
    return hodnota;
}

int sum_digits_n(const int n){
int i = 0, a = 0;
if(n < 1)
    return 0;
int cislo[n];
cislo[0] = 1;
for(i = 1; i <= n; i++){
    for(j = i-1; j >= 0; j--){
        a += sum_digits(cislo[j]);
    }
    cislo[i] = a;
    a = 0;
}
return cislo[n];
}

int constant(const int a, const int b){

}