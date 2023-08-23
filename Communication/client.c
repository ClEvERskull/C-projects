#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <math.h>
#define MAX 20000
#define PORT 8080
#define SA struct sockaddr

int P = 0;
int G = 0;
int private = 0;
long int public = 0;
long int key = 0;


char* encrypt(const char* text){
    if(text == 0 || key == 0)
    	return 0;
    int shift = key % 76;
    size_t n = strlen(text);
    char cipher[n];
    for(int i = 0; i < n; i++){
        if(text[i] > 47 && text[i] < 123){
            if((text[i] + shift) > 123){
               cipher[i] = 47 + ((text[i] + shift) - 123);
            }
            else
                cipher[i] = text[i] + shift;
        }
        else
            cipher[i] = text[i];
    }


    char* encrypted = (char*)calloc(n + 1, sizeof(char));
	
	for(int i = 0; i < n; i++){
		encrypted[i] = cipher[i];
	}
	return encrypted;

}
char* decrypt(const char* text){
    if(text == 0 || key == 0)
    	return 0;

    int shift = key % 76;
    size_t n = strlen(text);
    char cipher[n];
    for(int i = 0; i < n; i++){
        if(text[i] > 47 && text[i] < 123){
            if((text[i] - shift) < 47){
               cipher[i] = 123 - (47 - (text[i] - shift));
            }
            else
                cipher[i] = text[i] - shift;
        }
        else
            cipher[i] = text[i];
    }

    char* decrypted = (char*)calloc(n + 1, sizeof(char));
	
	for(int i = 0; i < n; i++){
		decrypted[i] = cipher[i];
	}
	return decrypted;

}


long int power(long int a, int b, int P)
{
    if (b == 1)
        return a;
    long long int num;
    num = power(a, b/2, P);
    if((b % 2) == 0)
        return (num % P);
    else
        return (((num % P) * a) % P);
}

void first(int sockfd)
{
    time_t t;
    srand((unsigned) time(&t));
    char buff[MAX];
    bzero(buff, sizeof(buff));  
    read(sockfd, buff, sizeof(buff));   
    P = atoi(buff); 
    printf("Client P: %s\n", buff); 
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("Client G: %s\n", buff);
    G = atoi(buff);
    public = power(G, private, P);
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    long int ans = atoi(buff);
    key = power(ans, private, P);
    printf("Client key: %ld\n", key);
    bzero(buff, sizeof(buff));
    sprintf(buff,"%ld", public);
    write(sockfd, buff, sizeof(buff));
}

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        
        while ((buff[n++] = getchar()) != '\n')
            ;
        char *text = buff;
        char* encrypted = (char*)calloc((strlen(buff)) + 1, sizeof(char));
        encrypted = encrypt(text);
        write(sockfd, encrypted, sizeof(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
        free(encrypted);
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        char* decrypted = (char*)calloc((strlen(buff)) + 1, sizeof(char));
        *text = buff;
        decrypted = decrypt(text);
        printf("Server: %s\n", decrypted);
        if ((strncmp(decrypted, "exit", 4)) == 0) {
            printf("Server Exit...\n");
            break;
        }
        free(decrypted);
    }
}
 
int main()
{
    private = rand();
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
 
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
 
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
 
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))
        != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
 
    first(sockfd);
    
    // function for chat
    func(sockfd);
 
    // close the socket
    close(sockfd);
}