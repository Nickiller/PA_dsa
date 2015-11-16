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
    int n,m,v,u,maxl;
    scanf("%d %d\n",&n,&m);
    List S; // store node of indgree == 0
    int* indegree = new int[n];
    int* l = new int[n];
    List* adj = new List[n];
    for (int i = 0; i < n; ++i)
    {
        indegree[i] = 0;
        l[i] = 0;
    }

    while (m--){
        scanf("%d %d\n",&v,&u);
        v--; // node number convert to index
        u--;
        adj[v].push(u);
        indegree[u] ++;
    }

    for (int i = 0; i < n; ++i){
        if (indegree[i] == 0){
            S.push(i);
            l[i] = 1;
        }
    }
    while (!S.isEmpty()){
        v = S.pop();
        if (adj[v].isEmpty())
            maxl = (maxl > l[v]) ? maxl : l[v];

        while (!adj[v].isEmpty()){
            u = adj[v].pop();
            indegree[u] --;
            l[u] = (l[u] < l[v] + 1) ? l[v] + 1 : l[u];

            if (indegree[u] == 0)
                S.push(u);
        }

    }
    printf("%d\n",maxl);
    return 0;
}
