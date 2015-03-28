#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct ss {
    int t, w, i;
}p[5005];

int f(const ss &a, const ss &b) {
    return a.w < b.w;
}

int main() {
    
    vector<int> s1, s2, s3;
    int n, a, b;
    cin >> n >> a >> b;
    
    for(int i = 0; i < n; i++) {
        cin >> p[i].t >> p[i].w;
        p[i].i = i + 1;
    }
    sort(p, p + n, f);  
    
    int ans1 = 0, ans2 = 0;
    
    for(int i = 0; i < n; i++) {
        if(s1.size() + s2.size() + s3.size() < a + b) {
            if(p[i].t == 1 && s1.size() < a) {
                s1.push_back(p[i].i);
                ans1++;
                ans2 = ans2 + p[i].w;
            } else if(p[i].t == 2 && s2.size() < b) {
                s2.push_back(p[i].i);
                ans1++;
                ans2 = ans2 + p[i].w;
            } else if(p[i].t == 3) {
                s3.push_back(p[i].i);
                ans1++;
                ans2 = ans2 + p[i].w;
            }           
        }
    }
    
    cout << ans1 << ' ' << ans2 << '\n';
    
    int k = 1, j = 0;
    for(int i = 0; i < s1.size(); i++) cout << s1[i] << ' ' << k++ << '\n';
    for(; j < s3.size() && s1.size() + j < a; j++) cout << s3[j] << ' ' << k++ << '\n';
    k = a + 1;
    for(int i = 0; i < s2.size(); i++) cout << s2[i] << ' ' << k++ << '\n';
    for(; j < s3.size(); j++) cout << s3[j] << ' ' << k++ << '\n';
}