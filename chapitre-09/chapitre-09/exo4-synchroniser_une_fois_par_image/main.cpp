#include <iostream>

int main() {
    int T;
    if (!(std::cin >> T)) return 0;

    int current = 0;
    int changed = 0;
    int active = 0;

    int precedentP = 0;   // p de l'image précédente (0 avant l'image 1)
    int appuisReels = 0;
    int saisies = 0;
    int refusees = 0;

    for (int t = 1; t <= T; t++) {
        int p, s, f;
        std::cin >> p >> s >> f;

        // Appui réel : p passe de 0 à 1 d'une image à l'autre
        if (p == 1 && precedentP == 0) appuisReels++;
        precedentP = p;

        // s appels à SyncActions pendant cette image
        for (int k = 0; k < s; k++) {
            if (f == 0) {
                // Refusé : rien ne change
                refusees++;
            } else {
                // Accepté : changed, puis current, puis active (dans cet ordre)
                changed = (p != current) ? 1 : 0;
                current = p;
                active = 1;
            }
        }

        // Lecture de l'état après les appels
        bool saisit = (current == 1 && changed == 1);
        if (saisit) saisies++;

        std::cout << t << " " << current << " " << changed << " " << active
                  << " " << (saisit ? "SAISIT" : "-") << "\n";
    }

    std::cout << "APPUIS REELS " << appuisReels << "\n";
    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "SYNC REFUSEES " << refusees << "\n";

    return 0;
}

