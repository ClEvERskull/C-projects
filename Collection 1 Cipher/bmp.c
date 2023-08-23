#include <stdio.h> 
#include <string.h> 
#include <ctype.h>
#include<stdlib.h>
#include "bmp.h"

char* reverse(const char* text) 
{ 
    if(text == 0)
    	return 0;
    size_t n = strlen(text);
   char* reversed = (char*)calloc(n+1, sizeof(char));
    int i = 0;
    for(i = 0; i < n; i++){
    	reversed[i] = toupper(text[n-i-1]);
	}
    return reversed;
} 

char* vigenere_encrypt(const char* key, const char* text){
	size_t n = strlen(key);
    char key_set[n];
    int i = 0, j = 0;
    while(j<n){
    	if(key[j] != 32)
    		key_set[i++] = toupper(key[j++]);
    	else{
    			j++;
    	}
	}
	j = 0;
	i = 0;
	size_t m = strlen(text);
	char encrypt[m];
	char revers[m];
	for(i = 0; i <= m; i++){
		revers[i] = toupper(text[i]);
	}
	for(i = 0; i <= m; i++){
		if(revers[i] >= 65 && revers[i] <= 90){
			encrypt[i] = revers[i] + (key_set[j++] - 65);
			if(encrypt[i] > 90)
				encrypt[i] = encrypt[i] - 26;
			if(j == n)
				j = 0;
		}
		else
			encrypt[i] = revers[i];
	}
	
	char* encrypted = (char*)calloc(m, sizeof(char));
	
	for(i = 0; i <= m; i++){
		encrypted[i] = encrypt[i];
	}
	return encrypted;
}

char* vigenere_decrypt(const char* key, const char* text){
	//char *reversed = reverse(text);
	int n = strlen(key);
    char key_set[n];
    int i = 0, j = 0;
    for(i = 0; i < n; i++){
    	key_set[i] = toupper(key[i]);
	}
	
	int m = strlen(text);
	char decrypt[m];
	char revers[m];
	for(i = 0; i <= m; i++){
		revers[i] = toupper(text[i]);
	}
	for(i = 0; i <= m; i++){
		if(revers[i] >= 65 && revers[i] <= 90){
			decrypt[i] = revers[i] - (key_set[j] - 65);
			if(decrypt[i] > 90)
				decrypt[i] = decrypt[i] - 26;
			if(j == n)
				j = 0;
			else if(j < n)
				j++;
		}
		else
			decrypt[i] = revers[i];
	}
	
	char* decrypted = (char*)calloc(m+1, sizeof(char));
	
	for(i = 0; i <= m; i++){
		decrypted[i] = decrypt[i];
	}
	
	return decrypted;
}


unsigned char* bit_encrypt(const char* text){
	int i = 0;
	unsigned char* final = (unsigned char*)calloc(strlen(text) + 1,sizeof(char));
	for(i = 0; i <= strlen(text); i++){
	char bgn = text[i];
	
	int j = 0, cislo[8], change;
	int cast1 = 0;

    for(j = 0; j < 8; j++)
    {
    	if(bgn > 0){
    		cislo[j] = bgn%2;
        	bgn /= 2;	
		}
        else
        	cislo[j] = 0;
    }
    change = cislo[7];
    cislo[7] = cislo[6];
    cislo[6] = change;
    change = cislo[5];
    cislo[5] = cislo[4];
    cislo[4] = change;
    for(j = 0; j < 4; j++){
    	cislo[j] = (cislo[j] ^ cislo[j + 4]);
	}
	
	cast1 = (128 * cislo[7]) + (64 * cislo[6]) + (32 * cislo[5])+ (16 * cislo[4]) + (8 * cislo[3]) + (4 * cislo[2]) + (2 * cislo[1])+ cislo[0];
	final[i] = cast1;
	}
	return final;
}

char* bit_decrypt(const unsigned char* text){
	int i = 0;
	char* final = (char*)calloc(255,sizeof(char));
	for(i = 0; i < 255; i++){
	char bgn = text[i];
	
	int j = 0, cislo[8], change;
	int cast1 = 0;

    for(j = 0; j < 8; j++)
    {
    	if(bgn > 0){
    		cislo[j] = bgn%2;
        	bgn /= 2;	
		}
        else
        	cislo[j] = 0;
    }
    change = cislo[7];
    cislo[7] = cislo[6];
    cislo[6] = change;
    change = cislo[5];
    cislo[5] = cislo[4];
    cislo[4] = change;
    for(j = 0; j < 4; j++){
    	cislo[j] = (cislo[j] ^ cislo[j + 4]);
	}
	
	cast1 = (128 * cislo[7]) + (64 * cislo[6]) + (32 * cislo[5])+ (16 * cislo[4]) + (8 * cislo[3]) + (4 * cislo[2]) + (2 * cislo[1])+ cislo[0];
	final[i] = cast1;
	}
	return final;
}

unsigned char* bmp_encrypt(const char* key, const char* text){
	
	if(text == 0)
		return 0;
	
	char* reversed = reverse(text);
    
    char* encrypted;  
    encrypted = vigenere_encrypt(key, reversed);
    
    unsigned char* last_encrypt; 
    last_encrypt = bit_encrypt(encrypted);
    
    free(encrypted);
    
    return last_encrypt;
	
}

char* bmp_decrypt(const char* key, const unsigned char* text){
	
	if(text == 0)
		return 0;
	
	char* decrypt; 
	decrypt = bit_decrypt(text);
    
	char* decrypted; 
	decrypted = vigenere_decrypt(key, decrypt);
		
	char* reversed = reverse(decrypted);
	
	free(decrypted);
	free(decrypt);
	
	return reversed;
	
}

int main(){
	int i = 0;
	char* reversed = reverse("nejaky nah/odny text * s nahodne rozm&iestneny&mi znak*mi/.");
printf("%s\n", reversed);
// "!DLROW OLLEH"


char* encrypted;

// basic test with long text
encrypted = vigenere_encrypt("debil niesom","nasrac na vsetkoooo");
printf("%s\n", encrypted);
// "JSXAI PSINR!"

unsigned char* encrypt;

// basic test with long text
encrypt = bit_encrypt("Hello world!");
printf("%x\n ", encrypt);
for(i=0; i < 12;i++) {
    printf("%x ", encrypt[i]);
    //80 9c 95 95 96 11 bc 96 b9 95 9d 10
}
free(encrypted);
}
