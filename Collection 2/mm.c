#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
	int cislo = 0;
	int vypocet = 0;
	int i = 0;
	char znak;
	char* cifry;
	cifry=(char*)malloc(200000 * sizeof(char*));
	scanf("%s", cifry);
	int dlzka = strlen(cifry);
	for(i = 0; i < dlzka;i++){
		znak = cifry[i];
		cislo += znak - 48;
	}
	while(cislo > 9){
		vypocet = 0;
		while(cislo > 0){
		vypocet += cislo%10;
			cislo /= 10;
		}
		cislo = vypocet;
	}
	free(cifry);
	printf("%d", cislo);
	return 0;
}
