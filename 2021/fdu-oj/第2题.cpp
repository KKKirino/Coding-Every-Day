#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 1001;
int dp[N][N];

int main() {
    int m, n;
    cin >> m;
    for (int i  = 0; i < m; ++ i) {
        cin >> n;
        for (int j = 0; j < n; ++ j) {
            for (int k = 0; k < n; ++ k) {
                cin >> dp[j][k];
            }
        }
        // 考虑边界处的值
        for (int j = 1; j < n; ++ j) {
            dp[0][j] += dp[0][j - 1];
            dp[j][0] += dp[j - 1][0];
        }
        // 每个方格都可以由左边和上边的方格转移过来，取最大值即可
        for (int j = 1; j < n; ++ j) {
            for (int k = 1; k < n; ++ k) {
                dp[j][k] = max(dp[j - 1][k], dp[j][k - 1]) + dp[j][k];
            }
        }
        // 特判 n 为 0 的情况
        cout << (n > 0 ? dp[n - 1][n - 1] : 0 ) << endl;
    }
    return 0;
}