#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50

int topIndex = -1;
int stack[N];

int Stack__push(int stack[], int number){  // umieszcza liczbę na gorę stosu i return 0 ; jeżeli stos jest pełny -> return -1
    if ( topIndex == N - 1){
        return -1;
    }
    else{
        topIndex++;
        stack[topIndex] = number;
        return 0;
    }
}

int Stack__pop(int stack[]){  // zdejmuję liczbe z góry stosu, jak stos jest pusty return -2
    if( topIndex == -1){
        return -2;
    }
    else{
        topIndex--;
        return stack[topIndex + 1];
    }
}

void Stack__print(int stack[]){
    int i;
    for ( i = 0 ; i <= topIndex ; i++){
        printf("%d ",stack[i]);
    }
}

int parowanie_nawiasow(char line[]){
    int i,p;
    int isPaired[N];                    // 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    for ( i = 0 ; i < N ; i++){
        isPaired[i] = 1;
    }
    
    for ( i = 0 ; i < strlen(line) ; i++ ){
        if ( line[i] == '(' || line[i] == '[' || line[i] == '{'){
            Stack__push(stack,i);
        }
        if ( line[i] == ')' || line[i] == ']' || line[i] == '}'){    
            int top = Stack__pop(stack);
            if ( (top != -2) && ((line[i] == ')' && line[top] == '(' )|| 
                (line[i] == ']' && line[top] == '[' )||
                (line[i] == '}' && line[top] == '{' ))){
                // nawiasy się parują
            }
            else{       // nie parują się
                isPaired[i] = 0;
                isPaired[top] = 0;
            }
        }
    }
    // wszystkie nawiasy które zostału na stosie też są niesparowane
    while(1){
        p = Stack__pop(stack);
        if( p == -2){
            break;
        }
        else{
            isPaired[p] = 0;
        }
    }  


    
    printf("\n-----------\n");
    for ( i = 0 ; i < strlen(line) ; i++){
        if(isPaired[i]){
            printf("%c",line[i]);
        }
        else{
            printf("\033[0;31m"); 
            printf("%c",line[i]); 
            printf("\033[0m"); 
        }

    }

    return 0;
}




int main(){
    
    char line[] = ")[( x )[ ( a { b ( [c] ) d } e )][()[{";
    int size = strlen(line);
    printf("rozmiar line to %d",size);
    parowanie_nawiasow(line);
    return 0;
}