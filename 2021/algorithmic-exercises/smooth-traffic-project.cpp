// 畅通工程（九度 OJ 1012）
// 时间限制：1 秒 内存限制：128 兆 特殊判题：否
// 1.题目描述：

// 某省调查城镇交通状况，得到现有城镇道路统计表，表中列出了每条道路直接连通的城镇。省政府“畅通工程”的目标是使全省任何两个城镇间都可以实现交通（但不一定有直接的道路相连，只要互相间接通过道路可达即可）。问最少还需要建设多少条道路？
// 输入：
// 测试输入包含若干测试用例。每个测试用例的第 1 行给出两个正整数，分别是城镇数目 N ( < 1000 )和道路数目 M；随后的 M 行对应 M 条道路，每行给出一对正整数，分别是该条道路直接连通的两个城镇的编号。为简单起见，城镇从1 到 N 编号。当 N 为 0 时，输入结束，该用例不被处理。
// 输出：
// 对每个测试用例，在 1 行里输出最少还需要建设的道路数目。
// 样例输入：
// 4 2
// 1 3
// 4 3
// 3 3
// 1 2
// 1 3
// 2 3
// 5 2
// 1 2
// 3 5
// 999 0
// 0
// 样例输出：
// 1
// 0
// 2
// 998

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
using namespace std;

const int N = 1010;
int father[N];

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



int main() {
    int n, m;
    while (cin >> n) {
        if (n == 0) break;
        init(n);
        cin >> m;
        for (int i = 0; i < m; ++ i) {
            int x, y;
            cin >> x >> y;
            Union(x, y);
        }
        unordered_set<int> mp;
        int cnt = 0;
        for (int i = 1; i <= n; ++ i) {
            if (father[i] == i) cnt ++;
        }
        cout << cnt - 1 << endl;
    }
    return 0;

}