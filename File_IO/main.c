#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>
#if 0
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
#endif
int main()
{/*
    int fd;
    fd = open("1.c",O_RDWR);
    if(-1 ==fd)
    {
        perror("open file error\n");
        return 0;
    }
*/
    //read data,what we read is multi_type,so we void *buf
    char data[100]={0};//一般1024
    char *p_data;
    p_data = (char *)malloc(10);//on heap
    memset(p_data,0,100);//clear

    int n;
#if 0
    //read 99byte(最多) data from fd(a file) to p_data(pointe to a heap)
    //返回what you read in reality,if 0,finish reading
    n = read(fd,p_data,99);//read to p_data where point to a heap place
    printf("n:%d",fd);
    printf("p_data:%s",p_data);
#endif
    //muiti read the data in file,until the end
    /*
    while(1)
    {
        n = read(fd,p_data,99);//read to p_data where point to a heap place
        if(0==n)
            break;//0 means the end
        printf("n:%d",fd);
    }
     *///改进版
    /*
    while(n = read(fd,p_data,99))//when n return 0,means you read the end,then it will break
    {
        //you need to clear the rest when you read the next，希望每次读取的是当前所指向的，就要清掉上次的内容
        printf("n:%d\n",fd);
        //此处可能有文件处理操作xxxx
        //p——data指针所指向的堆空间clear
        memset(p_data,0,100);//千万不要forget,类比舀奶茶，每次读99，最后一次还剩50，但我就想被子里50，得把上次的99倒掉，不能覆盖原空间！
    }
     */

    //write function
    int fd;
    fd = open("1.c",O_RDWR | O_APPEND);
    if(-1 ==fd)
    {
        perror("open file error\n");
        return 0;
    }
    char *buf = "hello world";//src
    //返回值：成功写入字节，写入失败0
    //write(fd,buf,5);//write how many byte,将buf所指向的空间的内容写到fd所指向的文件去，buf为const *void
    //如果不是O_APPEND写入，将会覆盖开头的n个覆盖掉，这个要注意！
    write(fd,"abc",3);
    close(fd);



    return 0;
}

