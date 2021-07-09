#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
#include <unordered_map>
using namespace std;

const int N  = 1010;
struct Node{
    string s1;
    string s2;
    int dis;
    int pri;
}node[N];

unordered_map<string, int> vis;
unordered_map<string, int> stringToint;
unordered_map<int, string> intTostring;
vector<Node> allRoad;
vector<Node> outRoad;
int G[2 * N][2 * N];
int father[2 * N];


bool cmp1(Node a, Node b) {
    return a.dis < b.dis;
}

bool cmp2(Node a, Node b) {
    return a.pri < b.pri;
}

bool cmp3(int a, int b) {
    return a < b;
}

void init(int x) {
    for (int i = 0; i <= x; ++ i) {
        for (int j = 0; j <= x; ++ j) {
            G[i][j] = -1;
        }
        G[i][i] = 0;
    }
    for (int i = 0; i <= x; ++ i) {
        father[i] = i;
    }
    return;
}

int findfather(int x) {
    if (father[x] != x) x = father[x];
    return father[x];
}

void Union (int a, int b) {
    int faA = findfather(a);
    int faB = findfather(b);
    if (faA != faB) {
        if (faA > faB) father[faA] = faB;
        else father[faB] = faA;
    }
    return;
}

int main() {
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; ++ i) {
        cin >> node[i].s1 >> node[i].s2 >> node[i].dis;
        if (stringToint.find(node[i].s1) == stringToint.end()) {
            stringToint[node[i].s1] = cnt;
            intTostring[cnt] = node[i].s1;
            cnt ++;
        }
        if (stringToint.find(node[i].s2) == stringToint.end()) {
            stringToint[node[i].s2] = cnt;
            intTostring[cnt] = node[i].s2;
            cnt ++;
        }
        node[i].pri = i;
        allRoad.push_back(node[i]);
    }
    init(cnt);
    // cout<< allRoad.size();
    sort(allRoad.begin(), allRoad.end(), cmp1);
    for (int i = 0; i < n ; ++ i) {
            int a = stringToint[allRoad[i].s1];
            int b = stringToint[allRoad[i].s2];
        if (findfather(a) != findfather(b)) {
            outRoad.push_back(allRoad[i]);
            Union(a, b);
            G[a][b] = G[b][a] = allRoad[i].dis;
        }
    }
    sort(outRoad.begin(), outRoad.end(), cmp2);
    int len = outRoad.size();
    // cout << outRoad.size();
    for (int i = 0; i < len; ++ i) {
        cout << outRoad[i].s1 << " " << outRoad[i].s2 << " " << outRoad[i].dis << endl;
    }
    vector<int> roadLen(cnt + 1);
    for (int i = 0; i < cnt; ++ i) roadLen[i] = 0;
    for (int k = 0; k < cnt; ++ k) 
            for (int i = 0; i < cnt; ++ i) {
                for (int j = 0; j < cnt; ++ j) {
                    if (G[i][k] == -1 || G[k][j] == -1) continue;
                    if (G[i][j] == -1 || G[i][j] > G[i][k] + G[k][j]) {
                        G[i][j] = G[i][k] + G[k][j];
                    }
            }
    }
    for (int i = 0; i < cnt; ++ i) {
        for (int j = 0; j < cnt; ++ j) {
            roadLen[i] += G[i][j];
            // cout << roadLen[i] << endl;
        }
    }
    sort(roadLen.begin(), roadLen.end(),cmp3);
    // for (int i = 0; i < cnt; ++ i) cout << G[2][i] << endl;
    // for (int i = 0; i <= cnt; ++ i) cout << roadLen[i] << endl;
    int i = 0;
    while (roadLen[i] == 0) i ++;
    double res;
    res = double(roadLen[i]) / double(cnt);
    printf("%.2f", res);
    return 0;
}