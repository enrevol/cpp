#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
 
int ff(int n) {
  std::stack<int> st;
  while (n) {
    st.push(n % 10);
    n /= 10;    
  }
  int res = 0, k = 1;
  while (!st.empty()) {
    res += k * st.top();
    st.pop();
    k *= 10;
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int a, b;
  scanf("%d %d", &a, &b);
  int aa = ff(a);
  int bb = ff(b);
  printf("%d", aa > bb ? aa : bb);
} 