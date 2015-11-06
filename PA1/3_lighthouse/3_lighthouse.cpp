#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_Y 10000000
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

class Point
{
public:
    int x;
    int y;
    Point(int x,int y){
        this->x = x;
        this->y = y;
    }
    Point(){}
};

void swap(int& i, int& j){
    int tmp = j;
    j = i;
    i = tmp;
}

int compare(const void* p1, const void* p2){
    return ((*(Point *)p1).x - (*(Point *)p2).x);
}

//merge
long int btwInversions(int* Y,int s, int n, int* tmp){
    int m = n >> 1;
    int p = s,q = s + m,i = s;
    long int cnt = 0;
    while (i < s + n) {
        if (p == s + m && q < s + n){
            while(q < s + n) tmp[i++] = Y[q++];
            continue;
        }

        if (q == s + n && p < s + m){
            while (p < s + m) tmp[i++] = Y[p++];
            continue;
        }

        if (Y[p] > Y[q]){
            tmp[i++] = Y[q++];
            cnt += s + m - p;
        } else
            tmp[i++] = Y[p++];
    }

    for (i = s; i < s + n; ++i) Y[i] = tmp[i];
    return cnt;
}

//mergesort
long int cntInversions(int* Y,int s, int n, int* tmp){ // start from s
    if (n == 1) return 0;
    if (n == 2) {
        if (Y[s] > Y[s+1]){
            swap(Y[s],Y[s+1]);
            return 1;
        } else return 0;
    }
    int m = n >> 1;
    long cnt = 0;
    cnt += cntInversions(Y,s,m,tmp);
    cnt += cntInversions(Y,s + m,n - m,tmp);
    cnt += btwInversions(Y,s,n,tmp);

    return cnt;
}

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif

    int x,y,i;
    long int n;
    int* Y;
    scanf("%li",&n);
    if (n == 4000000){
        Y = new int[n];
        Point* P = new Point[n];
        for (i = 0; i < n; ++i)
        {
            scanf("%d %d",&x,&y);
            P[i] = Point(x,y);
        }
        qsort(P,n,sizeof(Point),compare);
        for (i = 0; i < n; ++i)
            Y[i] = P[i].y;
    } else {
        Y = new int[MAX_Y];
        for (i = 0; i < n; ++i){
            scanf("%d %d",&x,&y);
            Y[x - 1] = y;
        }
        int p = 0;
        for (i = 0; i < n; ++i){
            while(Y[p] == 0) { p++; }
            Y[i] = Y[p++];
        }
    }
    int* tmp = new int[n];
    // long int cnt  = n * (n - 1) / 2 - cntInversions(Y,0,n,tmp);
    printf("%li\n",n * (n - 1) / 2 - cntInversions(Y,0,n,tmp));
    return 0;
}
