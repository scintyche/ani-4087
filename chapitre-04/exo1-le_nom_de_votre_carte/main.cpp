#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// Ordre d'essai des interfaces selon la plateforme
static vector<string> ordrePlateforme(const string& p) {
    if (p == "WINDOWS") return {"VULKAN", "DX12", "DX11", "OPENGL", "SOFTWARE"};
    if (p == "MACOS")   return {"METAL", "OPENGL", "SOFTWARE"};
    if (p == "IOS")     return {"METAL", "SOFTWARE"};
    if (p == "ANDROID") return {"VULKAN", "OPENGL", "SOFTWARE"};
    return {"VULKAN", "OPENGL", "SOFTWARE"};
}

int main() {
    const map<string, string> lisible = {
        {"VULKAN", "Vulkan"},
        {"DX12", "DirectX 12"},
        {"DX11", "DirectX 11"},
        {"OPENGL", "OpenGL"},
        {"METAL", "Metal"},
        {"SOFTWARE", "Software"}
    };

    int n;
    if (!(cin >> n)) n = 0;

    int ignorees = 0, logiciel = 0;
    set<string> differentes;

    for (int i = 0; i < n; i++) {
        string nom, plateforme;
        int k;
        cin >> nom >> plateforme >> k;

        vector<string> interfaces(k);
        for (int j = 0; j < k; j++) cin >> interfaces[j];

        vector<string> ordre = ordrePlateforme(plateforme);

        // Interfaces listées mais absentes de l'ordre de la plateforme
        for (const string& itf : interfaces) {
            if (find(ordre.begin(), ordre.end(), itf) == ordre.end())
                ignorees++;
        }

        // Première interface de l'ordre présente dans la liste
        string choix = "SOFTWARE";
        for (const string& o : ordre) {
            if (find(interfaces.begin(), interfaces.end(), o) != interfaces.end()) {
                choix = o;
                break;
            }
        }

        const string& affiche = lisible.at(choix);
        cout << nom << " " << affiche << "\n";

        if (choix == "SOFTWARE") logiciel++;
        differentes.insert(affiche);
    }

    cout << "IGNOREES " << ignorees << "\n";
    cout << "LOGICIEL " << logiciel << "\n";
    cout << "DIFFERENTES " << differentes.size() << "\n";
    return 0;
}

