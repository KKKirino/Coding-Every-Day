// 例 4.10 人见人爱 A ^ B (九度教程第 57 题) 
// 时间限制：1 秒 内存限制：128 兆 特殊判题：否 
// 题目描述： 
// 求 A^B 的最后三位数表示的整数。说明：A^B 的含义是“A 的 B 次方” 
// 输入： 
// 输入数据包含多个测试实例，每个实例占一行，由两个正整数 A 和 B 组成
// （1<=A,B<=10000），如果 A=0, B=0，则表示输入数据的结束，不做处理。 
// 输出： 
// 对于每个测试实例，请输出 A^B 的最后三位表示的整数，每个输出占一行。 
// 样例输入： 
// 2 3 
// 12 6 
// 6789 10000 
// 0 0 
// 样例输出： 
// 8 
// 984 
// 1

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int a, b;
    int n;
    cout << "请输入数据组数：" << endl;
    cin >> n;
    int ans = 1;
    cout << "请输入数据：" << endl;
    for (int i = 0; i < n; ++ i) {
        int ans = 1;
        cin >> a >> b;
        while (b != 0) {
            if (b % 2 == 1) {
                ans *= a;
                ans %= 1000;
            }
            b /= 2;
            a *= a;
            a %= 1000;
        }
        cout << ans << endl;
    }
    return 0;
}