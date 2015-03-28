#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr int N = 1010;
constexpr int DX[] = { 0, -1, 0, 1 };
constexpr int DY[] = { 1, 0, -1, 0 };

char s[N][N];
bool visited[N][N];
int q[N * N];

int main() {
//    freopen("in", "r", stdin);
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
    }
    int answer = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (!visited[i][j]) {
                visited[i][j] = true;
                if (s[i][j] != 'X') {
                    continue;
                }
                int cnt = 0;
                int min_i = i, max_i = i;
                int min_j = j, max_j = j;
                int tail = 0;
                q[tail++] = (i << 10) | j;
                for (int head = 0; head < tail; ++head) {
                    ++cnt;
                    int x = q[head] >> 10;
                    int y = q[head] & 1023;
                    for (int d = 0; d < 4; ++d) {
                        int xx = x + DX[d];
                        int yy = y + DY[d];
                        if (!visited[xx][yy]) {
                            visited[xx][yy] = true;
                            if (s[xx][yy] != 'X') {
                                continue;
                            }
                            min_i = min(min_i, xx);
                            max_i = max(max_i, xx);
                            min_j = min(min_j, yy);
                            max_j = max(max_j, yy);
                            q[tail++] = (xx << 10) | yy;
                        }
                    }
                }
                if ((max_i - min_i + 1) * (max_j - min_j + 1) == cnt) {
                    ++answer;
                }
            }
    printf("%d", answer);
}
