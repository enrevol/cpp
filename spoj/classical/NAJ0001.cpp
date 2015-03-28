#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int N = 101010;
const int MAX = 1000;

struct query {
    int id, f, t;
    query(int id, int f, int t) : id(id), f(f), t(t) { }
};

bool sieve[MAX + 11];
int p[200];
vector<int> pos[MAX + 1];
vector<long long> sum[MAX + 1];

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int pn = 0;
    for (int i = 2; i <= MAX + 10; ++i)
        if (!sieve[i]) {
            p[pn++] = i;
            for (int j = i * i; j <= MAX + 10; j += i) {
                sieve[j] = true;
            }
        }
    int tt;
    cin >> tt;
    for (int tn = 1; tn <= tt; ++tn) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= MAX; ++i) {
            pos[i].clear();
            pos[i].push_back(0);
            sum[i].clear();
            sum[i].push_back(0);
        }
        for (int i = 1; i <= n; ++i) {
            int a;
            cin >> a;
            vector<int> factors, powers;
            int tmp = a;
            for (int j = 0; p[j] * p[j] <= tmp; ++j)
                if (tmp % p[j] == 0) {
                    factors.push_back(p[j]);
                    int cnt = 0;
                    while (tmp % p[j] == 0) {
                        tmp /= p[j];
                        ++cnt;
                    }
                    powers.push_back(cnt);
                }
            if (tmp > 1) {
                factors.push_back(tmp);
                powers.push_back(1);
            }
            function<void(int, int)> dfs = [&factors, &powers, &dfs, a, i] (int prod, int k) {
                if (prod > MAX) {
                    return;
                }
                if (k == int(factors.size())) {
                    pos[prod].push_back(i);
                    sum[prod].push_back(sum[prod].back() + a);
                    return;
                }
                for (int j = 0; j <= powers[k]; ++j) {
                    dfs(prod, k + 1);
                    prod = prod * factors[k];
                }
            };
            dfs(1, 0);
        }
        cout << "Case #" << tn << '\n';
        for (int i = 1; i <= m; ++i) {
            int v, f, t;
            cin >> v >> f >> t;
            int pf = lower_bound(pos[v].begin(), pos[v].end(), f) - pos[v].begin() - 1;
            int pt = upper_bound(pos[v].begin(), pos[v].end(), t) - pos[v].begin() - 1;
            long long answer = sum[v][pt] - sum[v][pf];
            cout << answer << '\n';
        }
        cout << '\n';
    }
}