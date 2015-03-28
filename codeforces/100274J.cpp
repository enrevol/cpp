#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> v[100005];
int n, was[100005];
void bfs(int root, int& res) {
  fill(was, was + n, 0);
  queue<int> q;
  q.push(root);
  was[root] = 1;
  while (!q.empty()) {
    int t = q.front();
    res = t;
    q.pop();
    for (int i = 0; i < v[t].size(); ++i) {
      if (!was[v[t][i]]) {
        was[v[t][i]] = was[t] + 1;
        q.push(v[t][i]);
      }
    }
  }
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int a, b;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) v[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      scanf("%d %d", &a, &b);
      v[a].push_back(b);
      v[b].push_back(a);
    }
    int k, ans;
    bfs(0, k);
    bfs(k, ans);
    printf("%d\n", was[ans] / 2);
  }
}