#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <unordered_map>
using namespace std;

struct Node {
    int user;
    string name;
    int machine;
    int time;
    unordered_map<int, int> machineP;
    bool flag = false;
}node[210];

unordered_map<int, int> userP;
unordered_map<int, Node> infmap;

vector<Node> ans;

bool cmp1(Node a, Node b) {
    if (a.name != b.name) return a.user < b.user;
    else return a.time < b.time;
}


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        int u, m, t;
        string s;
        cin >> u >> s >> m >> t;
        if (userP.find(u) != userP.end()) {
            Node cur = infmap[u];
            if (cur.machineP.find(m) == cur.machineP.end()) {
                node[i].user = u;
                node[i].name = s;
                node[i].time = t;
                node[i].machine = m;
                node[i].machineP[m] = 1;
                cur.machineP[m] = 1;
                ans.push_back(node[i]);
                if (cur.flag == false) {
                    ans.push_back(cur);
                    cur.flag = true;
                }
            }
        }
        else {
            node[i].user = u;
            node[i].name = s;
            node[i].time = t;
            node[i].machine = m;
            node[i].machineP[m] = 1;
            userP[u] = 1;
            infmap[u] = node[i];
        }
        
    }
    int len = ans.size();
        sort(ans.begin(), ans.end(), cmp1);
        for (int i = 0; i < len; ++ i) {
            if (i > 0 && ans[i].user == ans[i - 1].user) {
                if (ans[i].machine != ans[i - 1].machine) cout << ans[i].user << " " << ans[i].name << " " << ans[i].machine << " " << ans[i].time << endl;
            }
            else cout << ans[i].user << " " << ans[i].name << " " << ans[i].machine << " " << ans[i].time << endl;
        }
    return 0;
}