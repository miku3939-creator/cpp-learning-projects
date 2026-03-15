#include <iostream>
#include<string>
using namespace std;
// 类模板语法
template <class nameT, class ageT>//模板参数列表
class Person
{public:
    nameT name;
    ageT age;
    Person(nameT n, ageT a)
    {
        name = n;
        age = a;
    }
};
//类模板与函数模板主要区别
//1.类模板没有自动类型推导的使用方式
//2.类模板在模板参数列表中可以有默认参数
//template <class nameT, class ageT= int >//模板参数列表

//类模板中成员函数创建时机：调用时才创建
//普通类：一开始就可以创建

//类模板对象做函数参数
//传入方式
//1.指定传入的类型 直接显示对象的数据类型
void test01(Person<string,int>&p);
//2.参数模板化 将对象中的参数变为模板进行传递
template<class T1,class T2>
void test02(Person<T1,T2>&p);
//3.整个类模板化 将这个对象类型模板化进行传递
template<class T>
void test03(T&p);
int main()
{
    Person<string,int> p1("xiaoming",18);
    
}