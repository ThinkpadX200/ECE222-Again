/* lab1.c
 * Richard Coffey
 * rrcoffe
 * ECE 2220, Fall 2016
 * MP1
 *
 * NOTE:  You must update all of the following comments!
 * 
 *Purpose: A binary calculator that is used to calculate the sum, difference, product, and quotient of two binary numbers and output the result in binary
 *
 * Assumptions: Since the operands are unsigned, negative values cannot be used with this calculator
 *
 * Bugs: 
 * - This program will only accept up to 32bit numbers, any sample value greater than 2,147,482,647 will overflow the memory value.
 * - "quit" must be entered in twice in order to quit the function 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//main loop 
int main() {

    //initial print
    //    printf("Please input as follows: Operand1 Operation Operand2 \n");

    //variables
    unsigned int operand1 = 0;
    unsigned int operand2 = 0;
    int decimal1, decimal2;
    char operator;
    int temp = 0;
    int remainder;
    int divrem;
    int base = 1;
    int i = 1;
    unsigned int answer;
    unsigned int binanswer = 0;
    char q[31] = {'\0'};
    char r[31] = {'\0'};

    //repeats until exited
    while (1) {

        //set/reset important variables
        temp = 0;
        remainder = 0;
        base = 1;
        binanswer = 0;
        i = 1;
        decimal1 = 0;
        decimal2 = 0;

        //input request
        printf("Please input as follows: Operand1 Operation Operand2. Type 'quit' to quit. \n");
        scanf("%s %c %s", r, &operator, q);
        //checks for quit
        if (q[0] == 'q' || r[0] == 'q') { 
            printf("Good bye!\n");
            return 0;
        } 
        //if no quit then put strings into into ints
        else {
            operand2 = atoi(q);
            operand1 = atoi(r);
        }

        //checks for correct operator: +,-,*,/ in that order
        if (operator != '+' && operator != '-' && operator != '*' && operator != '/') {
            printf("Please use one of the following operations: + - * / \n");
        }
        //makes sure q is not over 32 bits
        else if (strlen(q) > 10) {
            printf("Operand too long, please limit to 31 bits\n");
        }
        //makes sure operands aren't over 32bits
        else if (operand1 > 2147483647 || operand2 > 2147483647) {
            printf("Operand too big, please limit to 31 bits!\n");
        }
        else if (q[0] != '1' && q[0] != '0' && r[0] != '1' && r[0] != '0') {
            printf("Please enter binary numbers.\n");
        }
        else {


            //turns binary operands into decimals

            while (operand1 > 0) {
                remainder = operand1 % 10;
                temp = temp + (remainder * base);
                operand1 /= 10;
                base *= 2;
            }

            decimal1 = temp;
            base = 1;
            temp = 0;
            remainder = 0;

            while (operand2 > 0) {
                remainder = operand2 % 10;
                temp = temp + (remainder * base);
                operand2 /= 10;
                base *= 2;
            }

            decimal2 = temp;
            base = 1;
            temp = 0;
            remainder = 0;

            //addition
            if (operator == '+') {
                answer = decimal1 + decimal2;
            }

            //subtraction
            if (operator == '-') {
                answer = decimal1 - decimal2;
                if (decimal2 > decimal1) { 
                    answer = 0;
                }
            }

            //multiplication
            if (operator == '*') {
                answer = decimal1 * decimal2;
            }

            //division
            if (operator == '/') {
                answer = decimal1 / decimal2;
                divrem = decimal1 % decimal2;
            }

            //decimal to binary
            while (answer > 0) {
                remainder = answer%2;
                answer /= 2;
                binanswer = binanswer + (remainder*i);
                i *= 10;
            }


            //prints answer for division case
            if (operator == '/') {
                printf("= %i, with remainder of %i\n", binanswer, divrem);
            }
            //prints answer for all other cases
            else {
                printf("= %i\n", binanswer);
            }
        }

    }
    return 0;

}


