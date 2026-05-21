#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Person
{
public:
    int age;
    string name;
};

int main(){
//普通文件读写
ofstream ofs("write.txt");
ofs<<"hello world";
ofs.close();

ifstream ifs("read.txt");
if(!ifs.is_open()){
    cout<<"false";
    return 0;
}
string buf;
while(getline(ifs,buf)){
    cout<<buf;
}
ifs.close();

//二进制文件读写
ofstream ofs("write.txt",ios::out|ios::binary);
Person p{18,"wowo"};
ofs.write((const char*)&p,sizeof(Person));
ofs.close();

ifstream ifs;
ifs.open("write.txt",ios::in|ios::binary);
if(!ifs.is_open()){
    cout<<"false";
    return 0;
}
Person p2;
ifs.read((char*)& p2,sizeof(Person));
ofs.close(); 
return 0;
}