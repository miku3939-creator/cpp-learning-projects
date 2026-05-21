#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node(int val) : val(val), next(NULL) {}
    Node() : next(NULL) {}
};
class List
{
public:
    Node *head;
    Node *tail;
    List() : head(NULL), tail(NULL) {}
    void insert(int val)
    {
        if (head == NULL)
        {
            head = new Node(val);
            tail = head;
        }
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
};
int main()
{
    List l1, l2, res;
    string line;
    getline(cin, line);
    stringstream ss(line);
    int val;
    while (ss >> val)
        l1.insert(val);
    getline(cin, line);
    stringstream s(line);
    while (s >> val)
        l2.insert(val);
    Node *p1 = l1.head;
    Node *p2 = l2.head;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val < p2->val)
        {
            res.insert(p1->val);
            p1 = p1->next;
        }
        else if (p1->val > p2->val)
        {
            p2 = p2->next;
        }
        else
        {
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while(p1!=NULL){
        res.tail->next=p1;
    }
    p1=res.head;
    while(p1!=NULL){
        cout<<p1->val<<' ';
        p1=p1->next;
    }
    cout<<endl;
    return  0;
}