#include <stdio.h>

void fifoPaging(int frames, int references[], int n) {
    int memory[frames];  
    int page_faults = 0;
    int i, j;
    int index = 0; 
    
    
    for (i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    printf("Ref\tFrames\t\tFault\n");

    for (i = 0; i < n; i++) {
        int page = references[i];
        int fault = 1; 

       
        for (j = 0; j < frames; j++) {
            if (memory[j] == page) {
                fault = 0; 
                break;
            }
        }

        if (fault) {
            page_faults++;

            
            memory[index] = page;
            index = (index + 1) % frames;  
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

    fifoPaging(frames, references, n);

    return 0;
}