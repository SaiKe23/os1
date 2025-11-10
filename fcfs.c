// ASS3
#include <stdio.h>

struct Process 
{
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
};

void sortByArrivalTime(struct Process p[], int n) 
{
    struct Process temp;
    for (int i = 0; i < n-1; i++) 
    {
        for (int j = i+1; j < n; j++) 
        {
            if (p[i].arrivalTime > p[j].arrivalTime) 
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() 
{
    int n;
    float totalTAT = 0, totalWT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) 
    {
        p[i].id = i + 1;
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
    }

    sortByArrivalTime(p, n);

    int currentTime = 0;
    for (int i = 0; i < n; i++) 
    {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;

        p[i].completionTime = currentTime + p[i].burstTime;
        currentTime = p[i].completionTime;

        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;

        totalTAT += p[i].turnAroundTime;
        totalWT += p[i].waitingTime;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);

    printf("\nGant Chart of the Processes :\n|");
    for (int i = 0; i < n; i++) 
    {
        printf("  P%d  |", p[i].id);
    }
    printf("\n");
    
    printf("%d", p[0].arrivalTime > 0 ? p[0].arrivalTime : 0);
    currentTime = (p[0].arrivalTime > 0) ? p[0].arrivalTime : 0;
    for (int i = 0; i < n; i++) 
    {
        if (currentTime < p[i].arrivalTime)
            currentTime = p[i].arrivalTime;

        currentTime += p[i].burstTime;
        printf("     %d", currentTime);
    }

    printf("\n");
    return 0;
}
