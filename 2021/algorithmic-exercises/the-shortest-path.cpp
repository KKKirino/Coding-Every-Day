// 最短路
// http://acm.hdu.edu.cn/showproblem.php?pid=2544
// Time Limit: 5000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
// Total Submission(s): 128971    Accepted Submission(s): 55810


// Problem Description
// 在每年的校赛里，所有进入决赛的同学都会获得一件很漂亮的t-shirt。但是每当我们的工作人员把上百件的衣服从商店运回到赛场的时候，却是非常累的！所以现在他们想要寻找最短的从商店到赛场的路线，你可以帮助他们吗？

 

// Input
// 输入包括多组数据。每组数据第一行是两个整数N、M（N<=100，M<=10000），N表示成都的大街上有几个路口，标号为1的路口是商店所在地，标号为N的路口是赛场所在地，M则表示在成都有几条路。N=M=0表示输入结束。接下来M行，每行包括3个整数A，B，C（1<=A,B<=N,1<=C<=1000）,表示在路口A与路口B之间有一条路，我们的工作人员需要C分钟的时间走过这条路。
// 输入保证至少存在1条商店到赛场的路线。
 

// Output
// 对于每组输入，输出一行，表示工作人员从商店走到赛场的最短时间
 

// Sample Input
// 2 1
// 1 2 3
// 3 3
// 1 2 5
// 2 3 5
// 3 1 2
// 0 0
 

// Sample Output
// 3
// 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m;
const int  N = 110;
int ans[N][N];

void init(int x) {
    for (int i = 0; i <= x; ++ i) {
        for (int j = 0; j <= n; ++ j) {
            ans[i][j] = -1;
        }
        ans[i][i] = 0;
    }
    return;
}

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        init(n);
        for (int i = 0; i < m; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            ans[x][y] = ans[y][x] = z;
        }
        for (int k = 1; k <= n; ++ k) {
            for (int i = 1; i <= n; ++ i) {
                for (int j = 1; j <= n; ++ j) {
                    if (ans[i][k] == -1 || ans[k][j] == -1) continue;
                    if (ans[i][j] == -1 || ans[i][j] > ans[i][k] + ans[k][j]) {
                        ans[i][j] = ans[i][k] + ans[k][j];
                    }
            }
        }
    }
    cout << ans[1][n] << endl;
    }
    return 0;

}