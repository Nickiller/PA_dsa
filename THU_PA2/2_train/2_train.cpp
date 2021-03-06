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

class Node
{
public:
    Node* prev;
    Node* succ;
    int data;

    Node(){}
    Node(int data, Node* prev = NULL, Node* succ = NULL){
        this->prev = prev;
        this->succ = succ;
        this->data = data;
    }

    Node* insertAsPrev(int d){
        Node* p = new Node(d,prev,this);
        prev->succ = p;
        prev = p;
        return p;
    }

    Node* insertAsSucc(int d){
        Node* p = new Node(d,this,succ);
        succ->prev = p;
        succ = p;
        return p;
    }
};

class Stack
{
private:
    Node* header;
    Node* trailer;
public:
    int size;
    Stack(){
        header = new Node(-1);
        trailer = new Node(-2);
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
        size = 0;
    }

    int top(){ return last()->data; }
    void push(int e){ insertAsLast(e); }
    int pop(){ return remove(last()); }

    Node* first() { return header->succ;}
    Node* last() { return trailer->prev;}
    bool isEmpty() { return (header->succ == trailer);}

    Node* insertAsFirst(int e){
        size ++;
        return header->insertAsSucc(e);
    }

    Node* insertAsLast(int e){
        size ++;
        return trailer->insertAsPrev(e);
    }

    int remove(Node* p){
        int e = p->data;
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

    Node* insertIntoList(int pos, int e){
        Node* n = getNodeFromPos(pos);
        n = n->insertAsPrev(e);
        return n;
    }

    void printList(){
        if (isEmpty()) printf("-\n");
        else {
            Node* n = header->succ;
            while(n != trailer){
                printf("%c", n->data);
                n = n->succ;
            }
            printf("\n");
        }
    }
};

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    Stack S;

    int n,m,j = 0,flag = 1;
    scanf("%d %d\n",&n,&m);
    int* A = new int[n];
    for (int i = 0; i < n; ++i)
        A[i] = i+1;

    int b,curA = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d ",&b);
        while(curA < n && A[curA] <= b){
            S.push(A[curA++]);
        }

        if (S.size > m || S.isEmpty() || S.top() != b)
        {
            printf("No\n");
            flag = 0;
            break;
        } else {
            S.pop();
            // O[j++] = 0;
            // printf("pop\n");
        }
    }
    if (flag)
    {
        printf("Yes\n");
    }
    return 0;
}
