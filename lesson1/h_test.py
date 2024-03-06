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
    if kwargs.get("answer"):
        if res[0].lower() != kwargs.get("answer").lower():
            print(f"WRONG ANSWER: {res[0]} != {kwargs.get('answer')}")
            return
    if kwargs.get("value") != None and len(res) > 1:
        if abs(float(res[1]) - float(kwargs.get("value"))) > 10e-9:
            print(
                f"WRONG VALUE: {float(res[1])} != {float(kwargs.get('value'))}")


result = subprocess.run(["g++", "-std=c++20", "-g", "h.cpp"])
if result.returncode == 0:
    run_test("6 3 1 1 1", answer="yes", value=1.000000000)
    run_test("12 8 10 5 20", answer="YES", value=0.3000000000)
    run_test("5 0 0 1 2", answer="YES", value=2.0000000000)
    run_test("10 7 -3 1 4", answer="YES", value=0.8571428571)
    run_test("6 0 1 1 6", answer="yes", value=0.7142857143)
    run_test("6 0 1 1 4", answer="yes", value=1.000000000)
    run_test("55444931 17419156 0 53245822 -398046024",
             answer="yes", value=0.03823690247)
    run_test("72 20 -38121735 66 288888467", answer="yes", value=0.0000000795)
    run_test("94 76 0 76 0", answer="yes", value=0.0000000000)
    run_test("948744004 861724643 848773505 584154450 730556189",
             answer="yes", value=0.2859497398)
    run_test("938712409 11003268 0 278188417 0", answer="no")
    run_test("10 8 8 6 7", answer="yes", value=0.4000000000)
    run_test("6 2 3 5 2", answer="yes", value=1.000000000)
    run_test("615143346 79387687 -80123649 306422480 -80123649",
             answer="yes", value=2.4075923389)
    run_test("6 1 -1 3 -1", answer="yes", value=2.000000000)
    run_test("762899414 556082848 -539099316 556082848 -582799403",
             answer="yes", value=0.0000000000)
    run_test("977345779 636176199 0 165786447 815181433",
             answer="yes", value=0.2151461330)
    run_test("82 42 -354891707 42 -354891707",
             answer="yes", value=0.0000000000)
    run_test("956390104 549514100 7 315097830 -7",
             answer="yes", value=51569559.5714285714)
    run_test("6 1 -1 3 1", answer="yes", value=2.000000000)
    run_test("1000000000 10 1000000000 11 0", answer="yes", value=0.0000000000)
