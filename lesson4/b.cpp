#include <algorithm>
#include <iostream>
#include <vector>

long long ships(long long k) {
  //   long long res = 0;
  //   k0 = (k - 0 - 0) * (1 + 0) + (1 + 0);
  //   k1 = (k0 - 1 - 1) * (1 + 1) + (1 + 1);
  //   kn = (k[n - 1] - 1 - n) * (1 + n) + (1 + n);
  //   k0 = (k - 0) * (1 + 0) + (1 + 0);
  //   k1 = (k - 1) * (1 + 1) + (1 + 1);
  //   kn = (k - n) * (1 + n) + (1 + n);  // n<k
  //   for (int i = 0; i < k; i++) {
  //     res += (k - i) * (1 + i) + (1 + i);
  //   }
  return res - 1;
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