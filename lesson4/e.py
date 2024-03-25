def l_bin_search(start, end, n):
    mid = 0
    while start < end:
        mid = (start + end) // 2
        k = mid * (mid + 1) // 2
        if k >= n:
            end = mid
        else:
            start = mid + 1
    return start


def start_number(n):
    return (n + 1) * (n + 1) - n * (n + 3) // 2


n = int(input())
diagonal = l_bin_search(0, n, n)
position = n - start_number(diagonal - 1)
if diagonal % 2 == 0:
    row = diagonal - position
    column = position + 1
else:
    row = position + 1
    column = diagonal - position
print(f"{row}/{column}")
