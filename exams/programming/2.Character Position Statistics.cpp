#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(){
string s;
char c;
cin>>s>>c;
vector<int>v;
int pos=s.find(c);
if(pos==-1){
    cout<<"NULL";
    return 0;
}
while(pos!=-1){
v.push_back(pos);
pos=s.find(c,pos+1);
}
for(auto& elem:v){
    cout<<elem<<' ';
}
return  0;
}