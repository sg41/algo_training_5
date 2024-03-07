#include <iostream>
#include <vector>
int main(void) {
  int k;
  std::cin >> k;
  std::vector<long long> x(k), y(k);
  for (int i = 0; i < k; i++) {
    std::cin >> x[i] >> y[i];
  }

  long long max_x = x[0];
  long long max_y = y[0];
  long long min_x = x[0];
  long long min_y = y[0];

  for (int i = 1; i < k; i++) {
    if (x[i] > max_x) {
      max_x = x[i];
    } else if (x[i] < min_x) {
      min_x = x[i];
    }
    if (y[i] > max_y) {
      max_y = y[i];
    } else if (y[i] < min_y) {
      min_y = y[i];
    }
  }

  std::cout << min_x << " " << min_y << " " << max_x << " " << max_y
            << std::endl;

  return 0;
}