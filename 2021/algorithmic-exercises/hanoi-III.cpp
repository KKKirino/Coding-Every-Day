// 汉诺塔III
// http://acm.hdu.edu.cn/showproblem.php?pid=2064
// Time Limit: 1000/1000 MS (Java/Others)    Memory Limit: 32768/32768 K (Java/Others)
// Total Submission(s): 33083    Accepted Submission(s): 15963


// Problem Description
// 约19世纪末，在欧州的商店中出售一种智力玩具，在一块铜板上有三根杆，最左边的杆上自上而下、由小到大顺序串着由64个圆盘构成的塔。目的是将最左边杆上的盘全部移到右边的杆上，条件是一次只能移动一个盘，且不允许大盘放在小盘的上面。
// 现在我们改变游戏的玩法，不允许直接从最左(右)边移到最右(左)边(每次移动一定是移到中间杆或从中间移出)，也不允许大盘放到下盘的上面。
// Daisy已经做过原来的汉诺塔问题和汉诺塔II，但碰到这个问题时，她想了很久都不能解决，现在请你帮助她。现在有N个圆盘，她至少多少次移动才能把这些圆盘从最左边移到最右边？
 

// Input
// 包含多组数据，每次输入一个N值(1<=N=35)。
 

// Output
// 对于每组数据，输出移动最小的次数。
 

// Sample Input
// 1
// 3
// 12
 

// Sample Output
// 2
// 26
// 531440

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
long long F(int num) {
    if (num == 1) return 2;
    else {
        return 3 * F(num - 1) + 2;
    }
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        long long ans = F(n);
        printf("%lld\n", ans);
    }
    return 0;
}