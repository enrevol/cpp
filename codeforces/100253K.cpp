#include <iostream>

using namespace std;

typedef pair<int, int> pp;
int d[300005];
pp p[300005];

int main() {
    
    int n, j, ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> d[i];     
    
    for(int i = 0; i < n; i++) {
        int d1 = 0, d2 = 0;
        for(j = 1; i + j < n; j++) {
            if(d[i + j] <= j) break;
            else d1 = j;
        }
        int md = d[i];
        for(j = 1; i + j < n; j++) {
            if(md <= j) break;
            else {
                d2 = j;
                md = min(md, d[i + j] + j);
            }
        }
        if(d1 > d2) {
            p[ans++] = make_pair(i + 1, i + d1 + 1);
            i = i + d1;
        } else {
            p[ans++] = make_pair(i + d2 + 1, i + 1);
            i = i + d2;
        }
    }
    
    cout << ans << '\n';
    for(int i = 0; i < ans; i++) cout << p[i].first << ' ' << p[i].second << '\n';
}