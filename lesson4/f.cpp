#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

long l_bin_serach(std::vector<std::pair<long, long>> a, long x) {
  long s = 0, e = a.size() - 1;
  long mid = 0;
  while (s < e) {
    mid = (s + e) / 2;
    if (a[mid].first >= x) {
      e = mid;
    } else {
      s = mid + 1;
    }
  }
  return a[s].first < x ? s + 1 : s;
}
long r_bin_serach(std::vector<std::pair<long, long>> a, long x) {
  long s = 0, e = a.size() - 1;
  long mid = 0;
  while (s < e) {
    mid = (s + e + 1) / 2;
    if (a[mid].first > x) {
      e = mid - 1;
    } else {
      s = mid;
    }
  }
  return s;  // a[s].first < x ? s + 1 : s;
}
bool check(long x_width, std::vector<std::pair<long, long>> tiles,
           long start_index) {
  long start_x = tiles[start_index].first;
  long end_index = r_bin_serach(tiles, start_x + x_width - 1);
  long max_y = LONG_MIN, min_y = LONG_MAX;
  if (end_index < tiles.size()) {
    for (int i = 0; i < start_index; i++) {
      if (max_y < tiles[i].second) max_y = tiles[i].second;
      if (min_y > tiles[i].second) min_y = tiles[i].second;
    }
    for (int i = end_index + 1; i < tiles.size(); i++) {
      if (max_y < tiles[i].second) max_y = tiles[i].second;
      if (min_y > tiles[i].second) min_y = tiles[i].second;
    }
  }
  long delta_y = max_y - min_y + 1;
  return delta_y <= x_width;
}

long find_min_width(std::vector<std::pair<long, long>> tiles, long max_w,
                    long i) {
  long start = 0, end = max_w;
  long mid = 0;
  while (start < end) {
    mid = (start + end) / 2;
    if (check(mid, tiles, i)) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return start;
}
int main(void) {
  long w, h, n;
  std::cin >> w >> h >> n;
  std::vector<std::pair<long, long>> tiles(n);
  for (int i = 0; i < n; i++) {
    std::cin >> tiles[i].first >> tiles[i].second;
  }
  std::sort(tiles.begin(), tiles.end());

  long min = std::max(w, h);
  for (int i = 0; i < n; i++) {
    long width = find_min_width(tiles, std::min(w, h), i);
    if (width < min) min = width;
  }
  std::cout << min;

  return 0;
}