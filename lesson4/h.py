n = int(input())

min_cost = float('inf')
best_party = -1
final_votes = []

for i in range(n):
    vi, pi = map(int, input().split())

    # Calculate the maximum votes across all parties (including pi = -1)
    max_votes = max(final_votes + [vi])
    required_votes = max_votes - vi + 1

    if pi != -1:  # Only consider cost if the party is open to bribery
        cost = pi + required_votes
        if cost < min_cost:
            min_cost = cost
            best_party = i + 1
            final_votes = [vi if j != i else vi +
                           required_votes for j in range(n)]

print(min_cost)
print(best_party)
print(*final_votes)
