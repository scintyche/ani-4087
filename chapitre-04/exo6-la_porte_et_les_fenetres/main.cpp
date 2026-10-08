#include <iostream>
#include <string>
using namespace std;

int main() {
    long long W, H, seuil;
    int n;
    cin >> W >> H >> seuil;
    if (!(cin >> n)) n = 0;

    int ok = 0, areprendre = 0;

    for (int i = 0; i < n; i++) {
        string nom;
        long long u, y, l, h, e, d;
        if (!(cin >> nom >> u >> y >> l >> h >> e >> d)) break;

        long long saillie = d + e / 2;  // face avant
        long long arriere = d - e / 2;  // face arrière

        string verdict;
        // Comparaisons doublées pour éviter toute division entière sur W et H
        if (2 * u - l < -W || 2 * u + l > W || 2 * y - h < 0 || 2 * y + h > 2 * H)
            verdict = "DEBORDE";
        else if (saillie <= 0)
            verdict = "INVISIBLE";
        else if (saillie < seuil)
            verdict = "CLIGNOTE";
        else if (arriere > seuil)
            verdict = "DECOLLE";
        else
            verdict = "OK";

        if (verdict == "OK") ok++;
        else areprendre++;

        cout << nom << " " << saillie << " " << verdict << "\n";
    }

    cout << "OK " << ok << "\n";
    cout << "A REPRENDRE " << areprendre << "\n";
    return 0;
}

