
#include <iostream>
#include <string>
using namespace std;

int main() {
    int best_i = 0, best_j = 0, best_k = 0;
    int max_fours = -1;

    for (int i = 0; i < 1000; i++) {
        for (int j = i; j < 1000; j++) {
            for (int k = j; k < 1000; k++) {
                int sum = i + j + k;
                int product = i * j * k;

                if (sum % 2 != 0 || product % 2 != 0) continue;

                string sumStr = to_string(sum);
                bool validSum = true;
                for (int s = 0; s < sumStr.size(); s++) {
                    if (sumStr[s] != '2' && sumStr[s] != '4') {
                        validSum = false;
                        break;
                    }
                }
                if (!validSum) continue;

                string prodStr = to_string(product);
                bool validProd = true;
                for (int p = 0; p < prodStr.size(); p++) {
                    if (prodStr[p] != '2' && prodStr[p] != '4') {
                        validProd = false;
                        break;
                    }
                }
                if (!validProd) continue;

                // Count number of '4's in i, j, k
                int fours = 0;
                string istr = to_string(i);
                string jstr = to_string(j);
                string kstr = to_string(k);

                for (int a = 0; a < istr.size(); a++) {
                    if (istr[a] == '4') fours++;
                }
                for (int a = 0; a < jstr.size(); a++) {
                    if (jstr[a] == '4') fours++;
                }
                for (int a = 0; a < kstr.size(); a++) {
                    if (kstr[a] == '4') fours++;
                }

                if (fours > max_fours) {
                    max_fours = fours;
                    best_i = i;
                    best_j = j;
                    best_k = k;
                }
            }
        }
    }

    cout << best_i << ", " << best_j << ", " << best_k << endl;
    return 0;
}

