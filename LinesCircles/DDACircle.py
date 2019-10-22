#13-9-19
#CED16I031
#Shukrithi Rathna
#Circle using DDA Algorithm

import pygame

def drawCircle():
    i=0
    val=2**i
    x1=radius
    y1=0
    x=x1
    y=y1
    while val<radius:
        val=2**i
        i+=1
    eps=1/2**(i-1)
    x2=x1+y1*eps
    y2=y1-eps*x2
    pygame.draw.circle(screen, BLUE, [round(xc+x2), round(yc-y2)], 0, 0)
    while (y1-y)<eps or (x-x1)>eps:
        x2=x1+y1*eps
        y2=y1-eps*x2
        pygame.draw.circle(screen, BLUE, [round(xc+x2), round(yc-y2)], 0, 0)
        x1=x2
        y1=y2
     
#circle parameters
radius = int(input("Enter Radius: "))
xc = int(input("Enter x coordinate of centre: "))
yc = int(input("Enter y coordinate of centre: "))


# Define colour
BLUE = (0, 0, 255)
 

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
    drawCircle()
    pygame.display.flip()
 
# Close the window and quit.
pygame.quit()


