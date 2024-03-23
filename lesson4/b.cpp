#include <algorithm>
#include <iostream>
#include <vector>

long long sum(const std::vector<int> &a, int start, int length, long long s,
              const std::vector<long long> &pre_sum) {
  long long res =
      start + length - 1 < a.size()
          ? pre_sum[start + length - 1] - pre_sum[start] + a[start + length - 1]
          : s + 1;
  return res;
}

int l_bin_search(const std::vector<int> &a, long l, long long s,
                 const std::vector<long long> &pre_sum) {
  int start = 0, end = a.size() - 1;
  int mid = 0;
  while (start < end) {
    mid = (start + end) / 2;
    if (sum(a, mid, l, s, pre_sum) >= s) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return sum(a, start, l, s, pre_sum) == s ? start + 1 : -1;
}

int find_start_number(const std::vector<int> &a, long l, long long s,
                      const std::vector<long long> &pre_sum) {
  int start_number = l_bin_search(a, l, s, pre_sum);
  return start_number;
}
int main(void) {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  std::vector<long long> pre_sum(n, 0);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    if (i > 0) pre_sum[i] = pre_sum[i - 1] + a[i - 1];
  }

  std::vector<long> l(m);
  std::vector<long long> s(m);
  for (int i = 0; i < m; i++) {
    std::cin >> l[i] >> s[i];
  }

  for (int i = 0; i < m; i++) {
    std::cout << find_start_number(a, l[i], s[i], pre_sum) << "\n";
  }
  return 0;
}