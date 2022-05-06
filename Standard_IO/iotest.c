/*********************************************************************************
  *Copyright(C),2022 by JarvisChan
  *FileName: iotest.c 
  *Author:  //作者
  *Version:  //版本
  *Date:  2022 2022/5/5 13:41//完成日期
  *Description:  //用于主要说明此程序文件完成的主要功能
                //与其他模块或函数的接口、输出值、取值范围、
                //含义及参数间的控制、顺序、独立及依赖关系
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
**********************************************************************************/
struct Item{
    int x;
    char y;
    int z;
};
#include <stdio.h>
#include <string.h>
int main(){
#if 0
    FILE *fp;
    fp = fopen("test.txt","r+");//w+,w,r,.....
    int a[5] ={10,22,22,33,40};//读取结果是20字节

    //fwrite 先写进buffer，并没有真实写进文件
    fwrite(a,sizeof(int),sizeof(a)/sizeof(int),fp);
    //fflush(fp);//buffer的内容回写到文件
    //将读出来的数据当做字符处理
     char data[100];
    memset(data,0,sizeof(data));//我们希望将字符数组当字符串处理

     //注意光标问题
    fseek(fp,0,SEEK_SET);//光标从文件开头，偏移0个位置，也就是从末尾来到开头

    //将文件中读取到的数据当做字符数据处理
    int n;//成功读取到的元素个数，若返回0有两种情况，一个是报错，一个是读到末尾，fread分不清末尾和error，必须用feof和ferror
    //n =fread(data,1,100,fp);//他也有缓冲区，会放到read缓冲区，读到的是读缓冲区的内容
    //printf("[%s %s %d] n:%d,data:%s",__FILE__,__func__,__LINE__,n,data);//明确知道每条打印语句所在的文件，函数以及行号
    int b[5];
    n = fread(b,sizeof(b[0]),sizeof(b)/sizeof(b[0]),fp);//
    printf("[%s %s %d] n:%d,data:%d %d %d %d %d",__FILE__,__func__,__LINE__,n,b[0],b[1],b[2],b[3],b[4]);
    if(n<=100){
        //判断是否到达了文件末尾,end of file
        if(feof(fp)){
            printf("[%s %s %d]eof\n",__FILE__,__func__,__LINE__);
        }else if(ferror(fp)){
            printf("[%s %s %d]eof",__FILE__,__func__,__LINE__);
            perror("error!");
        }
        //将缓冲区的内容清空弄出来fflush
    }
#endif
#if 0
    FILE *fp;
    fp = fopen("test.txt","r+");//w+,w,r,.....
    //写入结构体
    struct Item item;
    item.x = 100;
    item.y = 'X';
    item.z = 200;

    fwrite(&item,sizeof(item),1,fp);
    fseek(fp,0,SEEK_SET);
    struct Item t;
    int n;
    n = fread(&t,sizeof(t),1,fp);
    printf("[%s %s %d] n:%d  data:%d %c %d",__FILE__,__func__,__LINE__,n,t.x,t.y,t.z);

    FILE *fp;
    fp = fopen("test.txt","r+");//w+,w,r,.....
    char *str = "hello world";
    fwrite(str,1,strlen(str),fp);//注意sizeof是数据类型的大小 ，strlen是某个对象的大小
    //此时光标在文件末尾，seekcur在末尾
    fseek(fp,-3,SEEK_CUR);//当前位置往前走-3，来到hellowo
    char data[100];
    memset(data,0,sizeof(data));
    int n;
    n = fread(data,1,sizeof(data),fp);
    printf("[%s %s %d] n:%d  data:%s",__FILE__,__func__,__LINE__,n,data);//输出rld
    fclose(fp);

    fseek(fp,0,SEEK_END);//move to the end
#endif

    //use a mode to open a file
    FILE *fp;//we only want to read sth:r only read,r+ read+write,they both no create new file when file no exist
    //we hope write successfully,and cover exist data(usually renew 配置文件):w only write,w+ read+write,they both create new file when file no exist,if exist,they will clean data
    //the most difference between r and w is "create and clean",the diff between w and r is "clean!!"
    //a(w+create),a+(r+w) we want to append,usually use in logfile(web coding),when file no exist,they will create
    //用的最多就是w和a，主要判断是否要清空
//    fp = fopen("test.txt","a+");//append mode,only write
//    if(NULL == fp){
//        perror("fopen error");
//        return 0;
//    }


    //此时光标在文件末尾，因此要用fseek将光标移动到开头，但是此时模式是a，不可读,必须设置为a+(append,可读可写）

    char data[100];//buffer
    int n;//return value of fread
    memset(data,0,100);
   // fseek(fp,0,SEEK_SET);

   //glibc中，a+打开文件，fread光标从文件开头，所以打开后能直接读
   //如果想使用上述性质，千万不要在前面用write等函数，否则要人工调整光标
//    n = fread(data,1,100,fp);//fread返回值小于0或者小于我们想要读的个数，需要另行判断
//    printf("%d %s",n,data);
#if 0
    //write data to file    in windows,\r\n    in linux,\n
    fseek(fp,0,SEEK_SET);//在a+面前不管用
    fwrite("date\n",1,5,fp);//no include /0
    //此时我们用了a+,output is always appended to the end of file(write),no mattet what seek u r!
    //如果想实现覆盖，要用r+，没有一种方式是覆盖和追加
    n = fread(data,1,100,fp);//fread返回值小于0或者小于我们想要读的个数，需要另行判断
    printf("%d %s",n,data);
#endif
    //in r+ way to open file
    fp = fopen("test.txt","r+");//append mode,only write
    if(NULL == fp){
        perror("fopen error");
        return 0;
    }
    if(feof(fp)){
        printf("end of file");
    }else if(ferror(fp)){
        perror("error");
    }
    fwrite("date11",1,6,fp);//
    fseek(fp,0,SEEK_END);
    fwrite("date11",1,6,fp);//no include /0
    fseek(fp,0,SEEK_SET);
    n = fread(data,1,100,fp);

    printf("%d %s",n,data);
    fclose(fp);
    return 0;
    //注意光标问题，写数据后光标在末尾，若此时开始读根本就读不到，因此fread总是返回0，eof也会提示出来    return 0;
}
