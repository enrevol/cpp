#include <cstdio>
#include <cstring>
 
long long fw[2][101010];
int n;
 
void internal_update(const int& num, int idx, const long long& val) {
  while (idx <= n) {
    fw[num][idx] += val;
    idx += idx & -idx;
  }  
}
 
void update(const int& left, const int& right, const long long& val) {
  internal_update(0, left, val);
  internal_update(0, right + 1, -val);
  internal_update(1, left, val * (left - 1));
  internal_update(1, right + 1, -val * right);
}
 
long long internal_get(const int& num, int idx) {
  long long res = 0;
  while (idx >= 1) {
    res += fw[num][idx];
    idx -= idx & -idx;
  }
  return res;
}
 
long long get(const int& idx) {
  return idx * internal_get(0, idx) - internal_get(1, idx);
}
 
long long get(const int& left, const int& right) {
  return get(right) - get(left - 1);
}
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int c;
    scanf("%d %d", &n, &c);
    memset(fw, 0, sizeof(fw));
    int t, l, r, val;
    while (c--) {
      scanf("%d %d %d", &t, &l, &r);
      if (t == 0) {
        scanf("%d", &val);
        update(l, r, val);
      } else {
        printf("%lld\n", get(l, r));
      }
    }
  }
} 