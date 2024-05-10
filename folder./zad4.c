#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define LINE_SIZE 1024
#define WORD_SIZE 64

void grep(char contentTable[100][LINE_SIZE], int counter, char options[]) {
    char line[LINE_SIZE];
    char pattern[WORD_SIZE];
    char result[100][LINE_SIZE];
    bool caseInsensitive = false;
    bool wholeWord = false;
    bool showLineNumber = false;
    bool countOnly = false;
    int resultCount = 0;

    // Check options
    for (int i = 0; options[i] != '\0'; i++) {
        switch (options[i]) {
            case 'i':
                caseInsensitive = true;
                break;
            case 'w':
                wholeWord = true;
                break;
            case 'n':
                showLineNumber = true;
                break;
            case 'c':
                countOnly = true;
                break;
            default:
                break; // Ignore unknown options
        }
    }

    // Get the pattern from the end of the contentTable
    strcpy(pattern, contentTable[counter - 1]);

    // Convert pattern to lowercase if case insensitive option is enabled
    if (caseInsensitive) {
        for (int i = 0; pattern[i]; i++) {
            pattern[i] = tolower(pattern[i]);
        }
    }

    // Search for pattern in input lines
    int k = 1;
    int lineNumTable[100];
    while (fgets(line, LINE_SIZE, stdin) != NULL) {
        int lineLength = strlen(line);
        if (line[lineLength - 1] == '\n')
            line[lineLength - 1] = '\0'; // Remove newline character

        char *linePtr = line;
        bool match = false;

        while (*linePtr) {
            char *patternPtr = pattern;
            char *linePtrCopy = linePtr;
            bool wildcardMatch = true;

            while (*patternPtr && *linePtrCopy) {
                if (*patternPtr == '.') {
                    // Wildcard character, match any single character
                    patternPtr++;
                    linePtrCopy++;
                } else {
                    char patternChar = *patternPtr;
                    char lineChar = *linePtrCopy;

                    if (caseInsensitive) {
                        patternChar = tolower(patternChar);
                        lineChar = tolower(lineChar);
                    }

                    if (patternChar != lineChar) {
                        wildcardMatch = false;
                        break;
                    }

                    patternPtr++;
                    linePtrCopy++;
                }
            }

            if (*patternPtr == '\0' && wildcardMatch) {
                match = true;
                break;
            }

            linePtr++;
        }

        if (match) {
            if (wholeWord) {
                // Check if the pattern is a whole word
                bool isWholeWord = false;

                if ((linePtr == line || !isalnum(linePtr[-1])) && (!isalnum(linePtr[strlen(pattern)])))
                    isWholeWord = true;

                if (isWholeWord) {
                    strcpy(result[resultCount], line);
                    lineNumTable[resultCount++] = k;
                }
            } else {
                strcpy(result[resultCount], line);
                lineNumTable[resultCount++] = k;
            }
        }
        k++;
    }

    // Print or count results based on options
    if (countOnly) {
        printf("Count: %d\n", resultCount);
    } else {
        for (int i = 0; i < resultCount; i++) {
            if (showLineNumber)
                printf("%d: ", lineNumTable[i]);
            printf("%s\n", result[i]);
        }
    }
}

void sort(char contentTable[100][LINE_SIZE], int counter) {
    char lines[100][LINE_SIZE];
    char linesCopy[100][LINE_SIZE];
    char line[LINE_SIZE];
    int linesOrder[100];
    int j,h,linesCounter;;
    int i = 0;
    int nflag = 0;
    int kflag = 0;
    int k=1;
    for( i = 0; i < counter; i++) {
        if (strcmp(contentTable[i], "-n") == 0) {
            nflag = 1;
        } else if ((sscanf(contentTable[i], "-k%d", &k) == 1)) {;
            kflag = 1;
        }
        if (nflag == 1 && kflag == 1) {
            break;
        }
    }
    printf("nflag: %d, kflag: %d, k: %d\n", nflag, kflag, k);
    i=0;
    while( fgets(line, LINE_SIZE, stdin) != NULL) {
        linesOrder[i] = i;
        strcpy(lines[i], line);
        i++;
    }
    // i shows how many lines we have
    linesCounter = i;
    for (j = 0; j < linesCounter ; j++) {
        strcpy(linesCopy[j], lines[j]);
    }
    
    if ( kflag == 1){
        for (h = 0; h < 100; h++) {
            char *schowek = strtok(lines[h], " ");
            for (j = 1; j < k; j++) {
                schowek = strtok(NULL, " ");
            }
            if (schowek != NULL){
                strcpy(lines[h], schowek);
            }else if (schowek == NULL){
                strcpy(lines[h], "");
                break;
            }
            
        }
    }
    for (i = 0; i < linesCounter; i++) {
        for (j = i + 1; j < linesCounter; j++) {
            if (nflag == 1) {
                if (atoi(lines[i]) > atoi(lines[j])) {
                    char temp[LINE_SIZE];
                    strcpy(temp, lines[i]);
                    strcpy(lines[i], lines[j]);
                    strcpy(lines[j], temp);
                    int temp2 = linesOrder[i];
                    linesOrder[i] = linesOrder[j];
                    linesOrder[j] = temp2;
                }
            } else {
                if (strcmp(lines[i], lines[j]) > 0) {
                    char temp[LINE_SIZE];
                    strcpy(temp, lines[i]);
                    strcpy(lines[i], lines[j]);
                    strcpy(lines[j], temp);
                    int temp2 = linesOrder[i];
                    linesOrder[i] = linesOrder[j];
                    linesOrder[j] = temp2;
                }
            }
        }
    }
    for (i = 0; i < linesCounter; i++) {
        printf("%s",linesCopy[linesOrder[i]]);
        //printf("\n lines : %s\n", lines[i]);
    }

    
}

void tail(char contentTable[100][LINE_SIZE], int counter) {
    char linesTable[100][LINE_SIZE];
    char line[LINE_SIZE];
    int n = 10;
    int p = 0;
    int i = 0;
    int j;
    int cN = 0;
    int cP = 0;
    int flagA = 0;
    int bytesCounter = 0;
    int plusIntOption = 0;
    int nIntOption = 0;
    int cNegativeOption = 0;
    int cPositiveOption = 0;
    char schowek[LINE_SIZE];
    //printf("counter: %d\n", counter);
    for (i = 0 ; i < counter  ; i++){
        //printf("contentTable[%d]: %s\n", i, contentTable[i]);
    }
    for( i = 1; i < counter ; i++) {
        if (strcmp(contentTable[i],"-n") == 0) {
            if ((i + 1 < counter) && (sscanf(contentTable[i+1], "%d", &n) == 1)) {
                nIntOption = 1;
                //printf( "opcja -n z argumentem %d\n", n);
                break;
            }
            else{
                printf("opcja -n bez argumentu\n");
                break;
            }
        }
        else if (sscanf(contentTable[i], "+%d", &n) == 1) {
            plusIntOption = 1;
            //printf("opcja +%d\n", n);
            break;
        }
        else if (sscanf(contentTable[i], "-%d", &n) == 1) {
            nIntOption = 1;
            //printf("opcja {n} -%d\n", n);
            break;
        }
        else if (strcmp(contentTable[i], "-c") == 0) {
            if (i + 1 < counter){
                if (sscanf(contentTable[i+1], "-%d", &cN) == 1){
                    cNegativeOption = 1;
                }
                else if (sscanf(contentTable[i+1], "+%d", &cP) == 1){
                    cPositiveOption = 1;
                }
                else{
                    printf("opcja -c bez argumentu\n");
                    break;
                }
            }
            else{
                printf("opcja -c bez argumentu\n");
                break;
            }    
        }
        else{
            printf("niepoprawne opcje\n");
            break;
        }
    
    }
    if( cNegativeOption != 1 && cPositiveOption != 1){
        while( fgets(line, LINE_SIZE, stdin) != NULL) {
            strcpy(linesTable[p], line);
            p++;
        }
        if (plusIntOption == 1) {
            for (i = n - 1; i < p; i++) {
                printf("%s", linesTable[i]);
            }
        }
        else if (nIntOption == 1) {
            for (i = p - n ; i < p; i++) {
                printf("%s", linesTable[i]);
            }
        }
    }
    else if (cNegativeOption == 1){ // printing last cN bytes
        bytesCounter = 0;
        printf("Printing last cN bytes\n");
        while( fgets(line, LINE_SIZE, stdin) != NULL){
            bytesCounter += strlen(line);
            strcpy(linesTable[p], line);
            p++;
        }
        printf("bytesCounter: %d\n", bytesCounter);
        int NumOfBytes = bytesCounter - 1;
        bytesCounter = 0;
        for (i = 0 ; i < p; i++){
            for (j = 0; j < strlen(linesTable[i]); j++){
                bytesCounter++;
                if (bytesCounter >= NumOfBytes - cN){
                    printf("%c", linesTable[i][j]);
                }
            }
        }
    }
    else if (cPositiveOption == 1){ // printing text starting from cP byte
        bytesCounter = 0;
        printf("Printing text starting from cP byte\n");
        while( fgets(line, LINE_SIZE, stdin) != NULL){
            bytesCounter += strlen(line);
            strcpy(linesTable[p], line);
            p++;
            /*if (bytesCounter >= cP && flagA == 0){
                char pom[LINE_SIZE] = "";
                for ((i = strlen(line) - (bytesCounter - cP)) ; i < strlen(line); i++){
                    strncat(pom, &line[i], 1);
                }
                printf("pom: %s\n", pom);
                strcpy(linesTable[p], pom);
                flagA = 1;

            }
            else if (flagA == 1){
                strcpy(linesTable[p], line);
            }*/
                
        }
        printf("bytesCounter: %d\n", bytesCounter);
        bytesCounter = 0;
        for (i = 0 ; i < p; i++){
            for (j = 0; j < strlen(linesTable[i]); j++){
                bytesCounter++;
                if (bytesCounter >= cP){
                    printf("%c", linesTable[i][j]);
                }
            }
        }
    }
    else {
        for (i = p - n ; i < p; i++) {
            printf("%s", linesTable[i]);
        }
    }
}

int main() {
    char line[LINE_SIZE];
    char korektor[] = " ,";
    char *schowek;

        
    printf("Podaj komende: \n");
    while (fgets(line, LINE_SIZE, stdin) != NULL) {
        int counter = 0;
        char contentTable[100][LINE_SIZE];
        char options[10] = ""; // Assuming at most 4 options (-w, -i, -n, -c) and a null terminator
        line[strlen(line) - 1] = '\0';
        schowek = strtok(line, korektor);
        // Parse the input to populate contentTable and options
        while (schowek != NULL) {
            if (schowek[0] == '-') {
                strcat(options, schowek + 1); // Skip the '-' character
                strcpy(contentTable[counter], schowek);
                counter++;
            } else {
                strcpy(contentTable[counter], schowek);
                counter++;
            }
            schowek = strtok(NULL, korektor);
        }

        // Debug print to check options
        //printf("Options: %s\n", options);

        if (strcmp(contentTable[0], "tail") == 0) {
            tail(contentTable, counter);
            //printf("Wywolano tail\n");
        } 
        
        else if (strcmp(contentTable[0], "sort") == 0) {
            //printf("Wywolano sort\n");
            for(int i = 1; i < counter; i++) {
                printf("%s\n", contentTable[i]);
            }
            sort(contentTable, counter);
        } 
        
        else if (strcmp(contentTable[0], "grep") == 0) {
            //printf("Wywolano grep\n");
            grep(contentTable, counter, options);
        } 
        
        else {
            printf("Nieznane polecenie\n");
        }
    printf("\nPodaj komende: \n");

    }
    return 0;
}

