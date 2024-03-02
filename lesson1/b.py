match1 = input()
match2 = input()
first_game=input()
kHome=1
kAway=2
if first_game == kHome:
    score1_home, score2_away = map(int,match1.split(':'))
    score1_away, score2_home = map(int,match2.split(':'))
else:
    score1_away, score2_home = map(int,match1.split(':'))
    score1_home, score2_away = map(int,match2.split(':'))
total1 = score1_home + score1_away
total2 = score2_home + score2_away
goals_difference = score2_home+score2_away - score1_home - score1_away
if goals_difference == 0 :
    if score1_away > score2_away:
        print(0)
    else:
        print(1)
else:
    if total1 > total2:
        print(0)
    else:
        