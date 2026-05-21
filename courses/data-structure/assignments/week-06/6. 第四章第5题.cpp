/*6. 第四章第5题
【问题描述】设计一个算法，删除一个链串s中所有非重叠的“abc”子串。例如，s=“aabcabcd”，删除后s=“ad”。
【输入形式】待删除子串
【输出形式】删除后子串 
【样例输入】aabcabcd

【样例输出】ad
【样例说明】
【评分标准】*/
#include <iostream>
#include <string>
using namespace std;

string deleteAbc(string s) {
    string res = ""; 
    for (int i = 0; i < s.size(); i++) {
        res += s[i]; // 将当前字符放入栈中
        
        // 检查栈顶是否构成 "abc"
        if (res.size() >= 3) {
            int len = res.size();
            if (res[len - 3] == 'a' && res[len - 2] == 'b' && res[len - 1] == 'c') {
                res.erase(len - 3, 3); // 弹出这三个字符
            }
        }
    }
    return res;
}

int main() {

    string s;
    if (cin >> s) {
        cout << deleteAbc(s) << endl;
    }
    
    return 0;
}