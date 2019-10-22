#13-9-19
#CED16I031
#Shukrithi Rathna
#bouncing Ball 

import pygame

#ball initial parameters
radius = 10     
xc=350
yc=100

# Define colour
BLUE = (0, 0, 255)
BLACK = (0,0,0)
WHITE = (255,255,255)
 
pygame.init()

# Set the width and height of the screen [width, height]
size = (700, 700)
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
UP= True
#print(not(UP))

# every 50 frames, increase movement. adjust higher or lower for varying speeds
#if frames % 75 == 0:
#    UP=not(UP)
#        #print(frames,UP)
# Loop until 
ContinueGame= True
#x = -1  # keep track of the x location
frames = 0  # keep track of frames
while ContinueGame:
    # --- Main event loop
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            ContinueGame = False

    # clear the screen each time
    screen.fill(BLACK)
     # draw the circle (notice no int() function here)
    pygame.draw.circle(screen, BLUE, [xc,yc], radius, 2 ) #drawing the ball on screen
    #pygame.draw.circle(screen, BLUE, [xc,yc], 1, 0 )
    pygame.time.wait(1)
    
#updating position and size of the ball every fifty frames
    if frames % 50 ==0:
        if radius < 75:
            if(UP):
                yc=yc+10
            else:
                yc=yc-5
        else:
            if(UP):
                yc=yc+20
            else:
                yc=yc-10
        radius= radius+1
    if frames % 500 ==0:
        UP=not(UP)
        #pygame.time.wait(30)
    if(radius>200):
        pygame.time.wait(100) #stop bouncing ball 
    frames += 1

    # flip the display
    pygame.display.flip()
 
# Close the window and quit.    
pygame.quit()


