/*
    prog6.c
    Richard Coffey
    rrcoffe
    ECE-222

    Purpose: Using signals to direct 3 submarines (child processes)     on their mission to launch their payload using mission control

    ***Usage: For ease of use with systems that have tons of terminals open, or with terminals that start at really high numbers, I have made the user input the terminal #'s on the command line, in the form of:

    ./prog6 MissionControl Sub1 Sub2 Sub3

    Simply type in "tty" in each of the 4 terminals you would like to use, and then input the numbers in order of what you would like the terminals to be. By doing this, the user can use the terminals they want, instead of the first 4 that are open.

    I had discussed with Dr. Reid, and he said that this was ok, as long as there was a note to users, and an appropriate error code for wrong usage.


    Bugs: None

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


int launched; //indicates whether all missles have been launched
int missles; //# of missles
int fuel; //amount of fuel
int alarmrung; //dummy alarm variable 
int back; //determines whether the sub is going or coming back to base

//the purpose of this is just to keep sounding the alarm for the children
void alrm(int signum) {

    alarmrung = 1;

}

//subtracts missle from total
void launch(int signum) {

    if (missles != 0) {
        missles -= 1;
    }

}

void fuelUp(int signum) {

    //there were contradictory instructions on what "rn" should do. The instruction to reset fuel to a random number between 1000-5000 didn't really make sense if there was more than 1000 gallons left, so I used the other instruction that said to just reset to 5000 gallons.
    fuel = 5000;
}


void Sub (int sNum, FILE *fpt) {

    int disTemp;
    int fuelTemp;
    int mcD = 0; //mission control distance    

    //setting up the signal handlers
    signal(SIGALRM, alrm);  
    signal(SIGUSR1, launch);
    signal(SIGUSR2, fuelUp); 

    //seeding the drand48
    srand48(time(NULL)+sNum);
    fuel = 5000 * drand48();
    while (fuel < 1000) {
        fuel = 5000 * drand48();
    }

    missles = 10 * drand48();
    while (missles < 6) {
        missles = 10* drand48();
    }

    //dealing with time printing 
    time_t mTime;
    struct tm * timeinfo;
    time(&mTime);
    timeinfo = localtime(&mTime);
      
 
    //first message for the terminals from the child processes
    fprintf(fpt, "Time: %s", asctime(timeinfo));
    fprintf(fpt, "Sub %d initiating mission. %d gallons left, %d missles left, %d miles from base\n", sNum, fuel, missles, mcD);

    alarm(1);

    //the purpose of this loop is to test the children every time there is an alarm to see whatmust be done with the new updates, such as missle count. When this loop meets proper conditions, it exits with a code.
    while(1) {
        pause();

        mTime = time(NULL);

        if (back == 1 && (mcD == 0 || mcD < 0)) {
            fprintf(fpt, "Made it home\n");
            exit(3);
        }

        if (fuel == 0 || fuel < 0) {
            fprintf(fpt, "Submarine %d dead in the water\n", sNum);
            exit(2);
        }

        if (launched == 0 && back == 0 && missles != 0) { 

            time(&mTime);
            timeinfo = localtime(&mTime);
            fprintf(fpt, "Time: %s", asctime(timeinfo));
            fprintf(fpt, "Sub %d to base. %d gallons left, %d missles left, %d miles from base\n", sNum, fuel, missles, mcD);
        } 

        if (back == 1 && launched == 1) {
            time(&mTime);
            timeinfo = localtime(&mTime);
            fprintf(fpt, "Time: %s", asctime(timeinfo));
            fprintf(fpt, "Sub %d to base. %d gallons left, %d missles left, %d miles from base\n", sNum, fuel, missles, mcD);
        }

        if (back == 0 && missles == 0) {
            fprintf(fpt, "Payload launched, returning to base\n");
            back = 1;
            launched = 1;
            
        }

        if (fuel <= 500) {
            fprintf(fpt, "Sub %d running out of fuel!\n", sNum);
        }

        if (back == 0) {
            disTemp = 10 * drand48();
            while (disTemp < 5) {
                disTemp = 10 * drand48();
            }    
            mcD += disTemp;
        }

        if (back == 1) {
            disTemp = 8 * drand48();
            while (disTemp < 3) {
                disTemp = 8 * drand48();
            }
            mcD -= disTemp;

        }

        if (fuel != 0 ) {
            fuelTemp = 200 * drand48();
            while (disTemp < 100) {
                disTemp = 200 * drand48();
            }
            fuel -= fuelTemp;
            
        }

        if (alarmrung > 0) {
            alarmrung = 0;

            alarm(1);
        }


    } 
}

void MC (int sNum, FILE *fpt, int *pid) {

    char text[50];

    while(1) {
        printf("enter command: \n");
        scanf("%s", text);

        //l launches missle
        if (strcmp(text,"l1") == 0) {
            kill(pid[0], SIGUSR1);
        }
        if (strcmp(text,"l2") == 0) {
            kill(pid[1], SIGUSR1);
        }
        if (strcmp(text,"l3") == 0) {
            kill(pid[2], SIGUSR1);
        }

        //s stands for scuttle (quit) process
        if (strcmp(text,"s1") == 0) {
            printf("Scuttled Submarine 1\n");
            kill(pid[0], SIGKILL);
        }
        if (strcmp(text,"s2") == 0) {
            printf("Scuttled Submarine 2\n");
            kill(pid[1], SIGKILL);
        }
        if (strcmp(text,"s3") == 0) {
            printf("Scuttled Submarine 3\n");
            kill(pid[2], SIGKILL);
        }

        //r stands for refuel the sub
        if (strcmp(text,"r1") == 0) {
            kill(pid[0], SIGUSR2);
        }
        if (strcmp(text,"r2") == 0) {
            kill(pid[1], SIGUSR2);
        }
        if (strcmp(text,"r3") == 0) {
            kill(pid[2], SIGUSR2);
        }
    
        //q stand for quit
        if (strcmp(text, "q") == 0) {
            kill(pid[0], SIGKILL);
            kill(pid[1], SIGKILL);
            kill(pid[2], SIGKILL);
            exit(5);
        }
    }
}

#define NUMTTYS 4


int main( int argc, char *argv[] ) { 

    FILE *fpt[NUMTTYS];
    int ttyindex;
    char strDev[100];
    int Terminal[NUMTTYS];
    int term_cnt = 0;
    int pid[NUMTTYS], i;
    int wait_ret1, wait_ret2, wait_ret3;
    int child_status1, child_status2, child_status3;
    int exit_byte;
    int exitSub1, exitSub2, exitSub3;
    int success = 0;    

    //determines if usage is correct
    if (argc != NUMTTYS+1) {
        printf("Usage: ./prog6 1 2 3 4, where the numbers are the terminal pts values\n");
        exit(1);
    }

    // determine which ttys are open and available to this user
    for (term_cnt = 0; term_cnt < NUMTTYS; term_cnt++)
    { 
        ttyindex = -1;
        ttyindex = atoi(argv[term_cnt+1]);
        if (ttyindex < 1) {
            printf("invalid terminal number %s\n", argv[term_cnt+1]);
            exit(1);
        }

        sprintf(strDev, "/dev/pts/%d", ttyindex);

        //puts ttyindex in Terminal array for later access
        if ((fpt[term_cnt] = fopen(strDev,"w")) != NULL) {
            Terminal[term_cnt] = ttyindex;
        } else {
            printf("failed to open terminal %s\n", strDev);
            exit(1);
        }
    }

    //for each terminal, send a initialization message to make sure that you can print to it
    for (ttyindex=0; ttyindex < term_cnt; ttyindex++)
    {

        if (ttyindex == 0) {
            fprintf(fpt[ttyindex], "Hello terminal %d, you are mission control\n", Terminal[ttyindex]);
        }
        if (ttyindex != 0) {
            fprintf(fpt[ttyindex], "Hello terminal %d, you are submarine %d\n", Terminal[ttyindex], ttyindex);
        }
    }


    i = 0;
    pid[i] = fork(); //1st child fork
    if (pid[i] != 0) { //parent
        i++;
        pid[i] = fork(); //2nd child fork
        if (pid[i] != 0) { //parent
            i++;
            pid[i] = fork(); //3rd child fork
            if (pid[i] != 0) { //parent
                i++;
                pid[i] = fork(); //4th child fork
                if (pid[i] != 0){ //parent
                    i++;
                }
                else{
                    MC(4, fpt[0], pid);
                }

            } else{
                Sub(3, fpt[3]);
            }
        } else{
            Sub(2, fpt[2]);    
        }
    } else{
        Sub(1, fpt[1]);
    } 

    //remeber to kill mission control after 
    //wait pid child process use 3 waits

    //waiting for sub 1
    wait_ret1 = wait(&child_status1);
    for (i = 0; i < 3; i++) {
        if (pid[i] == wait_ret1) {
            exitSub1 = i+1;
        }
    }
    exit_byte = child_status1 >> 8;
    if (exit_byte == 2) {
        printf("Rescue is on the way, Submarine %d\n", exitSub1);       
    }
    if (exit_byte == 3) {
        printf("Welcome home, Submarine %d\n", exitSub1); 
        success++;      
    } 

    //waiting for sub 2
    wait_ret2 = wait(&child_status2);
    for (i = 0; i < 3; i++) {
        if (pid[i] == wait_ret2) {
            exitSub2 = i+1;
        }
    }
    //move exit_byte over 8 bits
    exit_byte = child_status2 >> 8;
    if (exit_byte == 2) {
        printf("Rescue is on the way, Submarine %d\n", exitSub2);       
    }
    if (exit_byte == 3) {
        printf("Welcome home, Submarine %d\n", exitSub2);  
        success++;     
    } 

    //waiting for sub 3
    wait_ret3 = wait(&child_status3);
    for (i = 0; i < 3; i++) {
        if (pid[i] == wait_ret3) {
            exitSub3 = i+1;
        }
    }
    exit_byte = child_status3 >> 8;
    if (exit_byte == 2) {
        printf("Rescue is on the way, Submarine %d\n", exitSub3);       
    }
    if (exit_byte == 3) {
        printf("Welcome home, Submarine %d\n", exitSub3);
        success++;       
    } 

    if (success == 3) {
        printf("Congratulations team: Mission successful\n");
    }
    else { 
        printf("Mission failed\n");
    }
    
    kill(pid[3], SIGHUP);

    
    //closes all file pointers
    for (ttyindex=0; ttyindex < term_cnt; ttyindex++)
    { 
        fclose(fpt[ttyindex]);
    }

return 0;
}


