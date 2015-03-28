#include <iostream>
typedef long long LL;
using namespace std;
LL a[200005], n, p, q, r;
LL dp(LL L, LL R) {
    if(L > R) return 0;
    LL h = (L + R) / 2;
    LL cnt = 0;
    for(int i = 0; i < n; i++) {
        LL t = a[i];
        t = t - h * q;
        if(t > 0) cnt = cnt + t / r + (t % r != 0);
    }
    if(cnt < h) {
        LL h2 = dp(L, h - 1);
        if(h2 == 0) return h;
        else return h2;
    }
    else if(cnt > h) return dp(h + 1, R);
    else return h;
}
int main() {
    cin >> n >> p >> q;
    r = p - q;
    LL m = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        m = max(m, a[i]);
    }
    if(r == 0) cout << (m / p + (m % q != 0));
    else cout << dp(1, 1 << 30);
}