#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int n=s.size();
    string s1="",s2="";
    for(int i=0;i<n;i++){
        if(s[i]<='9'&&s[i]>='0'){
            s1+=s[i];
        }
        else{
            s2+=s[i];
        }
    }
    string res=s1+s2;
    cout<<res<<endl;
}