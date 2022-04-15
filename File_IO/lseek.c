//
// Created by 74476 on 2022/4/15.
//
//lseek光标便宜
//this is Jarvis Chan
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>
//off_t lseek(int fd, off_t offset, int whence);//whence is the start position,(seekset,seekcur,seekend
//返回值为距离文件开头位置的光标偏移量
int main()
{
    int fd;
    //文件可读写，以追加方式，打开
    //以O_APPEND打开，光标初始位置还是在文件开头，只是写入数据时会自动将光标移动到文件末尾，
    // 不要以为追加模式光标初始状态就是最后面
    fd = open("1.c",O_RDWR|O_APPEND);
    if(-1 == fd)
    {
        perror("file open error");
        return 0;
    }
    int n;
    //光标（cursor）当前位置偏移0位置，想知道当前光标距离文件开头的偏移量
    n = lseek(fd,0,SEEK_CUR);
    printf("n:%d\n",n);

    //将cursor移动到文件末尾
    n = lseek(fd,0,SEEK_END);//文件末尾偏移0个，返回值还是那个
    printf("n:%d\n",n);
    //小技巧：返回值就是文件字符个数！回车等都占字符
    //实际应用比如网络传输据，很多个包很多个编号，如何迅速定位缺失的包
    //比如每个包10k，假如第5个包丢了，就可以迅速移动。
    return 0;
}