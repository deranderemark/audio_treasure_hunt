input = []

with open('codes.txt', 'r') as reader:
    for code in reader.readlines():
        input.append(code.strip("\n"))

    for x in input:
        for index, char in enumerate(list(x)):
            match index:
                case 0:
                    print("{ " + char + ", ", end='')
                case 5:
                    print(char + " },")
                case _:
                    print(char + ", ", end='')
