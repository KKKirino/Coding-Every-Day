// Prime Ring Problem
// http://acm.hdu.edu.cn/showproblem.php?pid=1016
// Time Limit: 4000/2000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 90673    Accepted Submission(s): 37201


// Problem Description
// A ring is compose of n circles as shown in diagram. Put natural number 1, 2, ..., n into each circle separately, and the sum of numbers in two adjacent circles should be a prime.

// Note: the number of first circle should always be 1.


 

// Input
// n (0 < n < 20).
 

// Output
// The output format is shown as sample below. Each row represents a series of circle numbers in the ring beginning from 1 clockwisely and anticlockwisely. The order of numbers must satisfy the above requirements. Print solutions in lexicographical order.

// You are to write a program that completes above process.

// Print a blank line after each case.
 

// Sample Input
// 6
// 8
 

// Sample Output
// Case 1:
// 1 4 3 2 5 6
// 1 6 5 2 3 4

// Case 2:
// 1 2 3 8 5 6 7 4
// 1 2 5 8 3 4 7 6
// 1 4 7 6 5 8 3 2
// 1 6 7 4 3 8 5 2

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

bool prime[50];

void init(int n) {
    for (int i = 1; i <= n; ++ i) {
        prime[i] = true;
    }
    int x = 1;
    prime[1] = prime[2] = false;
    int bound = sqrt(n);
    for (int i = 2; i <= bound + 1; ++ i) {
        int x = 1;
        while (i * (x ++) <= n) {
            if (prime[i * x] == false) continue;
            else {
                prime[i * x] = false;
            }
        }

    }
    return;
}

void dfs(vector<vector<int>> &ans, vector<int> temp, int cur, int last, int n, int cnt, bool used[]) {
    // cout << cnt << endl;
    if (cnt == n) {
        if (prime[cur + last] == true && prime[cur + 1] == true) {
            temp.push_back(cur);
            ans.push_back(temp);
            return;
        }
        else return;
    }
    else {
        if (prime[cur + last] == true) {
            temp.push_back(cur);
            used[cur] = true;
            for (int i = 2; i <= n; ++ i) {
                if (used[i] == true) continue;
                else {
                    dfs(ans, temp, i, cur, n, cnt + 1, used);
                }
            }
        }
        used[cur] = false;
    }
    return;     
}

int main() {
    int n;
    int round = 0;
    while (scanf("%d", &n) != EOF) {
        init(2 * n);
        round ++;
        bool used[50];
        for (int i = 0; i <= n; ++ i) used[i] = false;
        vector<vector<int>> ans;
        vector<int> temp;
        used[1] = true;
        temp.push_back(1);
        int cnt = 1;
        for (int i = 2; i <= n; ++ i) {
            dfs(ans, temp, i, 1, n, cnt + 1, used);
        }
        printf("Case %d:\n", round);
        int len = ans.size();
        for (int i = 0; i < len; ++ i) {
            for (int j = 0; j < n; ++ j) {
                if (j != n - 1) cout << ans[i][j] << " ";
                else cout << ans[i][j] << endl;
            }
        }
        cout << endl;
    }
    return 0;

}