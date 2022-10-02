#include <stdio.h>
#include <string.h>

int printArt(int tryLost, int bodyParts[6]){

    if (tryLost == 8){
        return 1;
    }

    if (tryLost != 0){
        bodyParts[tryLost-1] = tryLost+1;
    }

    printf("\n|----------------");
    printf("\n|               |");
    printf("\n|               |");
    printf("\n|               |");
    if (bodyParts[0] == 2){
        printf("\n|               O");
    }

    if (bodyParts[1] == 3){
        printf("\n|               ¨");
    }

    if (bodyParts[2] == 4 && bodyParts[3] == 0){
        bodyParts[2] = 0;
        printf("\n|              /|");
    }

    if (bodyParts[3] == 5 && bodyParts[2] == 0){
        printf("\n|              /|\\");
    }

    if (bodyParts[4] == 6 && bodyParts[5] == 0){
        bodyParts[4] = 0;
        printf("\n|              /");
    }

    if (bodyParts[5] == 7 && bodyParts[4] == 0){
        printf("\n|              / \\");
    }
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    return 0;
}

void generateGround(char ground[20], char secretWord[20]){
        for(int i = 0; i < strlen(secretWord); i++){  
            if(ground[i] == 0){ 
                sprintf(&ground[i], "_");
            } 
        } 
}

void checkMissed(int *isRight, int *miss) {
        if (*isRight != 1) {
            (*miss)++;
        }
        *isRight = 0; 
}

int main(){


    int bodyParts[6] = {0, 0, 0, 0, 0, 0};
    char secretWord[20];
    char wordGround[20];
    char guessedLetter;
    int point = 0;
    int lose = 0;
    int miss = 0;
    int right = 0;
    int try = 0;

    sprintf(secretWord, "someword");

    do{ 
        printf("\nvalue of miss => %d\n\n", miss);
        generateGround(wordGround, secretWord);

        int some = printArt(miss, bodyParts);
        printf("\n");
        printf("\n%s", wordGround);
        printf("\n Type a letter that you think that have "); 
        scanf(" %c", &guessedLetter);
       
        for(int i = 0; i < strlen(secretWord); i++){
            if(guessedLetter == secretWord[i]){
                wordGround[i] = secretWord[i];
                /* printf("\nletter in position %d is %c \n", i, secretWord[i]); */
                right = 1;
            } 
        }
        checkMissed(&right, &miss);
        try++;

    }while(!point && !lose);

    return 0;
}
