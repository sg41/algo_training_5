// Сумма 2х нечетных = четное
// Произведение 2х нечетных = нечетное
// Сумма нечетного и четного = нечетное
// Произведение нечетного и четного = четное
//! Сумма 2х четных = четное
//! Произведение 2х четных = четное
#include <iostream>
#include <string>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<long long> a(n);
  static const int kEven = 0, kOdd = 1;
  int sum;
  std::string result;

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  sum = a[0] % 2 == kEven ? kEven : kOdd;
  for (int i = 1; i < n; ++i) {
    if (a[i] % 2 == kEven) {
      if (sum == kEven) {
        sum = kEven;
        result.append("+");
      } else {  // sum == kOdd
        sum = kOdd;
        result.append("+");
      }
    } else {  // a[i] % 2 == kOdd
      if (sum == kEven) {
        sum = kOdd;
        result.append("+");
      } else {  // sum == kOdd
        sum = kOdd;
        result.append("x");
      }
    }
  }
  std::cout << result << std::endl;

  return 0;
}
