// Сумма 2х нечетных = четное
// Произведение 2х нечетных = нечетное
// Сумма нечетного и четного = нечетное
// Произведение нечетного и четного = четное
// Сумма 2х четных = четное
// Произведение 2х четных = четное
#include <iostream>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  long sum = 0;
  long mult = 1;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    if (a[i] % 2 == 0) {
      sum += a[i];
    } else {
      mult *= a[i];
    }
  }
  std::cout << sum << " " << mult << std::endl;
  return 0;
}