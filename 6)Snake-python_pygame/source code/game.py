import pygame,sys
from pygame.locals import *
from random import randint

pygame.init()
pygame.font.init()
DISPLAYSURF =  pygame.display.set_mode((700,400))
pygame.display.set_caption('Snake')
font = pygame.font.SysFont('Comic Sans MS', 30)
clock = pygame.time.Clock()
time = 0
ltime = 0
height = 18
width =  35
pole = [[0]*height for i in range(width)]
kpole = [[0]*height for i in range(width)]
posx = 0
posy = 0
dir = 'none'
length = 3
highscore = 0

i = 0
while i < 18:
    pole[0][i] = 1
    pole[width-1][i] = 1
    i+=1
i = 0
while i < 35:
    pole[i][0] = 1
    pole[i][height-1] = 1
    i+=1

def menu():
    global time,posx,posy,dir,length,highscore,height,width
    try:
        hfile = open('highscore_snake.txt', 'r')
        highscore = hfile.read()
    except FileNotFoundError:
        highscore = 0
    DISPLAYSURF.fill((0, 150, 128))
    DISPLAYSURF.blit(font.render("Press SPACE to start new game,or ESC to exit.",True,(150, 0, 75)),(10,175))
    pygame.display.update()
    start = False
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == KEYDOWN:
                if (event.key == K_SPACE):
                    start = True
                    break
                if (event.key == K_ESCAPE):
                    pygame.quit()
                    sys.exit()
                    break
        if start:
            i = 1
            while i < width-1:
                j = 1
                while j < height-1:
                    pole[i][j] = 0
                    j += 1
                i += 1
            spawn_food()
            dir = 'right'
            length = 3
            posx = 5
            posy = 5
            time = pygame.time.get_ticks() /1000
            break

def spawn_food():
    global pole,width,height
    while True:
        fposx =  randint(1, width-2)
        fposy =  randint(1, height-2)
        if pole[fposx][fposy] == 0:
            pole[fposx][fposy] = 2
            break



def draw():
    global pole,font,height,width,highscore,time,ltime
    DISPLAYSURF.fill((0, 150, 128))
    i = 0
    while i < width:
        j = 0
        while j < height:
            if pole[i][j] == 0:
                color = (213, 215, 231)
            elif pole[i][j] == 1:
                color = (255, 255, 255)
                #color = (0, 0, 0)
            elif pole[i][j] == 2:
                color = (0, 150, 250)
            elif pole[i][j] == 3:
                color = (213, 105, 231)
            pygame.draw.rect(DISPLAYSURF,color,(i*20,j*20,20,20))
            j+=1
        i+=1
    ltime = pygame.time.get_ticks() /1000
    DISPLAYSURF.blit(font.render("Score:"+str(length-3)+' '+"Highscore:"+str(highscore)+' '+"Time:"+str(round(ltime-time,1))+'s',True,(150, 0, 75)),(10,357))
    pygame.display.update()

def getevents():
    global dir
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == KEYDOWN:
            if (event.key == K_RIGHT) and (dir != 'left'):
                dir = 'right'
                break
            elif (event.key == K_LEFT) and (dir != 'right'):
                dir = 'left'
                break
            elif (event.key == K_UP) and (dir != 'down'):
                dir = 'up'
                break
            elif (event.key == K_DOWN) and (dir != 'up'):
                dir = 'down'
                break


def deltail():
    global pole,kpole,length,width,height
    maxx = 0
    maxy = 0
    max = 0
    i = 0
    while i < width:
        j = 0
        while j < height:
            if pole[i][j] == 3:
                kpole[i][j] += 1
            j += 1
        i += 1
    i = 0
    while i < width:
        j = 0
        while j < height:
            if kpole[i][j] >= max:
                max = kpole[i][j]
                maxx = i
                maxy = j
            j += 1
        i += 1
    if max > length:
        pole[maxx][maxy] = 0
        kpole[maxx][maxy] = 0

def move():
    global posx,posy,dir,pole
    getevents()
    if dir == 'left':
        posx -= 1
    elif dir == 'right':
        posx += 1
    elif dir == 'up':
        posy -= 1
    elif dir == 'down':
        posy += 1
    check()
    pole[posx][posy] = 3
    deltail()


def check():
    global posx,posy,length,pole,height,width
    if (posx < 1) or (posx > width-2) or (posy < 1) or (posy > height-2) or (pole[posx][posy] == 3):
        if(int(highscore) < length-3):
            hfile = open('highscore_snake.txt', 'w')
            hfile.write(str(length-3))
            hfile.close()
        menu()
    if pole[posx][posy] == 2:
        spawn_food()
        length += 1

menu()
while True:
    move()
    draw()
    clock.tick(4)
