#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main() {
  freopen("ghanophobia.in", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    char s1[5], s2[5];
    int fa = 1, fb = 6;
    int sa, sb;
    scanf("%[^:]:%s", s1, s2);
    sa = atoi(s1);
    sb = atoi(s2);
    printf("Case %d: ", i);
    if (sa == fb && sb == fa) printf("PENALTIES\n");
    else if (sa + fa == sb + fb) {
      if (sa < fb) printf("YES\n");
      else printf("NO\n");
    } else if (sa + fa > sb + fb) printf("YES\n");
    else printf("NO\n");
  }
}