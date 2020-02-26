#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/shm.h>
//add/remove includes
#define BUF_SIZE 1024


//define struct
typedef struct pipe {
   int cnt;
   int complete;
   char buf[BUF_SIZE];
//add/remove variables
} 
pipe_t;

pipe_t *pipe_open(){	
	//use shmget() to create a new shared memory segment segment using private memory as key(IPC_PRIVATE)
}
int pipe_read(shmseg  * p, char *buf, int bytes){
	//use shmat{} to attach to the segment to get a pointer to it.
	//read from share memory and use shmdt() to detach the shared memory segment 
}
int pipe_write(pipe_t  * p, char *buf, int bytes){
	//use shmat{} to attach to the segment to get a pointer to it.
	//write to share memory and use shmdt() to detach the shared memory segment 
}
pipe_t *pipe_close(pipe_t *p){
	//use shmctl() to mark the segment to be destroyed (IPC_RMID)
}

int main(void)
{
        //define variables
        pid_t   childpid;
        char    string[] = "Hello, world!\n";	//sent string
        char    readbuffer[80];	//returned string
	//add/remove variables
        pipe_t pipe = pipe_open();	//open the pipe
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }
        if(childpid == 0)
        {
                /* Send "string" through the "pipe" */
                pipe_write(pipe, string, (strlen(string)+1));
                exit(0);
        }
        else
        {	
		//wait for child to write to pipe
		wait(NULL);
                /* Read in a string from the "pipe" */
                nbytes = pipe_read(pipe, readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}
