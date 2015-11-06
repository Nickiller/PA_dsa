#include <cstdio>
#include <cstdlib>
#include <cstring>
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

void rebuild(int* pre,int* post,int* in,int preBeg,int postBeg,int beg,int end){
    int count = end - beg;
    int i;

    // if (count == 0) return;
    if (count == 1)
    {
        in[beg] = pre[preBeg];
        return;
    }
    if (count == 3)
    {
        in[beg + 1] = pre[preBeg]; // inorder root
        in[beg] = pre[preBeg + 1]; // inorder left
        in[beg + 2] = pre[preBeg + 2]; // inorder right
        return;
    }
    int curNode = pre[preBeg];
    int left = pre[preBeg + 1];
    int right = post[postBeg + count - 2];
    for (i = 0; i < count && post[i + postBeg] != left; ++i);
    // assert(pre[preBeg + i + 2] == right);

    rebuild(pre,post,in,preBeg + 1,postBeg,beg,beg + i + 1);
    in[beg + i + 1] = curNode;
    rebuild(pre,post,in,preBeg + i + 2,postBeg + i + 1,beg + i + 2,end);
}


int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input2.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    int n;
    scanf("%d\n",&n);
    // assert(n <= 10);
    int* pre = new int[n];
    int* post = new int[n];
    int* in = (int*)calloc(n,sizeof(int));
    for (int i = 0; i < n; ++i) scanf("%d",&pre[i]);
    scanf("\n");
    for (int i = 0; i < n; ++i) scanf("%d",&post[i]);

    rebuild(pre,post,in,0,0,0,n); // inorder for [0,n)
    for (int i = 0; i < n; ++i)
        printf("%d ",in[i]);
    printf("\n");
    return 0;
}
