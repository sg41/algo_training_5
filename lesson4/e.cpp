#include <algorithm>
#include <iostream>
#include <vector>

long long l_bin_search(long long start, long long end, long long n) {
  // long long start = 0, end = n;
  long long mid = 0;
  long long k;
  while (start < end) {
    mid = (start + end) / 2;
    k = mid * (mid + 1) / 2;
    if (k >= n) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

long long start_number(long long n) {
  return (n + 1) * (n + 1) - n * (n + 3) / 2;
}

int main(void) {
  long long n;
  std::cin >> n;
  long long row, column, position;
  long long diagonal = l_bin_search(0, n, n);
  position = n - start_number(diagonal - 1);
  if (diagonal % 2 == 0) {
    row = diagonal - position;
    column = position + 1;
  } else {
    row = position + 1;
    column = diagonal - position;
  }
  std::cout << row << "/" << column;
  // std::cout << diagonal << " " << start_number(diagonal - 1) << " " <<
  // position
  //           << " " << row << " " << column << std::endl;

  return 0;
}