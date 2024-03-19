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
    return h1 * 100000 + h2 * 10000 + h3 * 1000 + h4;
  }
};
}  // namespace std

int main(void) {
  int n;
  std::cin >> n;
  std::vector<stick> a(n), b(n);
  std::vector<std::pair<Coord, Coord>> a_vector_set(n);
  std::vector<std::pair<Coord, Coord>> a_vector_set_reverse(n);
  std::vector<std::pair<Coord, Coord>> b_vector_set(n);
  std::unordered_multiset<std::pair<Coord, Coord>> b_set(n);
  int start_x_a = 0, start_y_a = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    if (i == 0) {
      start_x_a = std::min(a[i].x1, a[i].x2);
      start_y_a = std::min(a[i].y1, a[i].y2);
    } else {
      start_x_a = std::min(start_x_a, std::min(a[i].x1, a[i].x2));
      start_y_a = std::min(start_y_a, std::min(a[i].y1, a[i].y2));
    }
    a_vector_set[i] = {
        std::make_pair(std::make_pair(a[i].x1, a[i].y1),
                       std::make_pair(a[i].x2 - a[i].x1, a[i].y2 - a[i].y1))};
    a_vector_set_reverse[i] = {
        std::make_pair(std::make_pair(a[i].x2, a[i].y2),
                       std::make_pair(a[i].x1 - a[i].x2, a[i].y1 - a[i].y2))};
  }
  int start_x_b, start_y_b;
  for (int i = 0; i < n; i++) {
    std::cin >> b[i].x1 >> b[i].y1 >> b[i].x2 >> b[i].y2;
    if (i == 0) {
      start_x_b = std::min(b[i].x1, b[i].x2);
      start_y_b = std::min(b[i].y1, b[i].y2);
    } else {
      start_x_b = std::min(start_x_b, std::min(b[i].x1, b[i].x2));
      start_y_b = std::min(start_y_b, std::min(b[i].y1, b[i].y2));
    }
    b_vector_set[i] = {
        std::make_pair(std::make_pair(b[i].x1, b[i].y1),
                       std::make_pair(b[i].x2 - b[i].x1, b[i].y2 - b[i].y1))};
  }

  for (int i = 0; i < n; i++) {
    a_vector_set[i].first.first += -start_x_a + start_x_b;
    a_vector_set[i].first.second += -start_y_a + start_y_b;
    a_vector_set_reverse[i].first.first += -start_x_a + start_x_b;
    a_vector_set_reverse[i].first.second += -start_y_a + start_y_b;
    // b_vector_set[i].first.first += start_x_a;
    // b_vector_set[i].second += start_y_a;
    b_set.insert(b_vector_set[i]);
  }

  int done_count = 0;
  for (int i = 0; i < n; i++) {
    if (std::find(b_set.begin(), b_set.end(), a_vector_set[i]) != b_set.end()) {
      done_count++;
    }
    if (std::find(b_set.begin(), b_set.end(), a_vector_set_reverse[i]) !=
        b_set.end()) {
      done_count++;
    }
  }

  std::cout << n - done_count << std::endl;
}