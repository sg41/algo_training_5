def ships(n):
    return int((n * (n + 1) * (n + 2) // 6) + ((n + 1) * (n + 1) * (n + 1) - n*n*n - 1) // 6 - 1)


def r_bin_search(n):
    start = 0
    end = n
    mid = 0
    k = 0
    while start < end:
        mid = (start + end + 1) // 2
        k = ships(mid)
        if k > n:
            end = mid - 1
        else:
            start = mid
    return start


n = int(input())
print(r_bin_search(n))
