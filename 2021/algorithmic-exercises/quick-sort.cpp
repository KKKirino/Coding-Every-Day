// AcWing 786. 第k个数
// 题目描述
// 给定一个长度为n的整数数列，以及一个整数k，请用快速选择算法求出数列的第k小的数是多少。

// 输入格式
// 第一行包含两个整数 n 和 k。

// 第二行包含 n 个整数（所有整数均在1~1e9范围内），表示整数数列。

// 输出格式
// 输出一个整数，表示数列的第k小数。

// 数据范围
// 1≤n≤1000001≤n≤100000
// 1≤k≤n1≤k≤n
// 输入样例：
// 5 3
// 2 4 1 5 3
// 输出样例：
// 3

#include <iostream>
#include <vector>
using namespace std;

const int N = 100010;
int q[N];

int quickSort(int l, int r, int k) {
    if (l >= r) return q[l];
    int i = l, j = r, x = q[(l + r) >> 1];
    while (i < j) {
        if (q[i] == q[j]) j --; // 如果数据中有重复的数字，如果没有这个条件会无限循环swap。
        while (i < j && q[i] < x) i++;
        while (i < j && q[j] > x) j--;
        if (i < j) swap(q[i], q[j]);
    }
    // cout << "j" << j << endl;
    int inter = j - l + 1;
    // cout << inter << endl;
    if (inter >= k) return quickSort(l, j, k);
    else return quickSort(j + 1, r, k - (j - l + 1));
}

int main() {
    int n, k;
    cout << "请输入数据的个数以及k：" << endl;
    cin >> n >> k;
    cout << "请输入数据" << endl;
    for (int i = 0; i < n; ++ i) {
        cin >> q[i];
    }
    cout << quickSort(0, n - 1, k) << endl;
    return 0;
}