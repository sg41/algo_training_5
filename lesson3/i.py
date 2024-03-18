
import re
from sys import stdin

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
player_goals = {}
player_team = {}
player_opens = {}


def parse_match(match):
    match_info = match[0].split()
    team1_name = match_info[0]
    team2_name = match_info[2]
    game_score = list(map(int, match_info[3].split(":")))
    team1_goals = game_score[0]
    team2_goals = game_score[1]
    team_matches[team1_name] = team_matches.get(team1_name, 0) + 1
    team_matches[team2_name] = team_matches.get(team2_name, 0) + 1
    team_goals[team1_name] = team_goals.get(team1_name, 0) + team1_goals
    team_goals[team2_name] = team_goals.get(team2_name, 0) + team2_goals
    for i in range(team1_goals):
        goal_record = match[i + 1]
        goal_time = int(re.search(r"\d+", goal_record).group())
        player = re.search(r"^[^\d]+", goal_record).group().strip()
        player_team[player] = team1_name
        if player not in player_goals:
            player_goals[player] = {}
        player_goals[player][goal_time] = player_goals.get(
            player, {}).get(goal_time, 0) + 1
        if i == 0:
            open_time1 = goal_time
            open_player1 = player
    for i in range(team2_goals):
        goal_record = match[i + team1_goals + 1]
        goal_time = int(re.search(r"\d+", goal_record).group())
        player = re.search(r"^[^\d]+", goal_record).group().strip()
        player_team[player] = team2_name
        if player not in player_goals:
            player_goals[player] = {}
        player_goals[player][goal_time] = player_goals.get(
            player, {}).get(goal_time, 0) + 1
        if i == 0:
            open_time2 = goal_time
            open_player2 = player
    if open_time1 < open_time2:
        player_opens[open_player1] = player_opens.get(open_player1, 0) + 1
        team_opens[team1_name] = team_opens.get(team1_name, 0) + 1
    else:
        player_opens[open_player2] = player_opens.get(open_player2, 0) + 1
        team_opens[team2_name] = team_opens.get(team2_name, 0) + 1
    parse_questions(match[team1_goals + team2_goals + 1:])


def parse_questions(questions):
    for question in questions:
        match question.split():
            case ["Total", "goals", "for", *team_name]:
                team_name = " ".join(team_name)
                print(team_goals.get(team_name, 0))
            case ["Mean", "goals", "per", "game", "for", *team_name]:
                team_name = " ".join(team_name)
                print(
                    f"{team_goals.get(team_name, 0) / team_matches[team_name]:.3f}")
            case ["Total", "goals", "by", *player_name]:
                player_name = " ".join(player_name)
                print(player_goals.get(player_name, 0))
            case ["Mean", "goals", "per", "game", "by", *player_name]:
                player_name = " ".join(player_name)
                print(
                    f"{player_goals.get(player_name, 0) / team_matches[player_team[player_name]]:.3f}")
            case ["Goals", "on", "minute", minute, "by", player_name]:
                player_name = " ".join(player_name)
                print(player_goals[player_name][int(minute)])
            case ["Goals", "on", "first", minutes, "minutes", "by", *player_name]:
                player_name = " ".join(player_name)
                print(
                    sum(goal for goal in (player_goals[player_name][i] for i in range(int(minutes)+1))))


def parse_data(data):
    # matches = re.findall(r"^\".+\".+\".+\"[^\"]+", data, re.MULTILINE)
    lines = data.split("\n")
    matches = []
    match = []
    for i, line in enumerate(lines):
        match.append(line)
        if i == 0:
            continue
        if line.startswith("\""):
            match.pop(-1)
            matches.append("\n".join(match))
            match = []
    for match in matches:
        parse_match(match.split("\n"))


if __name__ == "__main__":
    data = stdin.read()
    parse_data(data)
