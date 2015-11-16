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
    int dequeue(){
        if (isEmpty())
        {
            printf("Queue is empty!\n");
            return -1;
        }
        return remove(first());
    }
    void enqueue(int e) {insertAsLast(e);}

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

int BFS(int v, List* adj, int* status){
    int u;
    List Q;
    Q.enqueue(v);
    status[v] = 1;
    while(!Q.isEmpty()){
        u = Q.dequeue();
        while(!adj[u].isEmpty()){
            int curV = adj[u].pop();
            if (status[curV] == 0)
            {
                status[curV] = -1 * status[u];
                Q.enqueue(curV);
            } else if (status[curV] == status[u])
            {
                return -1;
            } else {
                continue;
            }
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    int n,m,v,u,flag = 1;
    scanf("%d %d\n",&n,&m);
    int* status  = new int[n];
    List* adj = new List[n];
    for (int i = 0; i < n; ++i)
        status[i] = 0;// undiscovered status

    while (m--){
        scanf("%d %d\n",&v,&u);
        v--; // node number convert to index
        u--;
        adj[v].push(u);
        adj[u].push(v);
    }

    for (int v = 0; v < n; ++v)
    {
        if (status[v] == 0)
            flag = BFS(v,adj,status);
        if (!flag)
            break;
    }
    printf("%d\n", flag);
    return 0;
}
