#include <iostream>
#include <vector>

struct Pose {
    long long x, y;
    int k;
};

// Tourne un vecteur (u, v) de k quarts de tour (sens inverse des aiguilles)
static void tourner(long long u, long long v, int k, long long &ru, long long &rv) {
    switch (k) {
        case 0: ru = u;  rv = v;  break;
        case 1: ru = -v; rv = u;  break;
        case 2: ru = -u; rv = -v; break;
        default: ru = v; rv = -u; break;
    }
}

// Composition A * B : position A + (B tourné de A.k), angle (A.k + B.k) % 4
static Pose composer(const Pose &A, const Pose &B) {
    long long ru, rv;
    tourner(B.x, B.y, A.k, ru, rv);
    Pose r;
    r.x = A.x + ru;
    r.y = A.y + rv;
    r.k = (A.k + B.k) % 4;
    return r;
}

// Inverse de A : angle (4 - A.k) % 4, position (-A.x, -A.y) tournée de cet angle
static Pose inverse(const Pose &A) {
    Pose r;
    r.k = (4 - A.k) % 4;
    tourner(-A.x, -A.y, r.k, r.x, r.y);
    return r;
}

int main() {
    int M, T;
    if (!(std::cin >> M >> T)) return 0;

    std::vector<Pose> objet(M + 1);
    for (int j = 1; j <= M; j++) {
        std::cin >> objet[j].x >> objet[j].y >> objet[j].k;
        objet[j].k = ((objet[j].k % 4) + 4) % 4;
    }

    int tenu = 0;            // numéro de l'objet tenu, 0 si aucun
    Pose attache = {0, 0, 0};
    int bPrec = 0;           // b avant l'image 1
    int saisies = 0, ratees = 0;

    for (int t = 1; t <= T; t++) {
        Pose paume;
        int b;
        std::cin >> paume.x >> paume.y >> paume.k >> b;
        paume.k = ((paume.k % 4) + 4) % 4;

        bool rate = false;

        if (b == 1 && bPrec == 0) {
            // Appui : chercher l'objet le plus proche, à 150 mm au plus
            int meilleur = 0;
            long long meilleureDist = 0;
            for (int j = 1; j <= M; j++) {
                long long dx = objet[j].x - paume.x;
                long long dy = objet[j].y - paume.y;
                long long d = dx * dx + dy * dy;
                if (d <= 22500 && (meilleur == 0 || d < meilleureDist)) {
                    meilleur = j;
                    meilleureDist = d;
                }
            }
            if (meilleur != 0) {
                tenu = meilleur;
                attache = composer(inverse(paume), objet[tenu]);
                saisies++;
            } else {
                ratees++;
                rate = true;
            }
        } else if (b == 0 && bPrec == 1) {
            // Relâchement : plus rien n'est tenu, l'objet reste où il est
            tenu = 0;
        }
        bPrec = b;

        if (rate) {
            std::cout << t << " RATE\n";
        } else if (tenu != 0) {
            objet[tenu] = composer(paume, attache);
            std::cout << t << " TIENT " << tenu << " " << objet[tenu].x << " "
                      << objet[tenu].y << " " << objet[tenu].k << "\n";
        } else {
            std::cout << t << " LIBRE\n";
        }
    }

    std::cout << "SAISIES " << saisies << "\n";
    std::cout << "RATEES " << ratees << "\n";
    for (int j = 1; j <= M; j++) {
        std::cout << "OBJET " << j << " " << objet[j].x << " " << objet[j].y
                  << " " << objet[j].k << "\n";
    }
    return 0;
}

