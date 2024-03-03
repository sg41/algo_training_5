#include <iostream>
#include <string>
int main(void) {
  long long n, k, d;
  std::cin >> n >> k >> d;
  long long profit = n;
  bool ok = false;
  profit *= 10;
  for (int dig = 0; dig <= 9; dig++) {
    if ((profit + dig) % k == 0) {
      profit += dig;
      ok = true;
      break;
    }
  }

  if (!ok) {
    profit = -1;
    std::cout << profit << std::endl;
  } else {
    std::string answer = std::to_string(profit);
    answer.append(d - 1, '0');
    std::cout << answer << std::endl;
  }
  return 0;
}