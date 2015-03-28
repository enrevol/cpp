#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int time1[555], time2[555], cnt1, cnt2, match[555];
bool graph[555][555];
int bpm(int index, bool seen[], int match[]) {
  for (int i = 1; i <= cnt2; ++i) {
    if (graph[index][i] && !seen[i]) {
      seen[i] = 1;
      if (match[i] < 0 || bpm(match[i], seen, match)) {
        match[i] = index;
        return 1;
      }
    }
  }
  return 0;
}
int maxBPM() {
  fill(match, match + 555, -1);
  int res = 0;
  for (int i = 1; i <= cnt1; ++i) {
    bool seen[555];
    fill(seen, seen + 555, 0);
    if (bpm(i, seen, match)) res++;
  }
  return res;
}
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int a, b, n, t, d;
  cin >> a >> b >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> t >> d;
    if (d) {
      cnt2++;
      time2[cnt2] = t;      
    } else {
      cnt1++;
      time1[cnt1] = t;      
    }
  }
  for (int i = 1; i <= cnt1; ++i) {
    for (int j = 1; j <= cnt2; ++j) {
      d = time2[j] - time1[i];
      if (d > 0 && (d <= b || d >= a)) {
        graph[i][j] = 1;
      }
    }
  }
  int num = maxBPM();
  if (num == cnt1) {
    cout << "No reason\n";
    for (int i = 1; i <= cnt1; ++i) {
      cout << time1[match[i]] << ' ' << time2[i] << '\n';
    }    
  } else {
    cout << "Liar";
  }
}