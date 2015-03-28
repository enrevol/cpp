#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

constexpr int N = 1000010;

char s[N], t[N];
int p[N];

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%s %s", s, t);
        char* w = s;
        int cnt = 0;
        for (;;) {
            char* z = strstr(w, t);
            if (z == NULL) {
                break;
            }
            w = z + 1;
            p[cnt++] = z - s;
        }
        if (cnt == 0) {
            puts("Not Found");
        } else {
            printf("%d\n", cnt);
            for (int i = 0; i < cnt; ++i) {
                printf("%d ", p[i] + 1);
            }
            puts("");
        }
        puts("");
    }
}