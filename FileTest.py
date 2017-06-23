humidity = []
temp = []

try:
    text_file = open("Output.txt", "r")
    text_split = text_file.readline().split(",")
    for x in text_split:
        temp.append(int(x))
    print(temp)
except FileNotFoundError:
    print("File not found, created one")
    text_file = open("Output.txt", "w")
    text_file.close()
finally:
    text_file = open("Output.txt", "w")
    for x in range (0,10):
        temp.append(x)
    text_file.write(",".join(str(e) for e in temp))
    text_file.close()
