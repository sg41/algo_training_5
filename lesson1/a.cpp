#include <algorithm>
#include <cmath>
#include <iostream>
int max_trees(int p, int v, int q, int m) {
  int vasya_start, vasya_end, masha_start, masha_end;
  int kt = 0;
  if (k < p) vasya_start = p - std::abs(v);
  vasya_end = p + std::abs(v);
  masha_start = q - std::abs(m);
  masha_end = q + std::abs(m);
  int global_start = std::min(vasya_start, masha_start);
  int global_end = std::max(vasya_end, masha_end);
  return std::abs(global_start) + std::abs(global_end) + 1;
}
int main(void) {
  int p, v, q, m;
  std::cin >> p >> v >> q >> m;
  std::cout << max_trees(p, v, q, m) << std::endl;
  return 0;
}
