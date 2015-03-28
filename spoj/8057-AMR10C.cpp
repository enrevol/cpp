#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#define MAX 1005
using namespace std;
int sieve[MAX];
vector<int> primes;
void pre() {
  for (int i = 2; i < MAX; ++i) 
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i * i; j < MAX; j += i) sieve[j] = 1;
    }
}
int main() {
  pre();
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, ans = 1;
    scanf("%d", &n);
    int k = 0;
    while (n > 1 && k < primes.size()) {
      if (n % primes[k] == 0) {
        int t = 0;
        while (n % primes[k] == 0) {
          n /= primes[k];
          t++;
        }
        ans = max(ans, t);
      }      
      k++;
    }
    printf("%d\n", ans);
  }
} 