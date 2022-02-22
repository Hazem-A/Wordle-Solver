#include <stdio.h>
#include <stdbool.h>



#define CONSTANT_SIZE 5

int update(char word[], char pos[],int dup_pos,FILE* file_in,FILE* file_out,_Bool duplicate,int tries, int read_from);

int main() {
    // Define variables


    FILE* fkey;
    FILE* fin;
    FILE* fout;
    //5 letter words only
    char fkey_path[] = "C:\\Users\\Ammar\\ece220\\sgb-words.dat";
    char fout_path[] = "C:\\Users\\Ammar\\ece220\\possible-words.txt";

    // read from files
    fout = fopen(fout_path,"w");
    fkey = fopen(fkey_path,"r");




    char guess[CONSTANT_SIZE+1];
    char correct[CONSTANT_SIZE+1];
    _Bool duplicate = false;
    int dup_pos = -1;
    int tries = 1;
    int read = 0;
    while (tries<7) {
        printf("Enter a 5 letter word\n");
        scanf("%s", guess);

        // check if there are any illegal characters
        for (int i = 0; i < CONSTANT_SIZE; i++) {
            if (guess[i] < 65 || (guess[i] > 90 && guess[i] < 97) || guess[i] > 122) {
                printf("Invalid character \n");
                scanf("%s", guess);
                i = -1;
            }
        }
        printf("indicate whether each letter is in the correct spot or not.\n");
        printf("2 = correct letter and correct spot, 1 = correct letter but incorrect spot, 0 = incorrect letter.\n");
        // printf("eg input. 21001 indicates that the first letter is in the correct spot, the 2nd and 5th letters are correct"
        //"but in the wrong spot and the rest of the letters are wrong\n");
        scanf("%s", correct);

// checks to see if the input is illegal
        for (int i = 0; i < CONSTANT_SIZE; i++) {
            if (correct[i] < 48 || correct[i] > 50) {
                printf("Invalid number\n");
                scanf("%s", correct);
                i = 0;
            }
        }

        // Read from the files


        for (int i = 0; i < CONSTANT_SIZE; i++) {
            for (int j = i + 1; j < CONSTANT_SIZE; j++) {
                // checks to see if a duplicate of a letter was entered as a guess
                if (guess[i] == guess[j]) {
                    // checks to see if the final word has a duplicate or not
                    if (correct[i] == 48) {
                        dup_pos = i;
                    } else if (correct[i] == 49 && correct[j] != 48) {
                        dup_pos = i;
                        duplicate = true;
                    } else if (correct[j] == 49 && correct[i] != 48) {
                        dup_pos = j;
                        duplicate = true;
                    } else {
                        dup_pos = j;
                    }
                }
            }
        }
        if (tries == 1) {
            read = update(guess, correct, dup_pos, fkey, fout, duplicate,tries,read);
            fclose(fkey);
            fclose(fout);
        } else{
            fin = fopen(fout_path,"r");
            fout = fopen(fout_path,"a");
            read = update(guess, correct, dup_pos, fin, fout, duplicate,tries,read);
            fclose(fin);
            fclose(fout);

        }
        tries++;
    }
    fclose(fkey);
    fclose(fout);
    return 0;
}




