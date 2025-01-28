//https://pydefis.callicode.fr/defis/C24_AcidesNucleiques_01/txt
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // Map de correspondance des symboles avec leur nombre de possibilités
    unordered_map<char, int> possibilities = {
        {'A', 1}, {'C', 1}, {'G', 1}, {'U', 1},
        {'R', 2}, {'Y', 2}, {'K', 2}, {'M', 2},
        {'S', 2}, {'W', 2}, {'B', 3}, {'D', 3},
        {'H', 3}, {'V', 3}, {'N', 4}
    };

    string sequence;
    cin >> sequence;  // Lire la séquence d'ARN

    long long total_combinations = 1;  // Nombre total de combinaisons
    const int MOD = 100000;  // On garde seulement les 5 derniers chiffres

    // Calculer le nombre total de combinaisons
    for (char c : sequence) {
        total_combinations = (total_combinations * possibilities[c]) % MOD;
    }

    // Afficher le résultat
    cout << total_combinations << endl;
    
    return 0;
}
