#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

long cal_one_column_len(std::vector<long> a, long column_width) {
  long len = 0;
  long row = 0;
  long n = a.size();
  bool done = false;
  for (int i = 0; i < n; i++) {
    while (!done && (a[i] + len <= column_width)) {
      len += a[i++] + 1;
      if (i == n) done = true;
    }
    if (!done && a[i] > column_width) {
      row = LONG_MAX;
      break;
    }
    i--;
    row++;
    len = 0;
  }
  return row;
}
long calc_report_len(long w, std::vector<long> a, std::vector<long> b,
                     long column) {
  long row = cal_one_column_len(a, column);
  long row_2 = cal_one_column_len(b, w - column);
  return std::max(row, row_2);
}
long calc_min_len_left(long w, long n, long m, std::vector<long> a,
                       std::vector<long> b) {
  long l = 1;
  long r = w;
  //   long prev_a = 0, prev_b = 0;
  while (l < r) {
    long mid = (l + r) / 2;
    long col_a = cal_one_column_len(a, mid);
    long col_b = cal_one_column_len(b, w - mid);
    if (col_a <= col_b) {
      r = mid;
    } else {
      l = mid + 1;
    }
    // prev_a = col_a;
    // prev_b = col_b;
  }
  return calc_report_len(w, a, b, l);
}

long calc_min_len_right(long w, long n, long m, std::vector<long> a,
                        std::vector<long> b) {
  long l = 1;
  long r = w;
  //   long prev_a = 0, prev_b = 0;
  while (l < r) {
    long mid = (l + r + 1) / 2;
    long col_a = cal_one_column_len(a, mid);
    long col_b = cal_one_column_len(b, w - mid);
    if (col_a <= col_b) {
      r = mid - 1;
    } else {
      l = mid;
    }
    // prev_a = col_a;
    // prev_b = col_b;
  }
  return calc_report_len(w, a, b, l);
}

int main(void) {
  long w, n, m;
  std::cin >> w >> n >> m;
  std::vector<long> a(n);
  std::vector<long> b(m);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }
  std::cout << std::min(calc_min_len_left(w, n, m, a, b),
                        calc_min_len_right(w, n, m, a, b));

  return 0;
}