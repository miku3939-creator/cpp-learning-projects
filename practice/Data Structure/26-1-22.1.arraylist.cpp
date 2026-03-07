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
virtual int indexOf(const T& theElement)const=0;
virtual void erase(int index)const=0;
virtual void insert(int index,const T& element)const=0;
virtual void output(ostream& out)const=0;
};


//arraylist类声明
template<class T>
class arraylist:public linearList<T>
{
public:
//构造拷贝与析构
arraylist(int initialCapabality=10);
arraylist(const arraylist<T> &);
~arraylist(){
    delete element[];
}
//ADT方法 
bool empty()const{return listsize==0;}
int size()const{return listsize;}
T& get(int index)const;
int indexOf(const T& theElement)const;
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


//构造函数实现
template<class T>
arraylist<T>::arraylist(int initialCapability){
if(initialCapability<1){
    ostringstream s;
    s<<"initinal capability ="<<initialCapability<<"must be > 0";
    throw illegalParameterValue(s.str());
}
arraylength=initialCapability;
element=new T[arraylength];
listsize=0;  
}

//拷贝构造函数实现
template<class T>
arraylist<T>::arraylist(const arraylist<T> & list){
arraylength=list.arraylength;
listsize=list.listsize; 
element=new T[arraylength];
copy(list.element,list.element+listsize,element) 
}

//checkIndex
template<class T>
void arraylist<T>::checkIndex(int index)const{
    //确定索引合法
    if(index<0||index>=listsize){
        ostringstream s;
        s<<"index ="<<index<<"size ="<<listsize;
        throw illegalIndex(s.str());
    }
}

//get
template<class T>
T& arraylist<T>::get(int index)const{
    checkIndex(index);
    return element[index];
}

//indexOf
template<class T>
int arraylist<T>::indexOf(const T& theElement)const{
    int index=(int)(find(element,element+listsize,theElement)-element);
    if(index==listsize)
    return -1;
    else return index;
}

int main(){
//实例化
linearList *x=(linearList) new arraylist<int>(100);
arraylist<double> y(100);

arrayList<char> z;

arrayLiat<double>w(y);
}