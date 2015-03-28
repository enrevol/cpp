#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define pb push_back
typedef long long LL;
using namespace std;
vector <vector <int> > v;
int main() {
	LL ans = 0;
	int n;
	string s;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> s;
		int arr[26], d = 0;
		vector <int> v2;
		memset(arr, 0, sizeof(arr));
		for(int j = 0; j < s.length(); j++) {
			int k = s[j] - 'a';
			if(!arr[k]) arr[k] = ++d;
			v2.pb(arr[k]);
		}
		v.pb(v2);
	}
	sort(v.begin(), v.end());
	for(int i = 0; i < v.size(); i++) {
		LL t = 1;
		for(int j = 1; i + j < v.size(); j++) {
			int f = 1;
			if(v[i].size() != v[i + j].size()) break;
			for(int k = 0; k < v[i].size() && f; k++)
				if(v[i][k] != v[i + j][k]) f = 0;
			if(f) t++;
		}
		ans = ans + t * (t - 1) / 2;
		i = i + t - 1;
	}
	cout << ans;
}