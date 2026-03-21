/*1. 链表重排
【问题描述】

给定一个单链表 L1→L2→⋯→Ln−1→Ln，请编写程序将链表重新排列为 Ln→L1→Ln−1→L2→⋯。例如：给定L为1→2→3→4→5→6，则输出应该为6→1→5→2→4→3。

【输入形式】

每个输入包含1个测试用例。每个测试用例第1行给出第1个结点的地址和结点总个数，即正整数N (≤105)。结点的地址是5位非负整数，NULL地址用−1表示。

接下来有N行，每行格式为：

Address Data Next


其中Address是结点地址；Data是该结点保存的数据，为不超过105的正整数；Next是下一结点的地址。题目保证给出的链表上至少有两个结点。

【输出形式】

对每个测试用例，顺序输出重排后的结果链表，其上每个结点占一行，格式与输入相同。
【样例输入】

00100 6
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218
【样例输出】

68237 6 00100
00100 1 99999
99999 5 12309
12309 2 00000
00000 4 33218
33218 3 -1
【类库使用要求】可以使用STL类库。

【输入类型】标准输入

【输出类型】标准输出

【评分标准】

10个测试用例，按通过比例评分。

【解题思路】（仅供参考，可以有其他解法）

定义链表结点：包含三元组，addr存储该结点本身的地址（可以定义为int或string类型，如果是int类型要注意位数不足时的输出时格式），value存该结点序号，next为指向下一结点的指针。

从输入数据构建链表，根据value值将其插入到链表相应位置；

按要求重排链表；

输出重排后的链表，输出内容为："当前节点.addr" "当前结点.value" "下一结点.addr(尾节点输出-1)"*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include<string>
using namespace std;
struct node
{
    string curr;
    int val;
    string next;
};
int main()
{
    string head;
    int n;
    cin >> head >> n;
    vector<node> List;
    unordered_map<string, node> temp;
    for (int i = 0; i < n; i++)
    {
        int val;
        string curr;
        string next;
        cin >> curr >> val >> next;
        temp[curr] = {curr, val, next};
    }
    string addr = head;
    while (stoi(addr) != -1)
    {
        List.push_back(temp[addr]);
        addr = temp[addr].next;
    }
    vector<node> res;
    int hea= 0;
    int tail = n - 1;
    bool tai = true;
    while (tail >= hea)
    {
        if (tai)
        {
            res.push_back(List[tail]);
            tail--;
            tai = false;
        }
        else
        {
            res.push_back(List[hea]);
            hea++;
            tai = true;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout<<res[i].curr << ' ' << res[i].val << ' ' << res[i + 1].curr << endl;
        else
            cout << res[i].curr << ' ' << res[i].val << ' ' << -1 << endl;
    }
    return 0;
}