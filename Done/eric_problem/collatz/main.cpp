
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
  int M, N;
  cin >> M >> N;

  for (int i = M; i <= N; ++i) {
    int x = i;
    int top = -1;
    while (x != 4) {

      if (x % 2 == 0) {
        x = x / 2;
      } else {
        x = x * 3 + 1;
      }
      top = max(top, x);
    }
    cout << top << endl;
  }
  return 0;
}
