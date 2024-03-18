#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <vector>

namespace std {
template <>
class hash<std::pair<long, long>> {
 public:
  size_t operator()(const std::pair<long, long>& s) const {
    size_t h1 = std::hash<long>()(s.first);
    size_t h2 = std::hash<long>()(s.second);
    return h1 + h2;  // h1 ^ (h2 << 1);
  }
};
}  // namespace std
bool check_quadrangle(long x1, long y1, long x2, long y2, long x3, long y3,
                      long x4, long y4) {
  long s1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  long s2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
  long s3 = (x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4);
  long s4 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
  long s5 = (x2 - x4) * (x2 - x4) + (y2 - y4) * (y2 - y4);
  long s6 = (x3 - x4) * (x3 - x4) + (y3 - y4) * (y3 - y4);
  return ((s1 == s3 && s4 == s6 && s1 == s4) && (s2 == s5 && s2 == 2 * s1)) ||
         ((s1 == s2 && s5 == s6 && s1 == s5) && (s3 == s4 && s3 == 2 * s1)) ||
         ((s1 == s6 && s1 == 2 * s2) && (s2 == s5 && s3 == s4 && s2 == s3));
}
int find_start_point(const std::vector<std::pair<long, long>>& points,
                     int start) {
  int result = -1;
  long x1 = points[start].first;
  long y1 = points[start].second;
  long x2 = points[start + 1].first;
  long y2 = points[start + 1].second;
  long x3 = points[start + 2].first;
  long y3 = points[start + 2].second;
  long s1 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  long s2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
  long s4 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);
  if (s1 == s2 && s4 == 2 * s1) {
    result = start;
  } else if (s1 == s4 && s2 == 2 * s1) {
    result = start + 1;
  } else if (s2 == s4 && s1 == 2 * s2) {
    result = start + 2;
  }
  return result;
}

bool check_triangle(const std::vector<std::pair<long, long>>& points,
                    int start) {
  if (find_start_point(points, start) != -1) {
    return true;
  }
  return false;
}

bool check_triangle(const std::pair<long, long>& p1,
                    const std::pair<long, long>& p2,
                    const std::pair<long, long>& p3) {
  return check_triangle({p1, p2, p3}, 0);
}

std::vector<std::pair<long, long>> get_quadrangle(
    const std::vector<std::pair<long, long>>& points, int start,
    int have_points = 1) {
  std::vector<std::pair<long, long>> result(4 - have_points);
  if (have_points == 1) {
    result[0] = {points[start].first + 1, points[start].second};
    result[1] = {points[start].first, points[start].second + 1};
    result[2] = {points[start].first + 1, points[start].second + 1};
  } else if (have_points == 2) {
    long v12x = points[start + 1].first - points[start].first;
    long v12y = points[start + 1].second - points[start].second;
    long v13x = v12y;
    long v13y = -v12x;
    result[0] = {points[start].first + v13x, points[start].second + v13y};
    result[1] = {result[0].first + v12x, result[0].second + v12y};
  } else if (have_points == 3) {
    long x1 = points[start].first;
    long y1 = points[start].second;
    long x2 = points[start + 1].first;
    long y2 = points[start + 1].second;
    long x3 = points[start + 2].first;
    long y3 = points[start + 2].second;
    long x4, y4;

    long v12 = (x1 - x2) * (y1 - y2);
    long v13 = (x1 - x3) * (y1 - y3);
    long v23 = (x2 - x3) * (y2 - y3);

    if (v12 == -v13) {
      x4 = x2 + x3 - x1;
      y4 = y2 + y3 - y1;
    } else if (v12 == -v23) {
      x4 = x1 + x3 - x2;
      y4 = y1 + y3 - y2;
    } else {
      x4 = x1 + x2 - x3;
      y4 = y1 + y2 - y3;
    }
    result[0] = {x4, y4};
  }
  return result;
}

std::vector<std::pair<long, long>> get_quadrangle(
    const std::pair<long, long>& p1, const std::pair<long, long>& p2,
    int direction = 1) {
  std::vector<std::pair<long, long>> result(2);
  long v12x = p2.first - p1.first;
  long v12y = p2.second - p1.second;
  long v13x;
  long v13y;
  if (direction == 1) {  // clockwise
    v13x = v12y;
    v13y = -v12x;
  } else {  // counterclockwise
    v13x = -v12y;
    v13y = v12x;
  }
  result[0] = {p1.first + v13x, p1.second + v13y};
  result[1] = {result[0].first + v12x, result[0].second + v12y};
  return result;
}

std::vector<std::pair<long, long>> get_quadrangle(
    const std::pair<long, long>& p1, const std::pair<long, long>& p2,
    const std::pair<long, long>& p3) {
  return get_quadrangle({p1, p2, p3}, 0, 1);
}
bool check_exists(const std::unordered_set<std::pair<long, long>>& points_set,
                  const std::vector<std::pair<long, long>>& points) {
  return (points_set.find(points[0]) != points_set.end() &&
          points_set.find(points[1]) != points_set.end());
}
int main(void) {
  int n;
  std::cin >> n;
  std::vector<std::pair<long, long>> points(n);
  std::unordered_set<std::pair<long, long>> points_set(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i].first >> points[i].second;
    points_set.insert(points[i]);
  }
  bool found = false;
  bool found_triangle = false;
  std::vector<std::pair<long, long>> result;
  if (n < 4) {
    if (n == 1) {
      result = get_quadrangle(points, 0, 1);
    } else if (n == 2) {
      result = get_quadrangle(points, 0, 2);
    } else if (n == 3) {
      if (check_triangle(points, 0)) {
        result = get_quadrangle(points, 0, 3);
      } else {
        result = get_quadrangle(points, 0, 2);
      }
    }
    found = true;
  } else {
    for (auto p1 = points.begin(); p1 != points.end(); ++p1) {
      for (auto p2 = p1 + 1; p2 != points.end(); ++p2) {
        std::vector<std::pair<long, long>> current_result[2];
        current_result[0] = get_quadrangle(*p1, *p2, 1);
        current_result[1] = get_quadrangle(*p1, *p2, -1);
        for (auto cr : current_result) {
          if (check_exists(points_set, cr)) {
            result.clear();
            found = true;
            break;
          } else if (points_set.find(cr[0]) != points_set.end()) {
            result = {cr[1]};
            found_triangle = true;
          } else if (points_set.find(cr[1]) != points_set.end()) {
            result = {cr[0]};
            found_triangle = true;
          }
        }
        if (found) {
          break;
        }
      }
      if (found) {
        break;
      }
    }

    if (found == false && found_triangle == false) {
      result = get_quadrangle(points, 0, 2);
    }
  }
  std::cout << result.size() << std::endl;
  for (auto p : result) {
    std::cout << p.first << " " << p.second << std::endl;
  }

  return 0;
}