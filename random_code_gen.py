from random import randint

while True:
    code = []

    for i in range(0, 6):
        val = randint(1, 6)
        code.append(val)

    for i in code:
        print(i)
    
    feedback = input("New Code?")

    if input == "no":
        exit(0)
