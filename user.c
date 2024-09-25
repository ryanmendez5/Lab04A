/*-------------------------------------------------------------------------------
Assignment  : lab-04A
Date        : 9/25/24

Author      : Ryan Mendez      mendezrh@dukes.jmu.edu
Author      : Nischal Lawot    lawotnr@dukes.jmu.edu

File Name   : user.c
-------------------------------------------------------------------------------*/

#include <stdio.h> 

int main(void)
{   
    int num1;
    int num2;
    char op;
    scanf("%d %c %d", &num1, &op, &num2);
    printf("%d %c %d\n", num1, op, num2);
    return 0;
}