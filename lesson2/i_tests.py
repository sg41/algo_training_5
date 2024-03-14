import subprocess


def run_test(data, **kwargs):
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    if kwargs.get("comment") != None:
        print(kwargs.get("comment"))
    # print(data)
    # print(out)
    res = list(out.split("\n"))
    if kwargs.get("answer") != None and len(res) > 0:
        if int(res[-2]) != kwargs.get("answer"):
            print(f"WRONG ANSWER: {res[-2]} != {kwargs.get('answer')}")
    #         return
    # elif len(res) == 0:
    #     print(data)
    #     print(err)
    #     print("NO ANSWER")
    # if kwargs.get("value") != None and len(res) > 1:
    #     if "\n".join(res[1:-1]) != kwargs.get("value"):
    #         print(
    #             f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")


result = subprocess.run(["g++", "-std=c++20", "-g", "i.cpp"])
if result.returncode == 0:
    run_test("""3
1 2
3 3
1 1
""", answer=3, comment="test1")

    run_test("""3
2 1
2 2
2 3
""", answer=4, comment="test2")

    run_test("""3
1 1
2 2
3 3
""", answer=2, comment="test3")

    run_test("""3
1 2
2 2
3 2
""", answer=0, comment="test4")

    run_test("""3
1 1
1 2
1 3
""", answer=5, comment="test5")

    run_test("""4
1 1
1 2
2 1
2 2
""", answer=6, comment="test6")

# 9
    run_test("""5
1 1
2 2
3 3
4 4
5 5
""", answer=6, comment="test9")

    run_test("""10
1 6
6 2
5 5
7 5
8 9
6 10
8 2
10 8
8 7
7 8
""", answer=30, comment="test10, dont know right answer")  # !dont know right answer

# 13
    run_test("""10
9 4
8 9
5 4
10 8
7 9
10 5
9 2
8 10
3 9
6 2
""", answer=6, comment="test13, dont know right answer")  # ! dont know right answer

# 15
    run_test("""10
4 4
10 2
5 5
5 1
1 8
9 3
9 6
8 5
1 9
4 5
""", answer=23, comment="test15")

# 16
    run_test("""10
1 6
6 2
5 5
7 5
8 9
6 10
8 2
10 8
8 7
7 8
""", answer=35, comment="test16")

# 23
    run_test("""20
13 19
3 13
20 19
12 8
20 15
6 10
6 9
3 19
7 17
6 3
18 18
5 15
13 15
9 1
11 3
9 17
15 10
18 11
4 14
16 4
""", answer=108, comment="test23")

# 32
    run_test("""51
5 32
49 28
29 35
46 27
11 15
39 7
30 8
26 27
51 50
35 27
15 40
40 1
47 31
22 12
41 22
4 29
51 11
40 9
22 42
9 11
19 33
46 29
17 40
32 20
38 26
32 51
50 40
21 15
30 23
43 9
2 17
31 13
13 29
27 21
23 18
48 22
6 1
43 32
51 45
27 50
34 28
15 32
48 27
4 19
48 3
18 6
19 43
30 15
4 21
10 10
13 42
""", answer=688, comment="test32")
