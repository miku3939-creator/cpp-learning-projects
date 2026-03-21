#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<fstream>
#include<sstream>
using namespace std;
 bool isN(string &token)
    {
        return !(token == "+" || token == "-" || token == "*" || token == "/");
    }

    int evalRPN(vector<string> &tokens)
    {
        stack<int> s;
        int n = tokens.size();
        for (int i = 0; i<n; i++)
        {
            string &token = tokens[i];
            if (isN(token))
            {
                s.push(stoi(token));
            }
            else
            {
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                switch (token[0])
                {
                case '+':
                    s.push(a + b);
                    break;
                case '-':
                    s.push(b - a);
                    break;
                case '*':
                    s.push(a * b);
                    break;
                case '/':
                    s.push(b / a);
                }
            }
        }
        return s.top();
    }
int main(){
ifstream in("in.txt");
if(!in.is_open()){
    cout<<"文件打开失败"<<endl;
    return 1;
}
string line;
getline(in,line);
vector<string> tokens;
stringstream ss(line);
string token;
while(getline(ss,token,',')){
    tokens.push_back(token);
}
cout<<evalRPN(tokens)<< endl;
return 0;
}