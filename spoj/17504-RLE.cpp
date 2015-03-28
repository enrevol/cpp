#include <cstdio>
#include <cstring>
 
char s[101010];
 
int main() {
  while (gets(s + 1)) {    
    int sz = strlen(s + 1);
    int cnt = 1;
    for (int i = 1; i <= sz; ++i) {
      if (s[i] != s[i + 1]) {
        if (cnt <= 3) while (cnt--) putchar(s[i]);
        else printf("%d!%c", cnt, s[i]);
        cnt = 1;
      } else {
        ++cnt;
      }
    }
    puts("");
  }  
} 