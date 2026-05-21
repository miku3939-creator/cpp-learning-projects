/*【问题描述】

        一块花布条，里面有些图案，另有一块直接可用的小饰条，里面也有一些图案。对于给定的花布条和小饰条，计算一下能从花布条中尽可能剪出几块小饰条来呢？



【输入形式】

        输入中含有一些数据，分别是成对出现的花布条和小饰条，其布条都是用可见ASCII字符表示的，可见的ASCII字符有多少个，布条的花纹也有多少种花样。花纹条和小饰条不会超过1000个字符长。如果遇见#字符，则不再进行工作。



【输出形式】


输出能从花纹布中剪出的最多小饰条个数，如果一块都没有，那就老老实实输出0。



【样例输入】


abcde a3 #





【样例输出】

      0


【样例说明】

     输入的第一个字符串代表花布条，第二个字符串代表小饰条，#代表结束输入。输出的是可以裁剪出小饰条的个数。测试数据存放在in.txt文件中。


【评分标准】

       共10个测试用例，每通过一个测试得10分。*/
       #include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
vector<int> getPi(const string &t) {
    int m = t.size();
    vector<int> pi(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = pi[j - 1];
        if (t[i] == t[j]) j++;
        pi[i] = j;
    }
    return pi;
}


int countCuts(const string &s, const string &t) {
    int n = s.size();
    int m = t.size();
    if (m == 0) return 0;
    
    vector<int> pi = getPi(t);
    int count = 0;
    int j = 0; // 子串指针
    
    for (int i = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) j = pi[j - 1];
        if (s[i] == t[j]) j++;
        
        // 匹配成功
        if (j == m) {
            count++;
            j = 0; // 剪掉后，重置 j，防止重叠匹配
        }
    }
    return count;
}

int main() {
    ifstream in("in.txt");
    if (!in.is_open()) return 0;

    string s, t;
    while (in >> s && s != "#") {
        in >> t;
        cout << countCuts(s, t) << endl;
    }
    
    return 0;
}