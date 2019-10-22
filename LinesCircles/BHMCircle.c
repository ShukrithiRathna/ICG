/* Shukrithi Rathna
CED16I031
Print circle using Bresenham's algorithm
2-8-19
*/



#include<stdio.h>
#include<graphics.h>
#include<math.h>
float x0,z0;
void PlotPoints(float x, float y, float r);
void PlotPoints(float x, float y, float r)
{
    /*
        -> The circle is divided into 8 octants.
        -> Given a point in 1 octant, the other 7 can be found using symmetry.
    */
    
    putpixel(x+x0,y+z0,GREEN);  //Octant I
    putpixel(y+x0,x+z0,GREEN);  //Octant II
    putpixel(-y+x0,x+z0,GREEN);  //Octant III
    putpixel(x+x0,-y+z0,GREEN); //Octant IV 
    putpixel(-x+x0,-y+z0,GREEN);  //Octant V
    putpixel(-y+x0,-x+z0,GREEN);  //Octant VI
    putpixel(y+x0,-x+z0,GREEN); //Octant VII 
    putpixel(-x+x0,y+z0,GREEN);  //Octant VIII
    
    
    //putpixel(round(x0),round(z0),BLUE);
    //putpixel(round(x),round(y),GREEN); //Octant I #IV
    //putpixel(round(y),round(x),GREEN); //Octant II - # VII
    ////putpixel(round(y-(2*x0)),round(x),GREEN); //Octant III
    ////putpixel(round(x-(2*x0)),round(y),GREEN); //Octant IV #I
    //putpixel(round(x-x0),round(y-z0),GREEN); //Octant V
    ////putpixel(round(y-(2*x0)),round(x-(2*z0)),GREEN); //Octant VI 
    //putpixel(round(y),round(x-(2*z0)),GREEN); //Octant VII - #II
    //putpixel(round(x),round(y-(2*z0)),GREEN); //Octant VIII
    
    
}

void BHM(float x, float y, float r);
void BHM(float x, float y,float r)
{
    /* Given (x,y) next points could be: 
        -> p1 - (x+1,y)
        -> p2 - (x+1,y-1)
        
        # The algorithm identifies the point closest to the true circle using a decision parameter d 
        and that point is plotted.
    
        -> d1=pow(x+1,2)+pow(y,2)+pow(r,2) //dist(p1 and centre) - dist(true point and centre)
        -> d2=pow(x+1,2)+pow(y-1,2)+pow(r,2)//dist(p2 and centre) - dist(true point and centre)
        -> d=d+d1+d2 
        
        -> d1 is always postiive
        -> d2 is always negative

        inital point = (0,r)
        => d= 3-2*r
    */
    /*while(x<=y) //(moving from 90 degrees to 45 degrees in the first octant)
    {*/
        
       
        int d= 3-2*r; //initial value of d where x=0, r= r
        while(x<=y)  
        {  
            if(d<=0)  // => p1 is closer to true point
            {     
                d=d+(4*x)+6; 
                PlotPoints(x+1,y,r); 
                /*
                    x is incremented by 1
                    -> d1=pow(x+2,2)+pow(y,2)+pow(r,2)
                    -> d2=pow(x+2,2)+pow(y-1,2)+pow(r,2)
                    => d=d+(4*x)+6;
                */
            }  
            else  // => p2 is closer to true point
            {  
                d=d+(4*x)-(4*y)+10;  // x is incremented by 1 and y is decremented by 1
                PlotPoints(x+1,y-1,r);
                y=y-1;  
            }  
            x=x+1;  
        }
       
    //}
}
int main()
	{
		float  x,y,r;
        printf("\nEnter the coordinates of centre of circle:  ");
        scanf("%f %f",&x0,&z0);
        printf("Enter the radius:");
        scanf("%f",&r);
        int gd = DETECT, gm, color;
        initgraph(&gd, &gm, "");
        //float x1 = 100, y1 = 200, x2 = 100, y2 = 300;
		//float x1,y1; //coordinates of center of circle
        //PlotPoints(x0,z0+r,r);
        //x0=100;
        //z0=100;
        //r=50;
        BHM(0,r,r);
        //PlotPoints(x0,z0+r,r);
        putpixel(x0,z0,BLUE);
        getch();
        closegraph();
        return(0);
	}

