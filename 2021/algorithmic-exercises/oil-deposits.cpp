// Oil Deposits
// http://acm.hdu.edu.cn/showproblem.php?pid=1241
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 66445    Accepted Submission(s): 38277


// Problem Description
// The GeoSurvComp geologic survey company is responsible for detecting underground oil deposits. GeoSurvComp works with one large rectangular region of land at a time, and creates a grid that divides the land into numerous square plots. It then analyzes each plot separately, using sensing equipment to determine whether or not the plot contains oil. A plot containing oil is called a pocket. If two pockets are adjacent, then they are part of the same oil deposit. Oil deposits can be quite large and may contain numerous pockets. Your job is to determine how many different oil deposits are contained in a grid.
 

// Input
// The input file contains one or more grids. Each grid begins with a line containing m and n, the number of rows and columns in the grid, separated by a single space. If m = 0 it signals the end of the input; otherwise 1 <= m <= 100 and 1 <= n <= 100. Following this are m lines of n characters each (not counting the end-of-line characters). Each character corresponds to one plot, and is either `*', representing the absence of oil, or `@', representing an oil pocket.
 

// Output
// For each grid, output the number of distinct oil deposits. Two different pockets are part of the same oil deposit if they are adjacent horizontally, vertically, or diagonally. An oil deposit will not contain more than 100 pockets.
 

// Sample Input
// 1 1
// *
// 3 5
// *@*@*
// **@**
// *@*@*
// 1 8
// @@****@*
// 5 5 
// ****@
// *@@*@
// *@**@
// @@@*@
// @@**@
// 0 0 
 

// Sample Output
// 0
// 1
// 2
// 2

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int N = 110;
bool G[N][N];

void init(int x, int y) {
    for (int i = 0; i < x; ++ i) {
        for (int j = 0; j < y; ++ j) {
            G[i][j] = false;
        }
    }
    return;
}

bool check(int tempx, int tempy, int x, int y) {
    if (x > tempx && tempx >= 0 && y > tempy && tempy >= 0) return true;
    return false; 
}

void mark(int x, int y, int X, int Y) {
    if (check(x, y, X, Y) && G[x][y] == true) {
        G[x][y] = 0;
        mark(x - 1, y, X, Y);
        mark(x + 1, y, X, Y);
        mark(x, y + 1, X, Y);
        mark(x, y - 1, X, Y);
        mark(x - 1, y + 1, X, Y);
        mark(x + 1, y - 1, X, Y);
        mark(x - 1, y - 1, X, Y);
        mark(x + 1, y + 1, X, Y);
    }
    else return;

}

int main() {
    int x, y;
    while (scanf("%d %d", &x, &y), x || y) {
        int cnt = 0;
        init(x, y);
        for (int i = 0; i < x; ++ i) {
            string s;
            cin >> s;
            for (int j = 0; j < y; ++ j) {
                char cur = s[j];
                if (cur == '@') G[i][j] = 1;
                else G[i][j] = 0;
            }
        }
        for (int i = 0; i < x; ++ i) {
            for (int j = 0; j < y; ++ j) {
                if (G[i][j] == 1) {
                    cnt ++;
                    mark(i, j, x, y);
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}