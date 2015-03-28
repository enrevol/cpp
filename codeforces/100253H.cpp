#include <iostream>
#include <string>

using namespace std;

int main() {
    
    int n, j, k;
    string s, ans = "";
    cin >> n >> s;
        
    int flag = 1;
    for(int i = 0; i < s.length() && flag; i++)
        if(s[i] != '=') flag = 0;
    
    if(flag) {
        for(int i = 0; i < s.length() + 1; i++) cout << 'a';        
    } else {
        char last;
        s = s + '.';
        
        for(int i = 0; i < s.length() - 1; i++) {
            char c = '=';
            int cnt = 1;
            int end;
                    
            for(j = i; j < s.length() && c == '='; j++) c = s[j];
            
            for(j = i; j < s.length(); j++) {
                if(s[j] != '=') {
                    if(s[j] == c) {
                        cnt++;
                        end = j;
                    }
                    else break;
                }
            }
            
            if(cnt > n) {
                cout << -1;
                return 0;
            }
            
            char start;
            if(i == 0) {
                k = i;
                if(c == '<') start = 'a';
                else start = 'a' + n - 1;
            } else {
                k = i + 1;
                if(i == end) {
                    if(c == '<') start = 'a' + n - 1;
                    else start = 'a';
                } else {
                    if(c == '<') start = last + 1;
                    else start = last - 1;
                }
            }
            
            ans = ans + start;
            
            for(; k < j; k++) {
                if(s[k] == '<') start = start + 1;
                else if(s[k] == '>') start = start - 1;
                if(k == end) {
                    if(c == '<') start = 'a' + n - 1;
                    else start = 'a';
                }
                ans = ans + start;
            }
            
            last = start;
            
            i = j - 1;
        }
        
        cout << ans;
    }
}