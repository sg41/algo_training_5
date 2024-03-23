#include <algorithm>
#include <iostream>
#include <vector>

int l_bin_search(const std::vector<int> &a, long l, long r) {
  int s = 0, e = a.size() - 1;
  int mid = 0;
  while (s < e) {
    mid = (s + e) / 2;
    if (a[mid] >= l) {
      e = mid;
    } else {
      s = mid + 1;
    }
  }
  return a[s] < l ? s + 1 : s;
}

int r_bin_search(const std::vector<int> &a, long l, long r) {
  int s = 0, e = a.size() - 1;
  int mid = 0;
  while (s < e) {
    mid = (s + e + 1) / 2;
    if (a[mid] > r) {
      e = mid - 1;
    } else {
      s = mid;
    }
  }
  return a[s] > r ? s - 1 : s;
}
int count(const std::vector<int> &a, long l, long r) {
  int count = 0;
  int s = l_bin_search(a, l, r);
  int e = r_bin_search(a, l, r);
  return e - s + 1;
}
int main(void) {
  int n, k;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::sort(a.begin(), a.end());
  std::cin >> k;
  std::vector<long> l(k);
  std::vector<long> r(k);
  for (int i = 0; i < k; i++) {
    std::cin >> l[i] >> r[i];
  }

  for (int i = 0; i < k; i++) {
    std::cout << count(a, l[i], r[i]) << " ";
  }
  return 0;
}