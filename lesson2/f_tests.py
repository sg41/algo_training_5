import f
from contextlib import redirect_stdout
import io


def test1():
    task = """5
1 2 3 4 5
3 5 2
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 5


def test2():
    task = """5
1 2 3 4 5
15 15 2
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 4


def test3():
    task = """5
5 4 3 2 1
2 5 2
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 5


def test5():
    task = """9
707 805 279 713 584 352 923 1000 237
29 38 1
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 1000


def test28():
    task = """37
855 823 932 142 700 675 567 336 167 11 397 535 683 923 561 192 632 759 25 518 653 392 740 494 279 396 575 173 392 81 879 424 619 830 904 704 764
256446299 276722589 1351753
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 923


def test38():
    task = """95
467 82 925 465 738 918 810 693 167 434 327 624 440 514 383 420 821 488 74 78 538 316 986 77 201 967 370 930 177 925 476 17 287 761 805 101 439 474 806 185 351 3 786 731 872 569 159 251 66 341 243 769 124 465 893 573 900 807 428 512 785 333 440 328 426 229 907 408 858 417 571 46 803 908 912 373 684 627 852 547 209 266 652 189 141 835 274 767 903 449 523 864 742 10 500
43023377 192443105 1697952
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 986


def test9():
    task = """9
925 160 322 433 698 458 923 877 741
46 92 12
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 923  # ! don't know right answer


def test22():
    task = """8
952 159 945 463 133 101 767 314
47 448 28
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 952  # ! don't know right answer


def test10():
    task = """4
744 43 468 382
20 48 12
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 468


def test14():
    task = """34
56 1000 528 720 895 209 805 65 370 923 541 431 528 778 670 761 794 49 488 171 438 325 57 717 293 847 535 306 398 757 888 56 916 999
391 901 26
"""
    lines = task.split("\n")
    n = int(lines[0])
    ring = list(map(int, lines[1].split()))
    a, b, k = map(int, lines[2].split())
    s = f.calculate_winnings(n, ring, a, b, k)

    assert s == 1000
