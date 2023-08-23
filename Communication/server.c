#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <math.h>
#define MAX 20000
#define PORT 8080
#define SA struct sockaddr

int P = 0;
int G = 0;
int private = 0;
long int public = 0;
long int key = 0;
int run = 1;


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
    if(b%2 == 0)
        return (num % P);
    else
        return (((num % P) * a) % P);
}

// Function designed for chat between client and server.
void func(int connfd)
{
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
        
        char* decrypted = (char*)calloc((strlen(buff)) + 1, sizeof(char));
        char *text = buff;
        decrypted = decrypt(text);
        printf("Client: %s\n", decrypted);
        if (strncmp("exit", decrypted, 4) == 0) {
			printf("Client Exit...\n");
			break;
		}
        free(decrypted);
		
        bzero(buff, MAX);
		n = 0;
        printf("Enter the string : ");
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
			;

		// and send that buffer to client
        char* encrypted = (char*)calloc((strlen(buff)) + 1, sizeof(char));
        *text = buff;
        encrypted = encrypt(text);
		write(connfd, encrypted, sizeof(buff));
        free(encrypted);
		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
            run = 0;
			break;
		}
	}
}

void first(int connfd)
{
	char buff[MAX];
        bzero(buff, MAX); 
        sprintf(buff,"%d", P);  
        write(connfd, buff, sizeof(buff));  
        bzero(buff, MAX);
        sprintf(buff,"%d\n", G);
        write(connfd, buff, sizeof(buff));
        bzero(buff, MAX);
        sprintf(buff,"%ld\n", public);
        write(connfd, buff, sizeof(buff));
        bzero(buff, MAX);
		read(connfd, buff, sizeof(buff));

        long int ans = atoi(buff);
        key = power(ans, private, P);
        printf("Server key: %ld\n", key);
		bzero(buff, MAX);
}



// Driver function
int main()
{
	int sockfd, connfd, len;
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
    while(run){
        time_t t;
        srand((unsigned) time(&t));
        P = rand();
        printf("Server P int: %d\n", P);
        G = rand();
        printf("Server G int: %d\n", G);
        private = rand();
        public = power(G, private, P);
        if ((listen(sockfd, 5)) != 0) {
            printf("Listen failed...\n");
            exit(0);
        }
        else
            printf("Server listening..\n");
        len = sizeof(cli);

        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
            printf("server accept failed...\n");
            exit(0);
        }
        else
            printf("server accept the client...\n");

        first(connfd);

        // Function for chatting between client and server
        func(connfd);

        }
        // After chatting close the socket
        close(sockfd);
}

