#include <iostream>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<int> l(n);
  for (int i = 0; i < n; i++) {
    std::cin >> l[i];
  }
  int max = l[0];
  int sum = l[0];
  for (int i = 1; i < n; i++) {
    if (l[i] > max) {
      max = l[i];
    }
    sum += l[i];
  }
  if (max - (sum - max) <= 0) {
    std::cout << sum << std::endl;
  } else {
    std::cout << max - (sum - max) << std::endl;
  }
  return 0;
}