/*-------------------------------------------------------------------------------
Assignment  : lab-04A
Date        : 9/25/24

Team        : 8
Author      : Ryan Mendez      mendezrh@dukes.jmu.edu
Author      : Nischal Lawot    lawotnr@dukes.jmu.edu

File Name   : calculator.c
-------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{   
    // // for (int i = 0; i < argc; i++) {
    // //     printf("%d\n", argv[i]);
    // // }
    // if ( argc != 4 ) 
    // {
    //     printf("args: Number Operation Number\n");
    //     return -1;
    // }

    int requestPipe = atoi(argv[1]);
    int replyPipe = atoi(argv[2]);

    char buffer[100];
    int num1, num2, result;
    char op;

    // read the request from the pipe
    read(requestPipe, buffer, sizeof(buffer));
    sscanf(buffer, "%d %c %d", &num1, &op, &num2);
    printf("\tCalculator received the following: %d %c %d from FD %d\n", num1, op, num2, requestPipe);

    switch ( op )
    {
        case '+':   
            result = num1 + num2;
            break ;                 
        case '-':   
            result = num1 - num2;
            break ;
        case '*': 
            result = num1 * num2;
            break ;             
        case '/':   
            result = num1 / num2;
            break ;
        default:    
            printf("INVALID operation\n" );
            return 1;
    } 
    
    write(replyPipe, &result, sizeof(result));
    printf("Calculator sent the following to user: %d on FD %d\n", result, replyPipe);
    return 0;
}
