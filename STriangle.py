#13-9-19
#CED16I031
#Shukrithi Rathna
#Fractal graphics  - Sierpinski's triangle
#the program takes coordinates out of outer triangle and degree as input

def get_mid(X,Y): #function to get mid poitns of side
    x = (X[0]+Y[0])/2
    y = (X[1]+Y[1])/2
    return(round(x),round(y))

def drawTriangle(A,B,C):
    pygame.draw.line(screen, BLUE, [A[0], A[1]], [B[0], B[1]])
    pygame.draw.line(screen, BLUE, [B[0], B[1]], [C[0], C[1]])
    pygame.draw.line(screen, BLUE, [A[0], A[1]], [C[0], C[1]])
   
def sTriangle(A,B,C,degree):
    drawTriangle(A,B,C)
    if degree > 0:
        sTriangle(A,get_mid(A,B),get_mid(A,C),degree-1)
        sTriangle(B,get_mid(A,B),get_mid(B,C),degree-1)
        sTriangle(C,get_mid(C,B), get_mid(A,C),degree-1)

#Triangle parameters
A=list(map(int, input("Enter coordinates of point A: ").strip().split()))
B=list(map(int, input("Enter coordinates of point B: ").strip().split()))
C=list(map(int, input("Enter coordinates of point C: ").strip().split()))
degree = int(input("Enter degree: "))

import pygame

# Define colour
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
pygame.init()
# Set the width and height of the screen [width, height]
size = (700, 700)
screen = pygame.display.set_mode(size)

# Loop until 
done = False
# -------- Main Program Loop -----------
while not done:
    # --- Main event loop
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    sTriangle(A,B,C,degree)
    pygame.display.flip()
# Close the window and quit.
pygame.quit()

