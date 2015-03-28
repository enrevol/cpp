#include <iostream>
#include <string>
using namespace std;
int f = 0;
bool ss(char c) {   
    return (c == 'B') ^ (f & 1);
}
int main() {
    int n, ans = 0;
    string s;
    cin >> n >> s;
    for(int i = s.length() - 1; i >= 0;) {
        int k = i;
        while(ss(s[k]) && k >= 0) k--;
        if(i - k > 1) f++;
        if(i - k) ans++;
        //cout << "i = " << i << " k = " << k << " f = " << f << " ans = " << ans << "\n";
        i = min(k, i - 1);
    }
    cout << ans;
}