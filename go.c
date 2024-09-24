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
    pid_t pidLeft, pidRight;
	int fd[2];

    //printf("Implementing the shell command: cat someFile.txt | more\n" );
	/** create the pipe */
	if ( pipe(fd) == -1 ) 
	{
        fprintf(stderr,"Pipe failed");
        return 1;
	}

    pidLeft = Fork();
	if ( pidLeft == 0 )   /* Left-Child process */
	{	/* close the unused end of the pipe */
        close(  fd[READ_END]   );

        /* overwrite the stdout of Left-Child to the write-end of the pipe */
        dup2(   fd[WRITE_END]   ,    STDOUT_FD   ) ;

        // start the new executable for the Left-Child
        if( execlp("./user", "tom", NULL) < 0)
        {
            perror("execlp Left-Chiled Failed");
            exit(-1) ;
        }
	}
	else /* Parent process */
	{
        /* now fork the Right-Child process */
        pidRight = Fork();
        if ( pidRight == 0)   /* Right-Child process */
        {
            /* close the unused end of the pipe */
            close(   fd[WRITE_END]   );

            /* Overwrite the stdin of Right-Child 
               to the read-end of the pipe */
            dup2(    fd[READ_END]   ,    STDIN_FD   ) ;

            // start the new executable for the Left-Child
            if( execlp("/bin/more", "Jerry" , NULL) < 0 )
            {
                perror("execlp Right-Chiled Failed");
                exit(-1) ;
            }
        }
        else /* Parent process */
        { 
            // Parent:  Close both ends of the pipe
			close(   fd[READ_END]    ) ;
            close(   fd[WRITE_END]    ) ;

            // Wait for left-child to end
			waitpid( pidLeft, NULL, 0) ;
            
			// wait for right-child to end
			waitpid(pidRight, NULL, 0 ) ;

            printf("At Your Command #\n" ) ;
        }
	}
	return 0;
}