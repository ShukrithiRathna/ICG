#13-9-19
#CED16I031
#Shukrithi Rathna
#Bayers Demosaicing algorithm
#Image grid follows RGGB pattern

import pygame
import collections 
import random

square=[]

def corner(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-11,-9,9,11]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

def gmiddle(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-11,-9,0,9,11]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

def checkRed(square_no):
    square_no-=1
    try:
        colour = square[square_no-1].colour
    except IndexError:
        colour = square[square_no+1].colour
    if colour=='red':
        return True
    else:
        return False

def gcorner(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-10,-1,+10,+1]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

def middle(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-10,-1,+1,+10]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

def gLeft(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-1,+1]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

def gUp(square_no):
    square_no-=1
    count=0
    sum=0
    index=[-10,+10]
    for i in index:
        try:
            val = square[square_no+i].intensity
            count+=1
        except IndexError:
            val =0
        sum+=val
    avg=sum/count
    return avg

# Define colour
BLUE = (0, 0, 255)
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = (255,0,0)
GREEN = (0,255,0)
 
pygame.init()

# Set the width and height of the screen [width, height]
size = (700, 700)
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
font = pygame.font.Font('freesansbold.ttf', 12)

screen.fill(BLACK)

#initalizing
x=50
y=50
width = 300
height = 300
i=50
j=50
row=1
col=1
intensity=0
s_info = collections.namedtuple('s_info',['square_no','colour','intensity']) 

pygame.draw.rect(screen, BLUE,(x,y,width,height),2) #drawing RGB image
for i in range (50,x+height,30):
    
    for j in range (50,y+width,30):
    
        square_no=(row-1)*10+col #square number as function of row and column (image is 10 x 10 grid)
        intensity=random.randint(0,255) #setting random intensity of colour
        #image grid follows RGGB pattern
    
        if row % 2 !=0 and col % 2 !=0:
            COLOUR = (intensity,0,0) #RED
            s=s_info(square_no,'red',intensity) #storing grid info in tuple
    
        elif row % 2 ==0 and col % 2 ==0:
            COLOUR = (0,0,intensity) #BLUE
            s=s_info(square_no,'blue',intensity)
    
        else:
            COLOUR = (0,intensity,0) #GREEN
            s=s_info(square_no,'green',intensity)
        
        col+=1
        pygame.draw.rect(screen,COLOUR,(j,i,30,30)) #drawing rectangles
        square.append(s) #updating grid info in list
        #row+=1
    row+=1
    col=1 #setting column back to 1


#drawing demosaiced image
#initializing values for second image
r=0
g=0
b=0
row=1
col=1
#print(square[0])
for i in range (350,350+height,30):
    for j in range (350,350+width,30):
        square_no=((row-1)*10+col)-1 #square no as function of row and column
        #print(square_no)
        if square[square_no].colour=='red':
                r=square[square_no].intensity #no neighbouring squares are red
                b=corner(square_no) #4 diagonal corners are blue
                g=middle(square_no) #4 middle squares in boundary are green
                COLOUR = (r,g,b)
               
        elif square[square_no].colour=='blue':
                r=corner(square_no)
                g=middle(square_no)
                b=square[square_no].intensity
                COLOUR = (r,g,b)
        else:
            g=gmiddle(square_no)
            if checkRed(square_no): 
                r=gLeft(square_no) #left and right is red
                b=gUp(square_no) # up and down is blue
            else:
                b=gLeft(square_no) #left and right is blue
                r=gUp(square_no) #up and down is blue
                COLOUR = (r,g,b)
        col+=1 
        pygame.draw.rect(screen,COLOUR,(j,i,30,30))
    row+=1
    col=1 #set column back to 1
pygame.display.flip() #update screen
pygame.time.wait(5000) 

# Close the window and quit.    
pygame.quit()
