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
    // for (int i = 0; i < argc; i++) {
    //     printf("%d\n", argv[i]);
    // }
    if ( argc != 4 ) 
    {
        printf("args: Number Operation Number\n");
        return -1;
    }
    char op = argv[2][0];
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[3]);
    int result;

    switch ( op )
    {
        case '+':   
            result = num1 + num2 ;
            break ;
                    
        case '-':   
            result = num1 - num2 ;
            break ;

        case '*': 
        case 'x':   
        case 'X':   
            result = num1 * num2 ;
            break ;
                    
        case '/':   
            result = num1 / num2 ;
            break ;

        default:    
            printf("INVALID operation\n" );
            return -1;
    } ;
    printf("%d %c %d = %d\n", num1, op, num2, result);
    return 0;
}
