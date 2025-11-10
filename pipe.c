#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 100  

int main() {
    int fd[2]; 
    pid_t pid;
    char message[MAX];
    char buffer[MAX];


    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid > 0) {  
        close(fd[0]); 
        printf("Enter a message to send to child: ");
        fgets(message, MAX, stdin);
        write(fd[1], message, MAX);
        close(fd[1]);
        wait(NULL);
        printf("Parent: Child process finished.\n");
    } else {  
        close(fd[1]); 
        read(fd[0], buffer, MAX);
        close(fd[0]);
        printf("Child received: %s\n", buffer);
        exit(0);
    }
    return 0;
}