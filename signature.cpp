#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

int x = 7, y = 13, n, t, i, flag;
long int e[50], d[50], temp[50], j, m[50], en[50];
char msg[100];
int prime(long int);
void encryption_key();
long int cd(long int);
void encrypt();
void decrypt();


int gcd(int a, int h)
{
    int temp;
    while(1)
    {
        temp = a%h;
        if(temp==0)
            return h;
        a = h;
        h = temp;
    }
}

int rsa1(){
        //2 random prime numbers
        double p = 3;
        double q = 7;
        double n=p*q;
        double count;
        double totient = (p-1)*(q-1);

        //public key
        //e stands for encrypt
        double e=2;

        //for checking co-prime which satisfies e>1
        while(e<totient){
            count = gcd(e,totient);
            if(count==1)
                break;
            else
                e++;
        }

        //private key
        //d stands for decrypt
        double d;

        //k can be any arbitrary value
        double k = 2;

        //choosing d such that it satisfies d*e = 1 + k * totient
        d = (1 + (k*totient))/e;
        double msg = 12;
        double c = pow(msg,e);
        double m = pow(c,d);
        c=fmod(c,n);
        m=fmod(m,n);

        printf("Message data = %lf",msg);
        printf("\np = %lf",p);
        printf("\nq = %lf",q);
        printf("\nn = pq = %lf",n);
        printf("\ntotient = %lf",totient);
        printf("\ne = %lf",e);
        printf("\nd = %lf",d);
        printf("\nEncrypted data = %lf",c);
        printf("\nOriginal Message Sent = %lf",m);

        return 0;
}

unsigned long long int rsaEncrypt(unsigned long message, double e, double n){
    unsigned long long int c = pow(message,e);
    printf("%llu \n", c);
    printf("%lf %lf \n", e, n);
    c=fmod(c,n);
    return c;
}

unsigned long rsaDecrypt(unsigned long long int message, double d, double n){
    unsigned long c = pow(message,d);
    c=fmod(c,n);
    return c;
}

double publicKey(){

}

double privateKey(){

}

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main() {
    printf("Enter file name: ");
    char * buffer = 0;
    long length;
    char filename[20];
    unsigned long hashCode;
    scanf("%s", filename);
    printf("%s\n", filename);
    FILE * f = fopen (filename, "r");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
            printf("Content of file: %s\n", buffer);
        }
        fclose (f);
    }
    char* str;
    if (buffer)
    {
        hashCode = hash(buffer);
        printf("Hash is: %lu\n", hashCode);
        int l = snprintf( NULL, 0, "%lu", hashCode );
        str = malloc( l + 1 );
        snprintf( str, l + 1, "%lu", hashCode );
        printf("Hash in string: %s\n", str);
    }

    fclose(f);
    flag = prime(x);
    flag = prime(y);
    for(i = 0; str[i] != NULL; i++) {
        msg[i] = str[i];
        m[i] = str[i];
    }
    n = x * y;
    t = (x-1) * (y-1);
    encryption_key();
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
    for(i = 0; i < j-1; i++)
        printf("\n%ld\t%ld", e[i], d[i]);
    encrypt();
    decrypt();
    return 0;
}

int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for(i = 2; i <= j; i++)
    {
        if(pr % i == 0)
            return 0;
    }
    return 1;
}

//function to generate encryption key
void encryption_key()
{
    int k;
    k = 0;
    for(i = 2; i < t; i++)
    {
        if(t % i == 0)
            continue;
        flag = prime(i);
        if(flag == 1 && i != x && i != y)
        {
            e[k] = i;
            flag = cd(e[k]);
            if(flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if(k == 99)
                break;
        }
    }
}
long int cd(long int a)
{
    long int k = 1;
    while(1)
    {
        k = k + t;
        if(k % a == 0)
            return(k / a);
    }
}

//function to encrypt the message
void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while(i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for(j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    printf("\n\nTHE ENCRYPTED MESSAGE IS\n");
    for(i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
    FILE * fPtr;


    /*
     * Open file in w (write) mode.
     * "data/file1.txt" is complete path to create file
     */
    fPtr = fopen("podpis.txt", "w");


    /* fopen() return NULL if last operation was unsuccessful */
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }


    /* Input contents from user to store in file */


    /* Write data to file */
    for(i = 0; en[i] != -1; i++)
        fprintf(fPtr,"%c", en[i]);


    /* Close file to save file data */
    fclose(fPtr);
}

//function to decrypt the message
void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while(en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for(j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    printf("\n\nTHE DECRYPTED MESSAGE IS\n");
    for(i = 0; m[i] != -1; i++)
        printf("%c", m[i]);
    printf("\n");
}
