#include <algorithm>
#include <cstdio>
#include <iostream>
#define x first
#define y second
#define pdd pair<double, double>
#define MAX 50005
typedef long long LL;
using namespace std;
pdd p[MAX];
double s[MAX];
int n;
int nxt(int k) {
  if (k < n) return k + 1;
  return 1;
}
int main() {
  int q, a, b;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf %lf", &p[i].x, &p[i].y);
  }
  for (int i = 1; i <= n; ++i) {
    s[i] = s[i - 1] - p[i].x * p[nxt(i)].y + p[i].y * p[nxt(i)].x;
  }
  double area = s[n];
  double ans;
  for (int i = 0; i < q; ++i) {
    scanf("%d %d", &a, &b);
    if (a > b) swap(a, b);
    ans = s[b] - s[a] - p[b + 1].x * p[a + 1].y + p[b + 1].y * p[a + 1].x;
    ans = min(ans, area - ans);
    printf("%.1lf\n", ans / 2);
  }
} 