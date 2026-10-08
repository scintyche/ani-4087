#include <iostream>
#include <string>
using namespace std;

struct Pos {
    long long x, y, z;
};

// Centre d'un objet de hauteur sy posé au sol, en (x, z)
Pos PoserAuSol(long long sy, long long x, long long z) {
    Pos p = {x, sy / 2, z};
    return p;
}

// Centre d'un objet de hauteur sy posé sur un dessus à la hauteur H
Pos PoserSurTable(long long H, long long sy, long long x, long long z) {
    Pos p = {x, H + sy / 2, z};
    return p;
}

int main() {
    long long L, P, H, ep, pied, tx, tz;
    cin >> L >> P >> H >> ep >> pied >> tx >> tz;

    // Plateau : posé sur le haut des pieds (H - ep), épaisseur ep
    Pos plateau = PoserSurTable(H - ep, ep, tx, tz);
    cout << "PLATEAU " << plateau.x << " " << plateau.y << " " << plateau.z << "\n";

    // Pieds : hauteur H - ep, posés au sol
    // Ordre : moins-moins, plus-moins, moins-plus, plus-plus
    for (int sz = -1; sz <= 1; sz += 2) {
        for (int sx = -1; sx <= 1; sx += 2) {
            Pos p = PoserAuSol(H - ep, tx + sx * (L / 2 - pied), tz + sz * (P / 2 - pied));
            cout << "PIED " << p.x << " " << p.y << " " << p.z << "\n";
        }
    }

    // Objets
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string nom, ou;
        long long sx, sy, sz, x, z;
        cin >> nom >> sx >> sy >> sz >> x >> z >> ou;
        Pos p = (ou == "TABLE") ? PoserSurTable(H, sy, x, z) : PoserAuSol(sy, x, z);
        cout << nom << " " << p.x << " " << p.y << " " << p.z << "\n";
    }
    return 0;
}

