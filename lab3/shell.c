#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define TOKEN_DELIMETERS " \t\r\n\a"
#define DEFAULT_SIZE 1024

char *history[DEFAULT_SIZE];
char *argv[DEFAULT_SIZE];
int hist_count = 0;
int hist_num = 0;
int position = 0;
short isHistNum = 0;

void readLine(char *line)
{
    if(isHistNum)
    {
        line = memcpy(line,history[hist_num-1],DEFAULT_SIZE);
                printf("\n");
        }
        else
    {
                gets(line);
        }
        isHistNum = 0;
        memcpy(history[hist_count],line,DEFAULT_SIZE);
        hist_count++;
}

void parseLine(char *line, char *argv[])
{
    char *token;
    position = 0;
        token = strtok(line,TOKEN_DELIMETERS);
        while(token!=NULL)
    {
            argv[position] = token;
        position++;
            token =strtok(NULL,TOKEN_DELIMETERS);
        }
}

int nat_history(char *argv[])
{
    if(position==2){
                hist_num = atoi(argv[1]);
                for(int k = 1; k<=hist_count;k++){
                    if(hist_num == k){
                        isHistNum = 1;
            }
        }
        }
        if(isHistNum==0){
                for(int i =0; i <hist_count;i++)
                        printf(" %d %s\n",(i+1),history[i]);
    }
    return 1;
}

void execute(char *argv[])
{
    // Check if command is valid as a native command
    char quit[10];    strcpy(quit, "exit");
    char hist[10];    strcpy(hist, "history");
   
    char help[10];    strcpy(help, "help");
    char cd[10];    strcpy(cd, "cd");

    if(strcmp(argv[0], quit) == 0)
    {
        exit(0);
    }
    else if(strcmp(argv[0], hist) == 0)
    {
        nat_history(argv);
    }
    else if(strcmp(argv[0], help) == 0)
    {
        printf("\nexit\t\tclose CLI\ncd\t\tchange dir\nhistory\t\tlist executed commands\n\n");
    }
    else if(strcmp(argv[0], cd) == 0)
    {
        chdir(argv[1]);
    }
        //Native commands
    else
    {
        //Execute any other command. Uses child process.
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed");
            exit(-1);
        }
        else if (pid == 0) {
            execlp(argv[0], argv, NULL);
            exit(0);
        }
        else {
            pid = wait(NULL);
        }
    }
}


int main()
{
    int valid = 0;
    char *line = (char*)malloc(DEFAULT_SIZE);
    for(int i = 0; i < DEFAULT_SIZE; i++)
        history[i] = (char*)malloc(DEFAULT_SIZE);
    long size;
    char *buf;
    char *ptr;
    while(1)
    {
        printf("Shell->"); // Show imput
        readLine(line); // Read input line
        parseLine(line,argv); // Parse input to a string array
        execute(argv); // Execute command using a exec's family function
        for(int j = 0; j < DEFAULT_SIZE; j++)
            argv[j] = NULL;
    }
}
