// 胜利大逃亡
// http://acm.hdu.edu.cn/showproblem.php?pid=1253
// Time Limit: 4000/2000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 55157    Accepted Submission(s): 18910


// Problem Description
// Ignatius被魔王抓走了,有一天魔王出差去了,这可是Ignatius逃亡的好机会.

// 魔王住在一个城堡里,城堡是一个A*B*C的立方体,可以被表示成A个B*C的矩阵,刚开始Ignatius被关在(0,0,0)的位置,离开城堡的门在(A-1,B-1,C-1)的位置,现在知道魔王将在T分钟后回到城堡,Ignatius每分钟能从一个坐标走到相邻的六个坐标中的其中一个.现在给你城堡的地图,请你计算出Ignatius能否在魔王回来前离开城堡(只要走到出口就算离开城堡,如果走到出口的时候魔王刚好回来也算逃亡成功),如果可以请输出需要多少分钟才能离开,如果不能则输出-1.

// Input
// 输入数据的第一行是一个正整数K,表明测试数据的数量.每组测试数据的第一行是四个正整数A,B,C和T(1<=A,B,C<=50,1<=T<=1000),它们分别代表城堡的大小和魔王回来的时间.然后是A块输入数据(先是第0块,然后是第1块,第2块......),每块输入数据有B行,每行有C个正整数,代表迷宫的布局,其中0代表路,1代表墙.(如果对输入描述不清楚,可以参考Sample Input中的迷宫描述,它表示的就是上图中的迷宫)

// 特别注意:本题的测试数据非常大,请使用scanf输入,我不能保证使用cin能不超时.在本OJ上请使用Visual C++提交.
 

// Output
// 对于每组测试数据,如果Ignatius能够在魔王回来前离开城堡,那么请输出他最少需要多少分钟,否则输出-1.
 

// Sample Input
// 1
// 3 3 4 20
// 0 1 1 1
// 0 0 1 1
// 0 1 1 1
// 1 1 1 1
// 1 0 0 1
// 0 1 1 1
// 0 0 0 0
// 0 1 1 0
// 0 1 1 0
 

// Sample Output
// 11

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int N = 50;
int n;
bool mark[N][N][N];
int G[N][N][N];

struct Node {
    int x, y, z;
    int t;
};

queue<Node> q;
int go[][3] = {
    1, 0, 0,
    -1, 0, 0,
    0, 1, 0,
    0, -1, 0,
    0, 0, 1,
    0, 0, -1
};

bool check(int a, int b, int c, int newx, int newy, int newz) {
    if (newx >= 0 && newx < a && newy >= 0 && newy < b && newz >= 0 && newz < c && mark[newx][newy][newz] == 0 && G[newx][newy][newz] == 0) return true;
    return false;
}

int bfs(int a, int b, int c) {
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        int tempx = cur.x;
        int tempy = cur.y;
        int tempz = cur.z;
        for (int i = 0; i < 6; ++ i) {
            int newx = tempx + go[i][0];
            int newy = tempy + go[i][1];
            int newz = tempz + go[i][2];
            if (check(a, b, c, newx, newy, newz) == false) continue;
            Node temp;
            temp.x = newx;
            temp.y = newy;
            temp.z = newz;
            temp.t = cur.t + 1;
            q.push(temp);
            mark[newx][newy][newz] = 1;
            if (temp.x == a - 1 && temp.y == b - 1 && temp.z == c - 1) return temp.t; 
        }
    }
    return -1;

}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        int a, b, c, time;
        scanf("%d%d%d%d", &a, &b, &c, &time);
        for (int i = 0; i < a; ++ i) {
            for (int j = 0; j < b; ++ j) {
                for (int k = 0; k < c; ++ k) {
                    scanf("%d", &G[i][j][k]);
                    mark[i][j][k] = false;
                }
            }
        }
        while (!q.empty()) q.pop();
        mark[0][0][0] = true;
        Node start;
        start.x = start.y = start.z = start.t = 0;
        q.push(start);
        int ans = bfs(a, b, c);
        // cout <<"t"<< ans << endl;
        if (ans <= time) printf("%d\n", ans); //若所需时间符合条件,则输出
        else printf("-1\n"); 
    }
    return 0;
}