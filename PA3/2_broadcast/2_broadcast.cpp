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

class List
{
private:
    Node* header;
    Node* trailer;
public:
    int size;
    List(){
        header = new Node('~');
        trailer = new Node('!');
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
        size = 0;
    }
    int pop() {
        if (isEmpty()){
            printf("Stack is empty!\n");
            return -1;
        }
        return remove(first());
    }

    void push(int e) {insertAsFirst(e);}
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
                printf("%d ", n->data);
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
    int n,m,v,u,flag = 1;
    scanf("%d %d\n",&n,&m);
    int* status  = new int[n];
    List tmpV,tmpU;
    // List* adj = new List[n];
    for (int i = 0; i < n; ++i)
    {
        status[i] = -1;
    }

    scanf("%d %d\n",&v,&u);
    status[v] = 1;
    status[u] = 0;
    m--;

    while (m--){
        scanf("%d %d\n",&v,&u);
        v--; // node number convert to index
        u--;
        // adj[v].push(u);
        bool e = (status[v] == status[u]);
        // printf("%d\n", e);
        if (e)
        {
            if (status[v] == -1)
            {
                tmpV.push(v);
                tmpU.push(u);
            } else {
                flag = -1;
                break;
            }
        } else {
            if (status[v] == -1 && status[u] == 0)
                status[v] = 1;
            else if (status[v] == -1 && status[u] == 1)
                status[v] = 0;
            else if (status[u] == -1 && status[v] == 0)
                status[u] = 1;
            else if (status[u] == -1 && status[v] == 1)
                status[u] = 0;
            else
                continue;
        }
    }

    while(!tmpU.isEmpty() && flag){
        v = tmpV.pop();
        u = tmpU.pop();
        if (status[v] == status[u] && status[v] >= 0)
        {
            flag = -1;
            break;
        }
    }

    printf("%d\n", flag);
    return 0;
}
