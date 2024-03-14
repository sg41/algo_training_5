#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
int move_ships(std::vector<std::vector<int>> field,
               std::vector<std::pair<int, int>> ships, int column) {
  int moves = 0;

  for (int s = ships.size(); s >= 0; s--) {
    if (ships[s].second == column) {
      std::swap(ships[s], ships.back());
      ships.pop_back();
    }
  }
  for (int r = 1; r < field.size(); r++) {
    if (field[r][column] == 1) {
      continue;
    }
    int h_moves = 101;
    int best_index = -1;
    for (int s = 0; s < ships.size(); s++) {
      if (ships[s].first == r && ships[s].second != column) {
        if (std::abs(ships[s].second - column) < h_moves) {
          h_moves = std::abs(ships[s].second - column);
          best_index = s;
        };
      }
    }
    if (best_index != -1) {
      std::swap(ships[best_index], ships.back());
      ships.pop_back();
      moves += h_moves;
      field[r][column] = 1;
    }
  }
  if (ships.size() > 0) {
    std::sort(ships.begin(), ships.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return a.first > b.first;
              });
    for (int r = 1; r < field.size(); r++) {
      if (field[r][column] == 1) {
        continue;
      }
      if (ships.back().second != column) {
        moves += std::abs(ships.back().first - r) +
                 std::abs(ships.back().second - column);
        ships.pop_back();
      }
    }
  }
  return moves;
}

int main(int argc, char* argv[]) {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> ships(n);
  std::vector<std::vector<int>> field(n + 1, std::vector<int>(n + 1, 0));
  for (int i = 0; i < n; i++) {
    std::cin >> ships[i].first >> ships[i].second;
    field[ships[i].first][ships[i].second] = 1;
  }
  if (argc > 1 && std::string(argv[1]) == "-v") {
    std::cout << std::string(n * 2, '-') << std::endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        std::cout << '|' << ((field[i][j] == 1) ? 'X' : ' ');
      }
      std::cout << '|' << std::endl;
      std::cout << std::string(n * 2, '-') << std::endl;
    }
  }

  int min_moves = 100 * 100;
  int best_index = 0;
  for (int i = 1; i <= n; i++) {
    int moves = move_ships(field, ships, i);
    if (moves < min_moves) {
      min_moves = moves;
      best_index = i;
    }
  }
  std::cout << min_moves << std::endl;
  return 0;
}