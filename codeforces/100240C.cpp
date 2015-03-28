#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, x[25];
        cin >> n;
        for(int i = 0; i < n; i++) cin >> x[i];
        sort(x, x + n);
        cout << (x[n - 1] - x[0]) * 2 << '\n';
    }
}