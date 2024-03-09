#include <iostream>
#include <vector>
int main(void) {
  int t;
  std::cin >> t;
  std::vector<std::vector<int>> len(t, std::vector<int>(1, 0));
  for (int i = 0; i < t; i++) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    // std::vector<int> len(1);
    // len[0] = 0;
    int k = 0;
    int min = 10e6;
    for (int j = 0; j < n; j++) {
      std::cin >> a[j];
      if (a[j] <= len[i][k]) {
        k++;
        len[i].push_back(1);
        min = a[j];
      } else if (a[j] > len[i][k]) {
        if (a[j] < min) {
          min = a[j];
        }
        if (min < len[i][k] + 1) {
          k++;
          len[i].push_back(1);
          min = a[j];
          continue;
        }
        len[i][k]++;
        if (min == len[i][k]) {
          k++;
          len[i].push_back(0);
          min = 10e6;
        }
      }
    }
    if (len[i].back() == 0) len[i].pop_back();
  }
  for (int i = 0; i < t; i++) {
    std::cout << len[i].size() << "\n";
    for (auto l : len[i]) {
      std::cout << l << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}