#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef struct {
  int x1;
  int y1;
  int x2;
  int y2;
} Stick;

using Coord = std::pair<int, int>;

namespace std {
template <>
class hash<std::pair<int, int>> {
 public:
  size_t operator()(const std::pair<int, int>& s) const {
    size_t h1 = std::hash<int>()(s.first);
    size_t h2 = std::hash<int>()(s.second);
    return (h1 << 16) + h2;
  }
};
}  // namespace std

int main(void) {
  int n;
  std::cin >> n;
  std::vector<Stick> a(n), b(n);
  std::vector<std::pair<Coord, Coord>> a_coord(n);
  std::vector<std::pair<Coord, Coord>> b_coord(n);
  std::vector<std::pair<int, int>> a_vector(n);
  std::vector<std::pair<int, int>> b_vector(n);
  std::unordered_map<std::pair<int, int>, std::vector<int>> a_map_vector(n);
  std::unordered_map<std::pair<int, int>, std::vector<int>> b_map_vector(n);
  std::unordered_map<std::pair<int, int>, int> map_transfer(n * n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    if (a[i].x1 > a[i].x2) {
      std::swap(a[i].x1, a[i].x2);
      std::swap(a[i].y1, a[i].y2);
    } else if (a[i].x1 == a[i].x2 && a[i].y1 > a[i].y2) {
      std::swap(a[i].x1, a[i].x2);
      std::swap(a[i].y1, a[i].y2);
    }
    a_vector[i] = {std::make_pair(a[i].x2 - a[i].x1, a[i].y2 - a[i].y1)};
    a_coord[i] = {
        std::make_pair(std::make_pair(a[i].x1, a[i].y1), a_vector[i])};
    a_map_vector[a_vector[i]].push_back(i);
  }

  for (int i = 0; i < n; i++) {
    std::cin >> b[i].x1 >> b[i].y1 >> b[i].x2 >> b[i].y2;
    if (b[i].x1 > b[i].x2) {
      std::swap(b[i].x1, b[i].x2);
      std::swap(b[i].y1, b[i].y2);
    } else if (b[i].x1 == b[i].x2 && b[i].y1 > b[i].y2) {
      std::swap(b[i].x1, b[i].x2);
      std::swap(b[i].y1, b[i].y2);
    }
    b_vector[i] = {std::make_pair(b[i].x2 - b[i].x1, b[i].y2 - b[i].y1)};
    b_coord[i] = {
        std::make_pair(std::make_pair(b[i].x1, b[i].y1), b_vector[i])};
    b_map_vector[b_vector[i]].push_back(i);
  }

  int done_count = 0;

  for (auto [key, b_list] : b_map_vector) {
    for (auto bi : b_list) {
      for (auto aj : a_map_vector[key]) {
        int dx = a_coord[aj].first.first - b_coord[bi].first.first;
        int dy = a_coord[aj].first.second - b_coord[bi].first.second;
        map_transfer[std::make_pair(dx, dy)] += 1;
      }
    }
  }
  for (auto [key, value] : map_transfer) {
    if (value > done_count) done_count = value;
  }
  std::cout << n - done_count << std::endl;
}