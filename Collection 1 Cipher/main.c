#include<stdlib.h>
#include<stdio.h>
#include "bmp.h"
#include "playfair.h"

int main(){
	unsigned char* encrypted;
	char* decrypted;
	char* playFair;
	char* playFair_dec;
	
	playFair = playfair_encrypt("bElFest", "Hello world");
    printf("playfairova : %s\n", playFair);
    playFair_dec = playfair_decrypt("bElFest", playFair);
    printf("playfairova : %s\n", playFair_dec);
	
    encrypted = bmp_encrypt("secret", "Hello world!");
    printf("bmp: %s\n", encrypted);
    decrypted = bmp_decrypt("secret", encrypted);
    printf("bmp: %s\n", decrypted);
    
    free(encrypted);
    free(decrypted);
    free(playFair);
    free(playFair_dec);
}
