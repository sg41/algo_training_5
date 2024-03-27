import subprocess
import argparse
import timeit

task_name = "h.cpp"


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
    res = out.split("\n")
    res = [r.strip() for r in res]
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

    run_test("""3
7 -1
2 8
1 2
""", answer="""6
3
3 2 5
""", comment="test 1")
    run_test("""50
1 2
2 5
4 3
4 2
3 -1
4 3
5 2
1 -1
1 -1
1 2
5 4
2 -1
3 4
1 -1
1 4
2 -1
1 3
1 -1
5 -1
1 -1
2 -1
3 -1
1 2
2 5
1 -1
2 -1
1 4
3 4
2 2
3 1
2 3
4 -1
2 -1
4 -1
1 5
1 3
2 -1
2 -1
3 1
5 4
4 -1
5 -1
3 -1
1 -1
2 -1
5 -1
5 -1
1 1
5 -1
1 -1
""", answer="""6
3
3 2 5
""", comment="test 15")

    run_test("""100
999752 844759
993867 841816
986613 837960
937429 802772
922645 791684
904200 777848
902833 776825
893585 769889
888288 765914
878957 758918
875193 756095
847658 735443
842843 731831
830441 722531
826325 719444
822824 716816
822460 716543
816195 711845
807342 705206
806746 704759
798139 698303
793396 694745
788210 690857
786291 689417
781812 686057
778831 683822
776321 681941
774429 680522
737070 650882
694483 616773
676119 601473
666835 593733
645753 576168
637437 569238
637004 568873
628732 561983
628605 561878
624962 558838
618930 553813
610163 546508
596422 535058
588604 528543
573632 515767
570518 513044
558993 502957
527131 475076
525034 473242
513564 463204
509724 459844
508446 458731
503406 454321
498459 449947
492015 444219
491693 443931
468372 423203
456480 412635
450971 407709
448637 405603
448072 405099
411246 371952
373556 338031
373367 337860
342170 309620
338728 306490
306833 277399
302544 273472
294674 266256
285916 258226
274155 247446
269321 243013
268781 242518
267566 241407
260590 235016
254378 229318
242780 218692
239806 215964
232753 209496
229959 206933
194913 174813
180739 161822
150127 133761
144761 128833
136404 121177
129163 114544
122954 108846
117076 103456
114503 101102
100702 88452
76630 66386
61882 52867
54561 46157
43250 35784
33846 27160
32740 26148
22747 16996
19316 13850
17552 12233
11635 6810
4752 496
4210 1
""", answer="""844749
93
3 2 5
""", comment="test 51 wrong partys list")
