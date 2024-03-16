#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
int main(void) {
  std::string s1, s2;
  std::cin >> s1 >> s2;
  std::map<char, int> m1, m2;
  for (auto c : s1) {
    m1[c]++;
  }
  for (auto c : s2) {
    m2[c]++;
  }
  if (m1 == m2) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}