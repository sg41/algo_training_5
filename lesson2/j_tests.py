import subprocess


def run_test(data, **kwargs):
    test = subprocess.Popen(
        "./a.out",  stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    (out, err) = test.communicate(input=data)
    print(data)
    print(out)
    res = list(out.split("\n"))
    if kwargs.get("answer") and len(res) > 0:
        if res[0] != kwargs.get("answer"):
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


result = subprocess.run(["g++", "-std=c++20", "-g", "j.cpp"])
if result.returncode == 0:
    run_test("""2 1
#
.""", answer="NO")

    run_test("""2 2
..
##
""", answer="YES", value="""..
ba""")

    run_test("""1 3
###
""", answer="YES", value="""baa""")

    run_test("""1 5
####.
""", answer="YES", value="""baaa.""")

    run_test("""3 3
###
###
...
""", answer="YES", value="""baa
baa
...""")

    run_test("""3 3
###
###
###
""", answer="YES", value="""baa
baa
baa""")

    run_test("""3 3
###
##.
...
""", answer="YES", value="""aaa
bb.
...""")

    run_test("""3 3
#..
###
#..
""", answer="YES", value="""a..
abb
a..""")

    run_test("""3 3
..#
###
..#
""", answer="YES", value="""..a
bba
..a""")

    run_test("""3 3
.#.
...
###
""", answer="YES", value=""".a.
...
bbb""")

    run_test("""3 3
.#.
.#.
###
""", answer="YES", value=""".a.
.a.
bbb""")

    run_test("""3 3
..#
..#
###
""", answer="YES", value="""..a
..a
bba""")

    run_test("""3 3
###
#.#
###
""", answer="NO")

    run_test("""3 3
#.#
..#
###
""", answer="NO")

    run_test("""3 3
###
###
#.#
""", answer="NO")
