#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
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
bool check_h(long width, const std::vector<std::pair<long, long>>& tiles,
             long start_index, long h,
             const std::map<long, std::pair<long, long>>& down_top_min_max_x,
             const std::map<long, std::pair<long, long>>& top_down_min_max_x) {
  long start_y = tiles[start_index].second;
  long end_y = start_y + width - 1;
  long max = LONG_MIN, min = LONG_MAX;
  auto prew_row_ = down_top_min_max_x.lower_bound(start_y);
  if (--prew_row_ != down_top_min_max_x.end()) {
    max = std::max(max, prew_row_->second.second);
    min = std::min(min, prew_row_->second.first);
  }
  auto next_row_ = top_down_min_max_x.upper_bound(end_y);
  if (next_row_ != top_down_min_max_x.end()) {
    max = std::max(max, next_row_->second.second);
    min = std::min(min, next_row_->second.first);
  }
  long delta = max - min + 1;
  return delta <= width;
}

bool check_all(
    long width, const std::vector<std::pair<long, long>>& tiles,
    long start_index, long h,
    const std::map<long, std::pair<long, long>>& down_top_min_max_x,
    const std::map<long, std::pair<long, long>>& top_down_min_max_x) {
  bool result = false;
  for (int i = 0; i < tiles.size(); i++) {
    result =
        check_h(width, tiles, i, h, down_top_min_max_x, top_down_min_max_x);
    if (result) {
      break;
    }
  }
  return result;
}

long find_min_width(
    const std::vector<std::pair<long, long>>& tiles, long max_w, long i, long w,
    long h, const std::map<long, std::pair<long, long>>& down_top_min_max_x,
    const std::map<long, std::pair<long, long>>& top_down_min_max_x) {
  long start = 0, end = max_w;
  long mid = 0;
  while (start < end) {
    mid = (start + end) / 2;
    if (check_all(mid, tiles, i, h, down_top_min_max_x, top_down_min_max_x)) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

void fill_min_max_x(const std::vector<std::pair<long, long>>& tiles,
                    std::map<long, std::pair<long, long>>& row_min_max_x,
                    long i) {
  if (row_min_max_x[tiles[i].second] == std::make_pair(0l, 0l)) {
    row_min_max_x[tiles[i].second].first = tiles[i].first;
    row_min_max_x[tiles[i].second].second = tiles[i].first;
  } else {
    if (row_min_max_x[tiles[i].second].first > tiles[i].first) {
      row_min_max_x[tiles[i].second].first = tiles[i].first;
    } else if (row_min_max_x[tiles[i].second].second < tiles[i].first) {
      row_min_max_x[tiles[i].second].second = tiles[i].first;
    }
  }
}
int main(void) {
  long w, h, n;
  // std::ifstream f("12.txt");
  // f >> w >> h >> n;
  std::cin >> w >> h >> n;
  std::vector<std::pair<long, long>> tiles(n);
  std::map<long, std::pair<long, long>> down_top_min_max_x;
  std::map<long, std::pair<long, long>> top_down_min_max_x;

  for (int i = 0; i < n; i++) {
    // f >> tiles[i].first >> tiles[i].second;
    std::cin >> tiles[i].first >> tiles[i].second;
    fill_min_max_x(tiles, down_top_min_max_x, i);
    fill_min_max_x(tiles, top_down_min_max_x, i);
  }
  // f.close();
  std::sort(tiles.begin(), tiles.end(),
            [](const std::pair<long, long>& a, const std::pair<long, long>& b) {
              return a.second < b.second;
            });
  long cur_max = LONG_MIN, cur_min = LONG_MAX;
  for (long t = 0; t < tiles.size(); t++) {
    long i = tiles[t].second;
    cur_max = std::max(cur_max, down_top_min_max_x[i].second);
    cur_min = std::min(cur_min, down_top_min_max_x[i].first);
    down_top_min_max_x[i].second = cur_max;
    down_top_min_max_x[i].first = cur_min;
  }
  cur_max = LONG_MIN;
  cur_min = LONG_MAX;
  for (long t = tiles.size() - 1; t >= 0; t--) {
    long i = tiles[t].second;
    cur_max = std::max(cur_max, top_down_min_max_x[i].second);
    cur_min = std::min(cur_min, top_down_min_max_x[i].first);
    top_down_min_max_x[i].second = cur_max;
    top_down_min_max_x[i].first = cur_min;
  }

  long min = std::max(w, h);

  long width = find_min_width(tiles, std::min(w, h), 0, w, h,
                              down_top_min_max_x, top_down_min_max_x);
  std::cout << width;

  return 0;
}