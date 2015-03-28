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

constexpr int N = 100010;

bool sieve[N];
int p[N], cnt[N];

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 2; i * i < N; ++i)
        if (!sieve[i])
            for (int j = i * i; j < N; j += i)
                sieve[j] = true;
    int pn = 0;
    for (int i = 2; i < N; ++i)
        if (!sieve[i])
            p[pn++] = i;
    for (int i = 1; i < N; ++i) {
        int phi = i;
        int tmp = i;
        for (int j = 0; p[j] * p[j] <= tmp; ++j)
            if (tmp % p[j] == 0) {
                phi = (long long)phi * (p[j] - 1) / p[j];
                while (tmp % p[j] == 0) {
                    tmp /= p[j];
                }
            }
        if (tmp > 1) {
            phi = (long long)phi * (tmp - 1) / tmp;
        }
        cnt[i] = cnt[i - 1] + i - phi;
    }
    int tt;
    cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        int n;
        cin >> n;
        cout << "Case " << tn << ": " << cnt[n] << '\n';
    }
}