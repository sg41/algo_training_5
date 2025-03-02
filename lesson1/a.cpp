/*
Вася и Маша участвуют в субботнике и красят стволы деревьев в белый
цвет. Деревья растут вдоль улицы через равные промежутки в 1 метр. Одно
из деревьев обозначено числом ноль, деревья по одну сторону занумерованы
положительными числами 1, 2 и т.д., а в другую — отрицательными -1, -2 и
т.д.
Ведро с краской для Васи установили возле дерева P, а для Маши —
возле дерева Q. Ведра с краской очень тяжелые и Вася с Машей не могут их
переставить, поэтому они окунают кисть в ведро и уже с этой кистью идут
красить дерево. Краска на кисти из ведра Васи засыхает, когда он
удаляется от ведра более чем на V метров, а из ведра Маши — на M метров.
Определите, сколько деревьев может быть покрашено.

Формат ввода
В первой строке содержится два целых числа P и V — номер дерева, у которого
стоит ведро Васи и на сколько деревьев он может от него удаляться. В второй
строке содержится два целых числа Q и M — аналогичные данные для Маши. Все числа
целые и по модулю не превосходят 10^8.

Формат вывода
Выведите одно число — количество деревьев, которые могут быть покрашены.

Пример

Ввод: Вывод:
0 7 25
12 5

Объяснение:
Вася может покрасить деревья с номерами от -7 до 7 (15 деревьев).
Маша может покрасить деревья с номерами от 7 до 17 (11 деревьев).
Одно дерево (номер 7) они могут покрасить оба.
Итого: 15 + 11 - 1 = 25 деревьев.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
int max_trees(int p, int v, int q, int m) {
  int vasya_start, vasya_end, masha_start, masha_end;
  m = std::abs(m);
  v = std::abs(v);
  if (q > p) {
    std::swap(p, q);
    std::swap(v, m);
  } else if (q == p) {
    return std::max(v, m) * 2 + 1;
  }
  vasya_start = p - v;
  vasya_end = p + v;
  masha_start = q - m;
  masha_end = q + m;
  if (vasya_start <= masha_end) {
    int global_start = std::min(vasya_start, masha_start);
    int global_end = std::max(vasya_end, masha_end);
    return std::abs(global_start) + std::abs(global_end) + 1;
  } else {
    return 2 * v + 2 * m + 2;
  }
}
int main(void) {
  int p, v, q, m;
  std::cin >> p >> v >> q >> m;
  std::cout << max_trees(p, v, q, m) << std::endl;
  return 0;
}
