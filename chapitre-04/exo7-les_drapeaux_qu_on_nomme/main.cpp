#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

typedef unsigned long long u64;

int main() {
    const u64 RENDER2D = 1, RENDER3D = 2, TEXT = 4, UI = 8, SHADOW = 16,
              POST_PROCESS = 32, VFX = 64, ANIMATION = 128, OVERLAY = 256,
              SIMULATION = 512, OFFSCREEN = 1024, RAYTRACING = 2048,
              GPU_CULLING = 4096;
    const u64 ALL = 4294967295ULL;
    const u64 SIMPLES = 8191ULL;  // les 13 drapeaux simples (bits 0 à 12)

    map<string, u64> connus = {
        {"RENDER2D", RENDER2D}, {"RENDER3D", RENDER3D}, {"TEXT", TEXT},
        {"UI", UI}, {"SHADOW", SHADOW}, {"POST_PROCESS", POST_PROCESS},
        {"VFX", VFX}, {"ANIMATION", ANIMATION}, {"OVERLAY", OVERLAY},
        {"SIMULATION", SIMULATION}, {"OFFSCREEN", OFFSCREEN},
        {"RAYTRACING", RAYTRACING}, {"GPU_CULLING", GPU_CULLING},
        {"NONE", 0},
        {"2D_ESSENTIALS", RENDER2D | TEXT},
        {"3D_BASE", RENDER3D | SHADOW | POST_PROCESS},
        {"DEBUG", OVERLAY | SIMULATION},
        {"ALL", ALL}
    };

    int n;
    if (!(cin >> n)) n = 0;

    u64 valeur = 0;
    for (int i = 0; i < n; i++) {
        string nom;
        cin >> nom;
        map<string, u64>::iterator it = connus.find(nom);
        if (it == connus.end()) {
            cout << "INCONNU " << nom << "\n";
        } else {
            valeur |= it->second;
        }
    }

    // Aucun drapeau nommé : valeur par défaut
    if (n == 0) valeur = ALL;

    cout << "VALEUR " << valeur << "\n";
    printf("HEXA 0x%08llX\n", valeur);

    // Dépendances, dans l'ordre imposé
    struct Dep {
        const char* nom;
        u64 flag;
        vector<pair<const char*, u64> > besoins;
    };
    vector<Dep> deps(4);
    deps[0].nom = "TEXT";    deps[0].flag = TEXT;
    deps[0].besoins.push_back(make_pair("RENDER2D", RENDER2D));
    deps[1].nom = "UI";      deps[1].flag = UI;
    deps[1].besoins.push_back(make_pair("RENDER2D", RENDER2D));
    deps[1].besoins.push_back(make_pair("TEXT", TEXT));
    deps[2].nom = "SHADOW";  deps[2].flag = SHADOW;
    deps[2].besoins.push_back(make_pair("RENDER3D", RENDER3D));
    deps[3].nom = "OVERLAY"; deps[3].flag = OVERLAY;
    deps[3].besoins.push_back(make_pair("RENDER2D", RENDER2D));
    deps[3].besoins.push_back(make_pair("TEXT", TEXT));

    for (size_t i = 0; i < deps.size(); i++) {
        if (!(valeur & deps[i].flag)) continue;
        for (size_t j = 0; j < deps[i].besoins.size(); j++) {
            if (!(valeur & deps[i].besoins[j].second)) {
                cout << "MANQUE " << deps[i].nom << " "
                     << deps[i].besoins[j].first << "\n";
            }
        }
    }

    int allumes = 0;
    for (int b = 0; b < 13; b++)
        if (valeur & (1ULL << b)) allumes++;

    cout << "ALLUMES " << allumes << "\n";
    cout << "ETEINTS " << (13 - allumes) << "\n";
    return 0;
}

