#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
string s[10005];
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;       
        for(int i = 0; i < n; i++) cin >> s[i];
        sort(s, s + n);
        int f = 1;
        for(int i = 0; i < n - 1 && f; i++) {
            int L1 = s[i].length();
            int L2 = s[i + 1].length();
            f = 0;
            for(int j = 0; j < min(L1, L2) && !f; j++)
                if(s[i][j] != s[i + 1][j]) f = 1;
        }
        if(f) cout << "YES\n";
        else cout << "NO\n";
    }
}