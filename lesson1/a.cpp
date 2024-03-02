#include <algorithm>
#include <cmath>
#include <iostream>
int max_trees(int p, int v, int q, int m) {
  int vasya_start, vasya_end, masha_start, masha_end;
  m = std::abs(m);
  v = std::abs(v);
  if (q > p) {
    std::swap(p, q);
    std::swap(v, m);
  } else if (q == p) {
    return std::max(v, m) * 2 + 1;
  }
  vasya_start = p - v;
  vasya_end = p + v;
  masha_start = q - m;
  masha_end = q + m;
  if (vasya_start <= masha_end) {
    int global_start = std::min(vasya_start, masha_start);
    int global_end = std::max(vasya_end, masha_end);
    return std::abs(global_start) + std::abs(global_end) + 1;
  } else {
    return 2 * v + 2 * m + 2;
  }
}
int main(void) {
  int p, v, q, m;
  std::cin >> p >> v >> q >> m;
  std::cout << max_trees(p, v, q, m) << std::endl;
  return 0;
}
