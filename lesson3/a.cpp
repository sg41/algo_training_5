#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>
int main(void) {
  int n;
  std::cin >> n;
  std::vector<std::set<std::string>> playlist(n);
  for (int i = 0; i < n; i++) {
    int k;
    std::cin >> k;
    for (int j = 0; j < k; j++) {
      std::string song;
      std::cin >> song;
      playlist[i].insert(song);
    }
  }
  std::set<std::string> result{playlist[0]};
  for (int i = 1; i < n; i++) {
    std::set<std::string> current_result;
    std::set_intersection(
        playlist[i].begin(), playlist[i].end(), result.begin(), result.end(),
        std::inserter(current_result, current_result.begin()));
    result = current_result;
    if (result.size() == 0) {
      break;
    }
  }
  std::cout << result.size() << std::endl;
  for (auto song : result) {
    std::cout << song << " ";
  }
  return 0;
}