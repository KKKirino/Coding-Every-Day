// 题目描述：
// 立方根的逼近迭代方程是 y(n+1) = y(n)*2/3 + x/(3*y(n)*y(n)),其中y0=x.求给定的x经过n次迭代后立方根的值。

// 输入：
// 输入有多组数据。
// 每组一行，输入x n。

// 输出：
// 迭代n次后的立方根，double精度,保留小数点后面六位。

// 样例输入：
// 3000000 28
// 样例输出：
// 144.224957

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double x;
int n;

double func(double cur) {
    double next;
    next = cur * 2 / 3 + x / (3 * cur * cur); // 如果这里写 double(2 / 3) 反而计算不出来了，为什么？
    return next;

}

int main() {
    cout << "请输入数据和迭代次数：" << endl;
    cin >> x >> n;
    double res;
    double cur = x;
    for (int i = 0; i < n; ++ i) {
        cur = func(cur);
    }
    printf("%0.6f\n", cur);
    return 0;
}
