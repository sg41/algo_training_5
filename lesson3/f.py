dictionary = set(input().split())
text = input().split()

result_text = []

for word in text:
    for i in range(1, len(word)):
        if word[:i] in dictionary:
            result_text.append(word[:i])
            break
    else:
        result_text.append(word)

print(" ".join(result_text))
