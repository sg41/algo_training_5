#include <algorithm>
#include <cmath>
#include <iostream>
int decrease_or_zero(int a, int b) { return a - b >= 0 ? a - b : 0; };
int count_moves(int x, int y, int p, int delay) {
  int e = 0, r = 0;
  int prev_x = x, prev_y = y, prev_e = e;
  for (; x > 0 && (y > 0 || e > 0); r++) {
    if (e <= x) {
      int reminder = x - y;
      //   if (y <= x && ((x >= 10 && x > std::ceil(((1.0 + std::sqrt(5.)) / 2.)
      //   *
      //                                            (e - reminder)) ||
      //                   ((x < 10 || x == 78) && x > 1.618 * (e -
      //                   reminder))))) {
      //   if (y <= x && (double)x > ((1.0 + std::sqrt(5.)) / 2. * (e -
      //   reminder))) {
      double k = ((1.0 + std::sqrt(5.)) / 2.) * (e - reminder) + delay;
      //   if (round) k = std::ceil(k);
      if (y <= x && x > k) {
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

  int r1 = count_moves(x, y, p, 0);
  int r2 = count_moves(x, y, p, 1);
  int r;
  if (r1 > 0 && r2 > 0)
    r = std::min(r1, r2);
  else
    r = std::max(r1, r2);
  std::cout << r << std::endl;

  return 0;
}