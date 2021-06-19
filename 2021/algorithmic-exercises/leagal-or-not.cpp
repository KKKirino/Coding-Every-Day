// Legal or Not
// http://acm.hdu.edu.cn/showproblem.php?pid=3342
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
// Total Submission(s): 16781    Accepted Submission(s): 7799


// Problem Description
// ACM-DIY is a large QQ group where many excellent acmers get together. It is so harmonious that just like a big family. Every day,many "holy cows" like HH, hh, AC, ZT, lcc, BF, Qinz and so on chat on-line to exchange their ideas. When someone has questions, many warm-hearted cows like Lost will come to help. Then the one being helped will call Lost "master", and Lost will have a nice "prentice". By and by, there are many pairs of "master and prentice". But then problem occurs: there are too many masters and too many prentices, how can we know whether it is legal or not?

// We all know a master can have many prentices and a prentice may have a lot of masters too, it's legal. Nevertheless，some cows are not so honest, they hold illegal relationship. Take HH and 3xian for instant, HH is 3xian's master and, at the same time, 3xian is HH's master,which is quite illegal! To avoid this,please help us to judge whether their relationship is legal or not.

// Please note that the "master and prentice" relation is transitive. It means that if A is B's master ans B is C's master, then A is C's master.
 

// Input
// The input consists of several test cases. For each case, the first line contains two integers, N (members to be tested) and M (relationships to be tested)(2 <= N, M <= 100). Then M lines follow, each contains a pair of (x, y) which means x is y's master and y is x's prentice. The input is terminated by N = 0.
// TO MAKE IT SIMPLE, we give every one a number (0, 1, 2,..., N-1). We use their numbers instead of their names.
 

// Output
// For each test case, print in one line the judgement of the messy relationship.
// If it is legal, output "YES", otherwise "NO".
 

// Sample Input
// 3 2
// 0 1
// 1 2
// 2 2
// 0 1
// 1 0
// 0 0
 

// Sample Output
// YES
// NO

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 110;
vector<int> edge[N];
int inDegree[N];
queue<int> q;
int n, m;

void init(int n) {
    for (int i = 0; i < n; ++ i) {
        inDegree[i] = 0;
        edge[i].clear();
    }
    while (!q.empty()) q.pop();
    return;
}
int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        init(n);
        for (int i = 0; i < m; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            inDegree[y] ++;
            edge[x].push_back(y);
        }
        for (int i = 0; i < n; ++ i) {
            if (inDegree[i] == 0) q.push(i);
        }
        int cnt = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            cnt ++;
            for (auto &x : edge[cur]) {
                inDegree[x] --;
                if (inDegree[x] == 0) q.push(x);
            }
        }
        if (cnt == n) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}