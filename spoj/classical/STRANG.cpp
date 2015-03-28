#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

const int N = 100010;

int n, gap, rank[N], sa[N], tmp[N], lcp[N];
int stack[N], left[N], right[N];
std::string s;

bool cmp(int i, int j) {
    if (rank[i] != rank[j])
        return rank[i] < rank[j];
    i += gap;
    j += gap;
    if (i <= n && j <= n)
        return rank[i] < rank[j];
    return i > j;
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::cin >> s;
    n = s.size();
    s = s + '0';
    for (int i = 1; i <= n; ++i) {
        rank[i] = s[i - 1];
        sa[i] = i;
    }
    for (gap = 1, tmp[1] = 1; ; gap <<= 1) {
        std::sort(sa + 1, sa + n + 1, cmp);
        for (int i = 2; i <= n; ++i) {
            tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
        }
        for (int i = 1; i <= n; ++i) {
            rank[sa[i]] = tmp[i];
        }
        if (tmp[n] == n) break;
    }
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rank[i] == n) continue;
        for (int j = sa[rank[i] + 1]; s[i + k - 1] == s[j + k - 1]; ) {
            ++k;
        }
        lcp[rank[i]] = k;
        if (k) --k;
    }
    long long ans = n;
    lcp[0] = lcp[n] = -1;
    for (int i = 1, sz = 0; i < n; ++i) {
        while (sz > 0 && lcp[stack[sz]] >= lcp[i]) {
            --sz;
        }
        left[i] = stack[sz] + 1;
        stack[++sz] = i;
    }
    stack[0] = n;
    for (int i = n - 1, sz = 0; i >= 1; --i) {
        while (sz > 0 && lcp[stack[sz]] >= lcp[i]) {
            --sz;
        }
        right[i] = stack[sz] - 1;
        stack[++sz] = i;
    }
    for (int i = 1; i < n; ++i) {
        int w = right[i] - left[i] + 2;
        long long v = 1LL * lcp[i] * w;
        if (v > ans) ans = v;
    }
    std::cout << ans;
}