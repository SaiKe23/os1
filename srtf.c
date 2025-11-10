//ass4
#include <stdio.h>
#include <limits.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int isCompleted;
};

int main() {
    int n;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].isCompleted = 0;
    }

    int completed = 0, currentTime = 0;
    int prev = -2;

    int ganttProcesses[1000];
    int ganttTimes[1001];
    int ganttIndex = 0;

    ganttTimes[0] = 0; // starting time

    while (completed < n) {
        int idx = -1;
        int minRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].isCompleted == 0 && p[i].remainingTime < minRemaining && p[i].remainingTime > 0) {
                minRemaining = p[i].remainingTime;
                idx = i;
            }
        }

        if (idx != -1) {
            if (prev != idx) {
                ganttProcesses[ganttIndex] = idx;
                ganttTimes[ganttIndex] = currentTime;
                ganttIndex++;
                prev = idx;
            }

            p[idx].remainingTime--;
            currentTime++;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnAroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnAroundTime - p[idx].burstTime;

                totalTAT += p[idx].turnAroundTime;
                totalWT += p[idx].waitingTime;

                p[idx].isCompleted = 1;
                completed++;
            }
        } else {
            if (prev != -1) {
                ganttProcesses[ganttIndex] = -1; // idle
                ganttTimes[ganttIndex] = currentTime;
                ganttIndex++;
                prev = -1;
            }
            currentTime++;
        }
    }

    ganttTimes[ganttIndex] = currentTime;

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < ganttIndex; i++) {
        if (ganttProcesses[i] == -1)
            printf("  IDLE  |");
        else
            printf("  P%d  |", p[ganttProcesses[i]].id);
    }
    printf("\n");

    for (int i = 0; i <= ganttIndex; i++) {
        printf("%-7d", ganttTimes[i]);
    }
    printf("\n\n");

    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    return 0;
}