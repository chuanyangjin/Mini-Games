from random import randrange
from turtle import *

from freegames import square, vector

food = vector(0, 0)
snake = [vector(10, 0)]
aim = vector(0, -10)


def change(x, y):
    "Change snake direction."
    aim.x = x
    aim.y = y


def inside(head):
    "Return True if head inside boundaries."
    return -200 < head.x < 190 and -200 < head.y < 190


def move():
    global d
    
    "Move snake forward one segment."
    head = snake[-1].copy()
    head.move(aim)

    if not inside(head) or head in snake:
        square(head.x, head.y, 9, 'red')
        update()
        
        # 死掉
        print("Score:", len(snake))
        d1 = {174:"JCY",85:"JCY"}
        print("\nDifficulty1 (100)")
        for key in d1.keys():
            print(key," ",d1[key])
        d2 = {100:"JCY",75:"JCY"}
        print("\nDifficulty2 (50)")
        for key in d2.keys():
            print(key," ",d2[key])
        d3 = {37:"JCY",33:"JCY"}
        print("\nDifficulty3 (33)")
        for key in d3.keys():
            print(key," ",d3[key])
        d10 = {11:"JCY",4:"JCY"}
        print("\nDifficulty10 (10)")
        for key in d10.keys():
            print(key," ",d10[key])
            
        return

    snake.append(head)

    if head == food:
        print('Snake:', len(snake))
        food.x = randrange(-15, 15) * 10
        food.y = randrange(-15, 15) * 10
    else:
        snake.pop(0)

    clear()

    for body in snake:
        square(body.x, body.y, 9, 'black')

    square(food.x, food.y, 9, 'green')
    update()
    ontimer(move, d)

d = input("Choose Difficulty(1/2/3/10): ")
if d == "1":
    d = 100
elif d == "2":
    d = 50
elif d == "3":
    d = 33
else:
    d = 10
setup(420, 420, 370, 0)
hideturtle()
tracer(False)
listen()
onkey(lambda: change(10, 0), 'Right')
onkey(lambda: change(-10, 0), 'Left')
onkey(lambda: change(0, 10), 'Up')
onkey(lambda: change(0, -10), 'Down')
move()
done()
