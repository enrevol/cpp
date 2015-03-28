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

const int N = 2010;
const int BASE1 = 29;
const int BASE2 = 31;
const int MOD = 1e9 + 9;

char s[N];
bool nice[256];
pair<int, int> arr[N * N];

int main() {
//    freopen("in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    scanf("%d", &tt);
    while (tt--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        memset(nice, false, sizeof(nice));
        int p;
        scanf("%d", &p);
        for (int i = 0; i < p; ++i) {
            char c[2];
            scanf("%s", c);
            nice[*c] = true;
        }
        int k;
        scanf("%d", &k);
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            int d = 0, h1 = 0, h2 = 0;
            for (int j = i; j <= n; ++j) {
                d += !nice[s[j]];
                if (d > k) break;
                h1 = ((long long)h1 * BASE1 + s[j]) % MOD;
                h2 = ((long long)h2 * BASE2 + s[j]) % MOD;
                arr[cnt++] = make_pair(h1, h2);
            }
        }
        sort(arr, arr + cnt);
        int answer = unique(arr, arr + cnt) - arr;
        printf("%d\n", answer);
    }
}