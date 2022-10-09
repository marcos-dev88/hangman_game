#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "headers_hang.h" // this tell to compiler the all methods with its signatures
#include "headers_hang_file.h" // adding all file management functions here
                         
#define WORDPATH "./words.txt"

int main(){
    int bodyParts[7] = {0, 0, 0, 0, 0, 0, 0};
    char secretWord[100] = "";
    char wordGround[100] = "";
    char alpabeth[26] = {};
    char guessedLetter;
    int point = 0;
    int lose = 0;
    int miss = 0;
    int right = 0;

    int jumpTry = 0;
    int try;

    int hit = 0; 

    chooseSecretWord(secretWord);

    do{ 
        generateGround(wordGround, secretWord);
        int isLost = printArt(miss, bodyParts);
        if (isLost){
            lostGameScreen();
            return 0;
        }

        printf("\ntried letters: %s\n", alpabeth);

        printf("\n");
        printf("\n%s", wordGround);
        int won = checkWon(hit, secretWord);
        if (won){
            char wantAddNewWord;
            winScreen();
            printf("\nDo you wanna add a new word? [y/n] ");
            scanf(" %c", &wantAddNewWord);
            addNewWord(wantAddNewWord);
            return 0;
        }
        printf("\n Type a letter that you think that have "); 
        scanf(" %c", &guessedLetter);
      
        for(int i = 0; i < strlen(alpabeth); i++){ 
            jumpTry = 0;
            if(guessedLetter == alpabeth[i]){
                jumpTry = 1;
            }
        }

        alpabeth[try] = guessedLetter;

        for(int i = 0; i < strlen(secretWord); i++){
            if(guessedLetter == secretWord[i]){
                wordGround[i] = secretWord[i];
                /* printf("\nletter in position %d is %c \n", i, secretWord[i]); */
                right = 1;
                hit++;
            } 
        }
        checkMissed(&right, &miss);
        
        if(!jumpTry){
            try++;
        }
        
    }while(!point && !lose);

    return 0;
}

int fileLines(const char *restrict path){
    FILE *f;
    char fileCharacter;
    int lines = 0;

    f = fopen(path, "r");

    if (f == NULL){
        printf("Sorry, this file doesn't exist");
        exit(1);
    }

    while(fileCharacter != EOF){
        fileCharacter = fgetc(f);
        if (fileCharacter == '\n'){
            lines++;
        }
    }

    fclose(f);

    return lines;
}

int printArt(int tryLost, int bodyParts[7]){

    if (tryLost != 0){
        bodyParts[tryLost-1] = tryLost;
    }

    system("clear");
    printf("\n|----------------");
    printf("\n|               |");
    printf("\n|               |");
    printf("\n|               |");
    printf("\n|               %c", (tryLost >= 1 ? 'O' : ' '));
    printf("\n|               %c", (tryLost >= 2 ? '"' : ' '));
    printf("\n|              %c%c%c", (tryLost >= 4 ? '/' : ' '), (tryLost >= 3 ? '|' : ' '), (tryLost >= 5 ? '\\' : ' '));
    printf("\n|              %c %c", (tryLost >= 6 ? '/' : ' '), (tryLost >=7 ? '\\' : ' '));
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    printf("\n|");
    
    if (tryLost == 7){
        return 1;
    }

    return 0;
}

void generateGround(char ground[], const char *secretWord){
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

int checkWon(int hit, char const *secretWord){
    if (hit == strlen(secretWord)){
        return 1;
    }
    return 0;
}

void chooseSecretWord(char *secretWord){
    FILE *f;
    int lines = fileLines(WORDPATH);

    f = fopen(WORDPATH, "r");

    if (f == NULL){
        printf("Sorry, this file doesn't exist");
        exit(1);
    }

    srand(time(0));
    int rndm = rand() % lines;

    for(int i = 0; i <= rndm; i++){
        fscanf(f, "%s", secretWord);
    }
    fclose(f);
}

void addNewWord(char wantAddWord){
    if(wantAddWord == 'y' || wantAddWord == 'Y'){
        FILE *f;
        char newWord[100] = "";
        printf("Write the new word: ");
        scanf("%s", newWord);

        /* int qntt = fileLines(WORDPATH); */
        /* qntt++; */

        f = fopen(WORDPATH, "r+");
        if(f == NULL){
            printf("Sorry, this file doesn't exist");
            exit(1);
        }

        /* fseek(f, 0, SEEK_SET); */
        fseek(f, 0, SEEK_END);

        fprintf(f, "\n%s", newWord);

        fclose(f);
    }
}

void lostGameScreen(){
    printf("\nsorry bro, you lost...");
}

void winScreen(){
    printf("\nCongratulations! you won the game! ");
}

