/*【问题描述】
小明发明了一种新的字符串加密方法，该方法是统计每一个字符出现的频率，并按照频率从小到大进行排序。假设共有已经按照频率排好序的M个字符code，然后将字符code[i]和code[m-i]进行交换。如果输入的字母种类是奇数个，那么频率是中间的字母不加密。
【输入形式】
一行字符串，每一个字符出现的频率不一样。
【输出形式】
输出加密后的字符串
【样例输入】
ABCDBDCDBCCDD
【样例输出】
DCBACABACBBAA
DCBACABACBBAA
【样例说明】
每一个字符出现的频率是A=1，B=3，C=4，D=5
那么就是将A和D交换，B和C交换，加密后的字符串是
DCBACABACBBAA
DCBACABACBBAA
【评分标准】*/
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
int main(){
    string s;
    getline(cin,s);

    map<char,int>m;
    for(auto e:s){
        m[e]++;
    }
    string c;
      for(auto e:m){
        c.push_back(e.first);
    }
  sort(c.begin(),c.end(),
[&m](char a,char b){
    if(m[a]!=m[b]){
        return m[a]<m[b];
    }
    return a<b;
});
map<char,char>f;
int n=c.size();
for(int i=0;i<n;i++){
    f[c[i]]=c[n-i-1];
}
for(auto e:s){
    cout<<f[e];
}
cout<<endl;
return 0;
}