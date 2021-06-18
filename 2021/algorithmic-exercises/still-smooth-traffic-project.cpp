// 还是畅通工程
// Time Limit: 4000/2000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 81699    Accepted Submission(s): 37006


// Problem Description
// 某省调查乡村交通状况，得到的统计表中列出了任意两村庄间的距离。省政府“畅通工程”的目标是使全省任何两个村庄间都可以实现公路交通（但不一定有直接的公路相连，只要能间接通过公路可达即可），并要求铺设的公路总长度为最小。请计算最小的公路总长度。
 

// Input
// 测试输入包含若干测试用例。每个测试用例的第1行给出村庄数目N ( < 100 )；随后的N(N-1)/2行对应村庄间的距离，每行给出一对正整数，分别是两个村庄的编号，以及此两村庄间的距离。为简单起见，村庄从1到N编号。
// 当N为0时，输入结束，该用例不被处理。
 

// Output
// 对每个测试用例，在1行里输出最小的公路总长度。
 

// Sample Input
// 3
// 1 2 1
// 1 3 2
// 2 3 4
// 4
// 1 2 1
// 1 3 4
// 1 4 1
// 2 3 3
// 2 4 2
// 3 4 5
// 0
 

// Sample Output
// 3
// 5

// Hint
// Hint

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 110;
int father[N];

struct Edge{
    int u, v;
    int cost;
}edge[5500];

void init(int n) {
    for (int i = 1; i <= n; ++ i) father[i] = i;
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

bool cmp1(Edge a, Edge b) {
    return a.cost < b.cost;
}

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) return 0;
        int bound = n * (n - 1) / 2;
        init(n);
        for (int i = 0; i < bound; ++ i) {
            int a, b, c;
            cin >> a >> b >> c;
            edge[i].u = a;
            edge[i].v = b;
            edge[i].cost = c;
        }
        sort(edge, edge + bound, cmp1);
        int ans = 0;
        int num = 0;
        for (int i = 0; i < bound; ++ i) {
            int faA = findFather(edge[i].u);
            int faB = findFather(edge[i].v);
            if (faA == faB) continue;
            else {
                Union (edge[i].u, edge[i].v);
                ans += edge[i].cost;
                num ++;
                if (num == bound - 1) break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}