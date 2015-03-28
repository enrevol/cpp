#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#define pb push_back
typedef long long LL;
using namespace std;
map <int, int> m;
vector <int> v;
int n;
int dp(int size) {
    if(m[size]) return m[size];
    else {
        int res = size / 2 + 1;
        for(int i = 0; v[i] <= sqrt(size); i++)
            if(size % v[i] == 0) {
                res = min(res, dp(v[i]) * (size / v[i] / 2 + 1));
                res = min(res, dp(size / v[i]) * (v[i] / 2 + 1));
            }
        m[size] = res;
        return res;
    }
}
int main() {
    cin >> n;
    int ans = n / 2 + 1;
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0) {
            v.pb(i);
            if(i * i != n) v.pb(n / i);
        }
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++) {
        ans = min(ans, dp(v[i]) * (n / v[i] / 2 + 1));
        ans = min(ans, dp(n / v[i]) * (v[i] / 2 + 1));
    }
    cout << ans;
}