#include <iostream>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

struct Player {
    int id;
    int f;
    int s;
    long long dist;
    
    bool operator<(const Player& other) const {
        if (dist != other.dist)
            return dist > other.dist;  
        return id < other.id;        
    }
};

int main() {
    ifstream in("in.txt");
    int n;
    in >> n;
    
    vector<Player> players(n);
    set<Player> st;
    
    for (int i = 0; i < n; i++) {
        players[i].id = i + 1;
        in >> players[i].f >> players[i].s;
        players[i].dist = players[i].f;
        st.insert(players[i]);
    }
    
    vector<int> result;
    
    for (int t = 1; t <= n; t++) {
        Player out = *st.begin();
        st.erase(st.begin());
        result.push_back(out.id);
        
        vector<Player> updated;
        for (const auto& p : st) {
            Player np = p;
            np.dist += np.s;
            updated.push_back(np);
        }
        st.clear();
        for (const auto& p : updated) {
            st.insert(p);
        }
    }
    
    for (int i = 0; i < n; i++) {
        cout << result[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
    
    return 0;
}