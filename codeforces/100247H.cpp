#include <iostream>
#include <string>
using namespace std;
int main() {
    int n, ans = 0;
    string s1, s2;
    cin >> n >> s1 >> s2;
    for(int i = 0; i < n; i++) {
        int f = 0, j = i;
        for(; j < n; j++) {
            if(s1[j] != s2[j]) f = 1;
            else break;
        }
        if(f) ans++;
        i = j - 1;
        if(!f) i++;
    }
    cout << ans;
}