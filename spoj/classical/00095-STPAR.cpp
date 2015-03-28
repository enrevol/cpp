#include <cstdio>
#include <cstring>
#include <stack>
 
int a[1010];
 
int main() {
  int n;
  while (scanf("%d", &n)) {
    if (n == 0) break;
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    int nxt = 1;
    std::stack<int> s;
    for (int i = 1; i <= n; ++i) {
      if (a[i] == nxt) {
        ++nxt;
      } else {
        while (s.size() && s.top() == nxt) {
          s.pop();
          ++nxt;
        }
        s.push(a[i]);
      }
    }
    while (s.size() && s.top() == nxt) {
      s.pop();
      ++nxt;
    }
    if (nxt != n + 1) {
      puts("no");
    } else {
      puts("yes");
    }
  }
} 