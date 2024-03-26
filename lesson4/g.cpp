#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Info {
  int count_x;
  int count_y;
  int square;
};

bool check_cross(std::vector<std::vector<Info>>& metrics, int n, int m, int row,
                 int column, int width) {
  bool result = true;
  if (row + 3 * width - 1 > n || column + 3 * width - 1 > m) {
    return false;
  }
  if (metrics[row + 2 * width - 1][column + 3 * width - 1].count_x <
      3 * width) {
    return false;
  }
  if (metrics[row + 3 * width - 1][column + 2 * width - 1].count_y <
      3 * width) {
    return false;
  }
  for (int x = column; x < column + width; x++) {  // wings
    if (metrics[row + 2 * width - 1][x].count_y < width ||
        metrics[row + 2 * width - 1][x + 2 * width].count_y < width) {
      result = false;
      break;
    }
  }
  for (int x = column + width; x < column + 2 * width; x++) {
    if (metrics[row + 3 * width - 1][x].count_y < 3 * width) {
      result = false;
      break;
    }
  }
  return result;
}

bool check(std::vector<std::vector<Info>>& metrics, int n, int m, int k) {
  bool result;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      result = check_cross(metrics, n, m, i, j, k);
      if (result == true) {
        break;
      }
    }
    if (result == true) {
      break;
    }
  }
  return result;
}

int r_bin_search(std::vector<std::vector<Info>>& metrics, int n, int m) {
  int start = 1, end = std::min(n, m) / 3;
  while (start < end) {
    int mid = (start + end + 1) / 2;
    if (check(metrics, n, m, mid)) {
      start = mid;
    } else {
      end = mid - 1;
    }
  }
  return start;
}
int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> field(n);
  std::vector<std::vector<Info>> metrics(n + 2,
                                         std::vector<Info>(m + 2, {0, 0, 0}));
  for (int i = 1; i <= n; i++) {
    std::cin >> field[i - 1];
    for (int j = 1; j <= m; j++) {
      if (field[i - 1][j - 1] == '#') {
        metrics[i][j].count_x = metrics[i][j - 1].count_x + 1;
        metrics[i][j].count_y = metrics[i - 1][j].count_y + 1;
      }
    }
  }
  int k = r_bin_search(metrics, n, m);
  std::cout << k;
  return 0;
}
