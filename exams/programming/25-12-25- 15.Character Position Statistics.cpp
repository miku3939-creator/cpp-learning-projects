#include<string>
#include<iostream>
#include<vector>
using namespace std;
int main(){
string str;
char c;
cin>>str;
cin>>c;
vector<int>v;
int p=str.find(c);
if(p==-1){
cout<<"NULL";
return 0;}
while(p!=-1){
v.push_back(p);
p=static_cast<int>(str.find(c,p+1));
}
for(auto& b:v){
    cout<<b<<' ';
}
return 0;
}