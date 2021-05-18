// 第二题
// 这题稍微复杂点，但是熟悉数据结构中的树的各种操作（遍历）的话应该也好做

// 这是一个机场的场景
// 规定数字100代表根节点
// 数字<100代表登机口
// 数字>100代表分岔点

// 如下图

// 同时规定每个节点的分支最多为4个分岔点和4个登机口

// 树的输入格式
// 10
// 100 0
// 101 100
// 3 100
// 1 101
// 2 101
// 102 100
// 103 102
// 4 102
// 5 102
// 6 103
// 也就是节点个数+该节点号和父节点号

// 这时候有摆渡车，输入m个乘客，从100出发，送乘客到登机口
// 每个乘客有优先级且送客过程如果刚好到达其他乘客要去的登机口所在的分岔点，则顺带下车
// 例如
// 3
// thunder1 6 1
// thunder2 3 2
// thunder3 2 0
// thunder4 4 3
// 也就是乘客个数+乘客名字和乘客目的地和优先级（最低的先送）

// 最终输出
// thunder2 3
// thunder3 2
// thunder4 4
// thunder1 6

// 以上场景就是先送thunder3到2 ，100->101->2，经过100过程中由于thunder2要去3，顺路下车。
//然后送完thunder3和thunder2，开始送thunder1，100->102->103，经过102是顺带送thunder4到4登机口。

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

const int maxN = 1010;

struct Node {
  int my;
  vector<int> child;
  int father;
}node[maxN];

struct Person{
  string name;
  int des;
  int pri;
  bool visit;
};

bool cmp1 (Person a, Person b) {
  return a.pri < b.pri;
}

int main() {
  vector<Person> q;
  int n;
  cout << "请输入节点个数：" << endl;
  cin >> n;
  cout << "请依次输入节点号码和其父节点：" << endl;
  for (int i = 0; i < n; ++ i) {
    int x, y;
    cin >> x >> y;
    node[x].my = x;
    node[x].father = y;
    node[y].child.push_back(x);
  }
  int m;
  cout << "请输入乘客个数：" << endl;
  cin >> m;
  cout << "请依次输入乘客名字，目的地和优先级：" << endl;
  for (int i = 0; i < m; ++ i) {
    Person p;
    cin >> p.name >> p.des >> p.pri;
    p.visit = false;
    q.push_back(p);
  }
    sort(q.begin(), q.end(), cmp1);
    vector<Person> temp;
    for (int i = 0; i < m; ++ i) {
      if (q[i].visit == true) continue;
      Person curPerson = q[i];
      curPerson.visit = true;
      Node curNode = node[curPerson.des];
      while (curNode.father != 0) {
        curNode = node[curNode.father];
        if (curNode.child.size() != 0) {
          int t = curNode.child.size();
          for (int j = 0; j < t; ++ j) {
            int curDes = curNode.child[j];
            for (int z = i; z < m; ++ z) {
              if (q[z].des == curDes && q[z].visit == false) {
                q[z].visit = true;
                temp.push_back(q[z]);
              }
            }
          }
        }

      }
      int h = temp.size();
      for (int d = h - 1; d >= 0; -- d) {
        cout << temp[d].name << " " << temp[d].des << endl;
      }
      temp.clear();

    }
    return 0;
  
}