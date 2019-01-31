#include <stdio.h>
#include <unistd.h>



int main() {

int i, n;

n = fork(); 

printf("1"); fflush(stdout);

for(i=0; i<3; i++)
{
if (n == 0) 
{ sleep(3); printf("2"); fflush(stdout);
}
else
{ sleep(2); printf("3"); fflush(stdout);
}
}
}
