#include <algorithm>
#include <iostream>
using namespace std;
struct ss {
    int a[3];
} p[200005];
int arr[200005];
int main() {
    int n, ans = 0, mb = 0, mc = 0, fb = 0, fc = 0;
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 3; j++)
            cin >> p[i].a[j];
    for(int i = 0; i < n; i++) {
        sort(p[i].a, p[i].a + 3);
        if(p[i].a[1] > p[mb].a[1]) mb = i;
        if(p[i].a[0] > p[mc].a[0]) mc = i;
    }
    for(int i = 0; i < n; i++) {
        if(p[mb].a[1] == p[i].a[1]) fb++;
        if(p[mc].a[2] == p[i].a[2]) fc++;
    }   
    for(int i = 0; i < n; i++) {
        int b = p[i].a[2] > p[mb].a[1] || (i == mb && fb == 1);
        int c = p[i].a[1] > p[mc].a[0] || (i == mc && fc == 1);
        if(b && c) arr[ans++] = i + 1;
    }
    cout << ans << '\n';
    for(int i = 0; i < ans; i++) cout << arr[i] << ' ';
}