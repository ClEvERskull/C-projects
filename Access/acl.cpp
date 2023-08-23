#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE_LENGTH 80
#define BUFFER_SIZE 1000


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void permissions(char *filename)
{
    struct stat fs;
    int r;
    //printf("Obtaining permission mode for '%s':\n",filename);
    r = stat(filename,&fs);
    if( r==-1 )
    {
        fprintf(stderr,"File error\n");
        exit;
    }

    /* file permissions are kept in the st_mode member */
    printf("Permission bits: %X\n",fs.st_mode);

    return;
}

int getPermission(char* name){
    char *path;
    int level = 0;
    char line[MAX_LINE_LENGTH] = {0};
    
    path = "users.txt";
    
    /* Open file */
    FILE *file = fopen(path, "r");
    
    if (!file)
    {
        perror(path);
    }
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        char* token = strtok(line, " ");

        if(strcmp(name, token) == 0){
            char name_file[20];
            char token_list[20][20];
            int num_tokens = 0; // Index to token list. We will append to the list
            
            while (token != NULL) {
                strcpy(token_list[num_tokens], token); // Copy to token list
                num_tokens++;
                token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
            }

            int permissions = atoi(token_list[3]);
            return permissions;
        }
    }
    fclose(file);
    return 0;
}

int login(char* name, char* password){
    char *path;
    int level = 0;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;
    
    path = "users.txt";
    
    /* Open file */
    FILE *file = fopen(path, "r");
    
    if (!file)
    {
        perror(path);
        return EXIT_FAILURE;
    }
    
    /* Get each line until there are none left */
    while (fgets(line, MAX_LINE_LENGTH, file))
    {

        char name_file[20];
        char password_file[20];
        char token_list[20][20];
        char* token = strtok(line, " ");
        int num_tokens = 0; // Index to token list. We will append to the list
        
        while (token != NULL) {
            strcpy(token_list[num_tokens], token); // Copy to token list
            num_tokens++;
            token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
        }

        strcpy(name_file, token_list[0]);
        strcpy(password_file, token_list[1]);

        if(strcmp(name, name_file) == 0){
            printf("found name match\n");
            char* str;
            size_t len;
            int l = snprintf( NULL, 0, "%lu", hash(password) );
            str = malloc( l + 1 );
            snprintf( str, l + 1, "%lu", hash(password) );
            if(strcmp(str, password_file) == 0){
                level = atoi(token_list[2]);
                printf("success!\n");
            }
            else{
                printf("fuck you %sko!!!\n", name);
            }
        }
        
        /* Add a trailing newline to lines that don't already have one */
        if (line[strlen(line) - 1] != '\n')
            printf("\n");
    }
    fclose(file);
    
    return level;
}

void content(int clearance){
    char *path;
    struct dirent *de;  // Pointer for directory entry
    struct stat fs;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_count = 0;
    
    path = "content.txt";
    FILE *fp = fopen(path, "a+");

    DIR *dr = opendir(".");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }
    int i = 0;
    
    while ((de = readdir(dr)) != NULL){
        int exists = 0;
        if(i > 1)
        { 
            char str[255];
            char num[10];
            fseek(fp, 0, SEEK_SET);
            while (fgets(line, MAX_LINE_LENGTH, fp))
            {
                char token_list[20][20];
                char* token = strtok(line, " ");
                int num_tokens = 0; // Index to token list. We will append to the list
                
                while (token != NULL) {
                    strcpy(token_list[num_tokens], token); // Copy to token list
                    num_tokens++;
                    token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
                }
                if(strcmp(de->d_name, token_list[0]) == 0){
                    exists = 1;
                    break;
                }
            }
            //printf("%s with security level: %d\n", de->d_name, clearance);
            if(exists == 0){
                sprintf(num, "%d", clearance);
                strcpy(str, de->d_name);
                strcat(str, " ");
                strcat(str, num);
                strcat(str, "\n");
                fputs(str, fp);
            }
        }
        i++;
    }
    fclose(fp);
    closedir(dr);
}

void showFiles(int clearance){
    content(clearance);
    char *path;
    char line[MAX_LINE_LENGTH] = {0};
    path = "content.txt";
    FILE *fp = fopen(path, "r");
    while (fgets(line, MAX_LINE_LENGTH, fp)){
        printf("%s\n", line);
    }
    fclose(fp);
}

void showUsers(){
    char *path;
    char line[MAX_LINE_LENGTH] = {0};
    path = "users.txt";
    FILE *fp = fopen(path, "r");
    while (fgets(line, MAX_LINE_LENGTH, fp)){
        char str[255];
        char token_list[20][20];
        char* token = strtok(line, " ");
        int num_tokens = 0; // Index to token list. We will append to the list
                
        while (token != NULL) {
            strcpy(token_list[num_tokens], token); // Copy to token list
            num_tokens++;
            token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
        }
        int permissions = atoi(token_list[3]);
        if(permissions == 1)
            printf("name: %s, permissions: r and level: %s\n", token_list[0], token_list[2]);
        else if(permissions == 2)
            printf("name: %s, permissions: w and level: %s\n", token_list[0], token_list[2]);
        else
            printf("name: %s, permissions: rw and level: %s\n", token_list[0], token_list[2]);
    }
    fclose(fp);
}

void work(char* name, char* mode, int level, int permissions){
    char *path;
    char line[MAX_LINE_LENGTH] = {0};
    path = "content.txt";
    FILE *fp = fopen(path, "r");
    while (fgets(line, MAX_LINE_LENGTH, fp)){
        char str[255];
        char token_list[20][20];
        char* token = strtok(line, " ");
        int num_tokens = 0; // Index to token list. We will append to the list
        if(strcmp(name, token) == 0){
            while (token != NULL) {
                strcpy(token_list[num_tokens], token); // Copy to token list
                num_tokens++;
                token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
            }
            int permission = atoi(token_list[1]);
            if (strcmp(mode, "read") == 0) 
            {
                if(((level >= permission) && (permissions == 1)) || ((level == permission) && (permissions == 3))){
                    printf("OK\n");
                }
                else{
                    printf("PERMISION ERROR\n");
                }
                fclose(fp);
                return;
            } 
            else if (strcmp(mode, "write") == 0)
            {
                if(((level <= permission) && (permissions == 2)) || ((level == permission) && (permissions == 3))){
                    printf("OK\n");
                }
                else{
                    printf("PERMISION ERROR\n");
                }
                fclose(fp);
                return;
            }
        }
    }
    fclose(fp);
}

void showHelp(){
    printf("change - will change security level (only admin)\n");
    printf("files - will show all files and their level\n");
    printf("help - will show all possible commands\n");
    printf("logout - logout current user\n");
    printf("read - will try to read file with as logged user\n");
    printf("users - will show list of users and their clearance level\n");
    printf("write - will try to write into file as logged user\n");
    printf("quit - will exit application\n");
}

void deleteLine(FILE *src, FILE *temp, const int line){
   char buffer[BUFFER_SIZE];
   int count = 1;
   while ((fgets(buffer, BUFFER_SIZE, src)) != NULL){
      if (line != count)
         fputs(buffer, temp);
      count++;
   }
}



void changeSecurity(char* name, int level){
    char num[10];
    sprintf(num, "%d", level);
    char *path;
    char line[MAX_LINE_LENGTH] = {0};
    unsigned int i = 1;
    char str[255];
    char hash[100];
    char permissions[10];
    
    path = "users.txt";
    FILE *file = fopen(path, "r");
    FILE *temp;
    
    if (!file)
    {
        perror(path);
        return;
    }
    while (fgets(line, MAX_LINE_LENGTH, file))
    {
        char* token = strtok(line, " ");
        if(strcmp(name, token) == 0){
            printf("found name match\n");
            char token_list[20][20];
            int num_tokens = 0; // Index to token list. We will append to the list
                
            while (token != NULL) {
                strcpy(token_list[num_tokens], token); // Copy to token list
                num_tokens++;
                token = strtok(NULL, " "); // Get the next token. Notice that input=NULL now!
            }
            strcpy(hash, token_list[1]);
            strcpy(permissions, token_list[3]);
            rewind(file);
            temp = fopen("delete.tmp", "w");
            deleteLine(file, temp, i);
            fclose(file);
            fclose(temp);
            remove(path);
            rename("delete.tmp", path);
        }
        i++;
    }
    fclose(file);

    file = fopen(path, "a+");
    strcpy(str, name);
    strcat(str, " ");
    strcat(str, hash);
    strcat(str, " ");
    strcat(str, num);
    strcat(str, " ");
    strcat(str, permissions);
    strcat(str, "\n");
    fputs(str, file);
    fclose(file);
}



int main()
{
    system("clear");  
    printf("Enter your name: ");
    char name[20];
    scanf("%s", name);
    printf("Enter password: ");
    char password[20];
    scanf("%s", password);

    int level = login(name, password);
    int permissions = getPermission(name);

    if(level == 0){
        printf("Wrong input\n");
        return 0;
    }
    system("clear");  
    while(1){
        printf("Enter command: \n");
        char cmd[20];
        scanf("%s", cmd);
        
        if (strcmp(cmd, "read") == 0){
            printf("Enter name of file: \n");
            scanf("%s", name);
            work(name, "read", level, permissions);
        } 
        else if (strcmp(cmd, "write") == 0){
            printf("Enter name of file: \n");
            scanf("%s", name);
            work(name, "write", level, permissions);
        }
        else if (strcmp(cmd, "change") == 0){
            if(level >= 3){
                printf("Enter name: \n");
                scanf("%s", name);
                printf("Enter new security level: \n");
                int clearance;
                scanf("%d", &clearance);
                changeSecurity(name, clearance);
            }
            else{
                printf("Not admin rights!\n");
            }
        }
        else if (strcmp(cmd, "files") == 0){
            showFiles(level);
        }
        else if (strcmp(cmd, "users") == 0){
            showUsers();
        }
        else if (strcmp(cmd, "help") == 0){
            showHelp();
        }
        else if (strcmp(cmd, "quit") == 0){
            break;
        }
        else if (strcmp(cmd, "logout") == 0){
            system("clear");  
            printf("Enter your name: ");
            scanf("%s", name);
            printf("Enter password: ");
            scanf("%s", password);

            level = login(name, password);
            permissions = getPermission(name);

            if(level == 0){
                printf("Wrong input\n");
                return 0;
            }
            system("clear");
        }
        else{
            printf("don't know what you meant\n");
        } 
    }
    return 0;
}