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

class Queue
{
private:
    Node* header;
    Node* trailer;
public:
    int size;
    Queue(){
        header = new Node(-1);
        trailer = new Node(-1);
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
        size = 0;
    }

    int front(){ return first()->data; }
    int rear(){ return last()->data; }
    void enqueue(int e){ insertAsLast(e); }
    int dequeue(){ return remove(first()); }

    void enqueueWithMax(int e){
        Node* p = insertAsLast(e)->prev;
        while(p -> data > 0 && p -> data < e){
            p->data = e;
            p = p->prev;
        }
    }

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
                printf("%d", n->data);
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
    Queue Q,M;
    int n,h;
    char c;
    scanf("%d\n",&n);
    // printf("%d\n",n);
    while(n--){
        scanf("%c",&c);
        // printf("%c\n",c);

        if(c == 'E'){
            scanf(" %d\n",&h);
            // printf("E %d\n",h);
            Q.enqueue(h);
            M.enqueueWithMax(h);
            continue;
        }
        scanf("\n");
        if(c == 'D'){
            printf("%d\n", Q.dequeue());
            M.dequeue();
            continue;
        }
        if(c == 'M'){
            printf("%d\n",M.front());
            continue;
        }

    }
    return 0;
}
