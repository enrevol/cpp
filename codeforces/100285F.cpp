#include <algorithm>
#include <cstdio>
#include <iostream>
typedef long long LL;
using namespace std;
int weight[100005];
int main() {
  //freopen("output.txt", "w", stdout);
  int N, K, P;
  scanf("%d %d %d", &N, &K, &P);
  int current = 0;
  for (int i = 1; i <= N - K; ++i) {
    weight[i] = 1;
  }
  int val = 1, ok;
  for (int i = N - K + 1; i <= N; ++i) {
    ok = 0;
    while (!ok) {
      int pos = lower_bound(weight + 1, weight + i, val) - weight;
      if (pos == i || ((pos - 1) * 100 / (i - 1) >= P)) {
        ok = 1;
        weight[i] = val;
      } else {
        val++;
      }
    }
  }
  LL sum = 0;
  for (int i = 1; i <= N; ++i) {
    sum += weight[i];
  }
  cout << sum << '\n';
  for (int i = 1; i < N; ++i) {
    cout << weight[i] << ' ';
  }
  cout << weight[N];
}