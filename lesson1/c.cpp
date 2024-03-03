#include <iostream>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<long> a(n);
  long sum = 0;
  static const long kTab = 4;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum += a[i] / kTab;
    sum += a[i] % kTab == 3 ? 2 : a[i] % kTab;
  }

  std::cout << sum << std::endl;

  return 0;
}