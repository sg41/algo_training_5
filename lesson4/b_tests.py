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
        if res != kwargs.get("answer").split("\n"):
            answer = kwargs.get("answer").split("\n")
            print(f"WRONG ANSWER: {res} != {answer}")
            return

    if kwargs.get("value") != None and len(res) > 1:
        if "\n".join(res[1:-1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")


task_name = "b.cpp"
parser = argparse.ArgumentParser(description='My example explanation')
parser.add_argument('-d', '--debug', action='store_true', help='Debug mode')
args = parser.parse_args()
if args.debug:
    result = subprocess.run(["g++", "-std=c++20", "-g", task_name])
else:
    result = subprocess.run(["g++", "-std=c++20", "-g", "-O3",  task_name])
if result.returncode == 0:

    run_test("7", answer="2", comment="test 1")
    run_test("0", answer="0", comment="input = 0")
    run_test("1", answer="1", comment="input = 1")
    run_test("2", answer="1", comment="input = 2")
    run_test("5", answer="1", comment="test 5")
    run_test("200", answer="8", comment="test 11")
    run_test("117055765888857794", answer="888887", comment="test 42")
    run_test("973622521965965999", answer="1800999", comment="test 49")
    run_test("1000000000000000000", answer="1817118",
             comment="Dont know right answer")
