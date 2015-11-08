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
public:
    //注意：你不能添加更多的public函数或变量,如有需要可添加析构函数
    Stack();
    bool empty();
    void push(int);
    int pop();
    int top();
private:
    int size;
    Node* header;
    Node* trailer;
};

Stack::Stack()
{
    size = 0;
    header = new Node(-1);
    trailer = new Node(-2);
    header->prev = NULL;
    header->succ = trailer;
    trailer->prev = header;
    trailer->succ = NULL;
}

bool Stack::empty()
{
    return (size == 0);
}

void Stack::push(int value)
{
    size ++;
    header->insertAsSucc(value);
}

int Stack::pop()
{
    if (empty())
    {
        printf("Stack is empty!\n");
        return -1000;
    }
    size --;
    Node* delNode = header->succ;
    int delInt = delNode->data;
    header->succ = delNode->succ;
    delNode->succ->prev = header;
    delete delNode;
    return delInt;
}

int Stack::top()
{
    return header->succ->data;
}

class Queap
{
public:
    Queap();
    void enqueap(int);
    int dequeap();
    int min();
private:
    Stack enS,deS,minS1,minS2;
    int size;
};

Queap::Queap()
{
    enS = new Stack();
    deS = new Stack();
    minS1 = new Stack();
    minS2 = new Stack();
    size = 0;
}

void Queap::enqueap(int value)
{
    size ++;
    if (value < enS.top())
        minS1.push(enS.top())
    else
        minS1.push(value);
    enS.push(value);

}

int Queap::dequeap()
{
    if (deS.empty())
    {
        while(!enS.empty()){
            minS1.pop();
            int tmp = enS.pop();
            deS.push(tmp);
            if (tmp < deS.top())
                minS2.push(tmp);
            else
                minS2.push(deS.top());
        }
    }
    size --;
    minS2.pop()
    return deS.pop()
}

int Queap::min()
{
    return (minS2.top() < minS1.top()) ? minS2.top() : minS1.top();
}

int main()
{
    #ifndef _OJ_
        freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
    #endif
    return 0;
}
