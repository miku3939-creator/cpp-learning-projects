#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> n1(n);
    vector<int> n2(m);
    for (int i = 0; i < n; i++)
    {
        cin >>n1[i];
    }
      for (int i = 0; i < m; i++)
    {
        cin >>n2[i];
    }
    int t=m+n;
    n1.resize(t);
    n--;
    m--;
    t--;
    while(n>=0&&m>=0){
        if(n1[n]>n2[m]){
            swap(n1[n],n1[t]);
            n--;t--;
        }
        else{
            swap(n2[m],n1[t]);
            m--;t--;
        }
    }
    while(n>=0){
        swap(n1[n],n1[t]);
            n--;t--;
    }
    while(m>=0){
            swap(n2[m],n1[t]);
            m--;t--;
    }
    for(int i=0;i<n1.size();i++){
        cout<<n1[i]<<' ';
    }
    cout<<endl;
}