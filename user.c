/*-------------------------------------------------------------------------------
Assignment  : lab-04A
Date        : 9/25/24

Team        : 8
Author      : Ryan Mendez      mendezrh@dukes.jmu.edu
Author      : Nischal Lawot    lawotnr@dukes.jmu.edu

File Name   : user.c
-------------------------------------------------------------------------------*/

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{   
    int requestPipe = atoi(argv[1]);
    int replyPipe = atoi(argv[2]);

    int num1, num2;
    char op;

    // scans in the nums and op
    scanf("%d %c %d", &num1, &op, &num2);

    // sends the values in to the request pipe
    dprintf(requestPipe, "%d %c %d\n", num1, op, num2);
    printf("\tUser Sending the following: %d %c %d on FD %d\n", num1, op, num2, requestPipe);

    //read in result from calcualtor from reply pipe and put it in result
    int result;
    read(replyPipe, &result, sizeof(result));

    printf("User recieved the following result: %d from FD %d\n", result, replyPipe);
    return 0;
}
