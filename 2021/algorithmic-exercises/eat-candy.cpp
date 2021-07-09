// 吃糖果
// http://acm.hdu.edu.cn/showproblem.php?pid=1205
// Time Limit: 6000/3000 MS (Java/Others)    Memory Limit: 65535/32768 K (Java/Others)
// Total Submission(s): 65715    Accepted Submission(s): 18788


// Problem Description
// HOHO，终于从Speakless手上赢走了所有的糖果，是Gardon吃糖果时有个特殊的癖好，就是不喜欢将一样的糖果放在一起吃，喜欢先吃一种，下一次吃另一种，这样；可是Gardon不知道是否存在一种吃糖果的顺序使得他能把所有糖果都吃完？请你写个程序帮忙计算一下。
 

// Input
// 第一行有一个整数T，接下来T组数据，每组数据占2行，第一行是一个整数N（0<N<=1000000)，第二行是N个数，表示N种糖果的数目Mi(0<Mi<=1000000)。
 

// Output
// 对于每组数据，输出一行，包含一个"Yes"或者"No"。
 

// Sample Input
// 2
// 3
// 4 1 1
// 5
// 5 4 3 2 1
 

// Sample Output
// No
// Yes

#include<bits/stdc++.h>
using namespace std;

int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; ++ i) {
        int m;
        cin >> m;
        long long maxnum = 0;
        long long sum = 0;
        for (int j = 0; j < m; ++ j) {
            int cur;
            scanf("%d", &cur);
            maxnum = max(maxnum, cur);
            sum += cur;
        }
        sum -= maxnum;
        if (sum + 1 >= maxnum) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;

}