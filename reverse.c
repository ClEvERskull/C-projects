#include <stdio.h> 
#include <string.h> 
#include <ctype.h>

char* reverse(const char* text) 
{ 
    if(text == 0)
    	return 0;
    int n = strlen(text);
    char* reversed = malloc(strlen(text));
    int i = 0;
    for(i; i < n; i++){
    	reversed[i] = toupper(text[n-i-1]);
	}
    return reversed;
} 

int main() 
{ 
	char* reversed = reverse("sakmadong");
    printf("Reverse of the string: %s\n", reversed); 
  
    return 0; 
} 
