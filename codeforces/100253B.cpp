#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

double c[300005];

int main() {
    double ans = 0, dist, req, x, r, *t;
    int m, n, k = 0;
    cin >> m >> n >> r;
    
    for(int i = 0; i < m; i++) cin >> c[i];
    
    for(int i = 0; i < n; i++) {
        cin >> x;
        dist = abs(x - c[k]);
        req = sqrt(r * r  - 1);
        if(dist > req) {
            if(c[k] < x) {
                t = lower_bound(c, c + m, x - req);
                ans = ans + *t - c[k];
            } else {
                t = upper_bound(c, c + m, x + req) - 1;
                ans = ans + c[k] - *t;
            }
            k = t - c;
        }
        //cout << "ans = " << ans << " k = " << k << '\n';;
    }
    
    cout << fixed << setprecision(1) << ans;
}