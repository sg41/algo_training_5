import subprocess


def run_test(data, **kwargs):
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    res = list(out.split("\n"))
    for i in range(len(res)):
        res[i] = res[i].strip()
        if res[i] == '':
            res.pop(i)
    print(data)
    print(out)
    if kwargs.get("answer") and len(res) > 0:
        if res[0] != kwargs.get("answer"):
            print(f"WRONG ANSWER: {res[0]} != {kwargs.get('answer')}")
            return
    elif len(res) == 0:
        print(data)
        print(err)
        print("NO ANSWER")
    if kwargs.get("value") != None and len(res) > 1:
        if int(res[1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1]} != {kwargs.get('value')}")


result = subprocess.run(["g++", "-std=c++20", "-g", "h.cpp"])
if result.returncode == 0:
    run_test("""4 5
999999997 1 2 3 4
10 2 1000000000 1 7
3 9 999999999 5 10
1 7 3 999999998 6""", answer="4 3")
    run_test("""2 2
1 2
3 4""", answer="2 2")
    run_test("""3 4
1 3 5 7
9 11 2 4
6 8 10 12""", answer="3 2")
