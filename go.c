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
    pid_t userProcess, calcProcess;
	int requestPipe[2], replyPipe[2];

    //printf("Go started creating thes pipes\n" );
	/** create the pipe */
	if ( pipe(requestPipe) == -1 || pipe(replyPipe) == -1) 
	{
        fprintf(stderr,"Pipe failed");
        return 1;
	}

    userProcess = Fork();
	if ( userProcess == 0 )   /* Left-Child process */
	{	
        /* close the unused end of the pipes */
        close(requestPipe[READ_END]);
        close(replyPipe[WRITE_END]);

        printf("This is User process (id = %d).\n", getpid());
        printf("\tUser: Please, enter: value1 operation value2\n");
        
        /* pass the pipe desc to the users */
        char requestWrite[10], replyRead[10];
        sprintf(requestWrite, "%d", requestPipe[WRITE_END]);
        sprintf(replyRead, "%d", replyPipe[READ_END]);

        // start the new executable for the Left-Child
        if( execlp("./user", "user", requestWrite, replyRead, NULL) < 0)
        {
            perror("execlp Left-Chiled Failed");
            exit(-1) ;
        }
	}
	else /* Parent process */
	{
        /* now fork the Right-Child process */
        calcProcess = Fork();
        if ( calcProcess == 0)   /* Right-Child process */
        {

            /* close the unused end of the pipe */
            close(requestPipe[WRITE_END]);
            close(replyPipe[READ_END]);

            printf("This is Calculator process (id = %d).\n", getpid());
            /* Overwrite the stdin of Right-Child 
               to the read-end of the pipe */
            char requestRead[10], replyWrite[10];
            sprintf(requestRead, "%d", requestPipe[READ_END]);
            sprintf(replyWrite, "%d", replyPipe[WRITE_END]);
            
            // start the new executable for the Left-Child
            if( execlp("./calculator", "calculator", requestRead, replyWrite, NULL) < 0 )
            {
                perror("execlp Right-Chiled Failed");
                exit(-1) ;
            }
        }
        else /* Parent process */
        { 
            // Parent:  Close both ends of the pipes
			close(requestPipe[READ_END]);
            close(requestPipe[WRITE_END]);
            close(replyPipe[READ_END]);
            close(replyPipe[WRITE_END]);

            // Wait for left-child to end
            printf("Go is now waiting for User to terminate\n");
			waitpid( userProcess, NULL, 0) ;
            
			// wait for right-child to end
            printf("Go is now waiting for Calculator to terminate\n");
			waitpid(calcProcess, NULL, 0 ) ;

            printf("The Go process has terminated\n" ) ;
        }
	}
	return 0;
}