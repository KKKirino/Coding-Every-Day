// 非常可乐
// http://acm.hdu.edu.cn/showproblem.php?pid=1495
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
// Total Submission(s): 41639    Accepted Submission(s): 16290


// Problem Description
// 大家一定觉的运动以后喝可乐是一件很惬意的事情，但是seeyou却不这么认为。因为每次当seeyou买了可乐以后，阿牛就要求和seeyou一起分享这一瓶可乐，而且一定要喝的和seeyou一样多。但seeyou的手中只有两个杯子，它们的容量分别是N 毫升和M 毫升 可乐的体积为S （S<101）毫升　(正好装满一瓶) ，它们三个之间可以相互倒可乐 (都是没有刻度的，且 S==N+M，101＞S＞0，N＞0，M＞0) 。聪明的ACMER你们说他们能平分吗？如果能请输出倒可乐的最少的次数，如果不能输出"NO"。
 

// Input
// 三个整数 : S 可乐的体积 , N 和 M是两个杯子的容量，以"0 0 0"结束。
 

// Output
// 如果能平分的话请输出最少要倒的次数，否则输出"NO"。
 

// Sample Input
// 7 4 3
// 4 1 3
// 0 0 0
 

// Sample Output
// NO
// 3

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;

struct Node{
    int a, b, c;
    int t;
};

bool mark[101][101][101];
int s;
queue<Node> q;

void AtoB (int totala, int & a, int totalb, int & b) {
    if (totalb - b >= a) {
        b = b + a;
        a = 0; 
    }
    else {
        a = a - (totalb - b);
        b = totalb;
    }
    return;
}

// bool check(int a, int b, int c) {
//     if (mark[a][b][c] == 1) return false;
//     return true;
// }

bool checkans(int a, int b, int c) {
    if (a * 2 == s && b * 2 == s) return true;
    if (a * 2 == s && c * 2 == s) return true;
    if (b * 2 == s && c * 2 == s) return true;
    return false;
}

int bfs(int x, int y, int z) {
    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        int tempa, tempb, tempc;
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(x, tempa, y, tempb);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(x, tempa, z, tempc);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(y, tempb, x, tempa);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(y, tempb, z, tempc);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(z, tempc, x, tempa);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
        tempa = cur.a;
        tempb = cur.b;
        tempc = cur.c;
        AtoB(z, tempc, y, tempb);
        if (mark[tempa][tempb][tempc] == 0) {
            mark[tempa][tempb][tempc] = 1;
            Node temp;
            temp.a = tempa;
            temp.b = tempb;
            temp.c = tempc;
            temp.t = cur.t + 1;
            if (checkans(tempa, tempb, tempc)) return temp.t;
            else q.push(temp);
        }
    }
    return -1;
    

}

int main() {
    int o, n, m;
    while (scanf("%d%d%d", &o, &n, &m), o || n || m) {
        while (!q.empty()) q.pop();
        if (o % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }
        s = o;
        for (int i = 0; i <= o; i ++) {
            for (int j = 0; j <= n; ++ j) {
                for (int k = 0; k <= m; ++ k) {
                    mark[i][j][k] = false;
                }
            }
        }
        mark[o][0][0] = true;
        Node cur;
        cur.a = s;
        cur.b = cur.c = cur.t = 0;
        q.push(cur);
        int ans = bfs(o, n, m);
        if (ans != -1) cout << ans << endl;
        else cout << "NO" << endl;
    }
    return 0;
}