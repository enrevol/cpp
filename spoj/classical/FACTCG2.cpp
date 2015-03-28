#include <iostream>
#include <cmath>
#include <cstring>
#include <bitset>
#include <string>
#include <map>
#include <vector>
#define MAXI 10000005
#define SMAXI 3163
using namespace std;
bitset<MAXI> sieve;
int primes[666666], primesz, d;
void pre() {
  sieve.set();
  primes[primesz] = 2;
  primesz++;
  for (int i = 3; i < SMAXI; i += 2)
    if (sieve[i])
      for (int j = i * i; j < MAXI; j += i * 2)
        sieve[j] = 0;
  for (int i = 3; i < MAXI; i += 2)
    if (sieve[i]) {
      primes[primesz] = i;
      primesz++;
    }
}
void solve(int n) {  
  putchar('1');
  int index = 0;  
  int sq = sqrt(n);
  while (n > 1 && index < primesz && primes[index] <= sq) {
    if (n & 1 && sieve[n]) {      
      printf(" x %d", n);
      n = 1;
    }
    while (n % primes[index] == 0) {
      n /= primes[index];
      printf(" x %d",  primes[index]);
    }
    index++;
  }
  if (n > 1) printf(" x %d", n);
  putchar('\n');
}
int main() {
  pre();
  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }
} 