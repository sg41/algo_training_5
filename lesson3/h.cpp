#include <algorithm>
#include <iostream>
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
    return h1 + h2 + h3 + h4;
  }
};
template <>
class hash<std::pair<int, int>> {
 public:
  size_t operator()(const std::pair<int, int>& s) const {
    size_t h1 = std::hash<int>()(s.first);
    size_t h2 = std::hash<int>()(s.second);
    return h1 + h2;
  }
};
}  // namespace std

int move_picture(
    const std::vector<std::pair<Coord, Coord>>& a_coord,
    const std::vector<std::pair<Coord, Coord>>& b_coord, int i,
    const std::unordered_multiset<std::pair<Coord, Coord>>& b_set_coord) {
  int count = 0;
  int dx = b_coord[i].first.first - a_coord[i].first.first;
  int dy = b_coord[i].first.second - a_coord[i].first.second;
  std::vector<std::pair<Coord, Coord>> a_coord_new(a_coord.size());
  for (int j = 0; j < a_coord.size(); j++) {
    a_coord_new[j] = a_coord[j];
    a_coord_new[j].first.first += dx;
    a_coord_new[j].first.second += dy;
    if (std::find(b_set_coord.begin(), b_set_coord.end(), a_coord_new[j]) !=
        b_set_coord.end()) {
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
  std::unordered_multiset<std::pair<Coord, Coord>> b_set_coord(n);
  std::vector<std::pair<int, int>> a_vector(n);
  std::vector<std::pair<int, int>> b_vector(n);
  std::unordered_multiset<std::pair<int, int>> a_set_vector(n);
  int start_x_a = 0, start_y_a = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    if(a[i].x1 > a[i].x2){
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
  }
  int start_x_b, start_y_b;
  for (int i = 0; i < n; i++) {
    std::cin >> b[i].x1 >> b[i].y1 >> b[i].x2 >> b[i].y2;
    if(b[i].x1 > b[i].x2){
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
  }

  int done_count = 0;
  for (int i = 0; i < n; i++) {
    if (std::find(a_set_vector.begin(), a_set_vector.end(), b_vector[i]) !=
        a_set_vector.end()) {
      done_count =
          std::max(done_count, move_picture(a_coord, b_coord, i, b_set_coord));
    }
  }

  std::cout << n - done_count << std::endl;
}