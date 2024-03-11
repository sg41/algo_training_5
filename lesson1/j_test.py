import j
from contextlib import redirect_stdout
import io


def test3():
    def test():
        j.place_images(100, 2, 3, """
    (image dx=10 dy=11 height=100 width=20 layout=floating)"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """10 11\n"""


def test12():
    def test():
        j.place_images(11, 3, 10,
                       """(image width=10 layout=embedded height=2)
(image width=10 layout=embedded height=2)
(image width=10 layout=embedded height=3)
(image width=10 layout=embedded height=4)
(image width=10 layout=embedded height=2)
(image width=10 layout=surrounded height=4)
(image width=10 layout=embedded height=2)

(image width=10 layout=embedded height=3)

(image width=10 layout=embedded height=4)

(image width=10 layout=surrounded height=2)

(image width=10 layout=surrounded height=2)"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """0 0
0 3
0 6
0 9
0 13
0 16
0 22
0 25
0 28
0 32
0 35\n"""


def test1():
    def test():
        j.place_images(120, 10, 8,
                       """start (image layout=embedded width=12 height=5)
(image layout=surrounded width=25 height=58)
and word is 
(image layout=floating dx=18 dy=-15 width=25 height=20)
here new 
(image layout=embedded width=20 height=22)
another
(image layout=embedded width=40 height=19)
longword

new paragraph
(image layout=surrounded width=5 height=30)
(image layout=floating width=20 height=35 dx=50 dy=-16)
"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """48 0
60 0
74 -5
32 20
0 52
104 81
100 65
"""


def test8():
    def test():
        j.place_images(1000, 50, 37,
                       """(image
height=2 dx=-6
width=40
layout=floating
dy=-339) sR'KtP; 6 V3lYk zK.d
q0OAIF;
R
Qv9B
n
W T
(image
layout=floating
dy=345
dx=10 height=12 width=23) O Z H2A (image dx=1 width=4
height=5 dy=-427 layout=floating) ;
!,ZjR Tgb e 3fC
H,o 81i
(image
width=33
height=30 dx=2 layout=floating
dy=-341)
!c?9P
,Bu
(image
dx=9
layout=floating dy=-499
height=92
width=26) Qn?qfqy
(image
layout=floating width=46
height=96
dy=-318
dx=-8) 1PJ
9
MiFJXKq
C
S k
-LE
X ..
!
L
(image
layout=floating height=60 dx=-2 width=3
dy=57)
e-ssyxs c
(image dy=-90
dx=10
width=38
layout=floating
height=82)
p
i E 8sCPZ
xhbNXYX L
4
L-MnJ!sE,b
-TlT
m A
,G'gw
NQH L 8
n (image layout=floating
width=7 dx=-3 height=62
dy=-345)
uNSp
'7b. (image
height=29
dy=169 width=50
layout=floating
dx=2)
P
(image dx=-7
height=58
width=7
dy=34
layout=floating)
"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """0 -339
750 395
112 -327
113 -191
490 -349
769 -168
960 257
343 160
700 5
150 569
215 434
"""


# def test17():
#     def test():
#         j.place_images(100, 3, 9,
#                        """N0l7G
# yyaA
# JX; (image height=7 layout=embedded width=4) bm
# (image
# height=7
# width=1 layout=surrounded) (image height=2 layout=surrounded
# width=4)
# (image
# height=8 width=2 layout=embedded)
# (image layout=floating
# width=7
# height=9
# dx=-10
# dy=7) Bd8KO
# X4Y nUAB Xyb2 (image width=5 height=8
# layout=embedded) (image dx=-10 width=8
# dy=4 height=3 layout=floating)
# (image
# dx=-2 layout=floating width=3
# dy=-6
# height=2) (image height=2
# width=1 layout=surrounded) (image
# width=2 layout=surrounded
# height=4) (image
# width=5 dy=3 layout=floating dx=8 height=7) (image
# height=10 layout=embedded
# width=3)
# (image
# width=5
# layout=embedded
# height=3) (image layout=surrounded
# height=1 width=3)
# (image
# layout=surrounded
# height=1 width=3)
# (image
# height=5 width=4
# layout=embedded)
# (image width=2
# height=2
# layout=embedded)
# (image layout=embedded
# height=10 width=5) HKWju h'5X (image
# height=3 width=4 layout=surrounded)
# """
#                        )
#     f = io.StringIO()
#     with redirect_stdout(f):
#         test()
#     s = f.getvalue()
#     assert s == """
# """


def test13():
    def test():
        j.place_images(20, 2, 1,
                       """(image layout=surrounded width=1 height=8) 0123 (image layout=surrounded width=1 height=5) 123 (image layout=surrounded width=1 height=100) 1234 (image layout=surrounded width=2 height=6)
321 (image layout=surrounded width=1 height=3) (image layout=embedded width=4 height=1)
ab
(image layout=embedded width=1 height=3) (image layout=embedded width=3 height=1)
(image layout=embedded width=5 height=1)
ab
(image layout=embedded width=2 height=1)
(image layout=embedded width=6 height=1)
(image layout=surrounded width=1 height=20)
ab
(image layout=surrounded width=1 height=20)
abcde
ab bc cd x
(image layout=surrounded width=1 height=30)
yzah
abc bc a cde
(image layout=surrounded width=2 height=1)
abc
(image layout=surrounded width=4 height=20)
bcd (image layout=surrounded width=2 height=20)
abcd
(image layout=embedded width=4 height=1)
(image layout=embedded width=5 height=1)
(image layout=embedded width=10 height=1)
(image layout=embedded width=11 height=1)
"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """0 0
5 0
9 0
14 0
19 0
1 2
10 2
16 2
1 5
10 5
1 7
7 7
12 7
14 9
18 11
3 13
18 13
10 29
0 33
10 39
0 101
"""


def test10():
    def test():
        j.place_images(21, 1, 1,
                       """(image width=13 height=2 layout=embedded)
(image width=2 height=2 layout=surrounded)
(image width=4 height=2 layout=embedded)

(image width=3 height=2 layout=surrounded)
(image width=12 height=2 layout=embedded)
(image width=4 height=2 layout=surrounded)

(image width=1 height=4 layout=embedded)
(image width=1 height=4 layout=surrounded)
(image width=1 height=4 layout=surrounded)
. ?
(image width=1 height=4 layout=surrounded)
(image width=1 height=4 layout=embedded)
(image width=1 height=4 layout=embedded)
!
(image width=1 height=4 layout=embedded)
"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """0 0
13 0
15 0
0 2
3 2
15 2
0 4
1 4
2 4
6 4
7 4
9 4
13 4
"""


def test4():
    def test():
        j.place_images(100, 2, 3,
                       """(image dx=-10 dy=11 height=100 width=20 layout=floating)
(image dx=0 dy=11 height=100 width=20 layout=floating)
(image dx=0 dy=11 height=100 width=20 layout=floating)
"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """0 11
20 22
40 33
"""
