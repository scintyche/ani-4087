#include <iostream>
using namespace std;

struct Pose {
    long long x, y, z;
    int k;
};

// Tourne (x, z) de k quarts de tour ; y ne bouge pas.
Pose tourner(Pose p, int k) {
    long long x = p.x, z = p.z;
    switch (k % 4) {
        case 0: p.x = x;  p.z = z;  break;
        case 1: p.x = z;  p.z = -x; break;
        case 2: p.x = -x; p.z = -z; break;
        case 3: p.x = -z; p.z = x;  break;
    }
    return p;
}

// Compose l'ancre A avec la pose p (passage de LOCAL a STAGE).
Pose composer(const Pose& A, const Pose& p) {
    Pose r = tourner(p, A.k);
    r.x += A.x;
    r.y += A.y;
    r.z += A.z;
    r.k = (A.k + p.k) % 4;
    return r;
}

int main() {
    Pose A;
    cin >> A.x >> A.y >> A.z >> A.k;
    A.k = ((A.k % 4) + 4) % 4;

    int N;
    cin >> N;

    int justes = 0, fausses = 0;

    for (int i = 1; i <= N; i++) {
        char D, C;
        Pose p;
        cin >> D >> C >> p.x >> p.y >> p.z >> p.k;

        // Vraie pose dans STAGE : selon l'espace dans lequel elle a ete demandee (D)
        Pose vrai = (D == 'S') ? p : composer(A, p);

        // Pose crue par le compositeur : selon l'espace declare dans la couche (C)
        Pose cru = (C == 'S') ? p : composer(A, p);

        long long dx = cru.x - vrai.x;
        long long dy = cru.y - vrai.y;
        long long dz = cru.z - vrai.z;
        int dk = ((cru.k - vrai.k) % 4 + 4) % 4;

        cout << i << " CRU " << cru.x << " " << cru.y << " " << cru.z << " " << cru.k << "\n";
        cout << i << " ECART " << dx << " " << dy << " " << dz << " " << dk << "\n";

        if (dx == 0 && dy == 0 && dz == 0 && dk == 0) justes++;
        else fausses++;
    }

    cout << "JUSTES " << justes << "\n";
    cout << "FAUSSES " << fausses << "\n";
    return 0;
}

