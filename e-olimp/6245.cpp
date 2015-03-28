#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define c first
#define r second
#define node first
#define dist second
#define pp pair<int, int>
#define pp2 pair<pp, int>
#define mp make_pair
#define pb push_back
using namespace std;
vector<pp2> v[11][22];
int plateR[] = { 10, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int plateC[] = { 5, 1, 1, 2, 2, 3, 3, 4, 4, 5 };
int main() {
  for (int i = 1; i <= 10; ++i) {
    v[0][0].pb(mp(mp(1, i), 1));
    v[1][i].pb(mp(mp(0, 0), 1));
  }
  for (int i = 1; i <= 5; ++i)
    for (int j = 1; j <= 10; ++j) {
      v[i][j].pb(mp(mp((i + 1), j), 1));
      v[i + 1][j].pb(mp(mp(i, j), 1));
    }
  for (int i = 1; i <= 6; ++i)
    for (int j = 1; j <= 9; ++j) {
      v[i][j].pb(mp(mp(i, j + 1), i));
      v[i][j + 1].pb(mp(mp(i, j), i));
    }
  pp start, des;
  int plate;
  int nCase = 0;
  while (cin >> start.c >> start.r >> des.c >> des.r >> plate) {
    nCase++;
    string ans;
    int cost[11][22];
    memset(cost, 1, sizeof(cost));
    cost[start.c][start.r] = 0;
    int pR = plateR[plate];
    int pC = plateC[plate];
    queue<pp> q;
    q.push(start);
    while (!q.empty()) {
      pp t = q.front();
      q.pop();
      for (int i = 0; i < v[t.c][t.r].size(); ++i) {
        pp2 k = v[t.c][t.r][i];
        if ((t.c == 0 && t.r == 0 && k.node.r == pR) ||
            (k.node.c == pC && t.c == pC) ||
            (k.node.r == pR && t.r == pR)) continue;            
        int tot = cost[t.c][t.r] + k.dist;
        if (tot < cost[k.node.c][k.node.r]) {
          cost[k.node.c][k.node.r] = tot;
          q.push(k.node);
        }
      }
    }
    cout << "Case " << nCase << ": ";
    if (cost[des.c][des.r] >= 1 << 20) cout << "not possible\n";
    else cout << cost[des.c][des.r] << '\n';
  }
}