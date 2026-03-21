#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node() : next(NULL) {}
    Node(int val) : val(val), next(NULL) {}
};
class List
{
public:
    Node *head;
    List() : head(NULL) {}
    void create(vector<int> v, int n)
    {
        Node *q = head;
        for (int i = 0; i < n; i++)
        {
            Node *p = new Node(v[i]);
            q->next = p;
            q = p;
            if(i==n-1)
            p->next=head->next;
        }
    }

    void del(Node * node){
    }
};
int main(){
    int n,m;
    vector<int> v;
    for(int i=1;i<=n;i++){
        v.push_back(i);
    }
    List list;
    list.create(v,n);

}