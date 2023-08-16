//Lab1
//Joshua Colleran
//April 5th, 2023
//This lab with count the words in a file and will let the user know if the file is non existant or cannot be opened
#include <stdio.h>
#define MAX_WORD_LENGTH 30

void main (int argc, char *argv[]) {
        //initializing varibles
        char words[MAX_WORD_LENGTH];
        FILE *fp;
        int count = 0;
        //sets fp to read
        fp = fopen(argv[1], "r");
        //checks to see if there is a fire with that name
        if (argc < 2) {
                printf("There is no file");
                return;
        }
        //tells user if the file is unable to be opened
        if (fp == NULL) {
                printf("Cannot open the file");
                return;
        }
        //Repeatidly checks to see if there is another word in the file and incremeants count by 1 if it does
        while(fscanf(fp,"%s", words) == 1) {
                count++;
        }
        fclose(fp);
        //prings results
        printf("There are %d words\n", count);
}