#include <cstdio>
#include <iostream>
using namespace std;
int n1, n2, h1[1005], h2[1005];
void dfs(int k, int f) {  
  if (f == 1) {    
    int t = k % n1;
    int val = h1[t];
    h1[t] = k;
    if (val != -1) {
      dfs(val, 2);
    }    
  } else {    
    int t = k % n2;
    int val = h2[t];
    h2[t] = k;
    if (val != -1) {
      dfs(val, 1);
    }    
  }
}
int main() {
  int m, nCase = 0, a;
  while (cin >> n1 >> n2 >> m) {
    if (n1 == 0 && n2 == 0 && m == 0) break;
    fill(h1, h1 + 1005, -1);
    fill(h2, h2 + 1005, -1);
    for (int i = 0; i < m; ++i) {
      cin >> a;
      dfs(a, 1);
    }
    cout << "Case " << ++nCase << ":\n";
    for (int i = 0; i < n1; ++i)
      if (h1[i] != -1) {
        cout << "Table 1\n";
        for (int i = 0; i < n1; ++i) {
          if (h1[i] != -1) {
            cout << i << ':' << h1[i] << '\n';
          }
        }
        break;
      }
    for (int i = 0; i < n2; ++i)
      if (h2[i] != -1) {   
        cout << "Table 2\n";
        for (int i = 0; i < n2; ++i) {
          if (h2[i] != -1) {
            cout << i << ':' << h2[i] << '\n';
          }
        }
        break;
      }
  }
}