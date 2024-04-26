#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZEA 4
#define SIZEB 6
#define SIZE 5
#define OUT_SIZE 20

int unia(int setA[SIZEA], int setB[SIZEB], int unionResult[SIZEA + SIZEB]){
    int i, j, k, m;
    int copyA[SIZEA];
    for (i = 0 ; i < SIZEA ; i++){
        copyA[i] = setA[i];
    }
    for (i = 0 ; i < SIZEA ; i++){
        unionResult[i] = copyA[i];
    }
    k = SIZEA;
    for (i = 0 ; i < SIZEB ; i++){           // przechodzimy przez i-ty element setB
        j = 0;
        while((setB[i] != copyA[j]) && (j < SIZEA)){        // porównuje i-ty element z j-tymi elementami setA
            j++;
        }
        if (j == SIZEA){        // znaczy że w setA nie ma elementu setB[i]
            unionResult[k] = setB[i];
            k++;
        }
        else{
            for (j ; j < SIZEA-1 ; j++){
                copyA[j] = copyA[j+1];
            }
            copyA[SIZEA - 1] = 999;
        }
    }
    return k;
}

int intersection(int setA[SIZEA], int setB[SIZEB], int result[]){
    int i, j, k, m;
    int copyA[SIZEA];
    for (i = 0 ; i < SIZEA ; i++){
        copyA[i] = setA[i];
    }
    k = 0;
    for (i = 0 ; i < SIZEB ; i++){
        for (j = 0 ; j < SIZEA ; j++){
            if ( setB[i] == copyA[j]){
                result[k] = setB[i];
                k++;
                for (m = j ; m < SIZEA - 1 ; m++){
                    copyA[m] =copyA[m+1];
                }
                copyA[SIZEA - 1] = 999;
            }
        }
    }
    return k;
}

int diffrence(int setA[SIZEA], int setB[SIZEB], int result[]){  // A \ B
    int i, j, k;
    int copyB[SIZEB];
    for (i = 0 ; i < SIZEB ; i++){
        copyB[i] = setB[i];
    }
    k = 0;
    for (i = 0 ; i < SIZEA ; i++){
        j = 0;
        while ((setA[i] != copyB[j]) && (j < SIZEB)){
            j++;
        }
        if (j == SIZEB){
            result[k] = setA[i];
            k++;
        }
        else{
            for (j ; j < SIZEB - 1 ; j++){
                copyB[j] = copyB[j+1];
            }
            copyB[SIZEB - 1] = 999;
        }
    }
    return k;

}

int symmetricDiffrence(int setA[SIZEA], int setB[SIZEB], int result[]){ // A - B
    int i, j, k, n, m;
    int copyA[SIZEA];
    int copyB[SIZEB];
    int repetitions = 0;
    for (i = 0 ; i < SIZEA ; i++){
        copyA[i] = setA[i];
    }
    for (i = 0 ; i < SIZEB ; i++){
        copyB[i] = setB[i];
    }
    
    for (i = 0 ; i < SIZEA - repetitions ; i++){
        for (j = 0 ; j < SIZEB - repetitions ; j++){
            if ( copyA[i] == copyB[j] ){
                for (m = i ; m < SIZEA - 1 ; m++){
                    copyA[m] = copyA[m+1];
                }
                copyA[SIZEA-1] = 999;
                for (n= j ; n < SIZEB - 1 ; n++){
                    copyB[n] = copyB[n+1];
                }
                copyB[SIZEB-1] = 999;
                repetitions++;
                j--;
                i--;
            }
        }
    }
    j = 0;
    // adjust SIZE
    for (i = 0 ; i < SIZEA - repetitions ; i++){
        result[j] = copyA[i];
        j++;
    }
    for (i = 0 ; i < SIZEB - repetitions ; i++){
        result[j] = copyB[i];
        j++;
    }
    
    return repetitions;

}

int isSubset(int setA[SIZEA], int setB[SIZEB]) {
    int i, j;
    for (i = 0; i < SIZEA; i++) {
        int found = 0;
        for (j = 0; j < SIZEB; j++) {
            if (setA[i] == setB[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 1;
}

int areEqual(int setA[SIZEA], int setB[SIZEB]){
    if ( SIZEA == SIZEB){
        int i, j, pom;
        for ( j = 0 ; j < SIZEA ; j++){   
            for( i = 0 ; i < SIZEA - 1 ; i++){
                if ( setA[i] > setA[i+1] ){
                    pom = setA[i];
                    setA[i] = setA[i+1];
                    setA[i+1] = pom;
                }
            }
        }
        for ( j = 0 ; j < SIZEB ; j++){   
            for( i = 0 ; i < SIZEB - 1 ; i++){
                if ( setB[i] > setB[i+1] ){
                    pom = setB[i];
                    setB[i] = setB[i+1];
                    setB[i+1] = pom;
                }
            }
        }


        i = 0;
        while( setA[i] == setB[i] && i < SIZEA){
            i++;
        }
        if ( i == SIZEA ){
            printf("YES");
            return 1;
        }
        else{
            printf("NO");
            return 0;
        }
    }
    else{
        printf("NO");
        return 0;
    }
}

int main(){
    int setA[SIZEA];
    int setB[SIZEB];
    int unionResult[SIZEA + SIZEB];
    int maxresult = fmax(SIZEA, SIZEB);
    int result[maxresult];
    int outputTable[OUT_SIZE][SIZEA + SIZEB+1];
    int i, n, k, j;
    int s = 0;
    printf("Numery operacji:\n1 - unia\n2 - przecięcie\n3 - różnica\n4 - różnica symetryczna\n5 - czy są równe\n6 - czy zbiór A jest podzbiorem zbioru B\n");
    printf("podaj nr operacji(n) oraz zbiór A(%d) oraz zbiór B(%d) w podanym formacie :\nn;a1,a2,a3,a4;b1,b2,b3,b4,b5,b6\n", SIZEA, SIZEB);
    while ((scanf("%d;%d,%d,%d,%d;%d,%d,%d,%d,%d,%d",&n,&setA[0],&setA[1],&setA[2],&setA[3],&setB[0],&setB[1],&setB[2],&setB[3],&setB[4],&setB[5])) != EOF){
        if ( n == 1){
            k = unia(setA, setB, unionResult);
            outputTable[s][0] = k;
            for (i = 0 ; i < k ; i++){
                outputTable[s][i+1] = unionResult[i];
                //printf("%d",outputTable[s][i+1]);
            }
            printf("\n");
        }
        else if ( n == 2){
            k = intersection(setA, setB, result);
            outputTable[s][0] = k;
            for (i = 0 ; i < k; i++){
                outputTable[s][i+1] = result[i];
            }
        }
        else if ( n == 3){
            k = diffrence(setA, setB, result);
            outputTable[s][0] = k;
            for (i = 0 ; i < k; i++){
                outputTable[s][i+1] = result[i];
            }
        }
        else if ( n == 4){
            k = SIZEA + SIZEB - (2 * symmetricDiffrence(setA, setB, result));
            outputTable[s][0] = k;
            for (i = 0 ; i < k ; i++){
                outputTable[s][i+1] = result[i];
            }
        }
        else if ( n == 5){
            printf("\nequal? :\n");
            areEqual(setA, setB);
        }
        else if ( n == 6){
            printf("\nsubset? :\n");
            isSubset(setA, setB);
        }
        s++;
    }
    for (i = 0 ; i < s ; i++){
        printf("\n");
        n = outputTable[i][0];
        for (j = 1 ; j <= n ; j++){
            printf("%d, ", outputTable[i][j]);

        }
    }
    printf("\n\n--------------------------------\n\n");
    return 0;
}