from typing import List


def calculate_winnings(n: int, sectors: List[int], a: int, b: int, k: int) -> int:
    max_winning = 0
    max_sectors = b // k + (b % k != 0)  # 1   if b % k != 0 else b // k - 1
    max_finish_right = max_sectors % n - 1 if max_sectors % n != 0 else 0
    max_finish_left = n - max_finish_right
    min_sectors = a // k + (a % k != 0)  # 1   if a % k != 0 else a // k - 1
    min_finish_right = min_sectors % n - 1 if min_sectors % n != 0 else 0
    min_finish_left = n - min_finish_right if min_finish_right != 0 else 0
    if max_sectors - min_sectors >= n - 1:
        max_winning = max(sectors)
    else:
        for i in range(max_sectors-min_sectors+1):
            index = (i + min_finish_right) % n
            max_winning = max(max_winning, sectors[index])
            index = min_finish_left-i
            max_winning = max(max_winning, sectors[index])

    return max_winning


if __name__ == "__main__":
    n = int(input())
    sectors = list(map(int, input().split()))
    a, b, k = map(int, input().split())
    print(calculate_winnings(n, sectors, a, b, k))
