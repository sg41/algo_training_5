#include <iostream>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> ships(n);
  std::vector<std::vector<int>> field(n + 1, std::vector<int>(n + 1, 0));
  for (int i = 0; i < n; i++) {
    std::cin >> ships[i].first >> ships[i].second;
    field[ships[i].first][ships[i].second] = 1;
  }
  return 0;
}