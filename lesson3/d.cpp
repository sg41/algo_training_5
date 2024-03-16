#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
int main(void) {
  int n, k;
  std::cin >> n >> k;
  long long a;
  std::map<long long, std::pair<int, int>> repeats;
  bool yes = false;
  for (int i = 0; i < n; i++) {
    std::cin >> a;
    repeats[a].second++;
    if (repeats[a].second >= 2) {
      if (i - repeats[a].first <= k) {
        yes = true;
        break;
      }
    }
    repeats[a].first = i;
  }
  if (yes) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }

  return 0;
}