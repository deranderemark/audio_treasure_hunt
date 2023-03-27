from random import randint

while True:
    code = []

    for i in range(0, 6):
        val = randint(0, 6)
        code.append(val)

    for i in code:
        print(i)
    
    input("New Code?")
