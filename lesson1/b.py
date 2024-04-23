"""
Раунд плей-офф между двумя командами состоит из двух матчей. 
Каждая команда проводит по одному матчу «дома» и «в гостях».
Выигрывает команда, забившая большее число мячей. 
Если же число забитых мячей совпадает, выигрывает команда, 
забившая больше мячей «в гостях». Если и это число мячей совпадает,
матч переходит в дополнительный тайм или серию пенальти.
Вам дан счёт первого матча, а также счёт текущей игры 
(которая ещё не завершилась). 
Помогите комментатору сообщить, сколько голов необходимо 
забить первой команде, чтобы победить, не переводя игру в дополнительное время.
Формат ввода
В первой строке записан счёт первого мачта в формате G1:G2, 
где G1 — число мячей, забитых первой командой, а G2 — число мячей,
забитых второй командой.
Во второй строке записан счёт второго (текущего) матча в аналогичном формате.
Все числа в записи счёта не превышают 5.
В третьей строке записано число 1, если первую игру первая команда 
провела «дома», или 2, если «в гостях».
Формат вывода
Выведите единственное целое число "— необходимое количество мячей.

Пример 1
Ввод: Вывод:
0:0 1
0:0
1

Объяснение:
В первом матче была ничья 0:0.
Сейчас счет также 0:0, а первая команда играет дома (второй матч).
Чтобы победить, первой команде достаточно забить 1 гол.
"""
match1 = input()
match2 = input()
first_game = int(input())
kHome = 1
kAway = 2
if first_game == kHome:
    score1_home, score2_away = map(int, match1.split(':'))
    score1_away, score2_home = map(int, match2.split(':'))
else:
    score1_away, score2_home = map(int, match1.split(':'))
    score1_home, score2_away = map(int, match2.split(':'))
total1 = score1_home + score1_away
total2 = score2_home + score2_away
goals_difference = total2 - total1
away_difference = score2_away - score1_away
if goals_difference == 0:
    if score1_away > score2_away:
        print(0)
    else:
        print(1)
else:
    if total1 > total2:
        print(0)
    else:  # we are loosing now
        if score1_away > score2_away:
            print(goals_difference)
        else:
            if first_game == kAway:  # playing home now
                print(goals_difference+1)
            else:  # playing away now
                if goals_difference > away_difference:
                    print(goals_difference)
                else:
                    print(goals_difference+1)
