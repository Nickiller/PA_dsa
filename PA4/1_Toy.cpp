#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX 40325
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
class Node
{
public:
    Node* prev;
    Node* succ;
    char* data;
    int cnt;

    Node(){}
    Node(char* data,int cnt, Node* prev = NULL, Node* succ = NULL){
        this->prev = prev;
        this->succ = succ;
        this->data = data;
        this->cnt = cnt;
    }

    Node* insertAsPrev(char* d,int cnt){
        Node* p = new Node(d,cnt,prev,this);
        prev->succ = p;
        prev = p;
        return p;
    }

    Node* insertAsSucc(char* d,int cnt){
        Node* p = new Node(d,cnt,this,succ);
        succ->prev = p;
        succ = p;
        return p;
    }
};

class List
{
private:
    Node* header;
    Node* trailer;
public:
    int size;
    List(){
        char h[8] = "a";
        char t[8] = "A";
        header = new Node(h,-1);
        trailer = new Node(t,-2);
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
        size = 0;
    }
    Node* pop() {
        return remove(first());
    }

    void push(char* e,int cnt) {insertAsFirst(e,cnt);}
    Node* dequeue(){
        return remove(first());
    }
    void enqueue(char* e,int cnt) {insertAsLast(e,cnt);}

    Node* first() { return header->succ;}
    Node* last() { return trailer->prev;}
    bool isEmpty() { return (header->succ == trailer);}

    Node* insertAsFirst(char* e,int cnt){
        size ++;
        return header->insertAsSucc(e,cnt);
    }

    Node* insertAsLast(char* e,int cnt){
        size ++;
        return trailer->insertAsPrev(e,cnt);
    }

    Node* remove(Node* p){
        Node* e = new Node(p->data,p->cnt);
        p->prev->succ = p->succ;
        p->succ->prev = p->prev;
        delete p;
        size--;
        return e;
    }

    Node* getNodeFromPos(int pos){
        Node* n = header;
        for (int i = 0; i <= pos; ++i)
            n = n->succ;
        return n;
    }

    Node* insertIntoList(int pos, char* e, int cnt){
        Node* n = getNodeFromPos(pos);
        n = n->insertAsPrev(e,cnt);
        return n;
    }
};

void swap(char& a,char& b){
    char tmp = a;
    a = b;
    b = tmp;
}

char* swap_line(char* toy){
    char* new_toy = new char[8];
    strcpy(new_toy,toy);
    for (int i = 0; i < 4; ++i)
    {
        swap(new_toy[i],new_toy[7 - i]);
    }
    return new_toy;
}

char* shift_left(char* toy){
    char* new_toy = new char[8];
    strcpy(new_toy,toy);
    for (int i = 0; i < 3; ++i)
    {
        swap(new_toy[i],new_toy[i + 1]);
    }
    for (int i = 7; i > 4; --i)
    {
        swap(new_toy[i],new_toy[i - 1]);
    }
    return new_toy;
}

char* rotate_reverse(char* toy){
    char* new_toy = new char[8];
    strcpy(new_toy,toy);
    swap(new_toy[1],new_toy[2]);
    swap(new_toy[5],new_toy[6]);
    swap(new_toy[2],new_toy[6]);
    return new_toy;
}

int getIndex(char* toy){
    int convertInt = 1;
    int factorial[8] = {5040,720,120,24,6,2,1,1};
    int count_small;
    // 第i位
    for (int i = 0;i < 7;i++){
        // 之前有多少位比这位小
        count_small = 0;
        for (int j = 0;j < i;j++){
            if (int(toy[j] - '0') < int(toy[i] - '0'))
                count_small += 1;
        }
        convertInt += factorial[i] * (int(toy[i] - '0') - 1 - count_small);
    }
    return convertInt - 1;
}

void bfs(int* steps){
    List Q;
    Node* curT;
    char* tmp;
    char init[9] = "12345678";
    Q.enqueue(init,1);
    steps[0] = 1;
    int cnt = 0;
    // printf("%d\n", steps[0]);

    while(!Q.isEmpty()){
        curT = Q.dequeue();

        tmp = swap_line(curT->data);
        if (!steps[getIndex(tmp)])
        {
            cnt++;
            steps[getIndex(tmp)] = curT->cnt + 1;
            Q.enqueue(tmp,curT->cnt + 1);
        }

        tmp = shift_left(curT->data);
        if (!steps[getIndex(tmp)])
        {
            cnt++;
            steps[getIndex(tmp)] = curT->cnt + 1;
            Q.enqueue(tmp,curT->cnt + 1);
        }

        tmp = rotate_reverse(curT->data);
        if (!steps[getIndex(tmp)])
        {
            cnt++;
            steps[getIndex(tmp)] = curT->cnt + 1;
            Q.enqueue(tmp,curT->cnt + 1);
        }
    }
    // printf("bfs finished: %d\n", cnt);
}



int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    int* steps = new int[MAX];
    for (int i = 0; i < MAX; ++i)
    {
        steps[i] = 0;
    }
    bfs(steps);
    int n;
    char target[9];
    scanf("%d", &n);
    // printf("%d\n",n);
    while(n--){
        for (int i = 0; i < 8; ++i)
        {
            scanf("%s",&target[i]);
        }
        // printf("%s\n", target);
        printf("%d\n", steps[getIndex(target)] - 1);
    //     printf("%d\n", search(target));// 用bfs从正确状态倒序搜索target，返回最短路径
    }
    return 0;
}
