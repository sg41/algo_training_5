#include <iostream>
#include <vector>
int main(void) {
  int n, k;
  std::cin >> n >> k;
  std::vector<long long> price(n);
  for (int i = 0; i < n; i++) {
    std::cin >> price[i];
  }

  long long max_profit = 0;
  long long total_profit = 0;
  for (int i = 0; i < n - 1; i++) {
    long long max_price = price[i];
    long long buy_price = price[i];
    for (int d = 1; d <= k && i + d < n; d++) {
      if (price[i + d] > max_price) {
        max_price = price[i + d];
      }
    }
    if (max_price - buy_price > max_profit) {
      max_profit = max_price - buy_price;
    }
    total_profit += max_price - buy_price;
  }
  std::cout << max_profit << std::endl;
  return 0;
}