#include <iostream>
using namespace std;

int main() {
    int piece[7] = {1, 2, 3, 7, 10, 20, 25};
    int total = 26;
    int dp[100] = {0}; // initialise tout à 0
    dp[0] = 1;

    for (int j = 0; j < 7; j++) {
        for (int i = piece[j]; i <= total; i++) {
            dp[i] += dp[i - piece[j]];
        }
    }

    cout << dp[26] << endl;
    return 0;
}
