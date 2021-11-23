#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

static void batman(int signal){
    if(signal == SIGINT){
        int fd = open("info.data", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd == -1){
            printf("Error, Message is: %s", strerror(errno));
        }

        char * message = "BAD BAD, PROGRAM EXIT";
        write(fd, message, strlen(message));
        exit(0);
    }else if(signal == SIGUSR1){
        printf("PPID: %d\n", getppid());
    }
}

int main(){
    signal(SIGINT, batman);
    signal(SIGUSR1, batman);

    while(1==1){
        printf("PID: %d\n", getpid());
        sleep(1);
    }
}
