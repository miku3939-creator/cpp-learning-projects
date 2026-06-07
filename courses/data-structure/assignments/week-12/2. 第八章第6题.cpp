#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, v;
    cin >> n;
    
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            if (x == 1) g[i].push_back(j);
        }
    }
    cin >> v;
    
    // BFS
    vector<int> dist(n, -1);  
    queue<int> q;
    dist[v] = 0;
    q.push(v);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int w : g[u]) {
            if (dist[w] == -1) {
                dist[w] = dist[u] + 1;
                q.push(w);
            }
        }
    }
    int maxDist = -1;
    for (int i = 0; i < n; i++) {
        if (i != v && dist[i] > maxDist) {
            maxDist = dist[i];
        }
    }
    
    if (maxDist == -1) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < n; i++) {
            if (i != v && dist[i] == maxDist) {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}