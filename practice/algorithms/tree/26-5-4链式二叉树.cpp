#include <iostream>
using namespace std;
template <class T>
class node
{
public:
    T data;
    node *lc;
    node *rc;
    node()
    {
        lc = NULL;
        rc = NULL:
    }
    node(T d)
    {
        data = d;
        lc = NULL;
        rc = NULL:
    }
};
template <class T>
class tree
{
public:
    node<T> *r;
    tree()
    {
        r = NULL;
    }
    ~tree()
    {
        delete (r);
        r = NULL;
    }
    void delete (node<T> *p)
    {
        if (p != NULL)
        {
            delete (p->lc);
            delete (p->rc);
            delete p;
        }
    }
    
};
int main()
{
}