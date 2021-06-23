// 例 6.7 Temple of the bone（九度 OJ 1461）
// http://acm.hdu.edu.cn/showproblem.php?pid=1010
// 时间限制：1 秒
// 内存限制：32 兆
// 特殊判题：否
// 题目描述：
//
// The doggie found a bone in an ancient maze, which fascinated him a lot.
// However, when he picked it up, the maze began to shake, and the doggie could feel
// the ground sinking. He realized that the bone was a trap, and he tried desperately to
// get out of this maze.
// The maze was a rectangle with sizes N by M. There was a door in the maze. At
// the beginning, the door was closed and it would open at the T-th second for a short
// period of time (less than 1 second). Therefore the doggie had to arrive at the door on
// exactly the T-th second. In every second, he could move one block to one of the upper,
// lower, left and right neighboring blocks. Once he entered a block, the ground of this
// block would start to sink and disappear in the next second. He could not stay at one
// block for more than one second, nor could he move into a visited block. Can the poor
// doggie survive? Please help him.
//
// 输入：
// The input consists of multiple test cases. The first line of each test case contains
// three integers N, M, and T (1 < N, M < 7; 0 < T < 50), which denote the sizes of the
// maze and the time at which the door will open, respectively. The next N lines give the
// maze layout, with each line containing M characters. A character is one of the
// following:
// 'X': a block of wall, which the doggie cannot enter;
// 'S': the start point of the doggie;
// 'D': the Door; or
// '.': an empty block.
// The input is terminated with three 0's. This test case is not to be processed.
//
// 输出：
// For each test case, print in one line "YES" if the doggie can survive, or "NO"
// otherwise.
//
// 样例输入：
// 4 4 5
// S.X.
// ..X.
// ..XD
// ....
// 3 4 5
// S.X.
// ..X.
// ...D
// 0 0 0
// 样例输出：
// NO
// YES

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int N = 10;
int G[N][N];

void init(int x, int y) {
    for (int i = 0; i < x; ++ i) {
        for (int j = 0; j < y; ++ j) {
            G[i][j] = 0;
        }
    }
    return;
}

bool check(int tempx, int tempy, int x, int y) {
    if (tempx < x && tempx >= 0 && tempy < y && tempy >= 0) return true;
    return false;
}

void mark(int x, int y, int X, int Y, int cnt, bool &flag, int k) {
    if (flag) return;
    if (check(x, y, X, Y) && G[x][y] == 3 && cnt == k) {
        flag = true;
        return;
    }
    if (cnt + 1 > k) return;
    if (check(x, y, X, Y) && G[x][y] == 0) {
        G[x][y] = 1;
        cnt ++;
        mark(x + 1, y, X, Y, cnt, flag, k);
        mark(x, y + 1, X, Y, cnt, flag, k);
        mark(x - 1, y, X, Y, cnt, flag, k);
        mark(x, y - 1, X, Y, cnt, flag, k);
        G[x][y] = 0;
    }
    return;

}

int main() {
    int x, y, k;
    while (cin >> x >> y >> k) {
        if (x == 0 || y == 0 || k == 0) return 0;
        string s;
        int startx, starty, endx, endy;
        init(x, y);
        bool flag = false;
        for (int i = 0; i < x; ++ i) {
            cin >> s;
            for (int j = 0; j < y; ++ j) {
                char cur = s[j];
                if (cur == 'S') {
                    startx = i;
                    starty = j;
                    G[i][j] = 0;
                }
                else if (cur == 'D') {
                    endx = i;
                    endy = j;
                    G[i][j] = 3;
                    }
                else if (cur == 'X') G[i][j] = 1;
                else G[i][j] = 0;
            }
        }
        if ((startx + starty) % 2 == ((endx + endy) % 2 + k % 2 ) % 2) mark(startx, starty, x, y, 0, flag, k);
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
    
}