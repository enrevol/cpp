#include <algorithm>
#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, p[20005], ans = 0;
        cin >> n;
        for(int i = 0; i < n; i++) cin >> p[i];
        sort(p, p + n);
        reverse(p, p + n);
        for(int i = 2; i < n; i = i + 3) ans = ans + p[i];
        cout << ans << '\n';
    }
}