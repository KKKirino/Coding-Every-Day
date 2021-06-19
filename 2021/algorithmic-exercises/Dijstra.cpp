// 最短路径问题
// http://acm.hdu.edu.cn/showproblem.php?pid=3790
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
// Total Submission(s): 52718    Accepted Submission(s): 14652


// Problem Description
// 给你n个点，m条无向边，每条边都有长度d和花费p，给你起点s终点t，要求输出起点到终点的最短距离及其花费，如果最短距离有多条路线，则输出花费最少的。
 

// Input
// 输入n,m，点的编号是1~n,然后是m行，每行4个数 a,b,d,p，表示a和b之间有一条边，且其长度为d，花费为p。最后一行是两个数 s,t;起点s，终点。n和m为0时输入结束。
// (1<n<=1000, 0<m<100000, s != t)
 

// Output
// 输出 一行有两个数， 最短距离及其花费。
 

// Sample Input
// 3 2
// 1 2 5 6
// 2 3 4 5
// 1 3
// 0 0
 

// Sample Output
// 9 11

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1010;
const int INF = 1<<30;
int dis[N],cost[N], G1[N][N], G2[N][N];
bool vis[N];
int n, m;


void init(int x) {
    for (int i = 0; i <= x; ++ i) {
        for (int j = 0; j <= x; ++ j) {
            G1[i][j] = G2[i][j] = INF;
        }
        G1[i][i] = G2[i][i] = 0;
    }
    memset(vis, 0, sizeof(vis));
    return;
}

void dijstra(int start, int end) {
    for (int i = 1; i <= n; ++ i) {
        dis[i] = G1[start][i];
        cost[i] = G2[start][i];
    }
    dis[start] = 0;
    cost[start] = 0;
    vis[start] = 1;
    int MIN;
    for (int i = 1; i <= n; ++ i) {
        int u = -1, MIN = INF;
        for (int j = 1; j <= n; ++ j) {
            if (vis[j] == 0 && dis[j] < MIN) {
                u = j;
                MIN = dis[j];
            }
        }
        if (u == -1 || u == end) break;
        vis[u] = 1;
        for (int v = 1; v <= n; v ++) {
            if (vis[v] == 0 && dis[u] + G1[u][v] < dis[v]) {
                dis[v] = dis[u] + G1[u][v];
                cost[v] = cost[u] + G2[u][v];
            }
            else if (vis[v] == 0 && dis[u] + G1[u][v] == dis[v] && cost[u] + G2[u][v] < cost[v]) {
                cost[v] = cost[u] + G2[u][v];
            }
        }
    }
    return;
    
}


int main() {
    while(scanf("%d%d",&n,&m),n||m) {   
    init(n);
    for (int i = 0; i < m; ++ i) {
        int x, y, z, w;
        scanf("%d%d%d%d",&x,&y,&z,&w);
        if (G1[x][y] > z) {
            G1[x][y] = G1[y][x] = z;
            G2[x][y] = G2[y][x] = w;
            }
        else if (G1[x][y] == z && G2[x][y] > w) G2[x][y] = G2[y][x] = w;
    }
    
    int start, end;
    cin >> start >> end;
    dijstra(start, end);

    cout << dis[end] << " " << cost[end] << endl;
    }
    return 0;

}