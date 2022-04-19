//
// Created by 74476 on 2022/4/18.
//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>//有error number
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
//this is Jarvis Chan
//封装起来
int read_dir(const char* dir_name)
{


    //编程好习惯：指针形参检验合法性
    if(NULL==dir_name)
        return -1;

    //open dir，打开目录
    DIR *dir;//DIR结构体
    dir = opendir(dir_name);//point to the open file
    if(!dir)
    {
        perror("opendir error");
        return -1;
    }
    //read dir,receive dir pointer,return struct dirent *
//  ino_t  d_ino       File serial number.
//
//     char   d_name[]    Name of entry.
//what u read save in pointer struct dirent* readdir

    struct dirent *ent;//a struct pointer point to a dir A,use it to control dir A to get A'S imfomation

    //each time only read one file
    //if we need to read all file in dir,need 循环

    //but readdir only read the "first layer" of dir,but we want deeper!mnt/hgfs/Linux/Linux_IO/File_IO/test/1/11

    //we can use tree(yum -y install tree) to check the dir structure

    //读取目录
    while(ent = readdir(dir))//till the end is null,over
    {
        //判断该文件是否为. or ..（防止递归时函数栈被调用爆炸
        if(strcmp(ent->d_name,".")==0 | strcmp(ent->d_name,"..")==0)
            continue;//读其他文件

        printf("%s\n",ent->d_name);//read the name of file,d_name只是保存了个名字，想要write，read，要小心可执行程序的位置
        //判断文件类型
        //先获取文件信息,首先想到stat
        struct stat st;
        int ret;
        //需要对读取到的文件名字加上test/,或者是绝对路径从根开始（但有问题，若被其他机器使用就错了)
        char filename[128] = {0};//or memset
        strcpy(filename,dir_name);// 先把目录文件名字放到里面，但没斜杠
        strcat(filename,"/");//假设打开的目录是test，假设dname=1.c,we need test/1.c
        strcat(filename,ent->d_name);//string 拼接,成功拼完路径
        //大坑,路径问题，可执行程序与要操作的文件的路径问题
        ret = stat(filename,&st);
        if(-1 == ret)//获得失败
        {
            printf("****\n");
            printf("file %s error\n",ent->d_name);//指针才有->
            perror("state error");
            continue;//结束本次循环，接着下次循环
        }
        //!此处有巨大问题，要搞明白执行程序所在的路径是不是当前路径，若想判断其他文件夹，填上相对路径


        //判断文件类型，宏
        if(S_ISDIR(st.st_mode))//是否为目录
        {
            printf("%s is dir!\n",ent->d_name);
            //recursion to read dir，要注意退出条件，函数的调用会占用函数栈，若不退出会一直占用
            read_dir(filename);//再次读该目录下文件
            //这里有坑，会反复读.(当前目录）,..（上一级目录），直到函数栈被弄爆

            //if is dir,we need to read the thing in this dir,so how 2 read?
            //1.opendir
            //2,while circulate to readdir
            //3.get the imfo of dir     stat
            //4. is dir?(we can see that logic is very mess!)we dont know how deep dir is)---use"递归recursion"
            //1.opendir
            //2,while circulate to readdir
            //3.get the imfo of dir     stat
            //4. is dir?
            //1.opendir
            //2,while circulate to readdir
            //3.get the imfo of dir     stat
            //4. is dir?
            //we can find that 在一个函数中想实现某功能，其逻辑和本函数一样，用递归。
        }
        else if(S_ISREG(st.st_mode))//普通文件
        {
            printf("%s is a regular file!\n",ent->d_name);
        }
        //还可以继续写下去判断，此处不写了

    }
    return 0;
}
int main()
{
    //本次实验的文件目录结构：
    //(1(11(111.111.c),11.c),1.c)

    read_dir("/mnt/hgfs/Linux/Linux_IO/File_IO/test/");//要注意可执行程序和要操作的文件的位置关系，写成绝对路径，除非运行环境就是在同一级

    //最终读取结果：

    return 0;
}
