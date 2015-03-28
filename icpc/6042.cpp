#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::vector<int> sacred;
p2 tw[55];
int cost[505], cost_t[505];
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n, b_h, b_w;
    scanf("%d %d %d", &n, &b_h, &b_w);
    for (int i = 1; i <= n; ++i)
      scanf("%d %d", &tw[i].first, &tw[i].second);
    std::sort(tw + 1, tw + n + 1);
    tw[n + 1].first = 501;
    int max_h = tw[1].second;
    for (int i = 2; i <= n; ++i)
      if (tw[i].second > max_h) max_h = tw[i].second;
    int ans = -1;
    if (max_h <= b_h) {
      ans = 0;
    } else {
      sacred.clear();
      sacred.push_back(0);
      for (int i = 1; i <= n; ++i)
        if (tw[i].second == max_h) sacred.push_back(i);
      sacred.push_back(n + 1);
      for (int i = 1; i < sacred.size() - 1; ++i) {
        int idx = sacred[i];
        int l_idx = sacred[i - 1];
        int l_bound = tw[l_idx].first;
        int t_idx = l_idx + 1;
        for (int j = t_idx; j < idx; ++j)
          if (tw[j].second <= b_h) t_idx = j;
        if (t_idx < idx && tw[t_idx].second <= b_h) {
          int f = 1;
          for (int i = t_idx; i < idx && f; ++i)
            if (tw[i + 1].second - tw[i].second > b_h) f = 0;
          if (f) {
            memset(cost, 0, sizeof(cost));
            int r_bound = tw[idx].first - (idx - t_idx);
            for (int i = t_idx; i < idx; ++i) {
              memset(cost_t, 1, sizeof(cost_t));
              for (int j = l_bound; j <= r_bound; ++j) {
                int l_pos = std::max(l_bound, j - b_w);
                int r_pos = std::min(r_bound, j + b_w);
                cost_t[j] = abs(tw[i].first - j) * tw[i].second + *std::min_element(cost + l_pos, cost + r_pos + 1);
              }
              std::copy(cost_t + l_bound, cost_t + tw[idx].first, cost + l_bound);
              ++r_bound;
              ++l_bound;
            }
            int val = *std::min_element(cost + tw[idx].first - b_w, cost + tw[idx].first);
            if (ans == -1 || val < ans) ans = val;
          }
        }
      }
      for (int i = 1; i < sacred.size() - 1; ++i) {
        int idx = sacred[i];
        int r_idx = sacred[i + 1];
        int r_bound = tw[r_idx].first;
        int t_idx = r_idx - 1;
        for (int j = t_idx; j > idx; --j)
          if (tw[j].second <= b_h) t_idx = j;
        if (t_idx > idx && tw[t_idx].second <= b_h) {
          int f = 1;
          for (int i = t_idx; i > idx && f; --i)
            if (tw[i - 1].second - tw[i].second > b_h) f = 0;
          if (f) {
            memset(cost, 0, sizeof(cost));
            int l_bound = tw[idx].first + (t_idx - idx);
            for (int i = t_idx; i > idx; --i) {
              memset(cost_t, 1, sizeof(cost_t));
              for (int j = r_bound; j >= l_bound; --j) {
                int l_pos = std::max(l_bound, j - b_w);
                int r_pos = std::min(r_bound, j + b_w);
                cost_t[j] = abs(tw[i].first - j) * tw[i].second + *std::min_element(cost + l_pos, cost + r_pos + 1);
              }
              std::copy(cost_t + tw[idx].first + 1, cost_t + r_bound + 1, cost + tw[idx].first + 1);
              --r_bound;
              --l_bound;
            }
            int val = *std::min_element(cost + tw[idx].first + 1, cost + tw[idx].first + b_w + 1);
            if (ans == -1 || val < ans) ans = val;
          }
        }
      }
    }
    printf("Case #%d: %d\n", ++n_case, ans);
  }
}