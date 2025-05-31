#include<stdio.h>
#include<stdlib.h>

int main(){
    int i, j, noFrames, x, x1 = 10, x2;
    for(i=0; i<200; i++){
        rand();
    }
    noFrames = rand()%200;
    i=1, j =1;
    noFrames = noFrames/8;
    if (noFrames == 0) noFrames = 1; // Ensure at least 1 frame
    printf("Number of frames: %d\n", noFrames);
    while(noFrames > 0){
        printf("\nSending frame %d\n",i);
        srand(x1++);
        x = rand()%10;
        if(x%2 == 0){
            for(x2 = 1; x2<2; x2++){
                printf("Waiting for %d second\n", x2);
            }
            printf("\nSending frame %d", i);
            srand(x1++);
            x = rand()%10;
        }
        printf("\nACK for frame %d", j);
        noFrames--;
        i++;
        j++;
    }
    printf("\n End of Stop and Wait protocol.");
    return 0;
}