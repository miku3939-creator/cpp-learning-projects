#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool mys(string s1,string s2){
return (s1+s2)>(s2+s1);
}
int main(){
    int n;
    cin>>n;
    vector<string> v(n);
    for(auto&e :v){
        cin>>e;
    }
sort(v.begin(),v.end(),mys);
string res;
 for(auto&e :v){
        res+=e;
    }
    cout<< res<<endl;
    return 0;
}
