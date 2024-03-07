#include <iostream>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<int> x(n);
  std::vector<int> y(n);
  std::vector<std::vector<int>> field(64 + 2, std::vector<int>(64 + 2, 0));
  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
    field[x[i]][y[i]] = 1;
  }
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};
  int perimetr = n * 4;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      if (field[x[i] + dx[j]][y[i] + dy[j]] == 1) {
        perimetr--;
      }
    }
  }
  std::cout << perimetr << std::endl;
  return 0;
}