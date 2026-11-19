#include <iostream>
#include <cmath>
#include <string>
using namespace std;

typedef long long ll;

// Tourne (x, z) de k quarts de tour
void tourner(ll &x, ll &z, int k) {
    k = ((k % 4) + 4) % 4;
    ll nx = x, nz = z;
    if (k == 0)      { nx = x;  nz = z;  }
    else if (k == 1) { nx = z;  nz = -x; }
    else if (k == 2) { nx = -x; nz = -z; }
    else             { nx = -z; nz = x;  }
    x = nx;
    z = nz;
}

int main() {
    ll ax, ay, az;
    int ak;
    ll ex, ey, ez;
    int n;

    cin >> ax >> ay >> az >> ak;
    cin >> ex >> ey >> ez;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string e;
        ll x, y, z, w, h;
        int k;
        cin >> e >> x >> y >> z >> k >> w >> h;

        // "-" (non précisé) => LOCAL ; "S" => STAGE ; "L" => LOCAL
        bool local = (e != "S");

        ll cx = x, cy = y, cz = z;
        int lacet = k;

        if (local) {
            // centre du panneau tourné de ak, puis ajout de l'ancre
            tourner(cx, cz, ak);
            cx += ax;
            cy += ay;
            cz += az;
            lacet = (ak + k) % 4;
        }

        cout << "PANNEAU " << i << " " << (local ? "LOCAL" : "STAGE") << "\n";

        // coins avant rotation (dans le plan x, y de la pose)
        ll coinX[4] = { -w / 2,  w / 2, w / 2, -w / 2 };
        ll coinY[4] = { -h / 2, -h / 2, h / 2,  h / 2 };

        for (int c = 0; c < 4; c++) {
            ll rx = coinX[c];
            ll rz = 0;
            tourner(rx, rz, lacet);          // y ne tourne pas
            ll fx = cx + rx;
            ll fy = cy + coinY[c];
            ll fz = cz + rz;
            cout << fx << " " << fy << " " << fz << "\n";
        }

        // distance du CENTRE à l'œil
        long double dx = (long double)(cx - ex);
        long double dy = (long double)(cy - ey);
        long double dz = (long double)(cz - ez);
        long double d = sqrtl(dx * dx + dy * dy + dz * dz);
        cout << "DISTANCE " << llround(d) << "\n";
    }

    cout << "PANNEAUX " << n << "\n";
    return 0;
}

