#include <iostream>
using namespace std;
int main() {
 int W, H, w, h;
 cin >> W >> H >> w >> h;
 cout << ((W/w + 1)/2) * ((H/h+1)/2) << '\n';
}