
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
    if (match[0].startswith("\"")):
        # match_info = match[0].split()
        match_info = re.search(
            r"(\"[^\"]+\") - (\"[^\"]+\") (\d+:\d+)", match[0]).groups()
        team1_name = match_info[0]
        team2_name = match_info[1]
        game_score = list(map(int, match_info[2].split(":")))
        team1_goals = game_score[0]
        team2_goals = game_score[1]
        team_matches[team1_name] = team_matches.get(team1_name, 0) + 1
        team_matches[team2_name] = team_matches.get(team2_name, 0) + 1
        team_goals[team1_name] = team_goals.get(team1_name, 0) + team1_goals
        team_goals[team2_name] = team_goals.get(team2_name, 0) + team2_goals
        open_time1 = 999
        open_time2 = 999
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
        if team1_goals != 0 and open_time1 < open_time2:
            player_opens[open_player1] = player_opens.get(open_player1, 0) + 1
            team_opens[team1_name] = team_opens.get(team1_name, 0) + 1
        elif team2_goals != 0 and open_time1 > open_time2:
            player_opens[open_player2] = player_opens.get(open_player2, 0) + 1
            team_opens[team2_name] = team_opens.get(team2_name, 0) + 1
        match = match[team1_goals + team2_goals + 1:]
    parse_questions(match)


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
                print(sum(player_goals.get(player_name, {}).values()))
            case ["Mean", "goals", "per", "game", "by", *player_name]:
                player_name = " ".join(player_name)
                print(
                    f"{sum(player_goals.get(player_name, {}).values()) / team_matches[player_team[player_name]]:.3f}")
            case ["Goals", "on", "minute", minute, "by", *player_name]:
                player_name = " ".join(player_name)
                print(player_goals.get(player_name, {}).get(int(minute), 0))
                # print(player_goals[player_name][int(minute)])
            case ["Goals", "on", "first", minutes, "minutes", "by", *player_name]:
                player_name = " ".join(player_name)
                print(
                    sum(goal for goal in (player_goals.get(player_name, {})[i] for i in player_goals.get(player_name, {}).keys() if i <= int(minutes))))
            case ["Goals", "on", "last", minutes, "minutes", "by", *player_name]:
                player_name = " ".join(player_name)
                print(
                    sum(goal for goal in (player_goals.get(player_name, {})[i] for i in player_goals.get(player_name, {}).keys() if i >= (91-int(minutes)))))
            case ["Score", "opens", "by", *name]:
                name = " ".join(name)
                if name.startswith("\""):
                    print(team_opens.get(name, 0))
                else:
                    print(player_opens.get(name, 0))


def parse_data(data):
    lines = data.split("\n")
    matches = []
    match = []
    for i, line in enumerate(lines):
        if i != 0 and line.startswith("\""):
            matches.append("\n".join(match))
            match = []
        match.append(line)
    else:
        matches.append("\n".join(match))

    for match in matches:
        parse_match(match.split("\n"))


if __name__ == "__main__":
    data = stdin.read()
    parse_data(data)
