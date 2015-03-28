#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

const int N = 1234;
const int DX[] = { 0, -1, 0, 1 };
const int DY[] = { 1, 0, -1, 0 };

char s[N][N];
int id[N][N], dp[N * N];
int q[N * N];

void bfs(int x, int y, int& tail) {
    int tail2 = tail;
    q[tail2++] = (x << 16) | y;
    for (int head = tail; head < tail2; ++head) {
        int x = q[head] >> 16;
        int y = q[head] & 32767;
        for (int d = 0; d < 4; ++d) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            if (s[x][y] == s[nx][ny])
                if (id[nx][ny] == 0) {
                    id[nx][ny] = id[x][y];
                    q[tail2++] = nx << 16 | ny;
                }
        }
    }
    tail = tail2;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int tt;
    scanf("%d", &tt);
    while (tt--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i] + 1);
        }
        std::memcpy(s[n + 1], s[0], sizeof(s[0]));
        std::memset(id, 0, sizeof(id));
        int ccs = 0;
        id[1][1] = ++ccs;
        dp[ccs] = 0;
        int tail = 0;
        bfs(1, 1, tail);
        for (int head = 0; head < tail; ++head) {
            int x = q[head] >> 16;
            int y = q[head] & 32767;
            for (int d = 0; d < 4; ++d) {
                int nx = x + DX[d];
                int ny = y + DY[d];
                if (1 <= nx && nx <= n)
                    if (1 <= ny && ny <= m)
                        if (s[nx][ny] != s[x][y])
                            if (id[nx][ny] == 0) {
                                id[nx][ny] = ++ccs;
                                dp[id[nx][ny]] = dp[id[x][y]] + 1;
                                bfs(nx, ny, tail);
                            }
            }
        }        
        printf("%d\n", dp[id[n][m]]);
    }
}