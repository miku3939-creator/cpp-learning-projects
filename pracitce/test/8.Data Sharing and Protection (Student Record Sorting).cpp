/*#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    
    Student(int i = 0, string n = "", int a = 0) : id(i), name(n), age(a) {}
    
    void print() const {
        cout << setw(3) << id << " "
             << setw(6) << name << " "
             << setw(3) << age << endl;
    }
    
    // 按姓名比较
    bool operator<(const Student &other) const {
        return name < other.name;
    }
};

// 按年龄比较的仿函数
struct CompareByAge {
    bool operator()(const Student &a, const Student &b) const {
        if (a.age != b.age) return a.age < b.age;
        return a.name < b.name;
    }
};

int main() {
    int n;
    cin >> n;
    if (n > 50) n = 50;
    
    vector<Student> students;
    
    for (int i = 0; i < n; i++) {
        int id, age;
        string name;
        cin >> id >> name >> age;
        students.emplace_back(id, name, age);
    }
    
    // 按姓名排序（使用运算符重载）
    vector<Student> byName = students;
    sort(byName.begin(), byName.end());
    
    for (const auto &s : byName) {
        s.print();
    }
    cout << endl;
    
    // 按年龄排序（使用仿函数）
    vector<Student> byAge = students;
    sort(byAge.begin(), byAge.end(), CompareByAge());
    
    for (const auto &s : byAge) {
        s.print();
    }
    
    return 0;
}*/
/*#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
};

int main() {
    int n;
    cin >> n;
    
    // 处理最多50个学生
    if (n > 50) n = 50;
    
    vector<Student> students(n);
    
    // 读取学生信息
    for (int i = 0; i < n; i++) {
        cin >> students[i].id >> students[i].name >> students[i].age;
    }
    
    // 1. 按姓名排序
    vector<Student> nameSorted = students;
    sort(nameSorted.begin(), nameSorted.end(), 
        [](const Student &a, const Student &b) {
            return a.name < b.name;
        });
    
    // 输出姓名排序结果
    // 格式：学号占3位右对齐，空格，姓名占6位右对齐，空格，年龄占3位右对齐
    for (const auto &student : nameSorted) {
        cout << setw(3) << right << student.id 
             << setw(6) << right << student.name 
             << setw(3) << right << student.age << endl;
    }
    
    // 输出空行分隔
    cout << endl;
    
    // 2. 按年龄排序，年龄相同时按姓名排序
    vector<Student> ageSorted = students;
    sort(ageSorted.begin(), ageSorted.end(), 
        [](const Student &a, const Student &b) {
            if (a.age != b.age) {
                return a.age < b.age;
            }
            return a.name < b.name;
        });
    
    // 输出年龄排序结果
    for (const auto &student : ageSorted) {
        cout << setw(3) << right << student.id  
             << setw(6) << right << student.name 
             << setw(3) << right << student.age << endl;
    }
    
    return 0;
}*/
/*【问题描述】
从键盘中读入最多不超过50个学生的学生信息（包括空格隔开的姓名、学号、年龄信息，以学号从低到高排序）
【输入形式】
每次键盘读入最多不超过50个学生的学生信息：
第一行为学生人数；
后面每一行为空格隔开的学生学号、姓名、年龄，其中学号和年龄都是整数。
【输出形式】
分别以姓名顺序（从低到高）和年龄顺序（从低到高）将学生信息输出，每行输出一位学生的信息，
其中学号占3位，姓名（英文）占6位，年龄占3位，均为右对齐。
年龄相同时按姓名从低到高排序。两种顺序的输出结果用一行空行相隔。
【输入样例】
4
1 aaa 22
45 bbb 23
54 ddd 20
110 ccc 19
【输出样例】
1    aaa     22          
45     bbb     23      
110     ccc     19   
54     ddd     20                                      
110     ccc     19          
54     ddd     20             
1     aaa     22          
45     bbb     23
【样例说明】
从键盘输入四个学生记录，分别按姓名和年龄排序并输出。*/
#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;
class s{
public:
    int id;
    string n;
    int ag;
    s(){}
};
bool s1(s&p1,s&p2){
    return p1.n<p2.n;
}
bool s2(s&p1,s&p2){
    if(p1.ag==p2.ag)
    return p1.n<p2.n;
    return p1.ag<p2.ag;
}
istream& operator>>(istream &i,s&p){
i>>p.id>>p.n>>p.ag;
return i;
}
ostream& operator<<(ostream &i,s&p){
i<<setw(3)<<right<<p.id<<setw(6)<<right<<p.n<<setw(3)<<right<<p.ag;
return i;
}
int main(){
int n;cin>>n;
vector<s>v(n);
for(auto&e:v){
    cin>>e;
}
sort(v.begin(),v.end(),s1);
for(auto&e:v){
    cout<<e<<endl;
}
cout<<endl;
sort(v.begin(),v.end(),s2);
for(auto&e:v){
    cout<<e<<endl;
}
return 0;
}