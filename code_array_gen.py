with open('codes.txt', 'r') as reader:
    input = reader.readlines()
    ccodes = []

    for code in input:
        ccode = code.strip("\n")
        ccodes.append(ccode)

    for x in ccodes:
        chars = list(x)
        for index, char in enumerate(chars):
            match index:
                case 0:
                    print("{ " + char + ", ", end='')
                case 5:
                    print(char + " },")
                case _:
                    print(char + ", ", end='')
