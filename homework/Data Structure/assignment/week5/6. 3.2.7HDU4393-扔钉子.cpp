/*【问题描述】

年度学校自行车比赛开始了，ZL是这所学校的学生，他太无聊了，因为他不能骑自行车！因此，他决定干预比赛，他通过以前的比赛视频获得了选手的信息，一个选手第一秒可以跑F米，然后每秒跑S米。每个选手有一条直线跑道，ZL每秒向跑的最远的运动员跑道扔一个钉子，在自行车胎爆炸之后，该选手将被淘汰。如果有多个选手是NO.1，则他总是选择ID最小的选手扔钉子。

【输入形式】

每个测试用例的第一行包含一个整数n（1≤n≤50000），表示选手人数，然后跟随n行，每行包含第i个选手的两个整数Fi（0≤Fi≤500），Si（0<Si≤100），表示该选手第一秒可以跑Fi米，然后每秒跑Si米，i是玩家从1开始的ID。

【输出形式】

    输出n个数字，以空格分隔，第i个数字是选手的ID，该选手将在第i秒结束时被淘汰。

【样例输入】

 3

100 1

100 2

3 100

【样例输出】

1 3 2

【样例说明】

测试数据的文件名为in.txt*/
#include <iostream>
#include <fstream>
using namespace std;
class stu
{
    int id;
    int f;
    int s;
    int x;
    stu *next;
};
class compete{
stu *head;
};
int main()
{
    ifstream in("in.txt");
    int n, f, s;
    in >> n;
    compete c;
    for (int i = 1; i <= n; i++)
    {
        c.insert(i,f,s);
    }
    while(!c.empty()){
        
    }
}