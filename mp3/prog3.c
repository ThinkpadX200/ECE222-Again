/*
 *Richard Coffey
 *Lab3/Prog3
 *William Reid
 *ECE-222
 *
 *Notes: Last time, using scanf got me into a bit of a bind, so this time I'm using fgets and sscanf.
 *
 *Purpose: Takes in hex code, and converts it into it's huffman translation given the huffman code 
 *          on the sheet
 *
 *Bugs: Takes in only 8 hex at a time, so you have to account for the translations and separate them 
 *      into 8 bit bursts. This can be done by only submitting 8 hex digits, or by knowing that you 
        the 9th, 10th, etc will be read in as a new transmission.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defining a max length for fgets of hex code
#define MAXLINE 9
#define MAXBITS 32


int main() {

    enum { 
        LETTER_A,
        LETTER_B,
        LETTER_C,
        LETTER_D,
        LETTER_E,
        LETTER_F,
        LETTER_G,
        LETTER_H,
        LETTER_I,
        LETTER_J,
        LETTER_K,
        LETTER_L,
        LETTER_M,
        LETTER_N,
        LETTER_O,
        LETTER_P,
        LETTER_Q,
        LETTER_R,
        LETTER_S,
        LETTER_T,
        LETTER_U,
        LETTER_V,
        LETTER_W,
        LETTER_X,
        LETTER_Y,
        LETTER_Z,
        LETTER_EOT};

    //variables that needed be declared before main stuff
    char line[MAXLINE];
    char hexstring[MAXLINE];
    int code[LETTER_EOT];
    char bits[MAXBITS];
    int hexstrlen;
    unsigned int binarystr;

    //test tables using enum variables
    code[LETTER_A] = 0x1; bits[LETTER_A] = 4; //a 0001
    code[LETTER_B] = 0x15; bits[LETTER_B] = 6; //b 0011 11
    code[LETTER_C] = 0x16; bits[LETTER_C] = 5; //c 1011 0
    code[LETTER_D] = 0x0; bits[LETTER_D] = 5; //d 0000 0
    code[LETTER_E] = 0x3; bits[LETTER_E] = 3; //e 011
    code[LETTER_F] = 0x1B; bits[LETTER_F] = 5; //f 1101 1
    code[LETTER_G] = 0xC; bits[LETTER_G] = 6; //g 0011 00
    code[LETTER_H] = 0x9; bits[LETTER_H] = 4; //h 1001
    code[LETTER_I] = 0x4; bits[LETTER_I] = 4; //i 0100
    code[LETTER_J] = 0xCB; bits[LETTER_J] = 8; //j 1100 1011
    code[LETTER_K] = 0xC8; bits[LETTER_K] = 7; //k 1100 100
    code[LETTER_L] = 0x1; bits[LETTER_L] = 5; //l 0000 1
    code[LETTER_M] = 0x18; bits[LETTER_M] = 5; //m 1100 0
    code[LETTER_N] = 0x5; bits[LETTER_N] = 4; //n 0101
    code[LETTER_O] = 0x2; bits[LETTER_O] = 4; //o 0010
    code[LETTER_P] = 0xE; bits[LETTER_P] = 6; //p 0011 10
    code[LETTER_Q] = 0x328; bits[LETTER_Q] = 10; //q 1100 1010 00
    code[LETTER_R] = 0xA; bits[LETTER_R] = 4; //r 1010
    code[LETTER_S] = 0x8; bits[LETTER_S] = 4; //s 1000
    code[LETTER_T] = 0x7; bits[LETTER_T] = 3; //t 111
    code[LETTER_U] = 0x16; bits[LETTER_U] = 5; //u 1011 1
    code[LETTER_V] = 0x33; bits[LETTER_V] = 6; //v 1100 11
    code[LETTER_W] = 0x32; bits[LETTER_W] = 5; //w 1101 0
    code[LETTER_X] = 0x329; bits[LETTER_X] = 10; //x 1100 1010 01
    code[LETTER_Y] = 0xD; bits[LETTER_Y] = 6; //y 0011 01
    code[LETTER_Z] = 0x32A; bits[LETTER_Z] = 10; //z 1100 1010 10
    code[LETTER_EOT] = 0x32B; bits[LETTER_EOT] = 10; //eot 1100 1010 11

    printf("Input a hexadecimal string to be decoded. (Enter 'Quit' to end.)\n");

    //continues to take input 
    while (fgets(line, MAXLINE, stdin) != NULL) {
        sscanf(line, "%s", hexstring);
        
        //quit case
        if (strcmp(hexstring, "quit") == 0) {
            printf("Goodbye\n");
            return 0;
        }

        //puts hex letters into binarystr
        sscanf(line, "%x", &binarystr);
        fflush(stdout);

        printf("String Input: %s\n", hexstring);

        hexstrlen = strlen(hexstring);

        //declaring variables here because they are used with the loop and some need to be redeclared
        int bitcount = 0;
        int charcount = 0;
        int outcount = 0;
        char outstring[MAXLINE] = {'\0'};
        unsigned int temp;
        int codelen = hexstrlen*4;
        int bitsleft = codelen;

        //loop that exists while bits counted is less than the length of code
        while(bitcount < codelen) {

            for (charcount = 0; charcount < 26; charcount++) { //for each letter of alpha

                temp = (binarystr >> (codelen-bitcount)); //sets temp to the bits to be tested
                if (temp == code[charcount] && bitcount == bits[charcount]) { //if match
                    outstring[outcount++] = ('A' + charcount); //puts in string
                    if (outstring[outcount-1] == '[') { //test case for EOT
                        break;
                    }

                    //next two lines remove already tested code from string
                    binarystr -= (temp << (codelen-bitcount)); 
                    binarystr = binarystr << bitcount;
                    //resetting variable and subtracting bits tested from total
                    temp = 0;
                    bitsleft -= bitcount;
                    bitcount = 0;

                    break;
                }

            } 
            //test cases for break case
            if (bitcount > 10) {
                break; 
            }
            if (bitcount > bitsleft) {
                break;
            }   
            if (outstring[outcount-1] == '[') {
                break;
            }
            bitcount++;   
        } 
        printf("Resulting Code: %s\n", outstring);      
    }

    return 0;
}
