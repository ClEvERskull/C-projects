#include <stdio.h>

char last_letter(const char string[]);
int longest(const char string[]);

int main()
{
	printf("%c %c %c %c\n", last_letter("upon time...."), last_letter("$_a_b_c_d_1_2_3_4$"), last_letter("123456789"), last_letter("123456789 zZ 88"));
	printf("%d %d %d %d\n", longest("upon time...."), longest("$dickman aha dickyman$"), longest("nasrac na novo"), longest("la la laaaa"));
	getch();
}

char last_letter(const char string[])
{
	int i = 0;
	char lastchar = '?';
	
	while(string[i]!='\0')
	{
		if( (string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
		{
			lastchar = string[i];
		}
		i++;
	}
	
	return lastchar;
}

int longest(const char string[]){
    int i = 0;
    int max_dlzka = 0;
    int dlzka = 0;
    if(string[i]!='\0'){
    while(string[i]!='\0')
	{
		if( (string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
		{
			dlzka++;
		}
		else{
                    if(dlzka > max_dlzka)
                             max_dlzka = dlzka;
                    dlzka = 0;
             }
		i++;
	}
	if( (string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
		{
			dlzka++;
		}
		else{
                    if(dlzka > max_dlzka)
                             max_dlzka = dlzka;
                    dlzka = 0;
             }
	return max_dlzka;
}
}
