//
// Created by Ammar on 2022-02-20.
//
#define CONSTANT_SIZE 5

#include "stdbool.h"
#include "stdio.h"
#include "string.h"
int update(char word[], char pos[],int dup_pos,FILE* file_in,FILE* file_out,_Bool duplicate,int tries, int read_from){
    int id;
    _Bool write = true;
    char new_line[1];
    char buf_in[CONSTANT_SIZE+1];
    int bytes = read_from;



    if(tries >= 3){
        fseek(file_in,read_from,SEEK_SET);
    }


    while((id = fread(buf_in,1,5,file_in))==CONSTANT_SIZE){
        // Establish conditions in which a word will be written to a file.

        buf_in[5] = 0;

        _Bool check_num = false;
        //checks to see if the loop has read one of the numbers printed in the file
        for(int i = 0 ; i < CONSTANT_SIZE; i++){
            if(buf_in[i] < 97|| buf_in[i] > 122){
                check_num = true;
                break;
            }
        }

        if(check_num){
            break;
        }

        if (tries>=2){
            bytes+=7;
        }
        // check to see if there's an incorrect letter inputted

        for(int i = 0; i < CONSTANT_SIZE; i++){
            if(pos[i]==48 && i != dup_pos){
                // check to see if the word contains any incorrect letters and that the word wasn't already eliminated from
                // the possible words list

                if(write) {
                    for (int j = 0; j < CONSTANT_SIZE; j++) {
                        if (buf_in[j] == word[i]) {
                            write = false;
                            break;
                        }
                    }
                }
            } else if(pos[i]==49 && i != dup_pos){
                // checks to see that the letter at guess[i] is in buf_in but not at bif_in[i].
                if (write){
                    if(buf_in[i]==word[i]) {
                        write = false;
                        break;
                    }
                    write = false;
                    for (int j = 0; j < CONSTANT_SIZE; j++) {
                        if (buf_in[j] == word[i] && j != i) {
                            write = true;
                            break;
                        }
                    }
                }

            } else if(pos[i]==50) {
                // checks to see if buf_in[i] matches guess[i]
                if (buf_in[i] != word[i]) {
                    write = false;
                    break;
                }
            } else{
                // will only occur if a duplicate letter is guessed and only one of then has correct[i] = 0;
                if (write) {
                    char dup_char = word[dup_pos];
                    int count = 0;
                    for(int i = 0; i < CONSTANT_SIZE; i++) {
                        if (dup_char == buf_in[i]) {
                            count++;
                        }
                    }
                    // reads false for any word that has more than 1 of the duplicate letter
                    if(!duplicate) {
                        if (count > 1) {
                            write = false;
                            break;
                        }
                    } else{
                        if (count < 2) {
                            write = false;
                            break;
                        }
                        if (buf_in[dup_pos] == word[dup_pos]){
                            write = false;
                            break;
                        }
                    }
                }
            }
        }
        if(write) {
                fprintf(file_out, "%s\n",buf_in);

        }
        //prevents \n from being read as a character
        fread(new_line,1,1,file_in);
        write = true;
    }

if (tries != 1) {
    bytes += 3;
}
    fprintf(file_out,"%d\n",tries + 1);
    return bytes;
}
