#include<stdio.h>
#include<stdlib.h>

int main(){
	int pocet = 0, i = 0, end = 0, cas = 0;
	double vypocet = 0, vysledok = 0, min = 0, max = 0, cislo = 0;
	
	scanf("%d %d", &pocet, &cas);
	
	int draha[pocet],rychlost[pocet];
	
	for(i = 0; i < pocet; i++){
		scanf("%d %d", &draha[i], &rychlost[i]);
	}
	
	min = rychlost[0];
	max = cas;
	
	for(i = 0; i < pocet; i++){
		if(min > rychlost[i])
			min = rychlost[i];
	}
	min *= -1;
	/*printf("pocet = %d\n", pocet);
	printf("cas = %d\n", cas);
	printf("minimum = %f\n", max);*/
	
	while(end != 1){
		cislo = min + ((max - min) / 2);
		vypocet = 0;
		for(i = 0; i < pocet; i++){
			vypocet += draha[i] / (rychlost[i] + cislo);
		}	
		//printf("vysledok = %.8f ... cislo = %.8f\n", vypocet, cislo);
		if((vypocet >= cas - 0.000001) && (vypocet <= cas + 0.0002)){
			if(cislo < 0 && cislo > -0.000001)
				cislo *= -1;
			vysledok = cislo;
			end = 1;
			break;
		}
		
		else if(vypocet < cas){
			max = cislo;
		}
		else if(vypocet > cas){
			min = cislo;
		}
	}
	printf("%.6f\n", vysledok);
	return 0;
}
