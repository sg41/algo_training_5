import j
from contextlib import redirect_stdout
import io


def test1():
    def test():
        j.place_images(100, 2, 3, """
    (image dx=10 dy=11 height=100 width=20 layout=floating)"""
                       )
    f = io.StringIO()
    with redirect_stdout(f):
        test()
    s = f.getvalue()
    assert s == """10 11\n"""


def test2():
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


def test3():
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
