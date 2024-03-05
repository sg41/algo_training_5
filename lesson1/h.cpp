#include <iostream>

int main(void) {
  long double L, x1, v1, x2, v2;
  std::cin >> L >> x1 >> v1 >> x2 >> v2;
  long double time = -1;

  if (x1 == x2 || x1 == L - x2) {
    time = 0;
  } else {  // different position
    long double t1 = -1, t2 = -1, r11, r12, r21, r22;
    long double c1, c2;
    if (v1 - v2 != 0) t1 = (x2 - x1) / (v1 - v2);
    if (v1 + v2 != 0) t2 = (L - x1 - x2) / (v1 + v2);
    r11 = x1 + v1 * t1;
    r12 = x2 + v2 * t1;
    r21 = x1 + v1 * t2;
    r22 = x2 + v2 * t2;
    // if(t1<0)  = (L+x2-x1) / (v1-v2);
    // if (t1 < 0) time = (L + x2 - x1) / (-v1 - v2);
    if (t1 < 0 && t2 >= 0)
      time = t2;
    else if (t1 >= 0 && t2 < 0)
      time = t1;
    else if (t1 >= 0 && t2 >= 0) {
      if (r11 == r12 && r21 + r22 == L)
        time = std::min(t1, t2);
      else if (r11 == r12)
        time = t1;
      else if (r21 + r22 == L)
        time = t2;
    }
  }
  std::cout.precision(10);
  if (time == -1)
    std::cout << "No";
  else
    std::cout << "YES\n" << time;
  return 0;
}