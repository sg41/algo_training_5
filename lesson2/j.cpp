#include <iostream>
#include <string>
#include <vector>

bool check_corner(std::vector<std::vector<int>>& field, int i, int j) {
  int dx[4] = {0, 1, 0, -1};
  int dy[4] = {1, 0, -1, 0};
  int count = 0;
  for (int d = 0; d < 4; d++) {
    if (field[i + dx[d]][j + dy[d]] != 0) {
      count++;
    }
  }
  return count == 2 || count == 3 || count == 4;
}

bool check_top_left_corner(std::vector<std::vector<int>>& field, int i, int j,
                           int number = 1) {
  if (field[i - 1][j] != number && field[i][j - 1] != number) {
    return true;
  } else {
    return false;
  }
}
bool draw_rectangle(std::vector<std::vector<int>>& field, int i, int j,
                    int number) {
  bool result = true;
  int c = j;
  for (; c < field[i].size() && field[i][c] == 1; c++) {
    field[i][c] = number;
  }
  c--;
  int r = i + 1;
  for (; r < field.size(); r++) {
    // TODO use is_correct_cell function?
    if (field[r][j] == 1 && field[r][c] == 1 &&
        (field[r][j - 1] == 0 || field[r][c + 1] == 0)) {
      field[r][c] = number;
      field[r][j] = number;
    } else {
      break;
    }
  }

  for (int y = i + 1; y < r; y++) {
    for (int x = j; x <= c; x++) {
      if (field[y][x] == 1 || field[y][x] == number) {
        field[y][x] = number;
      } else {
        result = false;
        break;
      }
    }
    if (result == false) {
      break;
    }
  }
  return result;
}
bool check_picture(std::vector<std::vector<int>>& field, int n, int m) {
  bool result = true;
  int count = 0;
  std::vector<std::pair<int, int>> corners;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (field[i][j] == 1 && check_top_left_corner(field, i, j)) {
        result = draw_rectangle(field, i, j, ++count + 1);
        corners.push_back({i, j});
        if (count > 2) {
          result = false;
          break;
        }
        if (result == false) {
          break;
        }
      }
    }
    if (result == false) {
      break;
    }
  }
  if (count == 1) {
    int w = 0, h = 0;
    for (int i = corners[0].first; i <= n; i++) {
      if (field[i][corners[0].second] == 2) {
        h++;
      }
    }
    for (int j = corners[0].second; j <= m; j++) {
      if (field[corners[0].first][j] == 2) {
        w++;
      }
    }
    if (w == 1 && h == 1) {
      result = false;
    } else if ((w != 1 && h == 1) || (w == 1 && h != 1)) {
      field[corners[0].first][corners[0].second] = 3;
    } else {
      for (int i = corners[0].first; i < n - 1; i++) {
        field[i][corners[0].second] = 3;
      }
    }
  } else if (count == 0) {
    result = false;
  }
  return result;
}
int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> field(n);
  std::vector<std::vector<int>> field_int(n + 2, std::vector<int>(m + 2, 0));
  for (int i = 0; i < n; i++) {
    std::cin >> field[i];
    for (int j = 0; j < m; j++) {
      field_int[i + 1][j + 1] = field[i][j] == '.' ? 0 : 1;
    }
  }
  if (check_picture(field_int, n, m)) {
    std::cout << "YES" << std::endl;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        std::cout << (field_int[i][j] == 0   ? '.'
                      : field_int[i][j] == 2 ? 'a'
                      : field_int[i][j] == 3 ? 'b'
                                             : 'X');
      }
      std::cout << std::endl;
    }
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}