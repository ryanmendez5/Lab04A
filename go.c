/*-------------------------------------------------------------------------------
Assignment  : lab-04A
Date        : 9/25/24

Author      : Ryan Mendez      mendezrh@dukes.jmu.edu
Author      : Nischal Lawot    lawotnr@dukes.jmu.edu

File Name   : go.c
-------------------------------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

/*-------------------------------------------------------*/
/* Wrapper function for fork()                           */
pid_t Fork(void)
{
    pid_t n;
    n = fork() ;
    if ( n < 0 ) 
    {
		perror("Fork failed");
		exit(-1) ;
    }
    return n ;
}

#define  READ_END	0
#define  WRITE_END	1
#define  STDIN_FD	0
#define  STDOUT_FD	1

int main(void)
{    

}