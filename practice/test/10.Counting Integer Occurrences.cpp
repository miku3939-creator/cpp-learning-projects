/*【问题描述】
输入一组无序的整数，编程输出其中出现次数最多的整数及其出现次数。
【输入形式】
先从标准输入读入整数的个数（大于等于1，小于等于100），
然后在下一行输入这些整数，各整数之间以一个空格分隔。
【输出形式】
在标准输出上输出出现次数最多的整数及其出现次数，两者以一个空格分隔；
若出现次数最多的整数有多个，则按照整数升序分行输出。
【样例输入】
10
0 -50 0 632 5813 -50 9 -50 0 632
【样例输出】
-50 3
0 3*/
/*#include<iostream>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
int main(){
    int n;
    multiset<int> s;
    cin>>n;
    int e;
    for(int i=0;i<n;i++){
        cin>>e;
        s.insert(e);
      }
map<int,int> m;
int k,v;
   for(auto& e:s){
  k=e;
  v=s.count(e);
  m.insert(make_pair(k,v));
      }
    }*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  map<int, int> m;
  for (auto &e : v)
  {
    cin >> e;
    m[e]++;
  }
  int max = 0;
  for (auto &[k, v] : m)
  {
    if (v > max)
      max = v;
  }
  for (auto &[k, v] : m)
  {
    if (v == max)
      cout << k << ' ' << v << endl;
  }
  return 0;
}