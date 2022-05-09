/*********************************************************************************
  *Copyright(C),2022 by JarvisChan
  *FileName: binary_file.c 
  *Author:  //作者
  *Version:  //版本
  *Date:  2022 2022/5/6 9:36//完成日期
  *Description: 二进制文件io测试,封装协议
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1。fread,fwrite,fopen
     2.…………
**********************************************************************************/
#include <stdio.h>
#include <string.h>
#define FILENAME "1.mp3"
#define BACKFILE "1_bak.mp3"
int main(){
    FILE *fp;

    fp = fopen(FILENAME,"rb+");//if no exist,wont create!
    if(NULL == fp){
        printf("[%s %s %d]",__FILE__,__func__,__LINE__);//所在的函数，文件，行号,没有换行我们希望和error一起输出
        perror("sourcefile no exist");
        return 0;
    }

    //create a backup for the opened file
    //1.create a file
    FILE *bak_fp;//or *bakFP
    bak_fp = fopen(BACKFILE,"wb+");
    if(NULL == bak_fp){
        printf("[%s %s %d]",__FILE__,__func__,__LINE__);//所在的函数，文件，行号,没有换行我们希望和error一起输出
        perror("backupfile no exist");
        return 0;
    }

    while(1) {
        //2.from exist file read data,maybe we cant read all at once
        char data[1024];//why use char to store binary file?because we no have binary type in cLanguage.
    //不用memset 0了，之所以用memset是因为我们希望将数据当作字符串处理，此时是二进制文件
        int n;
        n = fread(data,1,sizeof(data),fp);
        if(0==n) {
            if (feof(fp))
                printf("end of file");
            else if (ferror(fp))
                perror("error!");
            break;
        }

        //对二进制文件数据进行封装，千万要避开字符串处理函数，避免只处理到'\0'
        char frame[2048] = {0};
        strcpy(frame,"##num=13;len=1024;data=");//data不一定是字符串，要strncat追加
        //二进制文件保存了0101等，若直接strncat，可能其中会有个00000000，代表’\0‘，导致强行截断，数据缺失，如hello\0world;。
        //所以循环数组放元素
        int i;
        for(i = 0;i<n;i++){
            frame[strlen(frame)+i] = data[0];//前面已经存了一些元素了，然后在后面拼
        }

        //假设从二进制文件中读取到的数据拷贝到另外一个地方
        char tmp [1024];
        //将data中n个字节拷贝到tmp中
//        for(i = 0;i<n;i++)//法1：暴力赋值
//            tmp[i] = data[i];
        //strncpy只能拷贝字符串，搞不了其他，只处理到'\0'，memcpy就能靠背任意类型
        memcpy(tmp,data,n);
        fwrite(data,1,n,bak_fp);//be careful,dont use sizeof,毒了多少，就写多少
        //sizeof 是瓶子大小，你装了n升的水就只能倒n升的水

        //3.write to b file
    }
    //close bk file
    fclose(bak_fp);
    fclose(fp);//写完open后立刻写close
    return 0;
}
