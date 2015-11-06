#include <stdio.h>
#include <stdlib.h>
#define MAXVAL 10000000

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          freopen("output.txt", "w", stdout);
    #endif

    int n,m,val,i;
    int max = 0, min = 10000000;
    scanf("%d %d",&n,&m);

    int* flag = new int[MAXVAL];
    for (i = 0; i < n; i++){
        scanf("%d",&val);
        max = (val > max) ? val : max;
        min = (val < min) ? val : min;
        flag[val] = 1;
    }
    for(i = min + 1; i <= max; i++)
        flag[i] += flag[i - 1];

    while(m--){
        int final,lo,hi;
        scanf("%d %d",&lo,&hi);
        if (lo > max || hi < min){
            printf("%d\n",0);
            continue;
        }
        if (lo < min) lo = min;
        if (hi > max) hi = max;
        printf("%d\n",flag[hi] - flag[lo] + (flag[lo] - flag[lo-1]));
    }
    return 0;
}
