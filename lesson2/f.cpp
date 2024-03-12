#include <algorithm>
#include <iostream>
#include <vector>

long long calculateWinnings(int n, const std::vector<long long>& sectors,
                            long long a, long long b, long long k) {
  long long max_winning = 0;
  long long max_sectors_right = b / k + (b % k != 0);
  long long max_finish_right = max_sectors_right % n;
  long long min_sectors_right = a / k + (a % k != 0);
  long long min_finish_right = min_sectors_right % n;
  if (max_sectors_right - min_sectors_right >= n) {
    max_winning = *std::max_element(sectors.begin(), sectors.end());
  } else {
    max_winning = *std::max_element(sectors.begin() + min_finish_right,
                                    sectors.begin() + max_finish_right + 1);
  }

  return max_winning;
}

int main() {
  long long n, a, b, k;
  std::cin >> n;
  std::vector<long long> sectors(n);
  for (int i = 0; i < n; i++) {
    std::cin >> sectors[i];
  }
  std::cin >> a >> b >> k;
  std::cout << calculateWinnings(n, sectors, a, b, k) << std::endl;
  return 0;
}