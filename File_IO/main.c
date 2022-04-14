#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
//有关open，close和报错信息
//自实现需求：
char * errorMsgArray[] = {"Success","ajdjd","fuc","dam"};
char * errorPrintf(int no){
    return errorMsgArray[no];
}
enum ERRNO
{
    Success,//不计数就0
    OTHER,
    NOFILE
};
int func1()
{
    //想达到成功调用返回0，失败2，长度太长返回3，模拟perror
    return NOFILE;
}

void func()
{
    int fd;
    fd = open("1.c",O_RDWR);//打开操作后要关掉

    printf("fd:%d\n",fd);

    /**/
    //close(fd)   //千万不要忘了关闭
}
int main()
{
    int fd;//文件描述符
    fd = open("1.c",O_RDWR,O_TRUNC);//trunc截尾
    printf("eoornum:%d\n",errno);//成功打开是0，失败是2
    perror("errormsg");//成功打开是success，失败就no such file。。
    printf("fd:%d\n",fd);
//    if(-1==fd)
//    {
//        perror("error open file\n");
//    }
    close(-100);//fd留出来给别人用
    printf("eoornum:%d\n",errno);//字符指针数组的下标，去访问perror的数组


    //内部
    perror("errormsg");//可以打印系统函数的出错原因，内部是个字符指针数组char *errorMsgArray,errornum为下标去访问
    //如果文件不存在就会被创建,若存在则打开
    /*
    fd = open("2.c",O_RDWR|O_CREAT,0664);
    printf("fd:%d\n",fd);
    if(-1==fd)
    {
        perror("error open file\n");
        return 0;
    }
    //写了open直接写close，然后把代码写中间
    close(fd);//一般最多1023 or2047个
     */

    //模拟perror内部实现原理
    //工作中就可以提供这样的机制给别人易于阅读错误
    int ret = func1();
    printf("ret:%d\n",ret);
    printf("errormsg:%s\n", errorPrintf(ret));
    return 0;

}