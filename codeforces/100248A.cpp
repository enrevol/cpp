#include <iomanip>
#include <iostream>
using namespace std;
int b[1005], a[6];
void ss(int t, int d) {
    if(!b[t] || b[t] > d) {
        b[t] = d;
        for(int i = 0; i < 6; i++) {
            if(t + a[i] <= 200)
                ss(t + a[i], d + 1);
            if(t - a[i] >= 1)
                ss(t - a[i], d + 1);
        }
    }
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        for(int i = 1; i <= 200; i++)
            b[i] = 0;
        for(int i = 0; i < 6; i++)
            cin >> a[i];
        for(int i = 0; i < 6; i++)
            ss(a[i], 1);
        double ans = 0;
        int mx = 1;
        for(int i = 1; i <= 100; i++) {
            ans = ans + b[i];
            if(mx < b[i])
                mx = b[i];
        }
        cout << fixed << setprecision(2) << ans / 100 << ' ';
        cout << mx << '\n';
    }
}