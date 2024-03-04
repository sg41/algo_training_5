#include <iostream>
int main(void) {
  long double L, x1, v1, x2, v2;
  std::cin >> L >> x1 >> v1 >> x2 >> v2;
  long double time = -1;
  if (v1 - v2 != 0) {
    time = (x2 - x1) / (v1 - v2);
    std::cout.precision(10);
    std::cout << "YES\n" << time << "\n";
  } else {
    std::cout << "No";
  }
  return 0;
}