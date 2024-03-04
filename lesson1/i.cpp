#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(void) {
  std::map<std::string, int> days = {
      {"Monday", 0}, {"Tuesday", 0},  {"Wednesday", 0}, {"Thursday", 0},
      {"Friday", 0}, {"Saturday", 0}, {"Sunday", 0}};
  std::map<int, std::string> week_day_name = {
      {0, "Monday"}, {1, "Tuesday"},  {2, "Wednesday"}, {3, "Thursday"},
      {4, "Friday"}, {5, "Saturday"}, {6, "Sunday"}};
  std::map<std::string, int> week_day_number = {
      {"Monday", 0}, {"Tuesday", 1},  {"Wednesday", 2}, {"Thursday", 3},
      {"Friday", 4}, {"Saturday", 5}, {"Sunday", 6}};

  std::vector<int> month_days = {31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};

  std::map<int, std::string> month_name = {
      {0, "January"},   {1, "February"}, {2, "March"},     {3, "April"},
      {4, "May"},       {5, "June"},     {6, "July"},      {7, "August"},
      {8, "September"}, {9, "October"},  {10, "November"}, {11, "December"}};

  int N, year;
  std::cin >> N >> year;
  if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {
    month_days[1] = 29;
  }
  int total_days = 0;
  for (auto month : month_days) {
    total_days += month;
  }
  std::vector<std::pair<int, std::string>> holidays(N);
  for (int i = 0; i < N; i++) {
    std::cin >> holidays[i].first >> holidays[i].second;
  }
  std::string day_of_week;
  std::cin >> day_of_week;

  std::vector<bool> is_holiday(total_days, false);
  for (auto h : holidays) {
    int days = 0;
    for (int month = 0; month < 12; month++) {
      if (h.second != month_name[month]) {
        days += month_days[month];
      } else {
        days += h.first;
        break;
      }
    }
    is_holiday[days - 1] = true;
  }

  for (int i = week_day_number[day_of_week];
       i < total_days + week_day_number[day_of_week]; i++) {
    if (!is_holiday[i - week_day_number[day_of_week]])
      days[week_day_name[i % 7]]++;
  }
  int min = 367, max = -1;
  std::string imax, imin;
  int i = 0;
  for (auto d : days) {
    if (d.second > max) {
      max = d.second;
      imax = d.first;
    }
    if (d.second < min) {
      min = d.second;
      imin = d.first;
    }
    i++;
  }
  std::cout << imax << " " << imin << std::endl;
  return 0;
}