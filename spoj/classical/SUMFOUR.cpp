#include <algorithm>
#include <bitset>
#include <iostream>
#include <unordered_map>
#include <vector>

const int N = 4000;

int a[N], b[N], c[N], d[N];

struct node {
    int val, cnt, next;
} pool[0x1000000];

int avail = 1, head[0x1000000];

int& get(int val) {
    int h = val & 0xFFFFFF;
    int p = 0;    
    for (int i = head[h]; i; i = pool[i].next)
        if (pool[i].val == val) {
            p = i;
            break;
        }
    if (p == 0) {
        pool[p = avail] = { val, 0, head[h] };
        head[h] = avail++;
    }
    return pool[p].cnt;
}

int find(int val) {
    int h = val & 0xFFFFFF;
    int p = 0;    
    for (int i = head[h]; i; i = pool[i].next)
        if (pool[i].val == val) {
            p = i;
            break;
        }
    return pool[p].cnt;
}

int main() {
//    freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            get(a[i] + b[j])++;
    long long ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            ans += find(-(c[i] + d[j]));
    std::cout << ans;
}