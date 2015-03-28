#include <iostream>
#define ll long long

using namespace std;

ll ar1[4] = {1, 4, 6, 3};
ll ar2[4] = {1, 5, 6, 2};
ll b[4];

int ss(int k) {
    if(k >= 4) k = k - 4;
    if(k < 0) k = k + 4;
    return k;
}

int main() {
    int r, c;
    cin >> r >> c;
    
    ll ans = 0;
    
    for(int i = 0; i < r; i++) {
        int k = c / 4;
        int d = c % 4;
        ans = ans + 14 * k;
        for(int j = 0; j < d; j++) ans = ans + ar1[j];
        for(int j = 0; j < 4; j++) b[j] = ar1[ss(j + d - 1)];
        for(int j = 0; j < 4; j++) ar1[j] = b[j];
        ar2[0] = ar1[0];
        ar2[2] = ar1[2];
        for(int j = 0; j < 4; j++) b[j] = ar2[ss(j + 1)];
        for(int j = 0; j < 4; j++) ar2[j] = b[j];
        ar1[0] = ar2[0];
        ar1[2] = ar2[2];
        b[0] = ar1[0];
        b[1] = ar1[3];
        b[2] = ar1[2];
        b[3] = ar1[1];
        for(int j = 0; j < 4; j++) ar1[j] = b[j];
    }
    
    cout << ans;
}