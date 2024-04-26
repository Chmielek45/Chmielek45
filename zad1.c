#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define N 16

void print__header(int size){
    int i;
    printf("\n");
    for ( i = 0 ; i < size*2; i++){
        printf(" ");
    }
    printf("heap  ");
    for ( i = 0 ; i < size*2; i++){
        printf(" ");
    }
    printf("sorted");
    printf("\n");
    for ( i = 0 ; i < size*6 + 6 ; i++){
        printf("-");
    }
    printf("\n");

}

void print__heap__sorted(int i, int size, int heap[], int sorted[]){
    int j;
    for ( j = 0 ; j < size-i ; j++){
        printf("%2d ",heap[j]);
    }
    for ( j = 0 ; j < i ; j++){
        printf("   ");
    }
    printf("  ||  ");
    for ( j = 0 ; j < size - i ; j++){
        printf("   ");
    }
    for ( j = 0 ; j < i ; j++){
        printf("%2d ",sorted[j]);
    }
    printf("\n");
}

void heapify(int heap[],int k,int size){
    if ( k < size && k >= 0){
        int left = k*2 + 1;
        int right = k*2 + 2;
        int pom;
        if ( right < size ){    
            if ( heap[k] < heap[left] || heap[k] < heap[right]){
                if ( heap[left] >= heap[right] ){
                    pom = heap[left];
                    heap[left] = heap[k];
                    heap[k] = pom;
                    heapify(heap,left,size);
                }
                else{
                    
                    pom = heap[right];
                    heap[right] = heap[k];
                    heap[k] = pom;
                    heapify(heap,right,size);
                }
            }
        }
        else if ( left < size && heap[left] > heap[k]){
            pom = heap[left];
            heap[left] = heap[k];
            heap[k] = pom;

        }
        
        heapify(heap,k-1,size);
    }

}

void heapSort(int heap[], int sorted[], int size, int track){
    int i,j;
    heapify(heap,(size-1)/2, size);

    // ------------------------------------//
    if (track == 1){
        print__header(size);
    }
    // ------------------------------------//
    
    for ( i = 0 ; i < size + 1 ; i++){
       
        // ------ print ---------//
        if(track == 1){
            print__heap__sorted(i,size,heap,sorted);
        }
        // ------- end ---------- //
        
        if ( i < size ){
            sorted[i] = heap[0];
            //printf("sorted[%d] = %d  ",i,sorted[i]);
            heap[0] = heap[size - 1 - i];
            heapify(heap,0,size - i);
        }
    }
    
}

int main(int argc, char *argv[]){
    int heap[N];
    int sorted[N];
    int i,size;
    int track = 0;
    //printf("argc = %d\n",argc);
    // sprawdzenie argumentów wywołania
    
    for ( i = 0 ; i < argc ; i++){
        if ( strcmp(argv[i], "--track") == 0 ){
            track = 1;
            //printf("track = 1\n");
        }
        else{
            //printf("track = 0\n");
        }
    }
    printf("Wylosowana tablica wygląda następująco:\n");
    srand(time(NULL));
    for ( i = 0 ; i < N ; i++ ){
        heap[i] = (rand() % 21) - 10 ;
        //sorted[i] = 999;
        printf("%d, ",heap[i]);
    }
    heapSort(heap, sorted, N, track);
    printf("\n\n----------------\n\nPosortowana tablica wygląda następująco:\n");
    for ( i = 0 ; i < N ; i++){
        printf("%d, ",sorted[i]);
    }
    printf("\n--------------------------------\n");
    return 0;

}
