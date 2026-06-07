#include<iostream>
#include<vector>
using namespace std;
int find(vector<int>& v,int l,int r,int k){
    if(l<r){
        int mid=(l+r)/2;
        if(k==v[mid])return mid;
        if(k<v[mid])return find(l,mid-1,k);
         else return find(mid+1,r,k);
    }
    else return -1;
}
int main(){
    int n,k;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    cin>>k;

}