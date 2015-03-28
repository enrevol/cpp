#include <algorithm>
#include <cstdio>
#include <iostream>
typedef long long LL;
using namespace std;
int main() {
  LL M, P, L, E, R, S, N;
  while (cin >> M >> P >> L >> E >> R >> S >> N) {
    LL t;
    for (int i = 0; i < N; ++i) {
      t = M * E;
      M = P / S;
      P = L / R;
      L = t;
    }
    cout << M << '\n';
  }
}