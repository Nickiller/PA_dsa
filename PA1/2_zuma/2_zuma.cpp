#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_LENGTH 10005
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
    char data;

    Node(){}
    Node(char data, Node* prev = NULL, Node* succ = NULL){
        this->prev = prev;
        this->succ = succ;
        this->data = data;
    }

    Node* insertAsPrev(char d){
        Node* p = new Node(d,prev,this);
        prev->succ = p;
        prev = p;
        return p;
    }

    Node* insertAsSucc(char d){
        Node* p = new Node(d,this,succ);
        succ->prev = p;
        succ = p;
        return p;
    }
};

class List
{
public:
    Node* header;
    Node* trailer;
    List(){
        header = new Node('!');
        trailer = new Node('~');
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
    }

    Node* first() { return header->succ;}
    Node* last() { return trailer->prev;}
    bool isEmpty() { return (header->succ == trailer);}

    Node* insertAsFirst(char e){
        return header->insertAsSucc(e);
    }

    Node* insertAsLast(char e){
        return trailer->insertAsPrev(e);
    }

    Node* getNode(int pos){
        Node* n = header;
        for (int i = 0; i <= pos; ++i)
            n = n->succ;
        return n;
    }

    Node* insertIntoList(int pos, char e){
        Node* n = getNode(pos);
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

    void eliminate(Node* p, Node* s){
        p->succ->prev = NULL;
        s->prev->succ = NULL;
        p->succ = s;
        s->prev = p;
    }

    void zumaElimination(Node* initNode){
        // if (initNode == header || initNode == trailer) return;
        char curData = initNode -> data;
        Node* p = initNode -> prev;
        Node* s = initNode -> succ;
        int rep = 1;
        int flag = 0;
        while (p->data == curData){
            // printf("p\n");
            rep++;
            p = p->prev;
        }
        while (s->data == curData){
            // printf("s\n");
            rep++;
            s = s->succ;
        }
        if (rep >= 3) flag = 1;

        while (rep >= 3 && p->data == s->data)
        {
            // printf("s==p\n");
            curData = p->data;
            p = p -> prev;
            s = s -> succ;
            rep = 2;
            while (p -> data == curData){
                rep ++;
                p = p -> prev;
            }
            while (s -> data == curData){
                rep++;
                s = s->succ;
            }
            if (rep == 2)
            {
                p = p -> succ;
                s = s -> prev;
                break;
            }
        }
        if (flag) eliminate(p,s);
    }

};

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif

    List l;
    Node* node;
    char* a = new char[MAX_LENGTH];
    int pos,cnt;
    char e;

    scanf("%s\n",a);
    // printf("%s %lu\n",a,strlen(a));
    if (a[0] >= 65 && a[0] <= 96)
    {
        for (int i = 0; i < strlen(a); ++i)
            l.insertAsLast(a[i]);
        scanf("%d\n",&cnt);
    } else {
        cnt = atoi(a);
    }

    delete a;
    while(cnt--)
    {
        scanf("%d %c\n",&pos,&e);
        // printf("%d %c\n",pos,e);
        node = l.insertIntoList(pos,e);
        l.zumaElimination(node);
        l.printList();
    }
    return 0;
}
