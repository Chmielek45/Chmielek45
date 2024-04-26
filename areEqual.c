#include "header.h"

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
