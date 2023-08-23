#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include "playfair.h"

char* playfair_encrypt(const char* key, const char* text){
	char* encrypt = (char*)calloc(strlen(text), sizeof(char));
	//int size = strlen(size);
	char* psw = (char*)calloc(strlen(key), sizeof(char));
	char* avadakedabrakurva = (char*)calloc(25, sizeof(char));
	char cifra[25];
	//char psw[size];
	char cipher[5][5];
	int i = 0, j = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, pocitadlo = 0, abc = 0;
	int n = strlen(key);
	for(i = 0; i < n; i++){
		if(key[pocitadlo] == 'w' || key[pocitadlo] == 'W'){
			psw[i] = 'V';
		}
		else if(key[pocitadlo] == key[pocitadlo + 1]){
			psw[i++] = toupper(key[pocitadlo++]);
			psw[i] = 'X';
		}
		else
			psw[i] = toupper(key[pocitadlo++]);
	}
	
	printf("%s\n", psw);
	pocitadlo = 0;
	abc = 0;	
	for(i = 0; i < 25; i++){
		for(j = 0;j < i; j++){
			if(pocitadlo >= n){
				if(cifra[j] == ALPHA[abc]){
					abc++;
					j = 0;
				}
			}
			else if(pocitadlo < n){
				if(cifra[j] == psw[pocitadlo]){
					pocitadlo++;
					j = 0;
				}
			}
			/*else{
				if(cifra[j] == ALPHA[abc] || ALPHA[abc] == psw[j]){
					abc++;
					j = 0;
				}
			}*/
		}
		if(pocitadlo < n){
			cifra[i] = psw[pocitadlo];
			pocitadlo++;
		}
		else{
			cifra[i] = ALPHA[abc];
			abc++;
		}
	}
	
	
	pocitadlo = 0;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			cipher[j][i] = cifra[pocitadlo];
			pocitadlo++;
		}
	}
	//printf("%s\n", cipher);
	
	n = strlen(text);
	pocitadlo = 0;
	for(abc= 0; abc <= n; abc++){
		if(text[pocitadlo] == 'w' || text[pocitadlo] == 'W'){
			avadakedabrakurva[abc] = 'V';
			pocitadlo++;
		}
		else if(text[pocitadlo] == text[pocitadlo + 1]){
			avadakedabrakurva[abc++] = toupper(text[pocitadlo++]);
			avadakedabrakurva[abc] = 'X';
		}
		else if(text[pocitadlo] == 32){
			pocitadlo++;
			abc--;
		}
		else
			avadakedabrakurva[abc] = toupper(text[pocitadlo++]);
	}
	if((--abc) % 2  == 1){
		avadakedabrakurva[abc] = 'X';
	}
	printf("%s\n", text);
	printf("%s\n", avadakedabrakurva);
	
	for(pocitadlo = 0; pocitadlo < n; pocitadlo += 2){
		int x = 0, y = 0;
		for(y = 0; y < i; y++){
			for(x = 0; x < j; x++){
				if(avadakedabrakurva[pocitadlo] == cipher[x][y]){
					x1 = x;
					y1 = y;
					x = j;
					y = i;
				}	
			}
		}
		
		for(y = 0; y < i; y++){
			for(x = 0; x < j; x++){
				if(avadakedabrakurva[pocitadlo + 1] == cipher[x][y]){
					x2 = x;
					y2 = y;
					x = j;
					y = i;
				}	
			}
		}
		
		
		if(x1 == x2){
			encrypt[pocitadlo] = cipher[x1][y1+1];
			encrypt[pocitadlo + 1] = cipher[x2][y2+1];
		}
		else if(y1 == y2){
			encrypt[pocitadlo] = cipher[x1+1][y1];
			encrypt[pocitadlo + 1] = cipher[x2+1][y2];
		}
		else{
			encrypt[pocitadlo] = cipher[x2][y1];
			encrypt[pocitadlo + 1] = cipher[x1][y2];
		}	
	}
	
	return encrypt;
	
}

char* playfair_decrypt(const char* key, const char* text){
	char* decrypt = (char*)calloc(strlen(text), sizeof(char));
	//int size = strlen(size);
	char* psw = (char*)calloc(strlen(key), sizeof(char));
	char* avadakedabrakurva = (char*)calloc(25, sizeof(char));
	char cifra[25];
	//char psw[size];
	char cipher[5][5];
	int i = 0, j = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, pocitadlo = 0, abc = 0;
	int n = strlen(key);
	for(i = 0; i < n; i++){
		if(key[pocitadlo] == 'w' || key[pocitadlo] == 'W'){
			psw[i] = 'V';
		}
		else if(key[pocitadlo] == key[pocitadlo + 1]){
			psw[i++] = toupper(key[pocitadlo++]);
			psw[i] = 'X';
		}
		else
			psw[i] = toupper(key[pocitadlo++]);
	}
	
	printf("%s\n", psw);
	pocitadlo = 0;
	abc = 0;	
	for(i = 0; i < 25; i++){
		for(j = 0;j < i; j++){
			if(pocitadlo >= n){
				if(cifra[j] == ALPHA[abc]){
					abc++;
					j = 0;
				}
			}
			else if(pocitadlo < n){
				if(cifra[j] == psw[pocitadlo]){
					pocitadlo++;
					j = 0;
				}
			}
			/*else{
				if(cifra[j] == ALPHA[abc] || ALPHA[abc] == psw[j]){
					abc++;
					j = 0;
				}
			}*/
		}
		if(pocitadlo < n){
			cifra[i] = psw[pocitadlo];
			pocitadlo++;
		}
		else{
			cifra[i] = ALPHA[abc];
			abc++;
		}
	}
	
	
	pocitadlo = 0;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 5; j++){
			cipher[j][i] = cifra[pocitadlo];
			pocitadlo++;
		}
	}
	//printf("%s\n", cipher);
	
	n = strlen(text);
	pocitadlo = 0;
	for(abc= 0; abc <= n; abc++){
		if(text[pocitadlo] == 'w' || text[pocitadlo] == 'W'){
			avadakedabrakurva[abc] = 'V';
			pocitadlo++;
		}
		else if(text[pocitadlo] == text[pocitadlo + 1]){
			avadakedabrakurva[abc++] = toupper(text[pocitadlo++]);
			avadakedabrakurva[abc] = 'X';
		}
		else if(text[pocitadlo] == 32){
			pocitadlo++;
			abc--;
		}
		else
			avadakedabrakurva[abc] = toupper(text[pocitadlo++]);
	}
	if((--abc) % 2  == 1){
		avadakedabrakurva[abc] = 'X';
	}
	printf("%s\n", text);
	printf("%s\n", avadakedabrakurva);
	
	for(pocitadlo = 0; pocitadlo < n; pocitadlo += 2){
		int x = 0, y = 0;
		for(y = 0; y < i; y++){
			for(x = 0; x < j; x++){
				if(avadakedabrakurva[pocitadlo] == cipher[x][y]){
					x1 = x;
					y1 = y;
					x = j;
					y = i;
				}	
			}
		}
		
		for(y = 0; y < i; y++){
			for(x = 0; x < j; x++){
				if(avadakedabrakurva[pocitadlo + 1] == cipher[x][y]){
					x2 = x;
					y2 = y;
					x = j;
					y = i;
				}	
			}
		}
		
		
		if(x1 == x2){
			decrypt[pocitadlo] = cipher[x1][y1+1];
			decrypt[pocitadlo + 1] = cipher[x2][y2+1];
		}
		else if(y1 == y2){
			decrypt[pocitadlo] = cipher[x1+1][y1];
			decrypt[pocitadlo + 1] = cipher[x2+1][y2];
		}
		else{
			decrypt[pocitadlo] = cipher[x2][y1];
			decrypt[pocitadlo + 1] = cipher[x1][y2];
		}	
	}
	
	return decrypt;
}




int main(){
	int i = 0;
	char* encrypt = playfair_encrypt("belfast","KRYPTOGRAFIA");
	printf("%s\n", encrypt);
	
	getchar();
}
