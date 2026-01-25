#include<iostream>
using namespace std;
//线性表抽象类
template<class T>
class linearList{
public:
virtual ~linearList(){};
virtual bool empty()const=0;
virtual int size()const=0;
virtual T& get(int index)const=0;
virtual int indexOf(const T& element)const=0;
virtual void erase(int index)const=0;
virtual void insert(int index,const T& element)const=0;
virtual void output(ostream& out)const=0;
};
int mian(){

}