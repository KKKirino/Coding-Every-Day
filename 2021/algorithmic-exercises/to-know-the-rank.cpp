// 确定比赛名次
// http://acm.hdu.edu.cn/showproblem.php?pid=1285
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 57855    Accepted Submission(s): 21079


// Problem Description
// 有N个比赛队（1<=N<=500），编号依次为1，2，3，。。。。，N进行比赛，比赛结束后，裁判委员会要将所有参赛队伍从前往后依次排名，但现在裁判委员会不能直接获得每个队的比赛成绩，只知道每场比赛的结果，即P1赢P2，用P1，P2表示，排名时P1在P2之前。现在请你编程序确定排名。
 

// Input
// 输入有若干组，每组中的第一行为二个数N（1<=N<=500），M；其中N表示队伍的个数，M表示接着有M行的输入数据。接下来的M行数据中，每行也有两个整数P1，P2表示即P1队赢了P2队。
 

// Output
// 给出一个符合要求的排名。输出时队伍号之间有空格，最后一名后面没有空格。

// 其他说明：符合条件的排名可能不是唯一的，此时要求输出时编号小的队伍在前；输入数据保证是正确的，即输入数据确保一定能有一个符合要求的排名。
 

// Sample Input
// 4 3
// 1 2
// 2 3
// 4 3
 

// Sample Output
// 1 2 4 3

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

const int N = 510;
vector<int> edge[N];
vector<int> q;
int inDegree[N];
int n, m; 

void init(int n) {
    for (int i = 1 ; i <= n; ++ i) {
        inDegree[i] = 0;
        edge[i].clear();
    }
    q.clear();

    return;
}

bool cmp1(int a, int b) {
    return a > b;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        init(n);
        for (int i = 0; i < m; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            inDegree[y] ++;
            edge[x].push_back(y);

        }

        for (int i = 1; i <= n; ++ i) {
            if (inDegree[i] == 0) q.push_back(i);
        }
        vector<int> res;
        while (q.size() != 0) {
            sort(q.begin(), q.end(), cmp1);
            int len = q.size();
            int cur = q[len - 1];
            q.pop_back();
            res.push_back(cur);
            for (auto &x : edge[cur]) {
                inDegree[x] --;
                if (inDegree[x] == 0) q.push_back(x);
            }
        }
        for (int i = 0; i < n; ++ i) {
            if (i != 0) cout << " " << res[i];
            else cout << res[i];
        }
        cout << endl;

    }
    return 0;


}