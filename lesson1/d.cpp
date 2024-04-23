/*
На шахматной доске стоят слоны и ладьи, необходимо посчитать, сколько клеток не
бьется ни одной из фигур.

Шахматная доска имеет размеры 8 на 8. Ладья бьет все клетки горизонтали и
вертикали, проходящих через клетку, где она стоит, до первой встретившейся
фигуры. Слон бьет все клетки обеих диагоналей, проходящих через клетку, где он
стоит, до первой встретившейся фигуры.

Формат ввода
В первых восьми строках ввода описывается шахматная доска. Первые восемь
символов каждой из этих строк описывают состояние соответствующей горизонтали:
символ B (заглавная латинская буква) означает, что в клетке стоит слон, символ R
— ладья, символ * — что клетка пуста. После описания горизонтали в строке могут
идти пробелы, однако длина каждой строки не превышает 250 символов. После
описания доски в файле могут быть пустые строки.

Формат вывода
Выведите количество пустых клеток, которые не бьются ни одной из фигур.
Ввод:
********
********
*R******
********
********
********
********
********
Вывод:
49
Ввод:
********
********
******B*
********
********
********
********
********
Вывод:
54
Ввод:
********
*R******
********
*****B**
********
********
********
********
Вывод:
40
*/
#include <iostream>
#include <string>
#include <vector>
int mark_rook(int y, int x, std::vector<std::string>& field) {
  int res = 0;
  for (int r = y + 1; r < 8; r++) {
    if (field[r][x] == '*' || field[r][x] == '+') {
      res++;
      field[r][x] = '+';
    } else {
      break;
    }
  }
  for (int r = y - 1; r >= 0; r--) {
    if (field[r][x] == '*' || field[r][x] == '+') {
      res++;
      field[r][x] = '+';
    } else {
      break;
    }
  }
  for (int c = x + 1; c < 8; c++) {
    if (field[y][c] == '*' || field[y][c] == '+') {
      res++;
      field[y][c] = '+';
    } else {
      break;
    }
  }
  for (int c = x - 1; c >= 0; c--) {
    if (field[y][c] == '*' || field[y][c] == '+') {
      res++;
      field[y][c] = '+';
    } else {
      break;
    }
  }
  return res;
}
int mark_bishop(int y, int x, std::vector<std::string>& field) {
  int res = 0;
  for (int r = y + 1, c = x + 1; r < 8 && c < 8; r++, c++) {
    if (field[r][c] == '*' || field[r][c] == '+') {
      res++;
      field[r][c] = '+';
    } else {
      break;
    }
  }
  for (int r = y - 1, c = x + 1; r >= 0 && c < 8; r--, c++) {
    if (field[r][c] == '*' || field[r][c] == '+') {
      res++;
      field[r][c] = '+';
    } else {
      break;
    }
  }
  for (int r = y + 1, c = x - 1; r < 8 && c >= 0; r++, c--) {
    if (field[r][c] == '*' || field[r][c] == '+') {
      res++;
      field[r][c] = '+';
    } else {
      break;
    }
  }
  for (int r = y - 1, c = x - 1; r >= 0 && c >= 0; r--, c--) {
    if (field[r][c] == '*' || field[r][c] == '+') {
      res++;
      field[r][c] = '+';
    } else {
      break;
    }
  }
  return res;
}
int main(void) {
  std::vector<std::string> field;
  std::vector<std::pair<int, int>> rooks;
  std::vector<std::pair<int, int>> bishops;
  for (int r = 0; r < 8; r++) {
    std::string s;
    std::cin >> s;
    s.resize(8);
    field.push_back(s);
    for (int c = 0; c < s.size(); ++c) {
      if (s[c] == 'R')
        rooks.push_back({c, r});
      else if (s[c] == 'B')
        bishops.push_back({c, r});
    }
  }
  for (auto rook : rooks) {
    mark_rook(rook.second, rook.first, field);
  }
  for (auto bishop : bishops) {
    mark_bishop(bishop.second, bishop.first, field);
  }
  int res = 0;
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      if (field[r][c] == '*') res++;
    }
  }
  std::cout << res << std::endl;

  return 0;
}