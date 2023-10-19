#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void 
find(char* path,char* file_name)
{
    char buf[512],*p;
    int fd;
    struct dirent de;
    struct stat st;
    
    //查看路径是否能打开
    if((fd = open(path,0))<0)
    {
        fprintf(2,"find: cannot open %s\n",path);
        return;
    }
      // 检查并将文件信息放到st中
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    // 检查文件类型的种类
    switch(st.type){
    // 文件直接显示信息
    case T_FILE:
        fprintf(2,"Usage: find should pass dir \n");
        break;
    // 目录
    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        // 将目录的drent结构遍历
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
        // 该目录项为空，跳出
            if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("find: cannot stat %s\n", buf);
                continue;
            }
            if(st.type==T_DIR){
                find(buf,file_name);
            }else if(st.type == T_FILE){
                if(!strcmp(de.name,file_name))
                    printf("%s\n",buf);
            }     
    }
    break;
  }
    close(fd);
}

int 
main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(2,"Usage: find need at least two arguments\n");
        exit(1);
    }else if(argc == 2)
    {
        find(".",argv[1]);
    }else
    {
        for(int i=2;i<argc;i++)
            find(argv[1],argv[i]);
    }
    exit(0);
}
