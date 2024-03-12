#include <algorithm>
#include <iostream>
#include <vector>

int calculateWinnings(int n, const std::vector<int>& sectors, int a, int b,
                      int k) {
  int maxWinnings = 0;
  for (int initialVelocity = a; initialVelocity <= b; initialVelocity++) {
    for (int direction : {-1, 1}) {
      int currentSector = 0;
      int currentVelocity = initialVelocity * direction;
      int winnings = 0;
      while (true) {
        if (std::abs(currentVelocity) <= k) {
          break;
        }
        currentSector = (currentSector + n + currentVelocity) %
                        n;  // +n to handle negative values
        winnings = std::max(winnings, sectors[currentSector]);
        currentVelocity -= direction * k;
      }
      maxWinnings = std::max(maxWinnings, winnings);
    }
  }
  return maxWinnings;
}

int main() {
  int n, a, b, k;
  std::cin >> n;
  std::vector<int> sectors(n);
  for (int i = 0; i < n; i++) {
    std::cin >> sectors[i];
  }
  std::cin >> a >> b >> k;
  std::cout << calculateWinnings(n, sectors, a, b, k) << std::endl;
  return 0;
}