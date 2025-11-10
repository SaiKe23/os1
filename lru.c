#include <stdio.h>

void lruPaging(int frames, int references[], int n) {
    int memory[frames];       
    int time[frames];        
    int page_faults = 0;
    int i, j;

    
    for (i = 0; i < frames; i++) {
        memory[i] = -1;
        time[i] = 0;
    }

    printf("Ref\tFrames\t\tFault\n");

    for (i = 0; i < n; i++) {
        int page = references[i];
        int fault = 1; 
        int lru_index = 0;
        int min_time = time[0];

       
        for (j = 0; j < frames; j++) {
            if (memory[j] == page) {
                fault = 0;  
                time[j] = i + 1;
                break;
            }
        }

        
        if (fault) {
            page_faults++;

           
            for (j = 1; j < frames; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }

           
            memory[lru_index] = page;
            time[lru_index] = i + 1;
        }

       
        printf("%d\t", page);

        
        for (j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }

        
        if (fault)
            printf("\tYes\n");
        else
            printf("\tNo\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int frames, n, i;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of page references: ");
    scanf("%d", &n);

    int references[n];
    printf("Enter page reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &references[i]);
    }

    lruPaging(frames, references, n);

    return 0;
}