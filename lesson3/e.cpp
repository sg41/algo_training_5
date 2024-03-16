#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
int main(void) {
  std::set<long> s[3];
  for (int i = 0; i < 3; i++) {
    int n;
    std::cin >> n;
    for (int j = 0; j < n; j++) {
      long a;
      std::cin >> a;
      s[i].insert(a);
    }
  }
  std::set<long> result1;
  std::set_intersection(s[0].begin(), s[0].end(), s[1].begin(), s[1].end(),
                        std::inserter(result1, result1.begin()));
  std::set<long> result2;
  std::set_intersection(s[1].begin(), s[1].end(), s[2].begin(), s[2].end(),
                        std::inserter(result2, result2.begin()));
  std::set<long> result3;
  std::set_intersection(s[0].begin(), s[0].end(), s[2].begin(), s[2].end(),
                        std::inserter(result3, result3.begin()));

  result3.insert(result1.begin(), result1.end());
  result3.insert(result2.begin(), result2.end());
  for (auto a : result3) {
    std::cout << a << " ";
  }

  return 0;
}