#include <cstdio>
#include <cstdlib>
#include <cstring>
#define Parent(i) ((i-1) >> 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)
#define LastInternal(n) Parent(n - 1)
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

struct Entry
{
    unsigned long rank;
    char name[9];
    Entry(){}
    Entry(int r,char* n){rank = r;strcpy(name,n);}
};

void swap(Entry &e1, Entry &e2);
bool isPrior(Entry e1, Entry e2);
class PriorityQueue
{
private:
    Entry* elem;
    int size; // 实际含有的元素个数，同时也指向下一个空闲的位置

    int properPa(int n, int i){
        int lc = LChild(i);
        int rc = RChild(i);
        int pc;
        if (lc >= n) return i;
        if ((rc >= n && lc < n) || isPrior(elem[lc],elem[rc]))
        {
            pc = lc;
        } else {
            pc = rc;
        }

        if (isPrior(elem[pc],elem[i]))
        {
            return pc;
        } else {
            return i;
        }
    }

    int percolateUp(int i){
        int j;
        while(i > 0){
            j = Parent(i);
            if (isPrior(elem[j], elem[i]))
            {
                break;
            }
            swap(elem[i],elem[j]);
            i = j;
        }
        return i;
    }

    int percolateDown(int n, int i){
        int j;
        j = properPa(n,i);
        while(i != j){
            swap(elem[i],elem[j]);
            i = j;
            j = properPa(n,i);
        }
        return i;
    }

public:
    PriorityQueue(Entry* elem,int n){
        // printf("init queue\n");
        this->elem = elem;
        this->size = n;
        heapify(this->size);
    }
    void heapify(int n){
        for (int i = Parent(n-1); i >= 0; --i)
        {
            percolateDown(n,i);
        }
    }

    bool isEmpty(){ return (size == 0); }

    int insert(Entry e){
        elem[size] = e;
        size++;
        return percolateUp(size - 1);
    }

    Entry getMax(){
        return elem[0];
    }

    Entry delMax(){
        Entry maxElem = elem[0];
        swap(elem[0], elem[size - 1]);
        size--;
        percolateDown(size,0);
        return maxElem;
    }

    void printPQ(){
        if (isEmpty())
        {
            printf("PQ is empty!\n");
        }
        printf("current size:%d\n",size);
        for (int i = 0; i < size; ++i)
            printf("%d th entry: %lu %s\n", i,elem[i].rank,elem[i].name);
    }

    void update(unsigned long max){
        // printPQ();
        printf("%s\n",elem[0].name);
        elem[0].rank = (elem[0].rank << 1);
        if (elem[0].rank < max){
            percolateDown(size,0);
        } else {
            delMax();
        }
    }

};

bool isPrior(Entry e1, Entry e2){
    if (e1.rank < e2.rank || (e1.rank == e2.rank && strcmp(e1.name,e2.name) < 0))
        return true;
    return false;
}

void swap(Entry &e1, Entry &e2){
    Entry tmp = e1;
    e1 = e2;
    e2 = tmp;
}

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    int n,m;
    unsigned long rank;
    char name[9];
    unsigned long max = 4294967296;
    // unsigned long max = 5;
    // printf("%lu\n",max);
    Entry* curMax;
    scanf("%d %d\n",&n,&m);
    Entry* elem = new Entry[n];

    for (int i = 0; i < n; ++i)
    {
        scanf("%lu %s\n",&elem[i].rank,elem[i].name);
    }
    PriorityQueue PQ(elem,n);
    // PQ.printPQ();
    while(!PQ.isEmpty() && m--){
        PQ.update(max);
    }
    // printf("%d\n",m);
    return 0;
}
