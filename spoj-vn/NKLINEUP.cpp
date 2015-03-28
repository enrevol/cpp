#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int h[50505], block_sz;
int a_max[7272][15], b_max[7272][11][5];
int a_min[7272][15], b_min[7272][11][5];
 
int query(const int& l, const int& r) {
  int block_idx_l = (l - 1) / block_sz + 1;
  int block_idx_r = (r - 1) / block_sz + 1;
  int block_start_pos_l = (block_idx_l - 1) * block_sz;
  int block_start_pos_r = (block_idx_r - 1) * block_sz;
  int pos_l = l - block_start_pos_l;
  int pos_r = r - block_start_pos_r;
  if (block_idx_l == block_idx_r) {
    int k = std::__lg(r - l + 1);
    int val_max = std::max(b_max[block_idx_l][pos_l][k], b_max[block_idx_l][pos_r - (1 << k) + 1][k]);
    int val_min = std::min(b_min[block_idx_l][pos_l][k], b_min[block_idx_l][pos_r - (1 << k) + 1][k]);    
    return val_max - val_min;
  } else {
    int k_l = std::__lg(block_sz - pos_l + 1);
    int k_r = std::__lg(pos_r);
    int val_max = std::max(b_max[block_idx_l][pos_l][k_l], b_max[block_idx_l][block_sz - (1 << k_l) + 1][k_l]);
    val_max = std::max(val_max, b_max[block_idx_r][1][k_r]);
    val_max = std::max(val_max, b_max[block_idx_r][pos_r - (1 << k_r) + 1][k_r]);
    int val_min = std::min(b_min[block_idx_r][1][k_r], b_min[block_idx_r][pos_r - (1 << k_r) + 1][k_r]);
    val_min = std::min(val_min, b_min[block_idx_l][pos_l][k_l]);
    val_min = std::min(val_min, b_min[block_idx_l][block_sz - (1 << k_l) + 1][k_l]);
    int d = (block_idx_r - 1) - (block_idx_l + 1) + 1;
    if (d) {
      int k_m = std::__lg(d);
      val_max = std::max(val_max, a_max[block_idx_l + 1][k_m]);
      val_max = std::max(val_max, a_max[block_idx_r - 1 - (1 << k_m) + 1][k_m]);
      val_min = std::min(val_min, a_min[block_idx_l + 1][k_m]);
      val_min = std::min(val_min, a_min[block_idx_r - 1 - (1 << k_m) + 1][k_m]);
    }
    return val_max - val_min;
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, q;
  scanf("%d %d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", h + i);
  block_sz = std::__lg(n) >> 1;
  int pos = 0, block_cnt = 0;
  for (int i = 1; pos < n; ++i, pos += block_sz) {
    ++block_cnt;
    a_max[i][0] = 0;
    a_min[i][0] = 1010101;
    for (int ii = 1; ii <= block_sz; ++ii) {
      b_max[i][ii][0] = h[pos + ii];
      b_min[i][ii][0] = h[pos + ii];
      a_max[i][0] = std::max(a_max[i][0], h[pos + ii]);
      a_min[i][0] = std::min(a_min[i][0], h[pos + ii]);
    }
    for (int jj = 1; 1 << jj <= block_sz; ++jj)
      for (int ii = 1; ii + (1 << jj) - 1 <= block_sz; ++ii) {
        b_max[i][ii][jj] = std::max(b_max[i][ii][jj - 1], b_max[i][ii + (1 << (jj - 1))][jj - 1]);
        b_min[i][ii][jj] = std::min(b_min[i][ii][jj - 1], b_min[i][ii + (1 << (jj - 1))][jj - 1]);
      }
  }
  for (int j = 1; 1 << j <= block_cnt; ++j)
    for (int i = 1; i + (1 << j) - 1 <= block_cnt; ++i) {
      a_max[i][j] = std::max(a_max[i][j - 1], a_max[i + (1 << (j - 1))][j - 1]);
      a_min[i][j] = std::min(a_min[i][j - 1], a_min[i + (1 << (j - 1))][j - 1]);
    }    
  int l, r;
  while (q--) {
    scanf("%d %d", &l, &r);
    printf("%d\n", query(l, r));
  }
}