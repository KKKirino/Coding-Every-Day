// 不容易系列之一
// http://acm.hdu.edu.cn/showproblem.php?pid=1465
// Time Limit: 2000/1000 MS (Java/Others)    Memory Limit: 65536/32768 K (Java/Others)
// Total Submission(s): 34180    Accepted Submission(s): 14841


// Problem Description
// 大家常常感慨，要做好一件事情真的不容易，确实，失败比成功容易多了！
// 做好“一件”事情尚且不易，若想永远成功而总从不失败，那更是难上加难了，就像花钱总是比挣钱容易的道理一样。
// 话虽这样说，我还是要告诉大家，要想失败到一定程度也是不容易的。比如，我高中的时候，就有一个神奇的女生，在英语考试的时候，竟然把40个单项选择题全部做错了！大家都学过概率论，应该知道出现这种情况的概率，所以至今我都觉得这是一件神奇的事情。如果套用一句经典的评语，我们可以这样总结：一个人做错一道选择题并不难，难的是全部做错，一个不对。

// 不幸的是，这种小概率事件又发生了，而且就在我们身边：
// 事情是这样的——HDU有个网名叫做8006的男性同学，结交网友无数，最近该同学玩起了浪漫，同时给n个网友每人写了一封信，这都没什么，要命的是，他竟然把所有的信都装错了信封！注意了，是全部装错哟！

// 现在的问题是：请大家帮可怜的8006同学计算一下，一共有多少种可能的错误方式呢？
 

// Input
// 输入数据包含多个多个测试实例，每个测试实例占用一行，每行包含一个正整数n（1<n<=20），n表示8006的网友的人数。
 

// Output
// 对于每行输入请输出可能的错误方式的数量，每个实例的输出占用一行。
 

// Sample Input
// 2
// 3
 

// Sample Output
// 1
// 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 30;
long long dp[N];

int main() {
    int n;
    
    for (int i = 1; i <= n; ++ i) {
        dp[i] = 0;
    }
    dp[1] = 0;
    dp[2] = 1;
    for (int i = 3; i <= 20; ++ i) {
        dp[i] = (i - 1) * dp[i - 1] + (i - 1) * dp[i - 2];
    
    } 
    while (scanf("%d", &n) != EOF) {
        cout << dp[n] << endl;
    }
    return 0;
}