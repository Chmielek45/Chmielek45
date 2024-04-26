#include <stdio.h>
#include<stdlib.h>

int main() {
    char line[100];
    char hline[100];
    int i = 0 ;
    printf("Wybierz działanie i podaj dwa zbiory: (aby zakończyć wciśnij ctrl+D / ctrl+Z\n");
    printf(" 1. Suma\n 2. Część wspólna\n 3. Różnica\n 4. Różnica symetryczna\n 5. Czy A = B?\n 6. Czy A podzbiór B, czy B podzbiór A ?");
    printf("\nFormat inputu:[n;(a1,a2,a3,a4,a5,a6,...):(b1,b2,b3,b4,b5,b6,...)]\n");
    while (fgets(line, sizeof(line), stdin) != NULL) {
        int s = strlen(line)-1;
        printf("size is %d", s);
        int j = 0;
        while( i < s){
            if( line[i] =! 32){
                hline[j] = line[i];
                j++;
            }
            i++;
        }
        for( i = 0 ; i < s ; i++){
            printf("c to %c", hline[i]);
        }
    }

    printf("Koniec wczytywania\n");

    return 0;
}