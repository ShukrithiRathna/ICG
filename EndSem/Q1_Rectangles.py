# 5-10-19
# CED16I031 - Shukrithi Rathna
# Program: Draw 25 rectangles filled with different shades of RED colour

import pygame
import math


# Define colour
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = [(255,0,0),(255,20,0),(255,30,0),(255,40,0),(255,50,0),(255,60,0),(255,70,0),(255,80,0),(255,35,0),(255,10,0),(255,0,25),(255,0,50),(255,50,50),(255,40,50),(255,60,60),(255,60,70),(255,70,30),(255,40,20),(255,90,50),(255,20,45),(255,55,87),(255,43,65),(255,40,10),(255,50,23),(255,0,0)]

 
pygame.init()

# Set the width and height of the screen [width, height]
size = (1000, 1000)
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
font = pygame.font.Font('freesansbold.ttf', 12)
screen.fill(BLACK)
x=0
y=0
height=100
width=100
j=0
k=0

pygame.draw.rect(screen, RED[0],(x,y,width,height))    
for i in range(24):
    CurrentShade=[255,j,k]
    if(x<800):
        x=x+104
    else:
        x=0
        y=y+104
        k+=25
    j+=25
    pygame.draw.rect(screen, RED[i],(x,y,width,height))    



pygame.display.flip() #update screen
pygame.time.wait(5000) 

# Close the window and quit.    
pygame.quit()
