#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using Berry = std::pair<long long, long long>;
using BerryIndex = std::pair<int, Berry>;
bool sort_by_height(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if (a.second.first > b.second.first) {
    result = true;
  } else if (a.second.first == b.second.first) {
    if (delta_a > delta_b) {
      result = true;
    }
  }
  return result;
}
bool sort_by_delta(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if (delta_a > delta_b) {
    result = true;
  } else if (delta_a == delta_b) {
    if (a.second.first < b.second.first) {
      result = true;
    }
  }
  return result;
}
bool sort_by_high_positive(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if ((delta_a >= 0 && delta_b >= 0) || (delta_a < 0 && delta_b < 0)) {
    if (a.second.first > b.second.first) {
      result = true;
    }
  } else if ((delta_a >= 0 && delta_b < 0)) {
    result = true;
  }
  return result;
}
bool sort_by_low_positive(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if ((delta_a >= 0 && delta_b >= 0)) {
    if (a.second.first < b.second.first) {
      result = true;
    }
  } else if ((delta_a >= 0 && delta_b < 0)) {
    result = true;
  } else if (delta_a < 0 && delta_b < 0) {
    if (a.second.first > b.second.first) {
      result = true;
    }
  }
  return result;
}
bool sort_by_positive_delta_first(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if (delta_a > 0) {
    if (a.first > b.first) result = true;
  } else if (delta_b < 0) {
    if (a.first > b.first) result = true;
  }
  return result;
}
bool sort_by_positive_second_first(BerryIndex a, BerryIndex b) {
  bool result = false;
  long long delta_a = a.second.first - a.second.second;
  long long delta_b = b.second.first - b.second.second;
  if (delta_a > 0) {
    if (a.second.second > b.second.second) result = true;
  } else if (delta_b < 0) {
    if (a.second.second > b.second.second) result = true;
  }
  return result;
}
std::pair<long long, long long> count_max_height(
    std::vector<BerryIndex> berry_index, long long start_max,
    long long start_height) {
  long long max_height = start_max;
  long long current_height = start_height;
  for (int i = 1; i < berry_index.size(); i++) {
    max_height =
        std::max(max_height, current_height + berry_index[i].second.first);
    current_height = current_height + berry_index[i].second.first -
                     berry_index[i].second.second;
  }
  return std::make_pair(max_height, current_height);
}
std::pair<long long, long long> count_max_height(
    std::vector<BerryIndex> berry_index,
    std::vector<BerryIndex> berry_index_minus) {
  long long max_height = 0;
  long long current_height = 0;
  for (int i = 0; i < berry_index.size(); i++) {
    max_height =
        std::max(max_height, current_height + berry_index[i].second.first);
    current_height = current_height + berry_index[i].second.first -
                     berry_index[i].second.second;
  }
  for (int i = 0; i < berry_index_minus.size(); i++) {
    max_height = std::max(max_height,
                          current_height + berry_index_minus[i].second.first);
    current_height = current_height + berry_index_minus[i].second.first -
                     berry_index_minus[i].second.second;
  }
  return std::make_pair(max_height, current_height);
}

long long dp(std::vector<BerryIndex>& berry_index) {
  int n = berry_index.size();
  std::vector<int> path(n + 1, 0);
  struct {
    long long h = 0;
    long long max = 0;
  } dp[n + 1][n];
  long long max = 0;
  long long max_h = 0;
  int max_h_index = 0;
  for (int i = 0; i < n; i++) {
    long long cur_max = max;
    long long cur_max_h = max_h;
    int cur_max_h_index = 0;
    for (int j = 0; j < n; j++) {
      dp[i][j].max = max_h + berry_index[j].second.first;
      dp[i][j].h = dp[i][j].max - berry_index[j].second.second;
      if (dp[i][j].max > cur_max_h) {
        cur_max_h_index = j;
        cur_max = dp[i][j].max;
        cur_max_h = dp[i][j].h;
        path[i] = j;
        berry_index[j].second.first = 0;
        berry_index[j].second.second = 0;
      }
    }
    max = cur_max;
    max_h = cur_max_h;
    max_h_index = cur_max_h_index;
  }
  return max;
}

int main(void) {
  int n;
  std::cin >> n;
  std::vector<Berry> berrys(n);
  std::vector<BerryIndex> berry_index(n);
  std::vector<BerryIndex> berry_index_plus;
  std::vector<BerryIndex> berry_index_minus;
  for (int i = 0; i < n; i++) {
    std::cin >> berrys[i].first >> berrys[i].second;
    berry_index[i].first = i;
    berry_index[i].second = berrys[i];
    if (berrys[i].first - berrys[i].second >= 0) {
      berry_index_plus.push_back(berry_index[i]);
    } else {
      berry_index_minus.push_back(berry_index[i]);
    }
  }
  // std::sort(berry_index_plus.begin(), berry_index_plus.end(),
  //           sort_by_low_positive);
  std::sort(berry_index_minus.begin(), berry_index_minus.end(),
            sort_by_low_positive);
  long long max_height, current_height;
  std::tie(max_height, current_height) =
      count_max_height(berry_index_plus, 0, 0);
  long long max_height2, current_height2;
  std::tie(max_height2, current_height2) =
      count_max_height(berry_index_minus, max_height, current_height);
  max_height += max_height2;
  for (int i = 0; i < berry_index_plus.size(); i++) {
    std::swap(berry_index_plus[i],
              berry_index_plus[berry_index_plus.size() - 1]);
    long long new_max, nex_height;
    std::tie(new_max, nex_height) =
        count_max_height(berry_index_plus, berry_index_minus);
    // long long new_max;
    // new_max = current_height + berry_index_plus[i].second.second;
    if (new_max > max_height) {
      max_height = new_max;
      // std::swap(berry_index_plus[i],
      //           berry_index_plus[berry_index_plus.size() - 1]);
    } else {
      std::swap(berry_index_plus[berry_index_plus.size() - 1],
                berry_index_plus[i]);
    }
  }

  // auto berry_index_copy = berry_index;
  // std::sort(berry_index.begin(), berry_index.end(), sort_by_low_positive);
  // long long max_heigt2 = count_max_height(berry_index);
  // if (max_heigt2 > max_height) {
  //   max_height = max_heigt2;
  // } else {
  //   berry_index = berry_index_copy;
  // }

  // max_height = dp(berry_index);

  std::cout << max_height << std::endl;
  // for (int i = 0; i < n; i++) {
  //   std::cout << berry_index[i].first + 1 << " ";
  // }
  for (auto berry : berry_index_plus) {
    std::cout << berry.first + 1 << " ";
  }
  for (auto berry : berry_index_minus) {
    std::cout << berry.first + 1 << " ";
  }
  std::cout << std::endl;
  return 0;
}