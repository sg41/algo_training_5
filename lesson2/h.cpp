#include <iostream>
#include <tuple>
#include <vector>
std::pair<int, int> find_max(std::vector<std::vector<long long>> field,
                             int exclude_i, int exclude_j) {
  long long max = field[0][0];
  int imax = 0;
  int jmax = 0;
  for (int i = 0; i < field.size(); i++) {
    if (i == exclude_i) continue;
    for (int j = 0; j < field[i].size(); j++) {
      if (j == exclude_j) continue;
      if (field[i][j] > max) {
        max = field[i][j];
        imax = i;
        jmax = j;
      }
    }
  }
  return std::make_pair(imax, jmax);
}
int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<long long>> field(n, std::vector<long long>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> field[i][j];
    }
  }

  int imax[5], jmax[5];
  std::tie(imax[0], jmax[0]) = find_max(field, -1, -1);
  long long max[4];
  max[0] = field[imax[0]][jmax[0]];
  field[imax[0]][jmax[0]] = 0;
  std::tie(imax[4], jmax[4]) = find_max(field, -1, -1);
  if (imax[4] != imax[0] && jmax[4] != jmax[0]) {
    std::tie(imax[1], jmax[1]) = find_max(field, imax[0], -1);
    max[1] = field[imax[1]][jmax[1]];
  } else if (imax[4] == imax[0]) {
    std::tie(imax[1], jmax[1]) = find_max(field, imax[0], -1);
    max[1] = field[imax[1]][jmax[1]];
  } else if (jmax[4] == jmax[0]) {
    std::tie(imax[1], jmax[1]) = find_max(field, -1, jmax[0]);
    max[1] = field[imax[1]][jmax[1]];
  }
  std::tie(imax[2], jmax[2]) = find_max(field, imax[0], jmax[1]);
  max[2] = field[imax[2]][jmax[2]];

  std::tie(imax[3], jmax[3]) = find_max(field, imax[1], jmax[0]);
  max[3] = field[imax[3]][jmax[3]];
  if (max[2] > max[3]) {
    std::cout << imax[1] + 1 << " " << jmax[0] + 1 << std::endl;
  } else {
    std::cout << imax[0] + 1 << " " << jmax[1] + 1 << std::endl;
  }

  return 0;
}