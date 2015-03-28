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

constexpr int N = 100010;

char s[N];
int cnt[256], need[256];

bool check() {
    for (int k = 'a'; k <= 'z'; ++k)
        if (cnt[k] < need[k]) {
            return false;
        }
    return true;
}

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    scanf("%d %s %d", &n, s + 1, &k);
    for (int i = 0; i < k; ++i) {
        int v;
        char c[2];
        scanf("%d %s", &v, c);
        need[*c] = v;        
    }
    int answer = -1;
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j < i) {
            ++cnt[s[++j]];
        }
        while (j + 1 <= n && !check()) {
            ++cnt[s[++j]];
        }
        if (j <= n && check()) {
            int len = j - i + 1;
            if (answer == -1 || answer > len) {
                answer = len;
            }
        }
        --cnt[s[i]];
    }
    if (answer == -1) {
        puts("Andy rapopo");
    } else {
        printf("%d", answer);
    }
}