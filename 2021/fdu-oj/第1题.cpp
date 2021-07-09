#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

const int N = 100000005;
int tree[N];

void inOrder(int &ans, int curIndex, int &cnt, int k, int n) {
    // 进入递归条件判断。只有当：1.当前索引小于总遍历数组长度；2.当前不为空结点；3.还未找到第K小的数字时，才继续进行递归。
    if (curIndex >= n || tree[curIndex] == -1 || cnt >= k) return; 
    inOrder(ans, curIndex * 2 + 1, cnt, k, n); // 中序遍历：先递归左子树。
    cnt ++; // 计数，遍历到第cnt小的结点。
    if (cnt == k) ans = tree[curIndex]; // 如果找到第K小结点，则得到最终结果。
    inOrder(ans, curIndex * 2 + 2, cnt, k, n); // 中序遍历：最后递归右子树。
    return;
}

int main() {
    int m;
    cin >> m;
    for (int j = 0; j < m; ++ j) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++ i) {
            cin >> tree[i]; // 建树，利用下标关系表示树的父子关系。
        }
        int k;
        cin >> k;
        int cnt = 0;
        int ans = -1;
        inOrder(ans, 0, cnt, k, n);
        cout << ans << endl;
    }
    return 0;      
}