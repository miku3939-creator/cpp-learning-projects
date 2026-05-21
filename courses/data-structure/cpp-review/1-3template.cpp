#include <iostream>
#include <string>
using namespace std;
// c++泛型编程思想主要利用的技术就是模板
// c++两种模板机制：函数模板与类模板
// 1-1函数模板
template <typename T> // template<class T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
// 数组排序函数模板
template <class T>
void mySort(T arr[], int len)
{
    for (int i = len - 1; i > 0; i--)
    {
        int max = i;
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }
        if (max != i)
        {
            mySwap(arr[i], arr[max]);
        }
    }
}
// 打印函数模板
template <typename T>
void printArray(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i];
    }
    cout << endl;
}

// 模板局限性
// 模板并不是万能的，有些特定数据类型，需要用具体化方式做特殊实现
// 对比两个数是否相等
template <class T>
bool com(T a, T b)
{
    if (a == b)
        return true;
    return false;
}
class Person
{
public:
    int age;
    string name;
};
// 利用具体化Person的版本实现代码，具体化优先调用
template <> bool com(Person &p1, Person &p2)
{
    if (p1.name == p2.name && p1.age == p2.age)
        return true;
    return false;
}

int main()
{
    int a = 1, b = 2;
    mySwap<int>(a, b);
    cout << a << ' ' << b;

    // 2-1函数模板注意事项
    // 1.自动类型推导，必选推导出一致的数据类型T才可以使用
    mySwap(a, b);
    // 2.模板必须要确定出T的数据类型，才可以使用
    // 无法自动推导时
    mySwap<int>(a, b);

    // 测试排序函数
    int arr[6];
    for (int i = 0; i < 6; i++)
    {
        cin >> arr[i];
    }

    char crr[6];
    for (int i = 0; i < 6; i++)
    {
        cin >> crr[i];
    }
    mySort(arr, 6);
    mySort(crr, 6);
    printArray(arr, 6);
    printArray(crr, 6);

    // 函数模板与普通函数在类型转换上的区别
    //1.普通函数支持隐式类型转换
    //2.函数模板自动推导时不支持隐式转换
    //3.函数模板显式指定类型时支持隐式转换

    // 函数模板调用规则
    //1.普通函数与函数模板同时存在时优先调用普通函数
    //2.通过空模板参数列表强制调用模板
    mySwap<>(a, b);
    //3.函数模板可以重载
    //4.函数模板如果能更好地匹配，调用函数模板
    return 0;
}