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
            # return

    if kwargs.get("value") != None and len(res) > 1:
        if "\n".join(res[1:-1]) != kwargs.get("value"):
            print(
                f"WRONG VALUE: {res[1:]} != {kwargs.get('value')}")
    print("------------------------------------------------------------------")


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

    run_test("""2
239 239
239 -1
""", answer="""240
1
240 238
""", comment="test 4")

    run_test("""2
239 239
240 -1
""", answer="""240
1
240 239
""", comment="test 5")

    run_test("""3
6 8
4 6
3 5
""", answer="""7
3
4 4 5
""", comment="test 6")

    run_test("""2
1000000 1000000
1000000 1000000
""", answer="""1000001
1
1000001 999999
""", comment="test 8")

    run_test("""2
1000000 -1
1 1000000
""", answer="""1500000
2
500000 500001
""", comment="test 9")

    run_test("""2
1 1
1 1
""", answer="""2
1
2 0
""", comment="test 10")

    run_test("""4
70 10
69 10
69 10
68 5
""", answer="""7
4
68 69 69 70
""", comment="test no number")

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
""", answer="""3
7
1 2 4 4 3 4 6 1 1 1 5 2 3 1 1 2 1 1 5 1 2 3 1 2 1 2 1 3 2 3 2 4 2 4 1 1 2 2 3 5 4 5 3 1 2 5 5 1 4 1
""", comment="test 15")
    run_test("""100
28 43
45 -1
66 61
65 45
56 50
25 60
60 -1
20 -1
63 25
24 33
26 46
33 -1
40 37
62 24
36 -1
23 34
62 -1
69 38
23 58
51 51
55 -1
41 -1
55 -1
52 -1
20 -1
32 -1
52 -1
29 67
55 -1
36 -1
53 -1
22 66
24 -1
29 -1
69 33
25 38
58 26
57 36
70 -1
40 52
52 -1
25 -1
61 42
68 -1
47 -1
68 28
63 -1
60 -1
26 -1
38 63
23 -1
64 -1
23 28
46 41
49 -1
43 -1
49 -1
28 -1
58 66
69 38
40 44
22 -1
20 -1
55 36
68 22
34 -1
49 31
63 66
45 67
68 65
48 -1
55 37
33 -1
26 65
34 -1
53 -1
70 66
53 -1
51 42
64 -1
60 -1
27 41
62 -1
29 -1
64 -1
57 -1
69 33
22 36
69 -1
25 50
36 69
70 63
54 57
66 41
39 63
56 -1
23 -1
60 55
67 -1
30 44
""", answer="""25
65
28 45 66 65 56 25 60 20 63 24 26 33 40 62 36 23 62 69 23 51 55 41 55 52 20 32 52 29 55 36 53 22 24 29 69 25 58 57 67 40 52 25 61 68 47 68 63 60 26 38 23 64 23 46 49 43 49 28 58 69 40 22 20 55 71 34 49 63 45 68 48 55 33 26 34 53 70 53 51 64 60 27 62 29 64 57 69 22 69 25 36 70 54 66 39 56 23 60 67 30 
""", comment="test 16")
    run_test("""110
37 65
64 29
60 32
36 67
59 46
40 53
33 68
51 71
46 74
41 41
33 65
48 26
43 29
38 21
50 47
66 27
59 44
67 61
56 43
40 21
40 20
29 59
39 50
21 58
54 55
36 71
59 68
31 26
59 44
69 37
63 32
43 22
66 21
68 76
57 79
51 62
69 24
59 54
46 41
47 23
46 30
46 70
65 24
32 69
22 68
53 28
25 34
63 43
70 49
68 28
51 30
32 68
21 51
54 47
26 68
67 58
42 28
60 31
67 35
56 71
51 23
46 69
67 74
26 75
22 41
57 48
46 -1
27 27
38 55
47 60
49 36
43 30
37 30
27 80
41 50
50 49
20 30
25 39
70 23
66 60
37 36
61 48
43 48
39 75
53 23
46 40
67 20
45 62
55 43
61 37
34 26
40 36
31 78
68 31
37 65
56 35
46 38
38 36
53 72
20 28
27 49
58 76
56 58
65 58
65 35
46 37
34 21
31 20
58 50
41 30
""", answer="""23
87
37 64 60 36 59 40 33 51 46 41 33 48 43 38 50 66 59 67 56 40 40 29 39 21 54 36 59 31 59 69 63 43 66 68 57 51 69 59 46 47 46 46 65 32 22 53 25 63 69 68 51 32 21 54 26 67 42 60 67 56 51 46 67 26 22 57 46 27 38 47 49 43 37 27 41 50 20 25 68 66 37 61 43 39 53 46 70 45 55 61 34 40 31 68 37 56 46 38 53 20 27 58 56 65 65 46 34 31 58 41
""", comment="test 17")
    run_test("""110
61 -1
27 -1
58 30
37 -1
21 -1
52 56
43 -1
64 -1
28 -1
29 -1
20 -1
22 -1
42 -1
55 73
37 -1
26 69
59 -1
51 53
54 -1
46 -1
20 39
56 -1
56 -1
38 44
47 -1
46 44
61 24
64 70
68 39
22 30
32 74
65 -1
65 80
69 -1
49 70
23 -1
49 61
50 25
44 35
39 71
49 67
38 -1
23 24
56 26
36 -1
61 -1
22 -1
63 54
54 -1
33 38
54 38
26 -1
66 -1
35 -1
70 -1
65 -1
66 -1
63 -1
63 -1
62 -1
27 -1
49 30
37 30
33 -1
27 -1
36 -1
58 -1
40 -1
56 -1
32 -1
64 23
58 -1
34 -1
54 -1
22 45
20 -1
49 38
69 -1
39 68
21 -1
23 77
59 64
62 -1
66 70
48 65
60 73
61 39
56 -1
66 -1
38 -1
24 -1
62 76
66 -1
59 -1
52 -1
67 51
52 -1
32 -1
22 -1
53 -1
68 39
61 -1
20 33
45 -1
44 -1
32 40
49 -1
44 -1
23 -1
26 -1
""", answer="""28
71
61 27 58 37 21 52 43 64 28 29 20 22 42 55 37 26 59 51 54 46 20 56 56 38 47 46 61 64 67 22 32 65 65 68 49 23 49 50 44 39 49 38 23 56 36 61 22 63 54 33 54 26 66 35 68 65 66 63 63 62 27 49 37 33 27 36 58 40 56 32 69 58 34 54 22 20 49 68 39 21 23 59 62 66 48 60 61 56 66 38 24 62 66 59 52 67 52 32 22 53 68 61 20 45 44 32 49 44 23 26
""", comment="test 19")

    run_test("""130
28 -1
22 -1
25 65
33 30
33 -1
54 -1
59 -1
88 -1
55 -1
77 -1
81 -1
25 -1
59 -1
62 -1
47 -1
41 -1
21 -1
66 35
53 24
59 -1
74 33
70 -1
25 65
73 -1
82 61
61 -1
70 -1
37 -1
26 -1
69 -1
22 -1
52 30
31 -1
46 31
40 77
47 -1
26 -1
50 73
67 -1
61 66
52 -1
53 68
59 -1
30 76
36 -1
69 -1
56 -1
69 20
25 -1
40 -1
30 -1
24 79
71 36
83 -1
76 -1
88 -1
49 61
31 73
76 -1
45 56
64 -1
41 22
34 -1
21 76
49 -1
34 -1
41 -1
21 -1
22 31
41 -1
44 -1
67 80
50 29
44 55
62 79
85 -1
51 -1
74 -1
25 69
88 -1
46 27
55 -1
89 -1
47 34
46 -1
25 -1
52 80
20 -1
57 -1
41 33
43 -1
48 -1
87 -1
48 22
33 -1
38 -1
80 -1
65 -1
36 -1
80 69
62 -1
22 -1
20 -1
87 68
71 -1
35 -1
37 -1
31 80
88 -1
26 68
27 53
53 51
74 -1
79 -1
52 63
49 -1
36 51
86 74
89 -1
23 -1
38 -1
55 54
36 -1
61 -1
27 -1
22 22
39 29
76 -1
63 -1
68 -1
""", answer="""38
48
28 22 25 33 33 54 59 86 55 77 81 25 59 62 47 41 21 66 53 59 74 70 25 73 82 61 70 37 26 69 22 52 31 46 40 47 26 50 67 61 52 53 59 30 36 69 56 87 25 40 30 24 71 83 76 86 49 31 76 45 64 41 34 21 49 34 41 21 22 41 44 67 50 44 62 85 51 74 25 86 46 55 84 47 46 25 52 20 57 41 43 48 86 48 33 38 80 65 36 80 62 22 20 86 71 35 37 31 86 26 27 53 74 79 52 49 36 86 86 23 38 55 36 61 27 22 39 76 63 68 
""", comment="test 35")

    run_test("""130
30 70
41 34
48 -1
81 39
60 55
90 60
42 50
20 32
72 54
94 -1
23 50
61 49
46 -1
27 32
61 -1
56 -1
63 -1
96 -1
78 -1
28 37
87 47
88 -1
85 25
84 -1
38 -1
79 -1
88 25
35 -1
30 69
99 -1
42 34
58 -1
92 51
60 57
57 -1
24 69
38 29
75 -1
57 -1
73 46
56 30
56 27
39 27
43 59
55 -1
49 -1
60 -1
75 -1
64 62
90 49
58 -1
56 47
47 34
41 46
42 -1
70 -1
78 33
30 -1
68 -1
38 -1
34 -1
42 -1
56 -1
58 67
56 57
86 -1
67 20
63 -1
26 -1
20 -1
48 -1
41 -1
67 -1
34 58
61 26
88 -1
58 70
50 -1
58 -1
54 -1
100 27
23 -1
62 28
68 61
26 -1
76 -1
54 45
94 64
29 64
31 -1
95 49
79 57
38 68
41 -1
83 -1
97 -1
58 40
42 64
56 -1
59 -1
87 60
66 25
33 60
86 -1
60 -1
52 34
89 38
77 46
35 34
78 22
30 70
88 45
78 -1
27 -1
85 69
76 -1
56 33
21 40
25 42
33 -1
62 -1
38 62
96 41
86 35
38 -1
74 61
20 -1
34 68
79 -1
48 62
""", answer="""6
3
3 2 5
""", comment="test 39 - dont kowright answer")

#     print(timeit.timeit('''f=open("47.txt", "r")
# a=open("47.a", "r")
# with a:
#     ans = a.read()
# with f:
#         run_test(f.read(), answer=ans, comment="test 47")''', setup="from __main__ import run_test", number=1))

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
851433 851434 851434 851434 851434 851434 851434 851434 851434 851434 851434 847658 842843 830441 826325 822824 822460 816195 807342 806746 798139 793396 788210 786291 781812 778831 776321 774429 737070 694483 676119 666835 645753 637437 637004 628732 628605 624962 618930 610163 596422 588604 573632 570518 558993 527131 525034 513564 509724 508446 503406 498459 492015 491693 468372 456480 450971 448637 448072 411246 373556 373367 342170 338728 306833 302544 294674 285916 274155 269321 268781 267566 260590 254378 242780 239806 232753 229959 194913 180739 150127 144761 136404 129163 122954 117076 114503 100702 76630 61882 54561 43250 851435 32740 22747 19316 17552 11635 4752 4210
""", comment="test 51")
