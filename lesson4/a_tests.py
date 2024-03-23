import subprocess
import argparse
import timeit


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
        if res[0].strip() != kwargs.get("answer"):
            print(f"WRONG ANSWER: {res[0]} != {kwargs.get('answer')}")
            return

    if kwargs.get("value") != None and len(res) > 1:
        if "\n".join(res[1:-1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")


task_name = "a.cpp"
parser = argparse.ArgumentParser(description='My example explanation')
parser.add_argument('-d', '--debug', action='store_true', help='Debug mode')
args = parser.parse_args()
if args.debug:
    result = subprocess.run(["g++", "-std=c++20", "-g", task_name])
else:
    result = subprocess.run(["g++", "-std=c++20", "-g", "-O3",  task_name])
if result.returncode == 0:

    run_test("""
5
10 1 10 3 4
4
1 10
2 9
3 4
2 2
""", answer="5 2 2 0", comment="test 1")
    run_test("1 100 1 -1000 -1", answer="0", comment="test 2")
    run_test("1 100 1 -1000 1000", answer="1", comment="test 3")
    run_test("1 100 1 100 100", answer="1", comment="test 4")
    run_test("1 100 1 1000 1000", answer="0", comment="test 5")
