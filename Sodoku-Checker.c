#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int row;
    int col;
    int (* grid)[9];
} PARMS;

void * rows(void * params);
void * cols(void * params);
void * square(void * params);

int main(void)
{
    /*Test case
    int grid[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };*/
    // Input
    int grid[9][9];
    char input[82];
    printf ("\n\nPlease input all numbers from left to right, top to bottom, \nwith no spaces or delimiters: \n");
    for(int i=0;i<9;i++){
        printf("---+++===");
    }
    printf("\n");
    fgets (input, 82, stdin);
    int k=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            grid[i][j]=input[k]-'0';
            k++;
        }
    }
    // Print grid
    printf("\n\nProposed Solution:\n");
    printf("-------------------");
    for(int i=0;i<9;i++){
        printf("\n|");
        for(int j=0;j<9;j++){
            if((j+1)%3!=0){
                printf("%d ",grid[i][j]);
            }
            else{
                printf("%d|",grid[i][j]);
            }
        }
        if((i+1)%3==0){
             printf("\n-------------------");
        }
    }
    printf("\n\n");
    
    // Rows - thread0
    PARMS * Data0 = (PARMS *) malloc(sizeof(PARMS));
    Data0->row = 0;
    Data0->col = 0;
    Data0->grid = grid;
    
    // Top left - thread1
    PARMS * Data1 = (PARMS *) malloc(sizeof(PARMS));
    Data1->row = 0;
    Data1->col = 0;
    Data1->grid = grid;
    
    // Top middle - thread2
    PARMS * Data2 = (PARMS *) malloc(sizeof(PARMS));
    Data2->row = 0;
    Data2->col = 3;
    Data2->grid = grid;
    
    // Top right - thread3
    PARMS * Data3 = (PARMS *) malloc(sizeof(PARMS));
    Data3->row = 0;
    Data3->col = 6;
    Data3->grid = grid;
    
    // Middle left - thread4
    PARMS * Data4 = (PARMS *) malloc(sizeof(PARMS));
    Data4->row = 3;
    Data4->col = 0;
    Data4->grid = grid;
    
    // Center - thread5
    PARMS * Data5 = (PARMS *) malloc(sizeof(PARMS));
    Data5->row = 3;
    Data5->col = 3;
    Data5->grid = grid;
    
    // Middle right - thread6
    PARMS * Data6 = (PARMS *) malloc(sizeof(PARMS));
    Data6->row = 3;
    Data6->col = 6;
    Data6->grid = grid;
    
    // Bottom left - thread7
    PARMS * Data7 = (PARMS *) malloc(sizeof(PARMS));
    Data7->row = 6;
    Data7->col = 0;
    Data7->grid = grid;
    
    // Bottom middle - thread8
    PARMS * Data8 = (PARMS *) malloc(sizeof(PARMS));
    Data8->row = 6;
    Data8->col = 3;
    Data8->grid = grid;
    
    // Bottom right - thread9
    PARMS * Data9 = (PARMS *) malloc(sizeof(PARMS));
    Data9->row = 6;
    Data9->col = 6;
    Data9->grid = grid;
    
    // Columns - thread10
    PARMS * Data10 = (PARMS *) malloc(sizeof(PARMS));
    Data10->row = 0;
    Data10->col = 0;
    Data10->grid = grid;
    
    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9, thread10;
    
    void * result[11];

    // Initialize threads
    pthread_create(&thread0, NULL, rows, (void *) Data0);
    pthread_create(&thread1, NULL, square, (void *) Data1);
    pthread_create(&thread2, NULL, square, (void *) Data2);
    pthread_create(&thread3, NULL, square, (void *) Data3);
    pthread_create(&thread4, NULL, square, (void *) Data4);
    pthread_create(&thread5, NULL, square, (void *) Data5);
    pthread_create(&thread6, NULL, square, (void *) Data6);
    pthread_create(&thread7, NULL, square, (void *) Data7);
    pthread_create(&thread8, NULL, square, (void *) Data8);
    pthread_create(&thread9, NULL, square, (void *) Data9);
    pthread_create(&thread10, NULL, cols, (void *) Data10);
    
    // Threads completed, store results
    pthread_join(thread0, &result[0]);
    pthread_join(thread1, &result[1]);
    pthread_join(thread2, &result[2]);
    pthread_join(thread3, &result[3]);
    pthread_join(thread4, &result[4]);
    pthread_join(thread5, &result[5]);
    pthread_join(thread6, &result[6]);
    pthread_join(thread7, &result[7]);
    pthread_join(thread8, &result[8]);
    pthread_join(thread9, &result[9]);
    pthread_join(thread10, &result[10]);
    
    // Check results
    for(int i=0;i<11;i++){
        if((int)result[i]!=1){
            printf("The proposed solution to the sodoku puzzle is invalid.\n\n");
            return(0);
        }
    }
    printf("The proposed solution to the sodoku puzzle is valid!\n\n");
    return 0;
}

void * rows(void * input) {
    PARMS * data = (PARMS *) input;
    int row = data->row;
    int col = data->col;
    int val;
    for (int i = row; i<9; i++) {
        int flags[10] = {0};
        for (int j = col; j < 9; j++) {
            val = data->grid[i][j];
            if (flags[val] != 0) {
                return (void *) 0;
            }
            else{
                flags[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * cols(void * input) {
    PARMS * data = (PARMS *) input;
    int row = data->row;
    int col = data->col;
    int val;
    for (int i = col; i<9; i++) {
        int flags[10] = {0};
        for (int j = row;j<9; j++) {
            val = data->grid[j][i];
            if (flags[val] != 0) {
                return (void *) 0;
            }
            else{
                flags[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * square(void * input) {
    PARMS * data = (PARMS *) input;
    int row = data->row;
    int col = data->col;
    int val;
    int flags[10] = {0};
    for (int i = row; i < row + 3; i++) {
        for (int j=col;j<col+3;j++) {
            val = data->grid[i][j];
            if (flags[val] != 0) {
                return (void *) 0;
            }
            else{
                flags[val] = 1;
            }
        }
    }
    return (void *) 1;
}
