#include <cmath>
#include <iostream>
int decrease_or_zero(int a, int b) { return a - b >= 0 ? a - b : 0; };
int main(void) {
  int x, y, p;
  std::cin >> x >> y >> p;
  int e = 0, r = 0;
  int prev_x = x, prev_y = y, prev_e = e;
  for (; x > 0 && (y > 0 || e > 0); r++) {
    if (e <= x) {
      int reminder = x - y;
      if (y <= x && ((x >= 10 && x > std::ceil(((1.0 + std::sqrt(5.)) / 2.) *
                                               (e - reminder)) ||
                      (x < 10 && x > 1.618 * (e - reminder))))) {
        //   x > 1.618 * (e - reminder)) {
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
  if (x <= 0)
    std::cout << -1 << std::endl;
  else
    std::cout << r << std::endl;

  return 0;
}