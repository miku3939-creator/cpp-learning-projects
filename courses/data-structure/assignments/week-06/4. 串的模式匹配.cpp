/*4. 串的模式匹配
问题描述】子串出现次数问题：基于KMP算法实现输出字符串t在主串S中出现的次数。
【输入形式】

第一行，输入子串字符串t

第二行，输入主串字符串S

【样例输入】

abcab

aabcabcabaabcab

【样例输出】

3
【样例说明】标准输入输出

【评分标准】10个测试用例，每通过一个计10分，没有用KMP算法计0分。  

允许使用STL类库*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> computePi(const string& t) {
    int m = t.size();
    vector<int> pi(m, 0);
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) {
            j = pi[j - 1];
        }
        if (t[i] == t[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int countOccurrences(const string& S, const string& t) {
    int n = S.size();
    int m = t.size();
    if (m == 0) return 0; 

    vector<int> pi = computePi(t);
    int count = 0;
    int j = 0; // 子串的指针

    for (int i = 0; i < n; i++) {
        while (j > 0 && S[i] != t[j]) {
            j = pi[j - 1];
        }
        if (S[i] == t[j]) {
            j++;
        }
        if (j == m) {
            count++;
            j = pi[j - 1]; 
        }
    }
    return count;
}

int main() {
    string t, S;
    if (getline(cin, t) && getline(cin, S)) {
        cout << countOccurrences(S, t) << endl;
    }
    return 0;
}