#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 20

int queue[10][N];
int front = -1;
int end = -1;

int Queue__push(int queue[], int number){
    if( end == -1){
        front++;
        end++;
        queue[end] = number;
        return 0;
    }
    else{
        int pom = end;
        end = (end + 1) % N;
        if ( end == front){
            end = pom;
            return -1;
        }
        else{
            queue[end] = number;
            return 0;
        }
    }
}

int Queue__pop(int queue[]){
    if ( front == -1){
        return -2;
    }
    else if( front == end){
        int pom = queue[front];
        front = -1;
        end = -1;
        return pom;
    }
    else{
        int pom = queue[front];
        front = (front + 1) % N;
        return pom;
    }
    
}

void Queue__print(int queue[]){
    int i;
    for ( i = front ; i != end ; i = (i + 1) % N){
        printf("%d ",queue[i]);
    }
    printf("%d ",queue[end]);
}

void RadixSort(int arr[], int arr2[], int size){
    int i,j,k,x;
    for ( i = 1 ; i <= 3 ; i++){
        printf("\n");
        int arr2Index = 0;
        for ( k = 0 ; k < 10 ; k++){
            front = -1;
            end = -1;
            for ( j = 0 ; j < size ; j++){
                x = arr[j] % (int)pow(10,i);
                x = x / (int)pow(10,i-1);
                if ( x == k){
                    Queue__push(queue[k],arr[j]);
                }
            }
            for ( arr2Index ; arr2Index < size ; arr2Index++){
                int pom = Queue__pop(queue[k]);
                if ( pom != -2){
                    arr2[arr2Index] = pom;
                }
                else{
                    break;
                }
            }
        }
        for ( j = 0 ; j < size ; j++){
            arr[j] = arr2[j];
            printf("%d ",arr[j]);
        }
    }
      

      
}

int main(){
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66, 234, 786, 975, 222};
    int size = sizeof(arr)/sizeof(arr[0]);
    int arr2[N];
    RadixSort(arr,arr2,size);
    
    
    
    /*int k = -1; // Initialize k with a default value
    while ( k != 0){
        printf("\n ------ \n 1 - push\n2 - pop\n0 - exit\n\n");
        scanf("%d",&k);
        if ( k == 1){
            int number;
            printf("number: ");
            scanf("%d",&number);
            if ( Queue__push(queue,number) == -1){
                printf("Queue is full\n");
            }
            Queue__print(queue);
        }
        else if ( k == 2){
            int pom = Queue__pop(queue);
            if ( pom == -2){
                printf("Queue is empty\n");
            }
            else{
                printf("poped: %d\n",pom);
            }
            Queue__print(queue);
        }
        else if ( k == 0){
            break;
        }
    }*/

}