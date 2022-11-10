#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

void getPIN(char pin[PIN_LENGTH+1]) 
{
    srand(getpid() + getppid());
    
    pin[0] = 49 + rand() % 7;
    for (int m = 1; m<PIN_LENGTH; m++) 
    {
    pin[m] = 48 + rand() % 7;
    }
    pin[PIN_LENGTH] = '\0';
}

void sigint_handler (int sig)
{
    printf("\n Sorry, seems like it is interrupted. ");
    exit(1);
}

int main(void) 
{
    char firstname[50];
    signal(SIGINT,sigint_handler);
        int pipefds[2];
        char pin[PIN_LENGTH + 1];
        char buffer[PIN_LENGTH + 1];
        
        pipe(pipefds);
        pid_t pid=fork();
        
        if (pid==0)
        {
            close(pipefds[1]);
            read(pipefds[0],firstname,50);
            printf("\nYour first name is %s",firstname); //child process
            close(pipefds[0]);
        }
        if (pid>0) 
        {
            printf("Enter your first name:\n"); //parent process
            scanf("%s", firstname);
            write(pipefds[1],firstname,50);
            close(pipefds[1]);
            wait(NULL);
        }
    return EXIT_SUCCESS;
}
