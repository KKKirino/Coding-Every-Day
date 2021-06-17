// http://acm.hdu.edu.cn/showproblem.php?pid=2817

// Problem Description
// Xinlv wrote some sequences on the paper a long time ago, they might be arithmetic or geometric sequences. The numbers are not very clear now, and only the first three numbers of each sequence are recognizable. Xinlv wants to know some numbers in these sequences, and he needs your help.
 

// Input
// The first line contains an integer N, indicting that there are N sequences. Each of the following N lines contain four integers. The first three indicating the first three numbers of the sequence, and the last one is K, indicating that we want to know the K-th numbers of the sequence.

// You can assume 0 < K <= 10^9, and the other three numbers are in the range [0, 2^63). All the numbers of the sequences are integers. And the sequences are non-decreasing.
 

// Output
// Output one line for each test case, that is, the K-th number module (%) 200907.
 

// Sample Input
// 2
// 1 2 3 5
// 1 2 4 5
 

// Sample Output
// 5
// 16

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long long quick(long long x, long long k, long long initVal) {
    long long ans = 1;
    while (k != 0) {
        if (k % 2 == 1) {
            ans *= x;
            ans %= 200907;
        }
        k /= 2;
        x = x * x % 200907;
    }
    return ((ans  % 200907) * (initVal % 200907)) % 200907;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        long long a, b, c, k;
        cin >> a >> b >> c >> k;
        long long dif1, dif2;
        dif1 = b - a;
        dif2 = c - b;
        if (dif1 == dif2) {
            long long ans = (a % 200907 + (dif1 % 200907) * ((k - 1) % 200907)) % 200907;
            cout << ans << endl;
            continue;
        }
        else {
            long long ans = quick(b / a, k - 1, a % 200907);
            cout << ans << endl;
            continue;
        }

    }
    return 0;

}