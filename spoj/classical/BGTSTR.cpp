#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr int N = 50010;
constexpr int MOD = 1e9 + 7;
constexpr int BASE = 31;

char s[N];
int h[N];
int power[N];

int get_hash(int f, int t) {
    return ((h[t] - (long long)h[f - 1] * power[t - f + 1]) % MOD + MOD) % MOD;
}

int main() {
//    freopen("in", "r", stdin);
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
    int tt;
    scanf("%d", &tt);
    power[0] = 1;
    for (int i = 1; i < N; ++i) {
        power[i] = (long long)power[i - 1] * BASE % MOD;
    }
    while (tt--) {
        int k;
        scanf("%s %d", s + 1, &k);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) {
            h[i] = ((long long)h[i - 1] * BASE + s[i]) % MOD;
        }
        int answer = 0;
        int rightmost = 0;
        int low = 1;
        int high = n;
        while (low <= high) {
            int mid = (low + high) / 2;
            unordered_map<int, int> cnt;
            for (int i = 1; i + mid - 1 <= n; ++i) {
                ++cnt[get_hash(i, i + mid - 1)];
            }
            bool ok = false;
            int pos = 0;
            for (int i = n - mid + 1; i >= 1; --i) {
                if (cnt[get_hash(i, i + mid - 1)] >= k) {
                    ok = true;
                    pos = i;
                    break;
                }
            }
            if (ok) {
                answer = mid;
                rightmost = pos;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        if (answer == 0) {
            puts("HATE");
        } else {
            printf("%d %d\n", answer, rightmost);
        }
    }
}