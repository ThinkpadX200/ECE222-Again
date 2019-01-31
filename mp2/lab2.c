/*Richard Coffey
*William Reid
*ECE 222
*Lab2
*
*Description: A simple menu driven interface that allows the user to input attributes about a football player. The user can display the data, or clear all the data as well.
*
*Assumptions: Input should be realistic for an athlete
*
*Bugs: Occasional buffer overflow due to the scanf statements. Tried to minimize these best I could.
*
*
*
*/



#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main() { 

    //variables
    int i;
    char firstname[33] = {'\0'};
    char middlename = '\0';
    char lastname[33] = {'\0'};
    char position[4] = {'\0'};
    char rating[6] = {'\0'};
    int age = -1;
    char state[3] = {'\0'};
    int feet = -1;
    int inches = -1;
    int weight = -1;
    char twitter[33] = {'\0'};
    long double bribe = -1;
    long double mps = -1;
    int arrests = -1;
    int quit = 0;
    char input[33] = {'\0'}; 
    int slen;   

    while (quit == 0) { 
        printf("Below is a menu to display or enter attributes for the football player. \n");
        printf("Type a menu command as it is displayed. \n");
        printf("If you would like to quit, type 'Quit'\n\n");

        printf("-Enter Name\t\t\t-Enter Twitter Account\n-Enter Position\t\t\t-Enter Money Paid\n-Enter Rating\t\t\t-Enter Arrests\n-Enter Age\t\t\t-Display Data\n-Enter State\t\t\t-Clear all Data\n-Enter Height and Weight\t-Quit\n\n");

        //scans until new line to get command
        scanf(" %[^\n]", input);
        slen = strlen(input);
        input[slen] = '\0';

        //begin stupidly long if-elseif chain for commands

        if (strcmp(input,"Enter Name") == 0) {

            //firstname
            printf("Please enter first name.\n");
            scanf(" %33s", firstname);
            while (strlen(firstname) > 32) {
                // firstname = {'\0'};
                printf("First name cannot be longer than 32 characters, please enter again.\n");
                scanf(" %33s", firstname);
            }
            //middle name
            printf("Please enter middle initial.\n");
            scanf(" %c", &middlename);
            while (isalpha(middlename) == 0) { 
                printf("Please use only a single character\n");
                scanf(" %c", &middlename);
            }
            //last name
            printf("Please enter last name.\n");
            scanf(" %33s", lastname);
            while (strlen(lastname) > 32) {
                // lastname = {'\0'};
                printf("Last name cannot be longer than 32 characters, please enter again.\n");
                scanf(" %33s", lastname);
            }
        }
        //position
        else if (strcmp(input,"Enter Position") == 0) {
            printf("Please enter player position: \n");
            scanf(" %4s", position);
            while (strlen(position) > 3 || strlen(position) < 2) {
                // position = {'\0'};
                printf("Position cannot be longer than 3 characters, please enter again.\n");
                scanf(" %4s", position);
                if (strlen(position) < 4 && strlen(position) > 1 ) {
                    break;
                }
            }

        }
        //Rating
        else if (strcmp(input,"Enter Rating") == 0) {

            printf("Please enter player rating from 1-5 using asterisks ONLY. If player has 0 stars, enter in 'None'.\n");
            scanf(" %6s", rating);
            //checks to make sure input is correct
            if (strcmp(rating, "None") != 0) {
                while (rating[0] != '*') {
                    printf("Please use asterisks ONLY!\n");
                    scanf(" %6s", rating);
                }
                
                //checks to make sure we don't go over 5 stars
                while (strlen(rating) > 5) {
                    // rating = {'\0'};
                    printf("Rating cannot be greater than 5 stars, please enter again.\n");
                    scanf(" %6s", rating);
                }

            }
        }
        //age
        else if (strcmp(input,"Enter Age") == 0) {
            printf("Please enter player age from 1-99\n");
            scanf(" %4i", &age);
            while (age > 99 || age < 1) {
                printf("Age must be within the range 1-99, please try again.\n");
                scanf(" %4i", &age);
                if (age < 100 && age > 0 ) {
                    break;
                }
            }

        }

        //State
        else if (strcmp(input,"Enter State") == 0) {
            printf("Please enter player state: \n");
            scanf(" %3s", state);
            while (strlen(state) != 2) {
                // state = {'\0'};
                printf("State must be 2 characters, please enter again.\n");
                scanf(" %3s", state);
            }


        }

        //Height/weight
        else if (strcmp(input,"Enter Height and Weight") == 0) {
            printf("Please enter player height (feet): \n");
            scanf(" %2i", &feet);
            while (feet > 7 || feet < 0) {
                printf("Feet must be within range 0-7, please enter again.\n");
                scanf(" %2i", &feet);
                if (feet < 8 && feet > 0 ) {
                    break;
                }
            }
            printf("Please enter player height (inches): \n");
            scanf(" %3i", &inches);
            while (inches > 11 || inches < 0) {
                printf("Inches must be within range 0-11, please enter again.\n");
                scanf(" %3i", &inches);
                if (inches < 12 && inches > 0 ) {
                    break;
                }
            }
            printf("Please enter player weight: \n");
            scanf(" %4i", &weight);
            while (weight > 500 || inches < 0) {
                printf("Weight must be within range 0-500, please enter again.\n");
                scanf(" %4i", &weight);
                if (weight < 501 && weight > 0 ) {
                    break;
                }
            }


        }

        //twitter account
        else if (strcmp(input,"Enter Twitter Account") == 0) {
            printf("Please enter twitter account name.\n");
            scanf(" %33s", twitter);
            while (strlen(twitter) > 32) {
                // twitter = {'\0'};
                printf("Twitter name cannot be longer than 32 characters, please enter again.\n");
                scanf(" %33s", twitter);
            }


        }

        //money paid
        else if (strcmp(input,"Enter Money Paid") == 0) {        
            printf("Please enter bribe money offered.\n");
            scanf(" %101Lf", &bribe);
            while (bribe > pow(10, 100) || bribe < 0) {
                // twitter = {'\0'};
                printf("Bribe money must be within range 0-10^100, please enter again.\n");
                scanf(" %101Lf", &bribe);
                if (bribe < pow(10, 100) && bribe > 0) {
                    break;
                }
            }

        }

        //arrest
        else if (strcmp(input,"Enter Arrests") == 0) {
            printf("Please enter number of arrests.\n");
            scanf(" %5i", &arrests);
            while (arrests > 1000  || arrests < 0) {
                // twitter = {'\0'};
                printf("Number of arrests must be within range 0-1000, please enter again.\n");
                scanf(" %4i", &arrests);
                if (arrests < 1001 && arrests > 0 ) {
                    break;
                }
            }


        }
        else if (strcmp(input,"Display Data") == 0) {
            //begin long if else section for data display
            //if variable has impossible value, i.e. -1 or Null, it flags as undefined

            if (firstname[0] == '\0') {    
                printf("First name: Undefined\n");
            } else { 
                printf("First name: %s\n", firstname);
            }

            if (middlename == '\0') {    
                printf("Middle Initial: Undefined\n");
            } else { 
                printf("Middle initial: %c\n", middlename);
            }

            if (lastname[0] == '\0') {    
                printf("Last name: Undefined\n");
            } else { 
                printf("Last name: %s\n", lastname);
            }

            if (position[0] == '\0') {    
                printf("Position: Undefined\n");
            } else { 
                printf("Position: %s\n", position);
            }

            if (rating[0] == '\0') {    
                printf("Rating: Undefined\n");
            } else { 
                printf("Rating: %s\n", rating);
            }

            if (age == -1) {    
                printf("Age: Undefined\n");
            } else { 
                printf("Age: %i\n", age);
            }

            if (state[0] == '\0') {    
                printf("State: Undefined\n");
            } else { 
                printf("State: %s\n", state);
            }

            if (feet == -1 || inches == -1) {    
                printf("Height: Undefined\n");
            } else { 
                printf("Height: %i'%i""\n", feet, inches);
            }

            if (weight == -1) {    
                printf("Weight: Undefined\n");
            } else { 
                printf("Weight: %ilbs\n", weight);
            }

            if (twitter[0] == '\0') {    
                printf("Twitter: Undefined\n");
            } else { 
                printf("Twitter Account: @%s\n", twitter);
            }

            if (bribe == -1) {    
                printf("Bribe Money Offered: Undefined\n");
            } else { 
                printf("Bribe Money Offered: %Lf\n", bribe);
            }
            if (arrests == -1) {    
                printf("Arrests: Undefined\n");
            } else { 
                printf("Arrests: %i\n", arrests);
            }

            if (strcmp(rating, "None") == 0 || rating[0] == '\0') {
                printf("Money offered per star: NAN\n\n");
            } else {
                mps = bribe/(strlen(rating));
                if (mps < 0) {
                    printf("Money offered per star: NAN\n\n");    
                } else {
                    printf("Money offered per star: %Lf\n\n", mps);
                }
            }
        }

        //resetting data back to impossible values to trigger undefined printing
        else if (strcmp(input,"Clear all Data") == 0) {

            for (i = 0; i < (strlen(firstname)); i++) {
                firstname[i] = '\0';
            }

            middlename = '\0';


            for (i = 0; i < (strlen(lastname)); i++) {
                lastname[i] = '\0';
            }

            for (i = 0; i < (strlen(rating)); i++) {
                rating[i] = '\0';
            }

            for (i = 0; i < (strlen(state)); i++) {
                state[i] = '\0';
            }

            for (i = 0; i < (strlen(twitter)); i++) {
                twitter[i] = '\0';
            }

            bribe = -1;
            feet = -1;
            inches = -1;
            weight = -1;
            age = -1;
            arrests = -1;
            mps = -1;

        }
        else if (strcmp(input,"Quit") == 0) {
            quit = 1;
            return 0;

        }
        //Catch all if command is put in wrong
        else {
            printf("Command not understood, input is case-sensitive! Be careful to input realistic attributes!\n");

        }

        //resets input buffer
        for (i = 0; i < (strlen(input)); i++) {
            input[i] = '\0';
        }

        }
        return 0;
    }
