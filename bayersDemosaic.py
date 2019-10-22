#13-9-19
#CED16I031
#Shukrithi Rathna
#Bayers Demosaicing algorithm
#Image grid follows RGGB pattern

import pygame
import Collections 
import random

Square=[]

def Corner(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-11,-9,9,11]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

def gMiddle(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-11,-9,0,9,11]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

def checkRed(SquareNum):
    SquareNum-=1
    try:
        Colour = Square[SquareNum-1].Colour
    except IndexError:
        Colour = Square[SquareNum+1].Colour
    if Colour=='red':
        return True
    else:
        return False

def gCorner(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-10,-1,+10,+1]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

def Middle(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-10,-1,+1,+10]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

def GreenLeft(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-1,+1]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

def GreenUp(SquareNum):
    SquareNum-=1
    Count=0
    Sum=0
    Index=[-10,+10]
    for i in Index:
        try:
            Val = Square[SquareNum+i].Intensity
            Count+=1
        except IndexError:
            Val =0
        Sum+=Val
    Avg=Sum/Count
    return Avg

# Define Colour
BLUE = (0, 0, 255)
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = (255,0,0)
GREEN = (0,255,0)
 
pygame.init()

# Set the Width and Height of the screen [Width, Height]
Size = (700, 700)
screen = pygame.display.set_mode(Size)
clock = pygame.time.Clock()
font = pygame.font.Font('freesansbold.ttf', 12)

screen.fill(BLACK)

#initalizing
x=50
y=50
Width = 300
Height = 300
i=50
j=50
Row=1
Col=1
Intensity=0
SquareInfo = Collections.namedtuple('SquareInfo',['SquareNum','Colour','Intensity']) 

pygame.draw.rect(screen, BLUE,(x,y,Width,Height),2) #drawing RGB image
for i in range (50,x+Height,30):
    
    for j in range (50,y+Width,30):
    
        SquareNum=(Row-1)*10+Col #Square number as function of Row and Column (image is 10 x 10 grid)
        Intensity=random.randint(0,255) #setting random Intensity of Colour
        #image grid follows RGGB pattern
    
        if Row % 2 !=0 and Col % 2 !=0:
            Colour = (Intensity,0,0) #RED
            s=SquareInfo(SquareNum,'red',Intensity) #storing grid info in tuple
    
        elif Row % 2 ==0 and Col % 2 ==0:
            Colour = (0,0,Intensity) #BLUE
            s=SquareInfo(SquareNum,'blue',Intensity)
    
        else:
            Colour = (0,Intensity,0) #GREEN
            s=SquareInfo(SquareNum,'green',Intensity)
        
        Col+=1
        pygame.draw.rect(screen,Colour,(j,i,30,30)) #drawing rectangles
        Square.append(s) #updating grid info in list
        #Row+=1
    Row+=1
    Col=1 #setting Column back to 1


#drawing demosaiced image
#initializing Values for second image
r=0
g=0
b=0
Row=1
Col=1
#print(Square[0])
for i in range (350,350+Height,30):
    for j in range (350,350+Width,30):
        SquareNum=((Row-1)*10+Col)-1 #Square no as function of Row and Column
        #print(SquareNum)
        if Square[SquareNum].Colour=='red':
                r=Square[SquareNum].Intensity #no neighbouring Squares are red
                b=Corner(SquareNum) #4 diagonal Corners are blue
                g=Middle(SquareNum) #4 Middle Squares in boundary are green
                Colour = (r,g,b)
               
        elif Square[SquareNum].Colour=='blue':
                r=Corner(SquareNum)
                g=Middle(SquareNum)
                b=Square[SquareNum].Intensity
                Colour = (r,g,b)
        else:
            g=gMiddle(SquareNum)
            if checkRed(SquareNum): 
                r=GreenLeft(SquareNum) #left and right is red
                b=GreenUp(SquareNum) # up and down is blue
            else:
                b=GreenLeft(SquareNum) #left and right is blue
                r=GreenUp(SquareNum) #up and down is blue
                Colour = (r,g,b)
        Col+=1 
        pygame.draw.rect(screen,Colour,(j,i,30,30))
    Row+=1
    Col=1 #set Column back to 1
pygame.display.flip() #update screen
pygame.time.wait(5000) 

# Close the window and quit.    
pygame.quit()
