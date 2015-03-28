#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;  
int pos[100005];
struct ss {  
  int pos;
  string flag;
} ant[100005];
int func(const ss& a, const ss& b) {  
  return a.pos > b.pos;
}      
int main() {
  int L, N, time, left, right, cnt, ans1, ans2;
  while (cin >> L >> N) {
    right = L;
    left = 0;
    for (int i = 0; i < N; ++i) cin >> ant[i].pos >> ant[i].flag;
    sort(ant, ant + N, func);
    for (int i = N - 1; i >=0; --i) {
      if (ant[i].flag[0] == 'R') {
        right = ant[i].pos;
        break;
      }
    }
    for (int i = 0; i < N; ++i) {
      if (ant[i].flag[0] == 'L') {
        left = ant[i].pos;
        break;
      }
    }
    time = max(L - right, left);
    for (int i = 0; i < N; ++i) {
      if (ant[i].flag[0] == 'R') {
        pos[i] = ant[i].pos + time;
      } else {
        pos[i] = ant[i].pos - time;
      }
    }
    sort(pos, pos + N);
    cnt = 0;
    for (int i = 0; i < N; ++i) {
      if (pos[i] == 0 || pos[i] == L) {
        cnt++;
        if (cnt == 1) ans1 = ant[N - 1 - i].pos;
        if (cnt == 2) ans2 = ant[N - 1 - i].pos;
      }
    }
    cout << "The last ant will fall down in " << time << " seconds - started at " << ans1;
    if (cnt == 2) cout << " and " << ans2;
    cout << ".\n";
  }
}