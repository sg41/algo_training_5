#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
int decrease_or_zero(int a, int b) { return a - b >= 0 ? a - b : 0; };
int count_moves(int x, int y, int p, double delay) {
  int e = 0, r = 0;
  int prev_x = x, prev_y = y, prev_e = e;
  for (; x > 0 && (y > 0 || e > 0); r++) {
    if (e <= x) {
      int reminder = x - y;
      double k = ((1.0 + std::sqrt(5.)) / 2.) * (e - reminder) + delay;
      if (y <= x && x >= k) {
        y = 0;
        e = decrease_or_zero(e, reminder);
      } else {
        reminder = x - e;
        e = 0;
        y = decrease_or_zero(y, reminder);
      }
    } else {
      if (y <= x) {
        int remider = x - y;
        y = 0;
        e = decrease_or_zero(e, remider);
      } else {
        e = decrease_or_zero(e, x);
      }
    }
    x = decrease_or_zero(x, e);
    if (y > 0) {
      e += p;
    }
    if (prev_e == e && prev_x == x && prev_y == y) {
      x = -1;
      break;
    } else {
      prev_e = e;
      prev_x = x;
      prev_y = y;
    }
  }
  return x <= 0 ? -1 : r;
}
int main(void) {
  int x, y, p;
  std::cin >> x >> y >> p;

  std::vector<int> res;
  res.push_back(count_moves(x, y, p, 0));
  res.push_back(count_moves(x, y, p, 1));
  for (int i = 0; i < 40; i++) {
    res.push_back(count_moves(x, y, p, x * 0.025 * i));
  }
  std::sort(res.begin(), res.end());

  int result = -1;
  for (auto r : res) {
    if (r > 0) {
      result = r;
      break;
    }
  }

  std::cout << result << std::endl;

  return 0;
}