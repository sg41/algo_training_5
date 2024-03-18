
from typing import DefaultDict
querues = ["Total goals for <Название команды>",
           "Mean goals per game for <Название команды>",
           "Total goals by <Имя игрока>",
           "Mean goals per game by <Имя игрока>",
           "Goals on minute <Минута> by <Имя игрока>",
           "Goals on first <T> minutes by <Имя игрока>",
           "Goals on last <T> minutes by <Имя игрока>",
           "Score opens by <Название команды>",
           "Score opens by <Имя игрока>"]

team_matches = {}
team_goals = {}
team_opens = {}


def parse_match(match):
    match_info = input().split()
    team1_name = match_info[0]
    team2_name = match_info[2]
    game_score = list(map(int, match_info[3].split(":")))
    team1_goals = game_score[0]
    team2_goals = game_score[1]
    team_matches[team1_name] = team_matches.get(team1_name, 0) + 1
    team_matches[team2_name] = team_matches.get(team2_name, 0) + 1
    team_goals[team1_name] = team_goals.get(team1_name, 0) + team1_goals
    team_goals[team2_name] = team_goals.get(team2_name, 0) + team2_goals
