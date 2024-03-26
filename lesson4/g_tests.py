import subprocess
import argparse
import timeit

task_name = "g.cpp"


def run_test(data, **kwargs):
    if kwargs.get("comment") != None:
        print(kwargs.get("comment"))
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    if test.returncode != 0:
        print(data)
        print(err)
        print("RE")
    # print(data)
    print(out)
    res = list(out.split("\n"))
    if kwargs.get("answer") and len(res) > 0:
        if res != kwargs.get("answer").split("\n"):
            answer = kwargs.get("answer").split("\n")
            print(f"WRONG ANSWER: {res} != {answer}")
            return

    if kwargs.get("value") != None and len(res) > 1:
        if "\n".join(res[1:-1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")


parser = argparse.ArgumentParser(description='My example explanation')
parser.add_argument('-d', '--debug', action='store_true', help='Debug mode')
args = parser.parse_args()
if args.debug:
    result = subprocess.run(["g++", "-std=c++20", "-g", task_name])
else:
    result = subprocess.run(["g++", "-std=c++20", "-g", "-O3",  task_name])
if result.returncode == 0:

    run_test("""9 12
...##.###...
...##.###...
.########...
.###########
...#########
...#########
......###...
......###...
......###...
""", answer="3", comment="test 1")
    run_test("""6 6
.##...
.##...
######
######
.##...
.##...
""", answer="1", comment="test 2")

    print(timeit.timeit('''f=open("09_G.txt", "r")
with f:
        run_test(f.read(), answer="2", comment="test 9 - dont know result")''', setup="from __main__ import run_test", number=1))

    print(timeit.timeit('''f=open("34.txt", "r")
with f:
        run_test(f.read(), answer="311", comment="test 34 - dont know result")''', setup="from __main__ import run_test", number=1))
