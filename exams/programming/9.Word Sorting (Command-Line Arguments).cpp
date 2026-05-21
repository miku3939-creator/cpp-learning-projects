/*【问题描述】
编写一个程序，从一个文件中读入单词（即：以空格或回车换行分隔的字符串），并对单词进行排序，删除重复出现的单词，然后将结果输出到另一个文件中。
【输入形式】
源文件名和目标文件名在执行时作为程序命令行参数输入，例如若程序名为sort，
源文件名和目标文件名分别为sort.in和sort.out，则命令行为：sort  sort.in  sort.out。
程序将从当前目录下sort.in文件中读入单词。
【输出形式】
对单词进行排序，删除重复出现的单词，然后将结果输出到文件sort.out中。
【输入样例】
假如sort.in文件内容如下：

rrr  sss  aaa  bbb  ccc   ddf  aaa  dd
【输出样例】
sort.out文件内容为：

aaa bbb ccc dd  ddf  rrr sss
【样例说明】
读入文件sort.in，做适当的排序，并删除重复出现的单词，输出到文件sort.out*/
/*#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
    string s1 = argv[1];
    string s2 = argv[2];
    ifstream ifs;
    ifs.open(s1.c_str(), ios::in);
    string buf;
    vector<string> p;
    while (getline(ifs, buf))
    {
        p.push_back(buf);
    }
    ifs.close();
    sort(begin(p), end(p));
    int n = p.size();
    for (int i = 0; i < n - 1; i++)
    {
        while (p[i] == p[i + 1])
        {
            p.erase(p.begin() + i + 1);
            n--;
        }
    }
    ofstream ofs;
    ofs.open(s2.c_str(), ios::out);
    for (auto &m : p)
    {
        ofs << m << ' ';
    }
    ofs.close();
    return 0;
}*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc != 3) {
        cerr << "用法: " << argv[0] << " <输入文件> <输出文件>" << endl;
        cerr << "示例: " << argv[0] << " sort.in sort.out" << endl;
        return 1;
    }
    
    string inputFile = argv[1];
    string outputFile = argv[2];
    
    // 打开输入文件
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cerr << "错误: 无法打开输入文件 '" << inputFile << "'" << endl;
        return 1;
    }
    
    // 读取所有单词
    vector<string> words;
    string line;
    
    // 方法1：使用stringstream逐行读取
    while (getline(inFile, line)) {
        stringstream ss(line);
        string word;
        while (ss >> word) {  // >> 操作符会自动跳过空格
            words.push_back(word);
        }
    }
    
    // 方法2：直接使用 >> 操作符（更简单）
    // string word;
    // while (inFile >> word) {
    //     words.push_back(word);
    // }
    
    inFile.close();
    
    // 如果没有读到任何单词
    if (words.empty()) {
        ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            cerr << "错误: 无法创建输出文件 '" << outputFile << "'" << endl;
            return 1;
        }
        outFile.close();
        return 0;
    }
    
    // 排序
    sort(words.begin(), words.end());
    
    // 去重
    words.erase(unique(words.begin(), words.end()), words.end());
    
    // 打开输出文件
    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "错误: 无法创建输出文件 '" << outputFile << "'" << endl;
        return 1;
    }
    
    // 输出到文件（单词之间用一个空格分隔）
    for (size_t i = 0; i < words.size(); ++i) {
        outFile << words[i];
        if (i < words.size() - 1) {
            outFile << " ";
        }
    }
    
    outFile.close();
    
   
    return 0;
}