#include <cstdio>
#include <cctype>
 
char s[101010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d\n", &n);
    gets(s + 1);
    for (int i = 1; s[i]; ++i) {
      if (s[i] == '.') {
        putchar(' ');
      } else {
        if (n <= 25) {
          if (std::islower(s[i])) {
            putchar((s[i] - 'a' + n) % 26 + 'a');
          } else {
            putchar((s[i] - 'A' + n) % 26 + 'A');
          }
        } else {
          if (std::islower(s[i])) {
            putchar(std::toupper((s[i] - 'a' + n) % 26 + 'a'));
          } else {
            putchar(std::tolower((s[i] - 'A' + n) % 26 + 'A'));
          }
        }
      }
    }
    putchar('\n');
  }
} 