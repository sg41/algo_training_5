#include <iomanip>
#include <iostream>

int main(void) {
  long double L, x1, v1, x2, v2;
  std::cin >> L >> x1 >> v1 >> x2 >> v2;
  long double time = -1;

  if (x1 == x2 || x1 == L - x2) {
    time = 0;
  } else {  // different position
    if (v1 == 0 & v2 == 0) {
    } else {
      long double t1 = -1, t2 = -1, r11, r12, r21, r22;
      long double c1, c2;
      if (v1 - v2 != 0) t1 = (x2 - x1) / (v1 - v2);
      if (v1 + v2 != 0) t2 = (L - x1 - x2) / (v1 + v2);

      if (t2 < 0 && v1 < 0 && v2 < 0) t2 = (-x1 - x2) / (v1 + v2);
      if (t1 < 0 && v1 - v2 != 0)
        t1 = std::min((L - x2 + x1) / std::abs(v1 - v2),
                      (L - x1 + x2) / std::abs(v1 - v2));
      if (t2 < 0 && v1 + v2 != 0) t2 = (2 * L - x2 - x1) / std::abs(v1 + v2);
      if (t1 >= 0 && t2 >= 0)
        time = std::min(t1, t2);
      else if (t1 >= 0 && t2 < 0)
        time = t1;
      else if (t1 < 0 && t2 >= 0)
        time = t2;
    }
  }
  if (time == -1)
    std::cout << "No";
  else
    printf("YES\n%.10Lf", time);
  return 0;
}