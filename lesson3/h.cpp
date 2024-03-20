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
} stick;

using Coord = std::pair<int, int>;

namespace std {
template <>
class hash<std::pair<Coord, Coord>> {
 public:
  size_t operator()(const std::pair<Coord, Coord>& s) const {
    size_t h1 = std::hash<int>()(s.first.first);
    size_t h2 = std::hash<int>()(s.first.second);
    size_t h3 = std::hash<int>()(s.second.first);
    size_t h4 = std::hash<int>()(s.second.second);
    return (h1 << 18) + (h2 << 12) + (h3 << 6) + h4;
  }
};
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

int move_picture(
    const std::vector<std::pair<Coord, Coord>>& a_coord,
    const std::vector<std::pair<Coord, Coord>>& b_coord, int ai, int bi,
    const std::unordered_set<std::pair<Coord, Coord>>& b_set_coord) {
  int count = 0;
  int dx = b_coord[bi].first.first - a_coord[ai].first.first;
  int dy = b_coord[bi].first.second - a_coord[ai].first.second;
  std::pair<Coord, Coord> a_coord_new;
  for (int j = 0; j < a_coord.size(); j++) {
    // if (i == j) continue;
    a_coord_new = a_coord[j];
    a_coord_new.first.first += dx;
    a_coord_new.first.second += dy;
    if (b_set_coord.contains(a_coord_new)) {
      count++;
    }
  }
  return count;
}
int main(void) {
  int n;
  std::cin >> n;
  std::vector<stick> a(n), b(n);
  std::vector<std::pair<Coord, Coord>> a_coord(n);
  std::vector<std::pair<Coord, Coord>> b_coord(n);
  std::unordered_set<std::pair<Coord, Coord>> b_set_coord(n);
  std::vector<std::pair<int, int>> a_vector(n);
  std::vector<std::pair<int, int>> b_vector(n);
  std::unordered_set<std::pair<int, int>> a_set_vector(n);
  std::unordered_set<std::pair<int, int>> used_point(n);
  std::unordered_map<std::pair<int, int>, std::vector<int>> a_map_vector(n);
  std::unordered_map<std::pair<int, int>, std::vector<int>> b_map_vector(n);

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
    a_set_vector.insert(a_vector[i]);
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
    b_set_coord.insert(b_coord[i]);
    b_map_vector[b_vector[i]].push_back(i);
  }

  int done_count = 0;

  for (auto [key, b_list] : b_map_vector) {
    auto a_list = a_map_vector[key];
    for (int i = 0; i < std::min(a_list.size(), b_list.size()); i++) {
      done_count = std::max(
          done_count,
          move_picture(a_coord, b_coord, a_list[i], b_list[i], b_set_coord));
    }
  }

  std::cout << n - done_count << std::endl;
}