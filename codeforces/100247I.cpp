#include <iostream>
#include <set>
using namespace std;
multiset <int> s;
int main() {
    int n, ans = 0, dmg = 0, d, t;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t >> d;
        s.insert(d);
        dmg = dmg + d;
        while(dmg > t) {
            int k = *(--s.end());
            s.erase(--s.end());
            dmg = dmg - k;
            ans++;
        }
    }
    cout << ans;
}