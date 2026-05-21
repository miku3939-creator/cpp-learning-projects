#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cctype>

using namespace std;

// 检查单词是否合法
bool isValid(const string& s) {
    if (s.empty()) return false;
    // 连字符不能作为首字符
    if (s[0] == '-') return false;
    
    // 只能包含字母或连字符
    for (char ch : s) {
        if (!isalpha(ch) && ch != '-') return false;
    }
    
    // 排除特定单词
    if (s == "a" || s == "an" || s == "the" || s == "and") return false;
    
    return true;
}

int main() {
    ifstream fin("crossin.txt");
    ofstream fout("crossout.txt");

    map<string, set<int>> crossRef;
    string line;
    int lineNum = 0;

    while (getline(fin, line)) {
        lineNum++;
        // 将行内非字母和非连字符的字符替换为空格，方便提取单词
        for (int i = 0; i < line.length(); i++) {
            if (!isalpha(line[i]) && line[i] != '-') {
                line[i] = ' ';
            }
        }

        stringstream ss(line);
        string word;
        while (ss >> word) {
            // 处理单词末尾可能是连字符的情况（根据题目描述：单词由字母和连字符构成）
            // 如果连字符在末尾或中间是合法的，只需过滤首位及含非字母字符
            if (isValid(word)) {
                crossRef[word].insert(lineNum);
            }
        }
    }

    // 输出结果
    for (auto const& [word, lines] : crossRef) {
        fout << word << ":";
        bool first = true;
        for (int num : lines) {
            if (!first) fout << ",";
            fout << num;
            first = false;
        }
        fout << endl;
    }

    return 0;
}
/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

// 检查单词合法性
bool isValid(const string& s) {
    if (s.empty() || s[0] == '-') return false;
    for (char ch : s) {
        if (!isalpha(ch) && ch != '-') return false;
    }
    // 排除黑名单
    static const unordered_map<string, bool> blacklist = {
        {"a", true}, {"an", true}, {"the", true}, {"and", true}
    };
    if (blacklist.count(s)) return false;
    return true;
}

int main() {
    ifstream fin("crossin.txt");
    ofstream fout("crossout.txt");

    // 1. 使用哈希表存储：单词 -> 行号集合
    // unordered_map 查找和插入比 map 更快
    unordered_map<string, set<int>> hashTable;
    
    string line;
    int lineNum = 0;
    while (getline(fin, line)) {
        lineNum++;
        // 预处理：非字母且非连字符转为空格
        for (char &ch : line) {
            if (!isalpha(ch) && ch != '-') ch = ' ';
        }
        
        stringstream ss(line);
        string word;
        while (ss >> word) {
            if (isValid(word)) {
                hashTable[word].insert(lineNum);
            }
        }
    }

    // 2. 哈希表不支持排序，需转存到 vector 中
    vector<pair<string, set<int>>> sortedWords(hashTable.begin(), hashTable.end());

    // 3. 手动排序：满足大写在前，小写在后（ASCII 顺序）
    sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // 4. 输出到文件
    for (const auto& item : sortedWords) {
        fout << item.first << ":";
        const set<int>& lines = item.second;
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            fout << *it << (next(it) == lines.end() ? "" : ",");
        }
        fout << endl;
    }

    return 0;
}
*/