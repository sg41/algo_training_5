#include <iostream>
#include <string>
#include <vector>
int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> field(n);
  for (int i = 0; i < n; i++) {
    std::cin >> field[i];
  }
  return 0;
}