#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1010;

int a[N], sa[N];
int b[N], sb[N];
long long dp[N][N];

struct line {
    int a;
    long long b;
    
    line(int a = 0, long long b = 0) : a(a), b(b) { }
    
    long long evaluate(int x) const {
        return (long long)a * x + b;
    }
};

bool bad(const line& L1, const line& L2, const line& L3) {
    return (L2.b - L1.b) * (L1.a - L3.a) > (L3.b - L1.b) * (L1.a - L2.a);
}

struct convex_hull {
    int ind, sz;
    line lines[N];
    
    void clear() {
        sz = ind = 0;
    }
    
    void add(const line& L) {        
        while (sz > 0 && lines[sz - 1].a == L.a && lines[sz - 1].b < L.b) {
            --sz;
        }
        if (sz == 0 || lines[sz - 1].a < L.a) {
            while (sz > 1 && bad(lines[sz - 2], lines[sz - 1], L)) {
                --sz;
            }
            lines[sz++] = L;
        }
    }
    
    long long query(int x) {
        if (ind >= sz) {
            ind = sz - 1;
        }
        while (ind + 1 < sz && lines[ind + 1].b - lines[ind].b >= (long long)(lines[ind].a - lines[ind + 1].a) * x) {
            ++ind;
        }
        return lines[ind].evaluate(x);
    }
} row, col[N];

long long sqr(int x) {
    return (long long)x * x;
}

int main() {
//    freopen("in", "r", stdin);
//    freopen("out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sa[i] = sa[i - 1] + a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        sb[i] = sb[i - 1] + b[i];
    }
    long long answer = 0;
    for (int i = 1; i <= n; ++i) {
        row.clear();
        for (int j = 1; j <= n; ++j) {
            long long v = -sqr(sa[i - 1]) - sqr(sb[j - 1]);
            if (i > 1 && j > 1) {
                col[j - 1].add(line(2 * sa[i - 1], -sqr(sa[i - 1]) + dp[i - 1][j - 1]));
                row.add(line(2 * sb[j - 1], -sqr(sb[j - 1]) + dp[i - 1][j - 1]));
                v = max(v, col[j - 1].query(sa[i - 1]) - sqr(sa[i - 1]));
                v = max(v, row.query(sb[j - 1]) - sqr(sb[j - 1]));
            }
            dp[i][j] = a[i] * b[j] + v;
            answer = max(answer, dp[i][j] - sqr(sa[n] - sa[i]) - sqr(sb[n] - sb[j]));
        }
    }
    cout << answer;
}
