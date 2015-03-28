#include <algorithm>
#include <cstdio>
 
using namespace std;
 
const int MAXN = 111111, MAXD = 18;
 
int a[MAXN], b[MAXN], d[MAXD][MAXN], s[MAXD][MAXN];
 
bool cmp(int x, int y) {
    return b[x] < b[y];
}
 
void build(int h, int f, int t) {
    if (f == t)
        return;
    int mid = f + t >> 1, c = 0;
    for (int i = f; i <= t; ++i)
        if (d[h][i] <= mid) {
            d[h + 1][f + c] = d[h][i];
            s[h][i] = ++c;
        }
        else {
            d[h + 1][mid + i - f + 1 - c] = d[h][i];
            s[h][i] = c;
        }
    build(h + 1, f, mid);
    build(h + 1, mid + 1, t);
}
 
int query(int h, int f, int t, int qf, int qt, int k) {
    if (f == t)
        return d[h][f];
    int mid = f + t >> 1, l = qf == f ? 0 : s[h][qf - 1], r = s[h][qt];
    if (r - l < k)
        return query(h + 1, mid + 1, t, mid + qf - f + 1 - l, mid + qt - f + 1 - r, k - r + l);
    return query(h + 1, f, mid, f + l, f + r - 1, k);
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[a[i] = i]);
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        d[0][a[i]] = i;
    build(0, 1, n);
    while (m--) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        printf("%d\n", b[a[query(0, 1, n, i, j, k)]]);
    }
    return 0;
} 