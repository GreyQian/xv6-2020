#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// 需要注意的是这里的文件描述符不能共用，原始父进程的，否则会出现多个相同的数值
void 
primes(int p[2])
{
    int prime,flag,num;

    close(p[1]);
    if(read(p[0],&prime,4)!=4)
    {
        fprintf(2,"child read prime number eorro\n");
        exit(1);
    }
    
    //打印数字
    printf("prime %d\n",prime);
    // 这种退出控制并不推荐，是取巧的做法，正确的做法应该看提示
    // if(prime==31)
    //     exit(0);
    
    //应该看提示，当wait端退出的时候，read返回值为0
    flag=read(p[0],&num,4);
    if(flag)
    {
        int newp[2];
        pipe(newp);
        
        if(fork()==0)
        {
            primes(newp);
        }else
        {
            close(newp[0]);
            if(num%prime) write(newp[1],&num,4);
            while (read(p[0],&num,4))
            {
                if(num%prime)
                    write(newp[1],&num,4);
            }
            close(newp[1]);
            close(p[0]);
            wait(0);
        }
    }
    //return;
    //不能使用return退出？
    exit(0);
}

int 
main(int argc,char *argv[])
{
    if(argc >= 2){
        fprintf(2,"Usage: primes just need one arguments\n");
        exit(1);
    }
    int p[2];
    pipe(p);

    if(fork() == 0)
    {
        primes(p);
    }else
    {
        close(p[0]);
        for(int i=2;i<=35;i++)
        {
            if(write(p[1],&i,4)!=4)
            {
                fprintf(2,"write number error\n");
                exit(1);
            }
        }
        close(p[1]);
        wait(0);
        exit(0);
        
    }
    return 0;
}