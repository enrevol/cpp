#include <cstdio>
#include <cstring>
 
char s[10];
int g[1212][1212], fw[1212][1212], n;
 
int get(const int& x, const int& y) {
  int res = 0;
  for (int i = x; i >= 1; i -= i & -i)
    for (int j = y; j >= 1; j -= j & -j)
      res += fw[i][j];
  return res;
}
 
int query(const int& x_1, const int& y_1, const int& x_2, const int& y_2) {
  return get(x_2, y_2) + get(x_1 - 1, y_1 - 1) - get(x_1 - 1, y_2) - get(x_2, y_1 - 1);
}
 
int set(const int& x, const int& y, const int& val) {
  for (int i = x; i <= n; i += i & -i)
    for (int j = y; j <= n; j += j & -j)
      fw[i][j] += val;
}
 
int update(const int& x, const int& y, const int& val) {
  set(x, y, -g[x][y]);
  set(x, y, val);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(fw, 0, sizeof(fw));
    memset(g, 0, sizeof(g));
    scanf("%d", &n);
    while (scanf("%s", s) == 1) {
      if (!strcmp(s, "END")) {
        break;
      } else if (!strcmp(s, "SET")) {
        int x, y, val;        
        scanf("%d %d %d", &x, &y, &val);
        update(x + 1, y + 1, val);
        g[x + 1][y + 1] = val;
      } else {
        int x_1, y_1, x_2, y_2;
        scanf("%d %d %d %d", &x_1, &y_1, &x_2, &y_2);
        printf("%d\n", query(x_1 + 1, y_1 + 1, x_2 + 1, y_2 + 1));
      }
    }
  }
} 