#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

const int w = 5;
const int mx = 243;
 
char s[30303], t[] = "RGW";

struct ss {
  int l;
  int val[3][3];
  int r[3];
} dp[mx];
int b[10101];
int mat[3][3], p3[w];
int n, k;

int ter_dec(int arr[], int sz) {
  int res = 0;
  for (int i = 0; i < sz; ++i)
    res += p3[i] * arr[i];
  return res;
}

void dec_ter(int n, int arr[]) {
  for (int i = 0; i < w; ++i) {
    arr[i] = n % 3;
    n /= 3;
  }
}

void pre() {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j)
      mat[i][j] = mat[j][i] = ((i + 1) ^ (j + 1)) - 1;
    mat[i][i] = i;
  }
  p3[0] = 1;
  for (int i = 1; i < w; ++i)
    p3[i] = p3[i - 1] * 3;
}

void build() {
  for (int mask = 0; mask < mx; ++mask) {
    int dig[w];
    dec_ter(mask, dig);
    dp[mask].l = dig[0];
    for (int l = 0; l < 3; ++l) {
      int ndig[w];
      ndig[0] = mat[l][dig[0]];
      for (int i = 1; i < w; ++i)
        ndig[i] = ndig[i - 1] = mat[dig[i]][ndig[i - 1]];
      dp[mask].r[l] = ndig[w - 1];
      int val = ter_dec(ndig, w - 1);
      for (int r = 0; r < 3; ++r)
        dp[mask].val[l][r] = val + mat[ndig[w - 1]][r] * p3[w - 1];
    }
  }
}

void input() {
  scanf("%d %d %s", &n, &k, s);
  for (int i = 0; s[i]; ++i) {
    switch (s[i]) {
      case 'R': s[i] = 0; break;
      case 'G': s[i] = 1; break;
      case 'W': s[i] = 2; break;
    }
  }
}

void process() {
  int bf = 1;
  int bt = 0;
  int bc = 0;
  while (bt + w < n - 1) {
    bt += w;
    ++bc;
  }
  int bi = 0;
  for (int i = bf; i < bt; i += w) {
    for (int j = 0; j < w; ++j)
      b[bi] += p3[j] * s[i + j];
    ++bi;
  }
  while (k--) {
    if (bc == 0) {
      for (int i = 1; i < n; ++i)
        s[i] = s[i - 1] = mat[s[i]][s[i - 1]];
      s[0] = s[n - 1] = mat[s[0]][s[n - 1]];
    } else if (bc) {
      int t = dp[b[0]].l;
      int u;
      if (bc == 1) {
        u = dp[b[0]].r[s[0]];
        b[0] = dp[b[0]].val[s[0]][s[bt + 1]];
      } else {
        int t = dp[b[0]].r[s[0]];
        b[0] = dp[b[0]].val[s[0]][dp[b[1]].l];
        for (int i = 1; i < bc - 1; ++i) {
          int k = t;
          t = dp[b[i]].r[k];
          b[i] = dp[b[i]].val[k][dp[b[i + 1]].l];
        }
        u = dp[b[bc - 1]].r[t];
        b[bc - 1] = dp[b[bc - 1]].val[t][s[bt + 1]];
      }      
      s[0] = mat[s[0]][t];
      s[bt + 1] = mat[s[bt + 1]][u];
      for (int i = bt + 2; i < n; ++i)
        s[i - 1] = s[i] = mat[s[i - 1]][s[i]];
      s[0] = s[n - 1] = mat[s[0]][s[n - 1]];
    }
  }
  putchar(t[s[0]]);
  for (int i = 0; i < bc; ++i) {
    for (int j = 0; j < w; ++j) {
      putchar(t[b[i] % 3]);
      b[i] /= 3;
    }
  }
  for (int i = bt + 1; i < n; ++i)
    putchar(t[s[i]]);
}

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  pre();
  build();
  input();
  process();
}