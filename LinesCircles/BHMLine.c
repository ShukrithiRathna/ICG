/* Shukrithi Rathna
CED16I031
Print line using Bresenham's line algorithm
31-7-19
*/
#include<stdio.h>
#include<graphics.h>
#include<math.h>
float x1,x2,y1,y2;

int main()
	{
			
		int gd = DETECT, gm, color;
		float  x,y;
        int Sign;
	//	float x1 = 100, y1 = 200, x2 = 100, y2 = 300;
		
		printf("\nEnter the coordinates (x1,y1,x2,y2) for the line:  ");
        scanf("%f %f %f %f",&x1,&y1,&x2,&y2);
		//printf("%f %f %f %f",x1,y1,x2,y2);
        initgraph(&gd, &gm, "");
        float Delx=x2-x1;
        float Dely=y2-y1;
        float Slope = abs(Delx/Dely);
		float Error = 0;
        int Signx=1, Signy=1;
        if(Delx<0)
            Signx=-1;
        if(Dely<0)
            Signy=-1;
        if(Delx>Dely)
        {
              y=y1;
            for(x=x1;x<x2;x++)
            {
                putpixel(x,y,GREEN);
                Error=Error+Slope;
                if(Error>=0.5)
                {
                    y=y+Signy;
                    Error=Error-1;
                }

            }
        }
        else
        {
           x=x1;
            for(y=y1;y<y2;y++)
            {
                putpixel(x,y,GREEN);
                Error=Error+Slope;
                if(Error>=0.5)
                {
                    x=x+Signx;
                    Error=Error-1;
                }

            }   
        }
        
      	getchar();
		closegraph();
		return(0);
	}

