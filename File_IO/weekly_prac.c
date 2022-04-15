//
// Created by 74476 on 2022/4/15.
//

//this is Jarvis Chan
//review on open close error lseek write read
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>

int main()
{
    //文件描述符file descriptor
    int fd;
    //以可读写以及可追加的方式打开文件，但要注意光标初始位置位于开头
    fd = open("1.c",O_RDWR | O_APPEND);
   if(-1==fd)//打开失败
   {
       perror("error to open file");
       printf("error_num%d\n",errno);//失败errno=2
       return 0;
   }
   char *buf = "hello chick";//想写入的内容
    char *p_data;
    p_data = (char *)malloc(10);//on heap
    memset(p_data,0,100);//clear
   int w = write(fd,buf,11);//if不是O_APPEND，将会从开头覆盖内容
   int r = read(fd,p_data,1);//每次读一个字节，读的数据相当于放在一个指向堆空间的地方
   while(r)//当读完后，r会返回0，自动跳出
   {
       printf("n:%d\n",fd);
       memset(p_data,0,10);//记得装完东西后想装新的记得倒掉
   }
   int j;
   j = lseek(fd,0,SEEK_CUR);//返回当前位置
    printf("seek_cur:%d\n",j);
   j = lseek(fd,0,SEEK_END);//返回全文件大小
    printf("j_end:%d\n",j);



    //写完open立刻写close
    close(fd);//
    return 0;
}