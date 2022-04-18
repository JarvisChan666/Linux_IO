//
// Created by 74476 on 2022/4/18.
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>
#include <time.h>
//this is Jarvis Chan
//
int main() {
#if 0
    //create file
    int fd;
    fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);//如果文件存在，会截断为0，不存在就创建,还要补充访问权限
    if (-1 == fd)
    {
        perror("open errtor");
        return 0;
    }
    unlink("test.txt");//硬链接数-1，但并没有真正删除. 文件不会显示硬链接数为0的文件
    write(fd,"hello world",11);//11byte
    lseek(fd,0,SEEK_SET);
    char buf[128] = {0};
    read(fd,buf,128);//如果能读出来说明文件没删除,但要把光标移动到开头位置，因为write完是在结尾
    printf("%s\n",buf);
#endif
#if 0

    int fd;
    fd = open("unlink.c",O_RDWR);
    if(-1 == fd)
    {
        perror("open error");
        return 0;
    }
    //get 属性
    //在stat结构体中访问
    struct stat st;//mingw64自带的结构体，无需自己实现
    fstat(fd,&st);//fstat传文件描述符进来访问(f=fd,一般在文件打开之后），而stat函数就传入文件名（就不用打开文件)
    //此时st变量就有了fd文件的相关属性,接下来就一一访问，具体结构体信息可查看man 2 stat
    printf("%ld\n",st.st_atime);//最近访问时间
    printf("%ld\n",st.st_mtime);//modify最近更改时间 对内容
    printf("%ld\n",st.st_ctime);//chmod 最近改动时间  对属性改动   ？？此处有问题
    //struct tm *localtime(const time_t *timep);//time.h 中定义的结构体tm,
    //用localtime转换
    //网络日志经常用！！！重点
    struct tm *t;//tm是time.h里有的结构体 ，其详细内容在尾部
    t = localtime(&st.st_atime);//这里用time.h中的函数，获得stat结构体中的访问时间
    printf("%d-%d-%d %d-%d-%d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

    time_t t1;//time_t 是在stat中的时间类型，一个整数，1970到现在的秒数
    t1 = time(NULL);//1970.1.1 to 当前时间
    //struct tm *localtime(const time_t *timep)
    t = localtime(&t1);//年月都做了相应的处理，将time_t类型的时间转换为时间结构体tm，
    printf("%d-%d-%d %d-%d-%d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    // time_t time(time_t *t);

    //时间结构体
#endif
    struct stat st;//类型为stat结构体的变量st,其内部存储的时间类型是time_t
    struct tm *t;//time.h里的结构体tm
    t = localtime(&st.st_atime);//这里t调用time.h中的localtime函数，传入time_t类型的时间(有三种时间)的地址，从而获得时间，本例子为访问时间，
    //用结构体指针指向结构体内的具体内容，
    printf("%d-%d-%d %d-%d-%d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    //time.h中定义的时间结构体tm
    //struct tm
    // tm_sec    The number of seconds after the minute, normally in the range
    //                 0 to 59, but can be up to 60 to allow for leap seconds.
    //       tm_min    The number of minutes after the hour, in the range 0 to 59.
    //       tm_hour   The number of hours past midnight, in the range 0 to 23.
    //       tm_mday   The day of the month, in the range 1 to 31.
    //       tm_mon    The number of months since January, in the range 0 to 11.
    //       tm_year   The number of years since 1900.
    //       tm_wday   The number of days since Sunday, in the range 0 to 6.
    //       tm_yday   The number of days since January 1, in the range 0 to 365.



    time_t t1;//time_t 是在stat中的时间类型，一个整数，1970到现在的秒数
    t1 = time(NULL);//1970.1.1 to 当前时间
    //struct tm *localtime(const time_t *timep)
    t = localtime(&t1);//年月都做了相应的处理，将time_t类型的时间转换为时间结构体tm，
    printf("%d-%d-%d %d-%d-%d\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
    return 0;
}