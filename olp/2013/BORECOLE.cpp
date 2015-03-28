#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
set<int> st[33333];
int h[1000005];
int main() {
  freopen("BORECOLE.INP", "r", stdin);
  freopen("BORECOLE.OUT", "w", stdout);
  int n, r, m, total;
  scanf("%d %d %d", &n, &r, &m);
  total = n;
  int hmin = 34567, hmax = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", h + i);
    st[h[i]].insert(i);
    hmin = min(hmin, h[i]);
    hmax = max(hmax, h[i]);
  }
  int left, right, pos;
  for (int i = 0; i < m && total > 0; ++i) {
    while (!st[hmin].size()) hmin++;
    pos = *st[hmin].begin();
    left = max(pos - r, 0);
    right = min(pos + r, n - 1);
    for (int j = left; j <= right; ++j) {
      if (h[j] > 0) {
        st[h[j]].erase(st[h[j]].begin());
        h[j]++;        
        st[h[j]].insert(j);
        hmax = max(hmax, h[j]);
      }
    }
    while (!st[hmax].size()) hmax--;
    pos = *st[hmax].begin();
    left = max(pos - r, 0);
    right = min(pos + r, n - 1);
    for (int j = left; j <= right; ++j) {
      if (h[j] > 0) {
        st[h[j]].erase(st[h[j]].begin());
        h[j] = 0;
        total--;
      }
    }
  }  
  if (total > 0) {
    while (!st[hmax].size()) hmax--;
    printf("%d", hmax);
  } else {    
    printf("0");
  }
}