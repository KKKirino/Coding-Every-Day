// I Wanna Go Home
// http://poj.org/problem?id=3767
// Time Limit: 1000MS		Memory Limit: 65536K
// Total Submissions: 3817		Accepted: 1623
// Description

// The country is facing a terrible civil war----cities in the country are divided into two parts supporting different leaders. As a merchant, Mr. M does not pay attention to politics but he actually knows the severe situation, and your task is to help him reach home as soon as possible.

// "For the sake of safety,", said Mr.M, "your route should contain at most 1 road which connects two cities of different camp."

// Would you please tell Mr. M at least how long will it take to reach his sweet home?

// Input

// The input contains multiple test cases.

// The first line of each case is an integer N (2<=N<=600), representing the number of cities in the country.

// The second line contains one integer M (0<=M<=10000), which is the number of roads.

// The following M lines are the information of the roads. Each line contains three integers A, B and T, which means the road between city A and city B will cost time T. T is in the range of [1,500].

// Next part contains N integers, which are either 1 or 2. The i-th integer shows the supporting leader of city i.

// To simplify the problem, we assume that Mr. M starts from city 1 and his target is city 2. City 1 always supports leader 1 while city 2 is at the same side of leader 2.

// Note that all roads are bidirectional and there is at most 1 road between two cities.

// Input is ended with a case of N=0.

// Output

// For each test case, output one integer representing the minimum time to reach home.

// If it is impossible to reach home according to Mr. M's demands, output -1 instead.

// Sample Input

// 2
// 1
// 1 2 100
// 1 2
// 3
// 3
// 1 2 100
// 1 3 40
// 2 3 50
// 1 2 1
// 5
// 5
// 3 1 200
// 5 3 150
// 2 5 160
// 4 3 170
// 4 2 170
// 1 2 2 2 1
// 0
// Sample Output

// 100
// 90
// 540

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;

const int N = 610;
const int INF = 9999999;
int G[N][N];
int d1[N], d2[N];
bool vis[N];
int n, m;
int camp[N];

void init(int n, int d[])
{
    for (int i = 1; i <= n; ++ i) {
        d[i] = INF;
        camp[i] = INF;
        vis[i] = false;
    }
    return;
}

void dijstra(int s, int d[])
{
    d[s] = 0;
    int u, MIN;
    for (int i = 1; i <= n; ++i)
    {
        u = -1, MIN = INF;
        for (int j = 1; j <= n; ++j)
        {
            if (vis[j] == 0 && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }

        if (u == -1)
            return;
        vis[u] = 1;
        for (int v = 1; v <= n; v++)
        {
            if (vis[v] == 0 && G[u][v] < INF && camp[u] == camp[v] && d[v] > G[u][v] + d[u])
            {
                d[v] = G[u][v] + d[u];
            }
        }
    }
}

int main()
{
    while (scanf("%d", &n), n)
    {
        scanf("%d", &m);
        init(n + 1, d1);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++ j) G[i][j] = INF;
            G[i][i] = 0;
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G[x][y] = G[y][x] = z;
        }
        
        for (int i = 1; i <= n; ++i)
        {
            int x;
            scanf("%d", &x);
            camp[i] = x;
        }
        dijstra(1, d1);
            for (int i = 1; i <= n; ++ i) {
        d2[i] = INF;
        vis[i] = false;
    }
        dijstra(2, d2);
        int ans = INF;
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                if (i == j) continue;
                if (camp[i] == 1 && camp[j] == 2) {
                    ans = min(d1[i] + d2[j] + G[i][j], ans);
                }
            }
        }
        if (ans != INF) cout << ans << endl;
        else cout << -1 << endl;
    }
    return 0;
}