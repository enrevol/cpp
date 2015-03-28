#include <algorithm>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 101010;
const int MAX = 999999;

bool skip[N];
int a[N], L[N], s[N], dp[7][MAX + 1];

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    int tt;
    scanf("%d", &tt);
    for (int tn = 1; tn <= tt; ++tn) {
        int n;
        scanf("%d", &n);
        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            char buf[7];
            scanf("%s", buf);
            int len = strlen(buf);
            int v = 0;
            for (int j = 0; j < len; ++j) {
                buf[j] = buf[j] - '0';
                v = v * 10 + buf[j];
            }
            a[i] = v;
            L[i] = len;
            s[i] = s[i - 1];
            skip[i] = false;
            if (dp[len][v] > 0) {
                skip[i] = true;
                continue;
            }
            int pos = i;
            for (int diff = 1; diff <= 9; ++diff) {
                bool ok = true;
                for (int j = 0; j < len; ++j)
                    if (buf[j] - diff < 0 && 9 < buf[j] + diff) {
                        ok = false;
                        break;
                    }
                if (!ok) {
                    break;
                }
                for (int mask = 0; mask < 1 << len; ++mask) {
                    bool ok = true;
                    int z = 0;
                    for (int j = 0; j < len; ++j) {
                        if ((mask >> j) & 1) {
                            if (buf[j] - diff < 0) {
                                ok = false;
                                break;
                            }
                            z = z * 10 + buf[j] - diff;
                        } else {
                            if (9 < buf[j] + diff) {
                                ok = false;
                                break;
                            }
                            z = z * 10 + buf[j] + diff;
                        }
                    }
                    if (!ok) {
                        continue;
                    }
                    if (dp[len][z] > 0 && !skip[dp[len][z]]) {
                        pos = min(pos, dp[len][z]);
                    }
                }
            }
            dp[len][v] = i;
            if (pos != i) {
                skip[i] = true;
            }
            s[i] = s[i - 1] + !skip[i];
            answer = max(answer, s[pos]);
        }
        for (int i = 1; i <= n; ++i) {
            dp[L[i]][a[i]] = 0;
        }
        printf("Case %d: %d\n", tn, answer);
    }
}