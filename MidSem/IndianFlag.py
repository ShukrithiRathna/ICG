# CED16I031 - Shukrithi Rathna
# Program: Draw our National Flag

import pygame
import math


# Define colour
BLUE = (0, 0, 255)
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = (255,0,0)
GREEN = (34,139,34)
ORANGE = (255,100,0)
 
pygame.init()

# Set the width and height of the screen [width, height]
size = (700, 700)
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
font = pygame.font.Font('freesansbold.ttf', 12)

screen.fill(BLACK)
x=100
y=200
height=100
width=400
angle=0
pygame.draw.rect(screen, ORANGE,(x,y,width,height))
pygame.draw.rect(screen, WHITE,(x,300,width,height))
pygame.draw.rect(screen, GREEN,(x,400,width,height))
pygame.draw.circle(screen,BLUE,[300,350],50,2)
pygame.draw.line(screen,BLUE,[300,300],[300,400],1)

x1 = 300
y1 = 350
angle = math.radians(0)
for i in range(24):
    x2 = x1 + math.cos(angle) * 50
    y2 = y1 + math.sin(angle) * 50
    pygame.draw.line(screen,BLUE,[x1,y1],[x2,y2],1)
    angle=angle+15
pygame.display.flip() #update screen
pygame.time.wait(5000) 

# Close the window and quit.    
pygame.quit()
