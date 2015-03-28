#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
vector<int> v[22];
int n;
int dfs(int index, vector<int> cover) {
  cover[index] = 1;
  for (int i = 0; i < v[index].size(); ++i) {
    cover[v[index][i]] = 1;
  }
  int sum = 0;
  for (int i = 1; i <= n; ++i) sum += cover[i];
  if (sum == n) return 1;
  int res = 22;
  for (int i = index + 1; i <= n; ++i) {
    res = min(res, dfs(i, cover) + 1);
  }
  return res;
}
int main() {
  //freopen("input.txt", "r", stdin);
  int T;
  cin >> T;
  while (T--) {
    int k, t;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      v[i].clear();
      cin >> k;
      for (int j = 0; j < k; ++j) {
        cin >> t;
        v[i].push_back(t);
      }
    }
    vector<int> cover(22, 0);
    int ans = 22;
    for (int i = 1; i <= n; ++i) {
      ans = min(ans, dfs(i, cover));
    }
    cout << ans << '\n';
  }
}