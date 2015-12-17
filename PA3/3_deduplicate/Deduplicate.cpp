#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
using namespace std;

# define MaxBucket 1000001

const int SZ = 1 << 20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

struct bucket
{
    char str[41];
    bool dup;
};


int main()
{
    int list_length;
    scanf("%d",&list_length);

    static bucket* bucketArray = new bucket[MaxBucket]; 
    for (int i = 0;i<MaxBucket;i++){
        strcpy(bucketArray[i].str,"");
        bucketArray[i].dup = false;
    }

    //初始化
    char str_temp[41];
    int hash_code;
    bool flag;
    int coll_time;
    for (int i=0; i<list_length; i++){
        scanf("%s",str_temp);
        // hash_code = 3* (str[0]*26^3 + str[1]*26^2 + str[2]*26 + str[3]) + digit(str_temp)
        hash_code = 0;
        for (int j=0;j<strlen(str_temp) & j<4;j++){
            hash_code *= 26;
            hash_code += str_temp[j] - 'a' + 1;
        }
        hash_code *= 3;
        for (int j=0;str_temp[j]!='\0';j++){
            hash_code += str_temp[j] - 'a' + 1;
        }
        hash_code = hash_code % MaxBucket;
        flag = true;
        while (flag){
            flag = false;
            // 若hash_code所在位置为空，则str插入该位置
            if (bucketArray[hash_code].str[0] == '\0'){
                strcpy(bucketArray[hash_code].str,str_temp);
            }
            else{
                // 否则若hash_code所在位置的字符串与该字符串一致，且还未输出，则输出
                if (strcmp(bucketArray[hash_code].str,str_temp)==0){
                    if (bucketArray[hash_code].dup == false){
                        bucketArray[hash_code].dup = true;
                        printf("%s\n",bucketArray[hash_code].str);
                    }
                }
                // 否则若hash_code所在位置的字符串与该字符串不一致，则为冲突，寻找下一个hash_code位置
                else{
                    hash_code++;
                    hash_code = hash_code % MaxBucket;
                    flag = true;
                }
            }
        }
        
        // cout<<str_temp<<"\t"<<hash_code<<endl;
    }
    
    return 0;
}