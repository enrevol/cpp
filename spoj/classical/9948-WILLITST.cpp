#include <cstdio>
#include <set>
 
std::set<unsigned long long> s;
 
int main() {
  unsigned long long n;
  scanf("%llu", &n);
  s.insert(n);
  while (n > 1) {
    if (n & 1) {
      n *= 3;
      n += 3;
    } else {
      n >>= 1;
    }
    if (s.count(n)) {
      puts("NIE");
      return 0;
    } else {
      s.insert(n);
    }
  }
  puts("TAK");
} 