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
    char* data;
    int cnt;

    Node(){}
    Node(char* data = NULL, Node* prev = NULL, Node* succ = NULL,int cnt = 0){
        this->prev = prev;
        this->succ = succ;
        this->data = data;
    }

    Node* insertAsPrev(char* d){
        Node* p = new Node(d,prev,this);
        prev->succ = p;
        prev = p;
        return p;
    }

    Node* insertAsSucc(char* d){
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
    int size;
    List(){
        char h[40] = "~";
        char t[40] = "!";
        header = new Node(h);
        trailer = new Node(t);
        header->prev = NULL;
        header->succ = trailer;
        trailer->prev = header;
        trailer->succ = NULL;
        size = 0;
    }
    char* pop() {
        if (isEmpty()){
            printf("Stack is empty!\n");
            return NULL;
        }
        return remove(first());
    }

    void push(char* e) {insertAsFirst(e);}
    char* dequeue(){
        if (isEmpty())
        {
            printf("Queue is empty!\n");
            return NULL;
        }
        return remove(first());
    }
    void enqueue(char* e) {insertAsLast(e);}

    Node* first() { return header->succ;}
    Node* last() { return trailer->prev;}
    bool isEmpty() { return (header->succ == trailer);}

    Node* insertAsFirst(char* e){
        size ++;
        return header->insertAsSucc(e);
    }

    Node* insertAsLast(char* e){
        size ++;
        return trailer->insertAsPrev(e);
    }

    char* remove(Node* p){
        char* e = p->data;
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

    Node* insertIntoList(int pos, char* e){
        Node* n = getNodeFromPos(pos);
        n = n->insertAsPrev(e);
        return n;
    }

    void printList(){
        if (isEmpty()) printf("-\n");
        else {
            Node* n = header->succ;
            while(n != trailer){
                printf("%s ", n->data);
                n = n->succ;
            }
            printf("\n");
        }
    }
};

int hash(char* s){
    char c;
    int sum = 0,i = 0;
    while(i < 40 && s[i] != '\0'){
        sum += int(s[i]);
        i ++;
    }
    return sum;
}

int equal(char* s1, char* s2){
    int flag = 1,i = 0;
    while(i < 40){
        if (s1[i] != s2[i])
        {
            flag = 0;
            break;
        }
        if (s1[i] == '\0')
        {
            break;
        }
        i++;
    }
    return flag;
}

int isInList(char* s, List L){
    int flag = 0;
    Node* p = L.first();
    while(p != L.trailer){
        if (equal(s,p->data))
        {

            flag = (p->cnt == 0) ? 2 : 1;
            p->cnt += 1;
            break;
        }
        p = p->succ;
    }
    return flag;

}

int main(int argc, char const *argv[])
{
    #ifndef _OJ_
          freopen("input.txt", "r", stdin);
          // freopen("output.txt", "w", stdout);
    #endif
    int n,m;

    scanf("%d\n",&n);
    m = n;
    List* H = new List[n];
    while(n--){
        // each time use new to gen a new pointer s;
        // if use char s[40], all str read in will link to the same s
        char* s = new char[45];
        scanf("%s\n",s);
        int hashPos = hash(s) % m;
        // printf("%s %d\n",s,hashPos);

        int flag = isInList(s,H[hashPos]);
        if (flag == 2)
        {
            printf("%s\n", s);
        } else if (flag == 0) {
            H[hashPos].enqueue(s);
        }
    }
    return 0;
}
