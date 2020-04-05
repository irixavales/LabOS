#include <stdio.h>
#include <mycalllib.h>

int main(){

    int c=5, pid=0, num_tickets = 0, i;
    for(i = 0; i < c; i++){
        pid = fork();
        if(pid == 0){
            num_tickets = 4+i*3;
            mycall(num_tickets);
            sleep(1);
            break;
        }
    }
    if(pid == 0){
        printf("This is child with %d tickets \n",num_tickets);
    }
    return 0;
}
