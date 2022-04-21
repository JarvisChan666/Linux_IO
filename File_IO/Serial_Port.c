/*********************************************************************************
  *Copyright(C),2022 by JarvisChan
  *FileName: Serial_Port.c 
  *Author:  //作者
  *Version:  //版本
  *Date:  2022 2022/4/21 8:35//完成日期
  *Description:  //用于主要说明此程序文件完成的主要功能
                //与其他模块或函数的接口、输出值、取值范围、
                //含义及参数间的控制、顺序、独立及依赖关系
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
**********************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>//文件相关信息判断
#include <termios.h>//this header must compile in linux env
//宏定义定义串口文件名
#define COM1 "/dev/ttyS1"
/*
 * @brief 初始化串口
 * @param file 串口所对应的设备文件名
 * @param baudrate 串口波特率
 * @return 成功就返回串口所对应的文件描述符，失败返回-1
 */
int init_serial(const char *file,int baudrate)
{
    int fd;

    fd = open(file,O_RDWR);
    if(-1 == fd)
    {
        perror("open device error");
        return -1;
    }
    struct termios myserial;//虚拟串口
    memset(&myserial,0, sizeof(myserial));//清空结构体
    myserial.c_cflag |= (CLOCAL | CREAD);

    myserial.c_cflag &= ~CSIZE;
    myserial.c_cflag &= ~CRTSCTS;
    myserial.c_cflag &= ~CS8;

    myserial.c_cflag &= ~CSTOPB;
    myserial.c_cflag &= ~PARENB;

    switch ((baudrate))
    {
        //若有其他波动率，自行添加
        case 2400:
            cfsetospeed(&myserial,B2400);
            cfsetospeed(&myserial,B2400);
            break;
        case 9600:
            cfsetospeed(&myserial,B9600);
            cfsetospeed(&myserial,B9600);
            break;
        case 115200:
            cfsetospeed(&myserial,B115200);
            cfsetospeed(&myserial,B115200);
            break;
        case 19200:
            cfsetospeed(&myserial,B19200);
            break;
    }
    tcflush(fd,TCIFLUSH);
    tcsetattr(fd,TCSANOW,&myserial);
    return fd;//返回串口文件所对应的文件描述符
    //close(fd);
}

int main()
{
    //初始化com1（我在虚拟机弄的）
    int fd;
    fd = init_serial(COM1,115200);//不要填字符串常量，设备名可能会不一样很多种，用macro
    if(-1 == fd)//初始化失败
    {
        printf("init com1 error\n");
        return 0;
    }
#if 0
    //向COM1发送数据    其实就是COM2这个串口所对应的设备文件中写入数据
    //char *buf = "hello";//buffer缓冲区
    char buf[10];
    strcpy(buf,"hello");
    int ret;
    while(1)
    {
        ret = write(fd,buf, strlen(buf));//sizeof(buf) or strlen(buf)?一个是数组的字节数10，一个是字符串长度
        printf("write %d bytes data\n",ret);
        sleep(1);//休眠一秒
    }
#endif
    //从com2读数据，从com2这个串口所对应的设备文件中读取数据
    char buf[10];//接受com2上的数据
    while(1)//循环接收循环发出的数据
    {
        memset(buf, 0, sizeof(buf));//这句话不能弄出循环，要不然又加上了上次的数据
        int ret;
        ret = read(fd, buf, sizeof(buf) - 1);//9个字符串，若不想当字符串处理可以不减1
        if(ret>0)//只有读到了数据才打印出来
            printf("read : %s\n",buf);
    }
    //


    //关闭
    close(fd);
    return 0;
}