import subprocess
import argparse
import timeit


def run_test(data, **kwargs):
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    if kwargs.get("comment") != None:
        print(kwargs.get("comment"))
    # print(data)
    print(out)
    res = list(out.split("\n"))
    if kwargs.get("answer") and len(res) > 0:
        if res[0].strip() != kwargs.get("answer"):
            print(f"WRONG ANSWER: {res[0]} != {kwargs.get('answer')}")
            return
    elif len(res) == 0:
        print(data)
        print(err)
        print("NO ANSWER")
    if kwargs.get("value") != None and len(res) > 1:
        if "\n".join(res[1:-1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")


task_name = "j.cpp"
parser = argparse.ArgumentParser(description='My example explanation')
parser.add_argument('-d', '--debug', action='store_true', help='Debug mode')
args = parser.parse_args()
if args.debug:
    result = subprocess.run(["g++", "-std=c++20", "-g", task_name])
else:
    result = subprocess.run(["g++", "-std=c++20", "-g", "-O3",  task_name])
if result.returncode == 0:

    run_test("3 2", answer="3 3", comment="test 1")
    run_test("2 1", answer="1", comment="test 2")
    run_test("4 4", answer="7 8 8", comment="test ?")
    run_test("3 10", answer="15 15", comment="test 11")
    run_test("4 1", answer="1 2 3", comment="test 16")
    run_test("4 3", answer="5 6 6", comment="test 18")
    run_test("5 3", answer="6 7 8 7", comment="test 24")
