/*【问题描述】
假设用C++定义了一个学生类，包含如下字段：
class Student {
private:
    int id;         // 学号
    int chinese;    // 语文
    int math;       // 数学
    int english;    // 英语
    int physics;    // 物理
    int chemistry;  // 化学
    int biology;    // 生物
    int total;      // 总分
public:
    Student (int id, int chinese, int math, int english, int physics, int chemistry, int biology);
};
任务要求：
1. 补全Student类的构造函数，在构造函数中计算并初始化total字段。
2. 编写一个main函数，实现以下功能：
￮ 接收用户输入的学生信息，并将学生信息存入合适的STL容器中。
￮ 根据用户的选择进行排序：输入1,按照学号升序排序并输出学生信息; 输入2, 按照总分降序排序并输出学生信息。
￮ 用户输入的语文、数学和英语的分数介于0~150之间，物理、化学、生物的分数介于0~100之间。如果学生的任一成绩不在合法范围内，则该学生总成绩无效，在排序输出时，该学生信息应置于最后，并在总分列标记“invalid”。
￮ 总成绩“invalid”的学生信息排在最后面（不论是按照学号排列，还是按照总分排列），若有多个学生总分无效，总分无效部分按照稳定排序方式进行（即：排序前顺序排列）
￮ 学生成绩合法性检查可在Student类的构造函数中实现。
￮ 建议：使用std::sort进行排序，编写函数对象或lambda表达式完成自定义排序逻辑。
￮ 可以适当在Student类中增加字段；可以适当改造构造函数；可以适当添加Student类的成员函数。
【输入形式】
• n个学生的测试用例由n+2行输入。第一行，表示学生的数量n；接下来第2~（n+1）行表示学生的信息；第n+2行，表示排序方式（1表示按学号排序，2表示按总分排序）。
• 学生信息由“学号 语文 数学 英语 物理 化学 生物”等7个整型数字组成，学号编号为4位数字，第一位数字不为0。
【输出形式】
学号: 语文 数学 英语 物理 化学 生物 总分
注意，
• 学号后面是英文状态下的“:",后面有空格（space键）；
• 分数之间有空（space键）
• 总分后面没有空格，但有回车换行符。*/
/*【样例输入】
输入样例1：
3
1001 85 80 78 90 85 80
1002 90 95 88 86 89 90
1003 75 70 65 68 72 60
2
输入样例2：
3
1001 85 80 78 90 85 80
1002 180 95 88 86 89 90
1003 75 70 65 68 72 60
2
【样例输出】
输出样例1：
1002: 90 95 88 86 89 90 538
1001: 85 80 78 90 85 80 498
1003: 75 70 65 68 72 60 410
输出样例2：
1001: 85 80 78 90 85 80 498
1003: 75 70 65 68 72 60 410
1002: 180 95 88 86 89 90 invalid
【样例说明】
暂无
【评分标准】
每个测试用例2分，共10分。
测试用例包括空输入或0名学生的情况。
*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class s{
public:
    int id;         // 学号
    int ch;    // 语文
    int m;       // 数学
    int e;    // 英语
    int p;    // 物理
    int che;  // 化学
    int b;    // 生物
    int t;      // 总分
    s (){}
};
bool s1(s&p1,s&p2){
    if(p1.t>=0&&p2.t>=0)
    return p1.id<p2.id;
return p1.t>=p2.t;
}
bool s2(s&p1,s&p2){
    return p1.t>=p2.t;
}
istream&operator>>(istream& i,s&p){
    i>>p.id>>p.ch>>p.m>>p.e>>p.p>>p.che>>p.b;
    if((p.ch<=150&&p.ch>=0)&&
(p.m<=150&&p.m>=0)&&
(p.e<=150&&p.e>=0)&&
(p.p<=100&&p.p>=0)&&
(p.che<=100&&p.che>=0)&&
(p.b<=100&&p.b>=0))
    p.t=p.ch+p.m+p.e+p.p+p.che+p.b;
    else
    p.t=-1;
    return i;
}
ostream&operator<<(ostream& o,s&p){
       if(p.t>=0)
   o<<p.id<<": "<<p.ch<<' '<<p.m<<' '<<p.e<<' '<<p.p<<' '<<p.che<<' '<<p.b<<' '<<p.t;
    else
   o<<p.id<<": "<<p.ch<<' '<<p.m<<' '<<p.e<<' '<<p.p<<' '<<p.che<<' '<<p.b<<' '<<"invalid";
   return o;
}
int main(){
int n,a;
cin>>n;
vector<s> v(n);
for(auto& e:v){
    cin>>e;
}
cin>>a;
if(a==1)
sort(v.begin(),v.end(),s1);
else
sort(v.begin(),v.end(),s2);
for(auto& e:v){
    cout<<e<<endl;
}
return 0;
}