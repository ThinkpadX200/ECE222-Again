#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

//store_dictionary() {
//}

//finds total number of words plus max novel word length
int words_in_file(FILE *novel, int *totalwords, int *maxnovelwordlen) {

    char temp[100];
    //*totalwords = twords;
    while (!feof(novel)) {
        fscanf(novel, "%s", temp);

        (*totalwords)++;

        if (strlen(temp) > *maxnovelwordlen) {
            *maxnovelwordlen = strlen(temp);
        }

    } 


    return(0);
}
//finds total number of letters in files for word percentages
int letters_in_file(FILE *novel, float *letters, float *totalletters) {

    int ch = 0;
    int i = 0;
    int j;
    char *line = NULL;
    line = (char *)malloc(sizeof(char));
    size_t len = 0;
    ssize_t templine;

    rewind(novel);

    while ((templine = getline(&line, &len, novel)) != -1) {
        i = 0; 
        while ((line[i] != '\n')) {

            ch = (char)line[i];


            if (isalpha(ch)) {
                ch = toupper(ch);
                (*totalletters)++;


                for(j = 0; j < 26; j++) {
                    if (ch == 65+j) {
                        letters[j] += 1;
                        break;
                    }
                }
            }
            else if (ch == '\n') {
                break;
            }
            i++;

        }
    }
    free(line);

    return (0);
}

//puts all novel words into array, and finds the max length and number of word of the lengths
int novel_to_array(FILE *novel, char **novelArray, int *lenArray, int *totalwords) {

    int i = 0;
    int templen;
    char *tempword = malloc(20*sizeof(char));

    while (fscanf(novel, "%s", tempword)) {

        tempword = realloc(tempword, (strlen(tempword) + 1));
        novelArray[i] = realloc(novelArray[i], (strlen(tempword) +1));
        strcpy(novelArray[i], tempword);

        templen = strlen(tempword);
        lenArray[templen] += 1;  
        i++; 
    }

    return(0);
}

//int novel_len_array(FILE *novel, char **novelArray, char *lenArray, int *totalwords) {

//  int i;

//for (i = 0 






//find the words ending in ous and puts them into an array
int words_ous(char **novelArray, int *totalwords, int ous_counter, char **ousArray ) {

    int i;

    for(i = 0; i < *totalwords; i++) {

      //  if (strstr (novelArray[i], "ous")) {
        //    ousArray[(ous_counter)++] = novelArray[i];
       // }    
    }
    return (0);
}

//finds words with aceslmtw and puts into array
int words_ace(char **novelArray, int *totalwords, char **aceArray) {

 //   int i;

   // for(i = 0; i < *totalwords; i++) {
      //  if (strchr
return (0); 
}

//finds word not in dictionary and puts into an array
int words_dict(char **novelArray, char **dictArray, char **addArray);


int main(int argc, char *argv[]) {

    //storing files
    FILE *fpt;
    FILE *novel;
    char filename[20];
    int filenum = 1;
    int file_lines = 0;
    int dict_count;
    int i;
    int word_len;
    int add_counter = 0;
    int ace_counter = 0;
    int ous_counter = 0;

    //counters
    int *totalwords = malloc(sizeof(int));
    float *totalletters = malloc(sizeof(float));
    int *maxnovelwordlen = malloc(sizeof(int));

    float letters[25];
    //init all letter counts to 0;
    for (i = 0; i < 26; i++) {
        letters[i] = 0;
    }

    //read in dictionary file

    if ((fpt = fopen("dictionary.txt", "r")) == NULL) {
        printf("Cannot read in dictionary, exiting\n");
        exit(1);
    }

    //getting filelines 
    char *line = NULL;
    line = (char *)malloc(sizeof(char));
    size_t len = 0;

    while ((getline(&line, &len, fpt)) != -1) {
        file_lines++;
    }

    rewind(fpt);

    //TEMP to load words in dictionary
    int maxdictwordlen = 30;

    //mallocing size for dictionary

    char **dictArray = (char **)malloc(file_lines * sizeof(char *));
    for (i = 0; i < file_lines; i++) { 
        dictArray[i] = (char *)malloc(maxdictwordlen * sizeof(char));
    }
    //temp

    //putting words in dictarray

    for (i = 0; i < file_lines; i++) { 
        fgets(dictArray[i], maxdictwordlen + 1, fpt);
        dict_count++;
        word_len = strlen(dictArray[i]); //length of each entry
        if (word_len == 0) {
            dictArray[i][word_len] = '\0';
        }
        else {
            dictArray[i][word_len-2] = '\0';
        }  //cuts off /r/n
        // dictarray[i] = realloc(dictarray[i], strlen(dictarray[i] +1));
    }

    fclose(fpt);


    //sorting novel stuff
    //malloc size for novel





    //storing words that have ous, aceslmtw, or not in dictionary.txt


    while (1) {
        sprintf(filename, "%s_%d.txt", argv[1], filenum);  

        //Note: Decided to open and close file, cause I was having some problems with reading them, and wanted a fresh opening every time

        //words in novel
        if ((novel = fopen(filename, "r")) != NULL) {

            //function that test things
            words_in_file(novel, totalwords, maxnovelwordlen); 

            fclose(novel);
        }

        //declaring here now that maxnovelwordlen is set
        int lenArray[*maxnovelwordlen]; 
        for (i = 0; i < 26; i++) {
            lenArray[i] = 0;
        }

        int templen = *maxnovelwordlen;

        //mallocing for novel array using totalwords
        char **novelArray; 
        if ((novelArray = (char **)malloc(sizeof(char *))) != NULL) {
            for (i = 0; i < *totalwords; i++) {
                if ((novelArray[i] = (char *)malloc(sizeof(char) * templen)) != NULL) {
                    novelArray[i] = "a";

                }
                //   memset(novelArray, 0, (sizeof(char) * (*maxnovelwordlen)));
            }
        }



        //find totalletters
        if ((novel = fopen(filename, "r")) != NULL) {

            letters_in_file(novel, letters, totalletters);

            fclose(novel);
        }

        //putting file words into novelArray and finding max novel word length
        if ((novel = fopen(filename, "r")) != NULL) {

            novel_to_array(novel, novelArray, lenArray, totalwords);

            fclose(novel);
        }
        //mallocing other arrays for "ous" "aceslmtw" and addendum for function call
        
        char **ousArray; 
        if ((ousArray = (char **)malloc(sizeof(char *))) != NULL) {
        }

        char **aceArray;
        if ((aceArray = (char **)malloc(sizeof(char *))) != NULL) {
        }
        
        char **addArray;
        if ((addArray = (char **)malloc(sizeof(char *))) != NULL) {
        }
        
        //  if ((novel = fopen(filename, "r")) != NULL) {

        //    novel_len_array(novel, novelArray, lenArray, totalwords);


        // }

        //        break;


        // 
        //else 

        
    //writing to file
    FILE *out;
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("Cannot Write File\n");
        exit (1);
    }
    

        fprintf(out, " %i %f\n", *totalwords, *totalletters);
        fprintf(out, " %i lines %i dict words\n", file_lines, dict_count);
        for (i = 0; i < 26; i++) {
            fprintf(out, "\n%c: %0.0f [%0.2f%%]", 65+i, letters[i], (letters[i]/(*totalletters) * 100));
        }
        for (i = 0; i < *maxnovelwordlen; i++) {
            fprintf(out, "\nTotal Words of Len %i = %i", i, lenArray[i]);
        } 
/*
        for (i = 0; i < *; i++) 
            fprintf(out, "\nTotal Words of Len %i = %i", i, lenArray[i]);
            
*/
    fclose(out);
    }
    //read in dictionary file



    //storing files





    for (i = 0; i <= file_lines; i++) {
        free(dictArray[i]);
    }

    for (i = 0; i < *totalwords; i++) {
     //    free(novelArray[i]);
    }
    
    for (i = 0; i <= ace_counter; i++) {
 //       free(aceArray[i]);
    }
    for (i = 0; i <= ous_counter; i++) {
   //     free(ousArray[i]);
    }
    for (i = 0; i <= add_counter; i++) {
     //   free(addArray[i]);
    }

   // free(ousArray);
   // free(aceArray);
   // free(addArray);
    free(dictArray);
   // free(novelArray);
    free(totalwords);
    free(totalletters);
    free(line);    

    return 0;

}
