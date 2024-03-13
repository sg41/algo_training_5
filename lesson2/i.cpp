#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
int move_ships(std::vector<std::vector<int>> field,
               std::vector<std::pair<int, int>> ships, int column) {
  int moves = 0;
  // for( int)
  for (int i = 1; i < field.size(); i++) {
    if (field[i][column] == 1) {
      continue;
    }
    std::sort(ships.begin(), ships.end(),
              [i, column](const std::pair<int, int>& a,
                          const std::pair<int, int>& b) {
                bool res = false;
                int patha = std::abs(a.first - i) + std::abs(a.second - column);
                int pathb = std::abs(b.first - i) + std::abs(b.second - column);
                if (patha > pathb) {
                  res = true;
                } else if (patha == pathb) {
                  if (b.first == i) res = true;
                }
                return res;
              });
    for (int s = ships.size() - 1; s >= 0; s--) {
      if (ships[s].second == column) {
        ships.pop_back();
        continue;
      } else {
        moves +=
            std::abs(ships[s].first - i) + std::abs(ships[s].second - column);
        ships.pop_back();
        break;
      }
    }
    field[i][column] = 1;
  }
  return moves;
}

int main(void) {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> ships(n);
  std::vector<std::vector<int>> field(n + 1, std::vector<int>(n + 1, 0));
  std::vector<int> ships_per_column(n + 1, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> ships[i].first >> ships[i].second;
    field[ships[i].first][ships[i].second] = 1;
    ships_per_column[ships[i].second]++;
  }
  // std::cout << std::string(n * 2, '-') << std::endl;
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     std::cout << '|' << ((field[i][j] == 1) ? 'X' : ' ');
  //   }
  //   std::cout << '|' << std::endl;
  //   std::cout << std::string(n * 2, '-') << std::endl;
  // }
  int max_ships_per_column =
      *std::max_element(ships_per_column.begin(), ships_per_column.end());
  int min_moves = 100 * 100;
  for (int i = 1; i <= n; i++) {
    if (ships_per_column[i] == max_ships_per_column) {
      int moves = move_ships(field, ships, i);
      if (moves < min_moves) {
        min_moves = moves;
      }
    }
  }
  std::cout << min_moves << std::endl;
  return 0;
}