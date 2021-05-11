#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <map>
#include <stack>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

void upAdjust(int low, int high, vector<int>& tree) {
    int i = high, j = high / 2;
    while (i >= 1 && j >= low) {
        if (tree[i] > tree[j]) {
            swap(tree[j], tree[i]);
            i = j;
            j = j / 2;
        }
        else break;
    }
    return;
}

void downAdjust(int low, int high, vector<int>& originNum) {
    int i = low, j = i * 2;
    while (j <= high) {
        if (j + 1 <= high && originNum[j + 1] > originNum[j]) {
            j = j + 1;
        }
        if (originNum[j] > originNum[i]) {
            swap(originNum[j], originNum[i]);
            i = j;
            j = i * 2; 
        }
        else break;
    }
    return;
}

void insert(int num, vector<int>& tree) {
    tree.push_back(num);
    int len = tree.size();
    upAdjust(1, len, tree);
    return;
}

void deleteTop(vector<int>& tree) {
    cout << tree[1] << " ";
    int len = tree.size();
    tree[1] = tree[len - 1];
    tree.pop_back();
    downAdjust(1, len - 1, tree);
    return;
}

void createHeap(int n, vector<int> originNum) {
    vector<int> tree;
    tree.push_back(-1);
    for (int i = 1; i <= n; ++ i) {
        tree.push_back(originNum[i]);
        upAdjust(1, i, tree);
    }
    printf("CreateHeap Result:");
    cout << endl;
    for (int i = 1; i <= n; ++ i) {
        cout << tree[i] << " "; 
    }
    cout << endl;
}

int main() {
    int n;
    printf("Please enter the number of digits:");
    cin >> n;
    printf("Please enter the digits:");
    vector<int> originNum;
    originNum.push_back(-1);
    for (int i = 1; i <= n; ++ i) {
        int num;
        cin >> num;
        originNum.push_back(num);
    }
    createHeap(n, originNum);
    
    for (int i = n / 2; i >= 1; -- i) {
        downAdjust(i, n, originNum);
    }
    printf("Adjust Result:");
    cout << endl;
    for (int i = 1; i <= n; ++ i) {
        cout << originNum[i] << " "; 
    }
    cout << endl;

    printf("HeapSort Result by Deleting:");
    for (int i = 1; i <= n; ++ i) {
        deleteTop(originNum);
    }
    cout << endl;

    return 0;
}