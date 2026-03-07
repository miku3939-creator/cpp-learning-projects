/*【问题描述】
有一种加密方法为：其使用一个字母串（可以含重复字母）作为密钥。假定密钥单词串为feather，则先去掉密钥单词中的重复字母得到单词串feathr，然后再将字母表中的其它字母以反序追加到feathr的后面：
其中第一行为原始英文字母，第二行为对应加密字母。其它字符不进行加密。编写一个程序，用这种密码加密文件。假定要加密的文件名为encrypt.txt及加密后的文件名为output.txt，并假定输入文件中字母全为小写字母，并且输入密钥也全为小写字母。
【输入形式】
从标准输入中输入密钥串，并从文件encrypt.txt中读入要加密的内容。
【输出形式】
加密后结果输出到文件output.txt中。
【样例输入】
feather
和文件encrypt.txt中内容，例如被加密的文件encrypt.txt中内容为：
c language is wonderful.
【样例输出】
加密后output.txt文件中内容为：
a ufqzjfzh xl gpqthmrju.
【样例说明】
首先将给定的密钥单词去除重复字母，然后按照上面的加密对应表对encrypt.txt文件内容进行加密即可得到加密后的文件，其中只对英文字母进行加密对换，并且假设encrypt.txt中的英文字母全是小写字母。*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main()
{
    string s;
    cin >> s;
    string key;
    for (auto c : s)
    {
        if (key.find(c) == string::npos)
            key += c;
    }

    for (char i = 'z'; i >= 'a'; i--)
    {
        if (key.find(i) == string::npos)
            key += i;
    }
    ifstream i("encrypt.txt");
    ofstream o("output.txt");
    string l;
    while (getline(i, l))
    {
        for (char &c : l)
        {
            if (c <= 'z' && c >= 'a')
                c = key[c - 'a'];
        }
        o<<l<<endl;
    }
    i.close();
    o.close();
    return 0;
}
/*#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    string key;
    cin >> key;

    // 去重
    string unique_key;
    for (char c : key) {
        if (unique_key.find(c) == string::npos) {
            unique_key += c;
        }
    }

    // 构建加密表
    string cipher_alphabet = unique_key;
    for (char c = 'z'; c >= 'a'; c--) {
        if (unique_key.find(c) == string::npos) {
            cipher_alphabet += c;
        }
    }

    // 加密映射
    char encrypt_map[26];
    for (int i = 0; i < 26; i++) {
        encrypt_map[i] = cipher_alphabet[i];
    }

    // 处理文件
    ifstream in("encrypt.txt");
    ofstream out("output.txt");

    string line;
    while (getline(in, line)) {
        for (char &c : line) {
            if (c >= 'a' && c <= 'z') {
                c = encrypt_map[c - 'a'];
            }
        }
        out << line << endl;
    }

    in.close();
    out.close();

    return 0;
}*/
