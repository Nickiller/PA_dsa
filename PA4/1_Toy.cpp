#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 2000001
using namespace std;
const int SZ = 1 << 20;
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

// 针对模式串P求next表
int* build_next(char* P){
    int lp = strlen(P);
    int* next = new int[lp];
    next[0] = -1;
    int t = -1, j = 0;
    while(j < lp - 1){
        if (t == -1 || P[t] == P[j])
        {
            j ++;
            t ++;
            next[j] = t;
        } else {
            t = next[t];
        }
    }
    return next;
}

// P:要匹配的模式串; T: 文本串
int kmp(char* P,char* T){
    int* next = build_next(P);
    int i = 0, j = 0;
    int lp = strlen(P);
    int lt = strlen(T);
    while(i < lp && j < lt){
        if (i == -1 || P[i] == T[j])
        {
            i++;
            j++;
        } else {
            i = next[i];
        }
    }
    delete [] next;
    return (i - j);
}

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    char s1[MAXN];
    char s2[MAXN];
    int n1,n2;
    while(scanf("%s %s\n",s1,s2) != EOF){
        // printf("%s %s\n",s1,s2);
        n1 = strlen(s1);
        n2 = strlen(s2);
        // printf("%d %d\n", n1,n2);
        if (n1 != n2)
        {
            printf("NO\n");
            continue;
        }
        // 将S2首尾拼接，然后用KMP算法匹配S1看是否成功
        for (int i = n2; i < 2 * n2; ++i)
        {
            s2[i] = s2[i - n2];
        }
        s2[2 * n2] = '\0';
        printf("%s %s\n",s1,s2);
        printf("kmp:%d n2:%d\n", -kmp(s1,s2),n2);
        if (kmp(s1,s2) * (-1) <= n2)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
