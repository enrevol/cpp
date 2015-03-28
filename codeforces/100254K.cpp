#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int main() {
    
    vector<int> v;
    
    int n, k, t, pos = 0, d;
    string s;
    cin >> n >> k >> s;
    d = n - k;
    while(k > pos - v.size()){
        for(int i = pos + 1; i < n - (d - 1 - v.size()); i++) {
            if(s[i] > s[pos])
                pos = i;
            if(s[pos] == '9')
                break;
        }
        v.push_back(s[pos] - '0');
        pos++;      
    }
    
    for(int i = pos; i < n; i++)
        v.push_back(s[i] - '0');
    
    for(int i = 0; i < v.size(); i++)
        cout << v[i];
}