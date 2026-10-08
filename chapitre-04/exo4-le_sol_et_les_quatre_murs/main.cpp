#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Mur {
    long long xmin, xmax, zmin, zmax;
};

int main() {
    long long L, e;
    int n;
    cin >> L >> e;
    if (!(cin >> n)) n = 0;

    vector<Mur> murs;
    for (int i = 0; i < n; i++) {
        string nom;
        long long cx, cz, sx, sz;
        cin >> nom >> cx >> cz >> sx >> sz;
        Mur m = {cx - sx / 2, cx + sx / 2, cz - sz / 2, cz + sz / 2};
        murs.push_back(m);
        cout << nom << " " << m.xmin << " " << m.xmax << " "
             << m.zmin << " " << m.zmax << "\n";
    }

    long long h = L / 2;

    // Carrés des angles : x0 x1 z0 z1, dans l'ordre imposé
    struct Angle {
        const char* nom;
        long long x0, x1, z0, z1;
    };
    Angle angles[4] = {
        {"FOND_GAUCHE",   -h - e, -h,     -h - e, -h},
        {"FOND_DROIT",     h,      h + e, -h - e, -h},
        {"ENTREE_GAUCHE", -h - e, -h,      h,      h + e},
        {"ENTREE_DROIT",   h,      h + e,  h,      h + e}
    };

    int trous = 0;
    for (const Angle& a : angles) {
        bool bouche = false;
        for (const Mur& m : murs) {
            if (m.xmin <= a.x0 && m.xmax >= a.x1 &&
                m.zmin <= a.z0 && m.zmax >= a.z1) {
                bouche = true;
                break;
            }
        }
        if (!bouche) trous++;
        cout << a.nom << " " << (bouche ? "BOUCHE" : "TROU") << "\n";
    }

    cout << "TROUS " << trous << "\n";
    return 0;
}

