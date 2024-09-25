/*-------------------------------------------------------------------------------
Assignment  : lab-04A
Date        : 9/25/24

Author      : Ryan Mendez      mendezrh@dukes.jmu.edu
Author      : Nischal Lawot    lawotnr@dukes.jmu.edu

File Name   : calculator.c
-------------------------------------------------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <unistd.h>

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
            return -1;
    } 

    dprintf(replyPipe, "%d %c %d = %d\n", num1, op, num2, result);
    return 0;
}
