#include <iostream>
using namespace std;
int main() {    
    int t, c, sum[1005], dp[1005], a[105], p[105];
    cin >> t;
    while(t--) {
        cin >> c;
        sum[0] = 0;
        dp[0] = 0;      
        for(int i = 1; i <= c; i++) {
            cin >> a[i] >> p[i];
            sum[i] = sum[i - 1] + a[i];
            dp[i] = (sum[i] + 10) * p[i];
        }
        for(int i = 1; i <= c; i++)
            for(int j = 1; j <= i; j++)
                dp[i] = min(dp[i], dp[j] + (sum[i] - sum[j] + 10) * p[i]);
        cout << dp[c] << '\n';
    }
}