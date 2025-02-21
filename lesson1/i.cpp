/*
Как же Илье надоело учиться! Сначала школа, потом университет...
Вот, наконец, наступил тот долгожданный день, когда Илье утром
не надо ехать на учебу. Но, к несчастью для Ильи, оказалось,
что после окончания университета начинается самое трудное —
надо устраиваться на работу.
Во всемирно известной фирме «Goondex», в которую устроился Илья,
принято очень много работать, в частности, для сотрудников
установлена шестидневная рабочая неделя. Но, в качестве бонуса,
«Goondex» каждый год предлагает своим сотрудникам выбрать любой
день недели в качестве выходного. В свою очередь, оставшиеся шесть
дней недели будут рабочими.
Илья сообразил, что с учётом государственных праздников (которые
всегда являются выходными) с помощью правильного выбора выходного
дня недели можно варьировать количество рабочих дней в году.
Теперь он хочет знать, какой день недели ему следует выбрать в
качестве выходного, чтобы отдыхать как можно больше дней в году,
или, наоборот, демонстрировать чудеса трудолюбия, работая по
максимуму.

Формат ввода
В первой строке входных данных находится одно целое число N
(0 ≤ N ≤ 366) — количество государственных праздников.
Во второй строке содержится одно целое число year
(1800 ≤ year ≤ 2100) — год, в который необходимо помочь Илье.
В каждой из последующих N строк расположено по паре чисел day month
(day — целое число, month — слово, между day и month ровно один
пробел), обозначающих, что день day месяца month является
государственным праздником.
В последней строке расположено слово — день недели первого
января в год year.
Гарантируется, что все даты указаны корректно (в том числе указанный
день недели первого января действительно является днём недели
первого января соответствующего года year) и все дни
государственных праздников различны.

Формат вывода
Выведите через пробел два дня недели — лучший и худший варианты дней
недели для выходного (то есть дни недели, для которых достигается
соответственно максимальное и минимальное количество выходных дней в
году). Если возможных вариантов ответа несколько, выведите любой из них.

Пример 1
Ввод
2
2015
1 January
8 January
Thursday

Вывод
Monday Thursday

Пример 2
Ввод
3
2013
1 January
8 January
15 January
Tuesday

Вывод
Monday Tuesday

Пример 3
Ввод
3
2013
6 February
13 February
20 February
Tuesday

Вывод
Tuesday Wednesday

Примечания
Рассмотрим подробно третий пример.
2013 год начинается и заканчивается во вторник (Tuesday), при этом
на вторник приходится 53 дня года, а на все остальные дни недели
–— по 52 дня. Все три государственных праздника выпадают на среду
(Wednesday). Если Илья выберет в качестве выходного дня вторник, то
в году у него будет 53 + 3 = 56 выходных дней (53 вторника и 3
государственных праздника). Если Илья выберет в качестве выходного
дня среду, то у него будет только 52 выходных дня. Если же Илья
выберет в качестве выходного дня любой другой день недели, то у
него будет 52 + 3 = 55 выходных дней.
Таким образом, лучший вариант для выходного дня — вторник, худший
— среда, и единственным правильным ответом в данном примере
является Tuesday Wednesday.
*/
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