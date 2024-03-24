#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
//   k0 = (k - 0 - 0) * (1 + 0) + (1 + 0);
//   k1 = (k0 - 1 - 1) * (1 + 1) + (1 + 1);
//   kn = (k[n - 1] - 1 - n) * (1 + n) + (1 + n);
//   k0 = (n - 0) * (1 + 0) + (1 + 0);
//   k1 = (n - 1) * (1 + 1) + (1 + 1);
//   kn = (n - n+1) * (1 + n) + (1 + n);  // n<k

// long long ships(long long n) {
//   long long res = 0;
//   for (int i = 0; i < n; i++) {
//     res += (n - i) * (1 + i) + (1 + i);
//   }
//   return res - 1;
// }
long long ships(long long ni) {
  long double n = ni;
  return floor(n * (n + 1) * (n + 2) / 6) +
         floor(((n + 1) * (n + 1) * (n + 1) - n * n * n - 1) / 6) - 1;
}

long long r_bin_search(long long n) {
  long long start = 0, end = n;
  long long mid = 0;
  long long k;
  while (start < end) {
    mid = (start + end + 1) / 2;
    k = ships(mid);
    if (k > n) {
      end = mid - 1;
    } else {
      start = mid;
    }
  }
  return start;
}

int main(void) {
  long long n;
  std::cin >> n;
  std::cout << r_bin_search(n);
  return 0;
}