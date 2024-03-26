#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

struct Point {
  double x;
  double y;
  double v;
};

double get_time_run(std::map<std::pair<double, double>, double> a,
                    std::pair<double, double> point, double eps) {
  double res = 0;
}

bool check_max_time(std::map<std::pair<double, double>, double> a,
                    std::pair<double, double> mid, double eps) {
  return get_time_run(a, mid, eps) > get_time_run(a, circle_point(mid, eps, radius);
}
Point find_best_radius(std::map<std::pair<double, double>, double> a,
                       double radius, double eps) {
  std::pair<double, double> start = circle_start(radius);
  std::pair<double, double> end = circle_end(radius);
  while (end.first - start.first > eps && end.second - start.second > eps) {
    std::pair<double, double> mid = circle_mid(start, end, radius);

    if (check_max_time(a, mid, eps)) {
      end = mid;
    } else {
      start = mid;
    }
  }
  return get_time_run(a, start, radius, eps);
}
double fbinsearch(double s, double e, double eps,
                  std::map<std::pair<double, double>, double> a) {
  while (e - s > eps) {
    double mid = (s + e) / 2;
    if (find_best_radius(a, mid, eps)) {
      s = mid;
    } else {
      e = mid;
    }
  }
  return s;
}
int mian(void) {
  double d, n;
  std::cin >> d >> n;
  std::map<std::pair<double, double>, double> a;
  for (int i = 0; i < n; i++) {
    double x, y, v;
    std::cin >> x >> y >> v;
    a[std::make_pair(x, y)] = v;
  }

  auto res = fbinsearch(0, d, 1e-5, a);
  return 0;
}