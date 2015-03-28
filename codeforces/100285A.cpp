#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
#define pLL pair<LL, LL>
#define X first
#define Y second
typedef long long LL;
using namespace std;
pLL Lp[100005], Rp[100005];
vector<LL> Cp[100005];
struct seg {
  LL A, B, C;
  pLL start, end;
  void create(const pLL& a, const pLL& b) {
    start = a;
    end = b;
    A = b.Y - a.Y;
    B = a.X - b.X;
    C = A * a.X + B * a.Y;
    LL g = __gcd(A, __gcd(B, C));
    A /= g;
    B /= g;
    C /= g;
  }
  double dist(const pLL& a) {
    double x = Xpos(a.Y);
    return abs(x - a.X);
  }
  double Xpos(const LL& Ypos) {
    return (C - B * Ypos) * 1.f / A;
  }
};
int main() {
  //freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(0);
  int N, M, Q, cnt = 0, f = 0;
  LL x, y;
  cin >> N;
  for (int i = 1; i <= N; ++i) cin >> Lp[i].X >> Lp[i].Y;
  cin >> M;
  for (int i = 1; i <= M; ++i) cin >> Rp[i].X >> Rp[i].Y;
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> x >> y;
    if (y < Lp[1].Y) continue;
    if (y > Lp[N].Y) continue;
    if (cnt == 0 || y != Cp[cnt][0]) {
      cnt++;
      Cp[cnt].push_back(y);
      Cp[cnt].push_back(x);      
    } else {
      Cp[cnt].push_back(x);
    }
  }
  int Li = 2, Ri = 2, Ci = 1, CLi, CRi;
  seg Ls, Rs;
  Ls.create(Lp[Li - 1], Lp[Li]);
  Rs.create(Rp[Ri - 1], Rp[Ri]);
  double ans = Rp[1].X - Lp[1].X;
  LL t;
  double dL, dR, d, Lx, Rx;
  while (Li <= N) {
    t = Ls.end.Y;
    if (Ri <= M) t = min(t, Rs.end.Y);
    if (Ci <= cnt) t = min(t, Cp[Ci][0]);
    if (Ci <= cnt && t == Cp[Ci][0]) {
      Lx = Ls.Xpos(Cp[Ci][0]);
      Rx = Rs.Xpos(Cp[Ci][0]);
      sort(Cp[Ci].begin() + 1, Cp[Ci].end());
      CLi = lower_bound(Cp[Ci].begin() + 1, Cp[Ci].end(), Lx) - Cp[Ci].begin();
      CRi = upper_bound(Cp[Ci].begin() + 1, Cp[Ci].end(), Rx) - Cp[Ci].begin() - 1;
      if (CLi <= CRi) {
        d = max(Cp[Ci][CLi] - Lx, Rx - Cp[Ci][CRi]);
        for (int i = CLi + 1; i <= CRi; ++i)
          d = max(d, double(Cp[Ci][i] - Cp[Ci][i - 1]));
        ans = min(ans, d);
      }
      Ci++;      
    } else if (Ri <= M && t == Rs.end.Y) {
      d = Ls.dist(Rs.end);
      ans = min(ans, d);      
      Ri++;
      if (Ri <= M) Rs.create(Rp[Ri - 1], Rp[Ri]);
    } else if (t == Ls.end.Y) {
      d = Rs.dist(Ls.end);
      ans = min(ans, d);
      Li++;
      if (Li <= N) Ls.create(Lp[Li - 1], Lp[Li]);
    } 
  }
  cout << fixed << setprecision(8) << ans;
}