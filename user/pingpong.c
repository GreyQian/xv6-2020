#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc,char* argv[])
{
    if(argc != 1)
    {
        fprintf(2,"Usage: pingpong only use one argument\n");
        exit(1);
    }
    int p1[2],p2[2];
    pipe(p1);pipe(p2);
    char str[10];
    int pid = fork();
    if(pid > 0){
        close(p1[0]);
        close(p2[1]);

        write(p1[1],"parent\n",sizeof("parent\n"));
        close(p1[1]);

        read(p2[0],str,sizeof(str));
        printf("%d: received pong\n",getpid());

        close(p2[0]);
        wait(0);
    }else if(pid == 0){
        close(p1[1]);
        close(p2[0]);

        read(p1[0],str,sizeof(str));
        close(p1[0]);

        printf("%d: received ping\n",getpid());

        write(p2[1],"child\n",sizeof("child\n"));
        close(p2[1]);

    }else{

        fprintf(2,"fork error\n");
        close(p1[0]);
        close(p2[0]);
        close(p1[1]);
        close(p2[1]);
        exit(1);
        
    }
    exit(0);
}