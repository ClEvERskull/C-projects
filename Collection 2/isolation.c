#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int main(){
	int n = 0, k = 0, i =0, j = 0, krok = 0, m = 0, pocet = 0;
	scanf("%d %d",&n, &k);
	pocet = n;
	int cislo[n][k];
	for(i = 0; i < n; i++){
		for(j = 0; j < k; j++){
			scanf("%d",&cislo[i][j]);
		}
	}
	int mocnina = pow(2, (k - 1)) - 1;
	int pole[n][mocnina];
	int zaciatok = (mocnina - 1) / 2;
	for(j = 0; j < n; j++){
		for(i = 0; i < k; i++){
			krok = k - 3;
			zaciatok = (mocnina - 1) / 2;
			while(pole[j][zaciatok] != 0){
				if(cislo[j][i] < pole[j][zaciatok]){
					zaciatok -= krok;
					krok--;
				}
				else if(cislo[j][i] > pole[j][zaciatok]){
					zaciatok += krok;
					krok++;
				}
				else if(cislo[j][i] == pole[j][zaciatok])
					break;		
			}
			//printf("%d ",cislo[j][i] );
			pole[j][zaciatok] = cislo[j][i];
			//printf("%d ",pole[j][i]);
		}
		for(i = 0; i < mocnina; i++){
			if(pole[j][i] != 0)
				pole[j][i] = 1;
			printf("%d",pole[j][i] );
		}
		printf("\n");
	}
	for(j = 0;j < n; j++){
		for(i = j + 1; i < n; i++){
			for(m = 0;m < mocnina; m++){
				if(pole[j][m] == pole[i][m]){
					pocet--;
					break;
				}
			}
		}
	}
	
	printf("%d\n", pocet);
	return 0;
}
