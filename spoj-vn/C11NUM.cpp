#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
typedef unsigned long long uint64_t;

uint64_t power[20];

uint64_t dfs(uint64_t n, int p, int s, bool l) {
    if (p < s) {
        return n == 0;
    }
    uint64_t coeff = power[p] + power[s];
    if (!l) {
        if (coeff * 36 < n)
            return 0;
    }
    uint64_t result = 0;
    if (p > s) {
        for (int j = 0; j <= 18; ++j) {
            if (n >= coeff * j) {
                uint64_t v = dfs(n - coeff * j, p - 1, s + 1, false);
                if (v > 0) {
                    int f = max(int(l), j - 9);
                    int t = min(9, j);
                    result += v * (t - f + 1);
                }
            }
        }
    } else {
        for (int j = 0; j <= 9; ++j) {
            if (n >= coeff * j) {
                uint64_t v = dfs(n - coeff * j, p - 1, s + 1, false);
                if (v > 0) {
                    ++result;
                }
            }
        }
    }
    return result;
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    power[0] = 1;
    for (int i = 1; i < 20; ++i) {
        power[i] = power[i - 1] * 10;
    }
    int tt;
    cin >> tt;
    while (tt--) {
        uint64_t n;
        cin >> n;
        int d = 0;
        for (uint64_t tmp = n; tmp; tmp /= 10, ++d);
        uint64_t answer = 0;
        for (int i = max(1, d - 1); i <= d; ++i) {
            answer += dfs(n, i - 1, 0, true);
        }
        cout << answer << '\n';
    }
}
