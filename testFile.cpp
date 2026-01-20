#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void test01()
{
    ofstream ofs;
    ofs.open("test.txt", ios::in);
    ofs << "hey,what is your name?\n";
    ofs << "my name is lily\n";
    ofs << "nice to meet you!\n";
    ofs << "nice to meet you too!\n";
    ofs.close();
}
void test02()
{
    ifstream ifs;
    ifs.open("test.txt", ios::in);
    if (!ifs.is_open())
    {
        cout << "failed";
        return;
    }
    else
        cout << "success!\n";

    // first
    /*char buf[1024] = {0};
    while (ifs >> buf)
    {
        cout << buf << endl;
    }
    */

    // second
    /*char buf[1024] = {0};
    while (ifs.getline(buf,sizeof(buf)))
        {
            cout << buf << endl;
        }*/
    

    // third
    /*string s;
    while (getline(ifs,s))
    {
        cout << s << endl;
    }*/

//fourth
char c;
while((c=ifs.get())!=EOF){
    cout<<c;
}
    ifs.close();
}
int main()
{
    test01();
    test02();
    return 0;
}
