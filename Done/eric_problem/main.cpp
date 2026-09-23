#include <bits/stdc++.h>
#include <string>

using namespace std;

bool isPrime(int n) {
  // 1. Handle corner cases
  if (n <= 1)
    return false; // 0 and 1 are not prime numbers
  if (n == 2 || n == 3)
    return true; // 2 and 3 are prime numbers

  // 2. Eliminate all even numbers and multiples of 3
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  // 3. Check odd factors up to the square root of n
  // We increment by 6 (i += 6) because all primes greater than 3
  // are of the form (6k ± 1).
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false; // Found a factor, so it's not prime
    }
  }

  return true; // No factors found, it is prime
}
int main() {
  int count = 0;
  for (int i = 1; i < 1000000; i++) {
    string n = to_string(i);
    if (n.size() < 2 && isPrime(i)) {
      count++;
    }

    else if (isPrime(i)) {
      bool good = true;
      for (int l = 0; l < n.size() - 1; l++) {
        if (n[l] <= n[l + 1]) {
          continue;
        } else {
          good = false;
          break;
        }
      }
      if (good) {
        cout << n << endl;
        ++count;
      }
    }
  }

  cout << count << endl;
  return 0;
}
