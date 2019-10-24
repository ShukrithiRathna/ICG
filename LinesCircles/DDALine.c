/* Shukrithi Rathna
CED16I031
Print line using DDA algorithm
30-7-19

*/
#include<stdio.h>
#include<graphics.h>
#include<math.h>
int main()
	{
			
		int gd = DETECT, gm, color;
		float  x,y;
	//	float x1 = 100, y1 = 200, x2 = 100, y2 = 300;
		float x1,x2,y1,y2;
		printf("\nEnter the coordinates (x1,y1,x2,y2) for the line: () ");
        scanf("%f %f %f %f",&x1,&y1,&x2,&y2);
		float dely=y2-y1;
		float delx = x2-x1;
		float slope = dely/delx;
        int signx=1, signy=1;
        if(delx<0)
            signx=-1;
        if(dely<0)
            signy=-1;
        x=x1;
        y=y1;
        //printf("%f %f",signx*delx,signy*dely);
        initgraph(&gd, &gm, "");
        //printf("%d %d",signx,signy);
        int i=1;
        if((signx*delx)>=(signy*dely))
        {
            //printf("inside");
        
            while(i<(signx*delx))
            {
                x=x+signx;
                y=y+(signx*slope);
                putpixel(x,y,GREEN);
                i++;
                //delay(100);
            }
            
        }
        else if((signy*dely)>(signx*delx))
        {
           //printf("Entered else");}
            while(i<(signy*dely))
            {
                y=y+signy;
                x=x+(signy/slope);
                //printf("%f ",signx/slope);
                putpixel(x,y,GREEN);
                i++;
                //delay(100);
            }
            
        }
        getch();
        closegraph();
		return(0);
	}

