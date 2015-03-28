#include <cmath>
#include <iostream>
#include <map>
#include <vector>
#define M 1000000
typedef long long LL;
using namespace std;
int sieve[M + 5];
vector <int> primes;
map <LL, int>::iterator ii;
int main() {
    for (int i = 2; i <= M; i++)
        if (!sieve[i]) {
            primes.push_back(i);
            for (int j = i; j <= M; j += i) sieve[j] = i;
        }
    int T;
    cin >> T;
    while (T--) {
        LL n, k, ans = 1LL << 60;
        cin >> n >> k;
        map <LL, int> m;
        int index = 0;
        int sq = sqrt(k);
        while (primes[index] <= sq && index < primes.size()) {
            while (k % primes[index] == 0) {
                m[primes[index]]++;
                k /= primes[index];
            }
            index++;
        }
        if (k > 1) m[k]++;
        for (ii = m.begin(); ii != m.end(); ii++)
            if (ii->second) {
                LL temp = n;
                LL t = 0;
                while (temp) {
                    t += temp / ii->first;
                    temp /= ii -> first;
                }
                t /= ii->second;
                ans = min(ans, t);
            }
        cout << ans << '\n';
    }
}