#include <bits/stdc++.h>
#include <string>
using namespace std;
int main() {
  map<string, int> peoples;
  int list = 1;
  string word;

  while (getline(cin, word)) {

    if (word.length() < 1) {
      list++;
      continue;
    }
    peoples[word]++;
  }

  for (auto i : peoples) {
    if (i.second == list) {
      cout << '\"' << i.first << "\",";
    }
  }
}
