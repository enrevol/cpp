#include <iostream>
#include <map>
typedef long long LL;
using namespace std;
map <LL, LL> m;
int main() {
	int n;
	LL s, a, b = 0, ans = 0;
	cin >> n >> s;
	m[0]++;
	for(int i = 0; i < n; i++) {
		cin >> a;
		b = b + a;		
		ans = ans + m[b - s];
		m[b]++;
	}
	cout << ans;
}