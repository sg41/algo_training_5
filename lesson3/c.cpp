#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::map<long, long> m;
  for (int i = 0; i < n; i++) {
    int a;
    std::cin >> a;
    m[a]++;
  }
  long digit = m.begin()->first;
  long count = m.begin()->second;
  long max = 0;
  long max_value = m.begin()->second;
  for (auto d = ++(m.begin()); d != m.end(); d++) {
    if (d->first - digit == 1 && d->second + count > max) {
      max = d->second + count;
    }
    if (d->second > max_value) {
      max_value = d->second;
    }
    digit = d->first;
    count = d->second;
  }
  if (max == 0) max = max_value;
  std::cout << n - max << std::endl;
  return 0;
}