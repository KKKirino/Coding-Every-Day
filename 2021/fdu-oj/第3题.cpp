#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int m, n, ans;
    cin >> m;
    for (int i = 0; i < m; ++ i) {
        ans = 0;
        cin >> n;
        for (int j = 0; j < n; ++ j) {
            int x;
            cin >> x;
            ans = ans ^ x; // 成对数字异或后等于 0
        }
        cout << ans << endl;
    }
    return 0;
}