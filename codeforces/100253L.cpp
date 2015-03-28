#include <iostream>

using namespace std;

int main() {
    
    int n, d, a, b, p[100005];
    cin >> n >> d >> a >> b;
    
    int k = 0;
    int f = 0;
    
    int ans = 0;
    
    for(int i = 0; i < n; i++) cin >> p[i];
    for(int i = 1; i < n; i++) {        
        if(p[i] > p[i - 1]) {
            if(f != 1) {
                k = 1;
                f = 1;
            } else k++;
            
            int s = min(d / p[i], k * a);
            d = d - s * p[i];
            ans = ans + s;
        } else if(p[i] < p[i - 1]){
            if(f != -1)  {
                k = 1;
                f = -1;
            } else k++;
            
            int s = min(ans, k * b);
            d = d + s * p[i];
            ans = ans - s;
        }
    }
    
    cout << d << ' ' << ans;    
}