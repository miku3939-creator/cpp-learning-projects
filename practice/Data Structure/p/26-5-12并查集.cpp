#include<iostream>
#include<vector>
using namespace std;
vector<int> v;
vector<int> h;
int find(int x){
    if(v[x]==x)
    return x;
    else return v[x]=find(v[x]);
}

void Union(int x,int y){
    int rootx=find(x);
    int rooty=find(y);
    if(rootx!=rooty){
        if(h[rootx]<h[rooty])
        v[rootx]=rooty;
        else if(h[rooty]<h[rootx])
        v[rooty]=rootx;
        else{
            v[rootx]=rooty;
            h[rooty]++;
        }
    }
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        v[i]=i;
    }
}