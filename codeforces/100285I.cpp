#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
int time[100005];
int weight[100005];
int main() {
  //freopen("input.txt", "r", stdin);
  int N, M, K, t;
  scanf("%d %d %d", &N, &M, &K);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &t);
    weight[i] = weight[i - 1] + t;
  }
  weight[N + 1] = 1234567890;
  for (int i = 1; i <= M; ++i) {
    scanf("%d", &time[i]);
  }
  time[0] = 0;
  time[M + 1] = 1234567890;
  int ans;
  int hold = 0;
  for (int i = 1; i <= M + 1; ++i) {
    int delta = time[i] - time[i - 1] - 1;
    if (delta + hold >= N) {
      ans = time[i - 1] + N - hold;
      break;
    } else {
      int tot = delta + hold;
      hold = lower_bound(weight, weight + N + 1, weight[tot] - K) - weight - 1;
      hold = max(0, hold);
    }
  }
  cout << ans;
}