/*3. 2023考研408试题编程题
【问题描述】

已知优先图 G 采用邻接矩阵存储是，其定义如下：

typedef struct{

 int numberVertices, numEgges;

char VerticesList[maxV];

int edge[maxV][maxV];

 } MGraph;

将图中出度大于入度的顶点成为 K 顶点，如图，


绘图1.jpg




a 和 b 都是  K  顶点，设计算法 int printVertices(MGraph G)对给定任意非空有向图 G，输出 G 中所有 K 顶点的算法，并返回 K 顶点的个数。


【输入形式】

please input the vertices such as '{a,b,c,d}':

{a,b,c,d}

please input the edge pair,such as '(a,b),(c,d)'

(a,b),(a,d),(b,d),(b,c),(c,d)

【输出形式】

K vertices: a b

Number of K vertices: 2

【样例输入】

{a,b,c,d}
(a,b),(a,d),(b,d),(b,c),(c,d)

【样例输出】

K vertices: a b

Number of K vertices: 2





【样例说明】

顶点以字母表示，边以数对表示。

注意：输出 G 中所有 K 顶点时，请保证这些节点的相对次序与第一行输入这些节点的相对次序一致


【评分标准】

正确输出给100分，错误输出给0分。*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
using namespace std;
#define maxv 100
class graph
{
public:
    int n, e;
    char list[maxv];
    int edge[maxv][maxv];
};
int main()
{
    string line;
    getline(cin, line);
    map<char, int> m;
    int n = 0;
    graph g;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] >= 'a' && line[i] <= 'z')
        {
            m[line[i]] = n;
            g.list[n++] = line[i];
        }
    }

    memset(g.edge, 0, sizeof(g.edge));

    getline(cin, line);
    int i = 0;
    while (i < line.size())
    {
        if (line[i] >= 'a' && line[i] <= 'z')
        {
            g.edge[m[line[i]]][m[line[i + 2]]] = 1;
            i += 6;
        }
        else
        i++;
    }
    vector<int> ind(n);
    vector<int> outd(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (g.edge[i][j] != 0)
            {
                outd[i]++;
                ind[j]++;
            }
        }
    int cnt = 0;
    cout << "K vertices: ";
    for (int i = 0; i < n; i++)
    {
        if (outd[i] > ind[i])
        {
            cout << g.list[i] << ' ';
            cnt++;
        }
    }
    cout << endl;
    cout << "Number of K vertices: " << cnt << endl;
    return 0;
}
