// 第一题：
// 输入：
// 一句c语言的非控制类（不包括if/while等）语句，如a=find(b+c)+d这样的
// 输出：
// 输出函数调用及传入的参数

// 例如：
// 输入：
// a = function(1, 2 + 3, d) + functio() + functi( 1+ b+ d);

// 输出
// function 1 2+3 d
// functio
// functi 1+b+d

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void out (string s, int &i, int len) {
  while (i < len && s[i] != ')') {
    if (s[i] == ',') {
      cout << " ";
      i ++;
      continue;
    }
    else if (s[i] == ' ') {
      i ++;
      continue;
    }
    else {
      while (i < len && s[i] != ',' && s[i] != ')') {
        if (s[i] == ' ') {
          i++;
          continue;
          }
        cout << s[i];
        i ++;
      }
    }
  }
  cout << endl;
  i ++;
  return;
}

int main() {
  string s;
  cout << "请输入一句c++语句：" << endl;
  getline(cin, s);
  int len = s.size();
  bool flagPara = false;
  string tempFunc = "";
  int i = 0;
  while (s[i] != '=') i ++;
  i ++;
  for (i; i < len; ++ i) {
    char ch = s[i];
    if (ch == ' ') continue;
    else if (ch == '(') {
      cout << tempFunc;
      tempFunc.clear();
      cout << " ";
      i ++;
      out(s, i, len);
    }
    else if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')|| (ch <= '9' && ch >= '0') ) tempFunc += ch;
    else tempFunc.clear();
  }
  return 0;

}
