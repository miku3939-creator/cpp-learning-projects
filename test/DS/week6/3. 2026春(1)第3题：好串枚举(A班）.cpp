#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    
    vector<vector<bool>> good(n, vector<bool>(n, false));
    vector<vector<bool>> nd(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; ++i) {
        good[i][i] = true;
        nd[i][i] = true;
    }
    
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            
            if (nd[i][j-1]) {
                if (s[j] >= s[j-1] && s[j] - s[j-1] <= 1) {
                    nd[i][j] = true;
                }
            }
            
            for (int k = i; k < j; ++k) {
                if (k == i && j == k + 1) {
                    good[i][j] = true;
                    break;
                }
                if (k == i && nd[k+1][j]) {
                    good[i][j] = true;
                    break;
                }
                if (j == k + 1 && nd[i][k]) {
                    good[i][j] = true;
                    break;
                }
                if (nd[i][k] && nd[k+1][j]) {
                    good[i][j] = true;
                    break;
                }
            }
        }
    }
    
    vector<string> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (good[i][j]) {
                ans.push_back(s.substr(i, j - i + 1));
            }
        }
    }
    
    cout << s << "有" << ans.size() << "个好串：";
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    
    return 0;
}