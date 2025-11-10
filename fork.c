#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// ----------------------------
// Program 1: Fork Sorting Demo
// ----------------------------

void sortAscending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortDescending(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortingProcess() {
    printf("\n==== Fork Program: Ascending & Descending Sorting ====\n");

    int arr[] = {5, 2, 8, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    }
    else if (pid == 0) {
        printf("\nChild process: Sorting in Descending Order\n");
        sortDescending(arr, n);
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
    else {
        wait(NULL);
        printf("\nParent process: Sorting in Ascending Order\n");
        sortAscending(arr, n);
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
}


// ----------------------------
// Program 2: Zombie Process
// ----------------------------
void zombieProcess() {
    printf("\n==== Zombie Process Demonstration ====\n");

    pid_t pid;
    if((pid=fork()) < 0)
        printf("\tfork error\n");
    else
    if(pid==0)
        printf("child process id is %d\n",getpid());
    else {
        sleep(10);
        printf("*****parent\n");
        system("ps -axj | tail");
    }
    exit(0);
}


// ----------------------------
// Program 3: Orphan Process
// ----------------------------
void orphanProcess() {
    printf("\n==== Orphan Process Demonstration ====\n");

    int pid = fork();
    if (pid > 0){
        printf("parent process id%d\n", getpid());
        printf("child process id %d\n", pid);
    }
    else if (pid == 0) {
        sleep(10);
        printf("child process id %d\n", getpid());
        printf("parent process id %d\n", getppid());
    }
}


// ----------------------------
// Main Menu with Switch Case
// ----------------------------
int main() {
    int choice;
    printf("\n===== PROCESS DEMONSTRATION MENU =====");
    printf("\n1. Sorting using Fork");
    printf("\n2. Zombie Process");
    printf("\n3. Orphan Process\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice) {
        case 1: sortingProcess(); break;
        case 2: zombieProcess(); break;
        case 3: orphanProcess(); break;
        default: printf("\nInvalid Choice!\n");
    }

    return 0;
}