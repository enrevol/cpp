#include <cstring>
#include <iostream>
#include <queue>
#define i first
#define j second
#define pb push_back
#define pp pair<int, int>
#define mp make_pair
typedef long long LL;
using namespace std;
LL a[100005][3];
LL cost[100005][3];
vector<pp> v[3];
int main() {
  v[0].pb(mp(0, 1));
  v[0].pb(mp(1, 0));
  v[0].pb(mp(1, 1));
  v[1].pb(mp(0, 1));
  v[1].pb(mp(1, -1));
  v[1].pb(mp(1, 0));
  v[1].pb(mp(1, 1));
  v[2].pb(mp(1, -1));
  v[2].pb(mp(1, 0));
  int n, nCase = 0;  
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < 3; ++j) {
        cin >> a[i][j];
        cost[i][j] = 1 << 20;
      }
    cost[0][1] = a[0][1];
    queue<pp> q;
    q.push(mp(0, 1));
    while (!q.empty()) {
      pp t = q.front();
      q.pop();
      for (int i = 0; i < v[t.j].size(); ++i) {
        pp k = mp(t.i + v[t.j][i].i, t.j + v[t.j][i].j);
        if (k.i < n) {
          LL tot = cost[t.i][t.j] + a[k.i][k.j];
          if (cost[k.i][k.j] > tot) {
            cost[k.i][k.j] = tot;
            q.push(k);
          }
        }        
      }
    }
    cout << ++nCase << ". " << cost[n - 1][1] << '\n';
  }
}