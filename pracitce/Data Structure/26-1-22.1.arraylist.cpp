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
//arraylist类
template<class T>
class arraylist:public linearList<T>
{
public://构造复制与析构
arraylist(int initialCapabality=10);
arraylist(const arraylist<T> &);
~arraylist(){
    delete element[];
}
//ADT方法 
bool empty()const{return listsize==0;}
int size()const{return listsize;}
T& get(int index)const;
int indexOf(const T& element)const;
void erase(int index)const;
void insert(int index,const T& element)const;
void output(ostream& out)const;
//其他方法
int capability()const{return arraylength;}

protected:
void checkIndex(int index)const;
T*element;
int arraylength;
int listsize;                                             
};

template<class T>
arraylist<T>::arraylist(int initialCapability){

}
int mian(){

}