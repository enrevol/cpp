#include <cmath>
#include <iomanip>
#include <iostream>
#define x first
#define y second
#define pp pair<double, double>
#define PI 3.14159265358
using namespace std;
void vt(pp &v, double d) {
    v.x = cos(d / 180 * PI);
    v.y = sin(d / 180 * PI);
}
void co(double &a, double &b, double &c, pp v, pp p) {
    a = - v.y;
    b = v.x;
    c = - v.y * p.x + v.x * p.y;
}
void an(double &k) {
    k = 45 - (k - 45);
    if(k < 0)
        k = 360 + k;
}
int main() {
    int t;
    cin >> t;
    double d1, d2, a1, b1, c1, a2, b2, c2, det, dx, dy;
    pp p1, p2, v1, v2;
    while(t--) {
        cin >> p1.x >> p1.y >> d1 >> p2.x >> p2.y >> d2;
        an(d1);
        an(d2);
        vt(v1, d1);
        vt(v2, d2);
        co(a1, b1, c1, v1, p1);
        co(a2, b2, c2, v2, p2);
        det = a1 * b2 - b1 * a2;
        dx = c1 * b2 - b1 * c2;
        dy = a1 * c2 - a2 * c1;
        cout << fixed << setprecision(4) << dx / det  << ' ' << dy / det << '\n';
    }
}