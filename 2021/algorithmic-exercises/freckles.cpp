// Freckles
// http://poj.org/problem?id=2560
// Time Limit: 1000MS		Memory Limit: 65536K
// Total Submissions: 10110		Accepted: 4627
// Description

// In an episode of the Dick Van Dyke show, little Richie connects the freckles on his Dad's back to form a picture of the Liberty Bell. Alas, one of the freckles turns out to be a scar, so his Ripley's engagement falls through.
// Consider Dick's back to be a plane with freckles at various (x,y) locations. Your job is to tell Richie how to connect the dots so as to minimize the amount of ink used. Richie connects the dots by drawing straight lines between pairs, possibly lifting the pen between lines. When Richie is done there must be a sequence of connected lines from any freckle to any other freckle.
// Input

// The first line contains 0 < n <= 100, the number of freckles on Dick's back. For each freckle, a line follows; each following line contains two real numbers indicating the (x,y) coordinates of the freckle.
// Output

// Your program prints a single real number to two decimal places: the minimum total length of ink lines that can connect all the freckles.
// Sample Input

// 3
// 1.0 1.0
// 2.0 2.0
// 2.0 4.0
// Sample Output

// 3.41
// Source

// Waterloo local 2000.09.23

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 110;
int father[N];
vector<vector<double>> edgepair;
int cnt = 0;

struct Edge{
    int u, v;
    double cost;
}edge[5000];

void init(int n) {
    for (int i = 0; i < n; ++ i) father[i] = i;
    return;
}

int findFather(int x) {
    int y = x;
    while (father[x] != x) {
        x = father[x];
    }
    while (y != x) {
        int temp = father[y];
        father[y] = x;
        y = temp;
    }
    return x;
}

void Union(int a, int b) {
    int faA = findFather(a);
    int faB = findFather(b);
    if (faA == faB) return;
    int minF = min(faA, faB);
    father[faA] = minF;
    father[faB] = minF;
    return;
}

double findCost(double a, double b, double c, double d) {
    double x = (a - c) * (a - c) + (b - d) * (b - d);
    return sqrt(x);
}

bool cmp1(Edge a, Edge b) {
    return a.cost < b.cost;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        double a, b;
        cin >> a >> b;
        edgepair.push_back({a, b});
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            double c = findCost(edgepair[i][0], edgepair[i][1], edgepair[j][0], edgepair[j][1]);
            edge[cnt].u = i;
            edge[cnt].v = j;
            edge[cnt].cost = c;
            cnt ++;
        }
    }

    init(cnt);
    double ans = 0;
    int edgenum = 0;
    sort(edge, edge + cnt, cmp1);
    for (int i = 0; i < cnt; ++ i) {
        int faA = findFather(edge[i].u);
        int faB = findFather(edge[i].v);
        if (faA == faB) continue;
        else {
            Union (edge[i].u, edge[i].v);
            ans += edge[i].cost;
            edgenum ++;
            if (edgenum == cnt - 1) break;
        }
    }
    printf("%.2f", ans);
    return 0;
}
