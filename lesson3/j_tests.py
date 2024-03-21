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
        if res[-2].strip() != kwargs.get("answer"):
            # print(len(res[0].strip().split(" ")))
            print(f"WRONG ANSWER: {res[-2]} != {kwargs.get('answer')}")
            return

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
    run_test("3 10", answer="15 15", comment="test 11")
    run_test("4 1", answer="1 2 3", comment="test 16")
    run_test("4 3", answer="5 6 6", comment="test 18")
    run_test("4 4", answer="7 8 8", comment="test ?")
    run_test("5 3", answer="6 6 7 7", comment="test 24")
    run_test("5 10", answer="19 24 24 23", comment="test 27")
    run_test("35 100", answer="1342 1357 1233 1354 1323 1358 1058 1275 994 1359 1249 1255 1104 1359 1353 1276 1341 1005 999 1358 1356 1307 1006 1357 1360 1205 1343 1121 830 1361 1360 1238 1318 1195", comment="35x100")
    run_test("100 35", answer="1134 843 1153 1153 280 1085 1075 1139 1154 1093 1133 1154 1155 1135 1156 893 1157 946 1041 1142 1105 358 1157 1082 931 261 1108 1158 1123 1102 1126 866 1116 249 1028 1131 907 993 1144 1098 688 1076 1137 1088 1158 1056 917 1159 940 869 1160 654 1159 1055 1094 1161 1124 1160 711 1129 1079 1156 1162 1162 1163 1163 1164 1089 1111 1031 397 1164 995 1100 898 819 740 898 1111 1149 1147 1062 1165 1165 1090 939 1140 1155 851 809 1037 1025 1166 1136 1070 1166 1161 1152 959", comment="100x35")
    run_test("100 200", answer="5394 4883 1317 5430 6458 6447 2322 2897 5701 6419 5702 5261 4891 6150 6459 6166 6275 5232 6417 6266 6459 4894 5202 5793 3898 5790 6452 6030 4531 6154 6460 6363 4993 6337 4032 6458 5252 6114 6461 3910 6245 3408 4123 6235 6462 4261 6421 4279 6443 5391 5619 6461 4969 6244 4563 5990 6107 3788 3903 6094 4934 6264 6460 5794 6067 5498 6451 5425 5768 6462 5801 3466 6457 5530 6341 5944 6391 3367 6060 6036 5434 6172 6455 5922 4124 6463 4966 6435 6463 6339 6209 6464 6254 6464 5293 6465 5003 4242 4197", comment="test 100x200")
