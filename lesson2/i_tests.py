import subprocess


def run_test(data, **kwargs):
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    print(data)
    print(out)
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
""", answer=3)

    run_test("""3
2 1
2 2
2 3
""", answer=4)

    run_test("""3
1 1
2 2
3 3
""", answer=2)

    run_test("""3
1 2
2 2
3 2
""", answer=0)

    run_test("""3
1 1
1 2
1 3
""", answer=5)

    run_test("""4
1 1
1 2
2 1
2 2
""", answer=6)

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
""", answer=39)  # !dont know right answer

    run_test("""5
1 1
2 2
3 3
4 4
5 5
""", answer=6)

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
""", answer=6)  # ! dont know righ answer

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
""", answer=108)
