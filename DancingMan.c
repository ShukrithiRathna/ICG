/* Shukrithi Rathna
CED16I031
Dancing Stick Man
2-8-19
*/
#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define BLACK 0
#define BLUE 1


float x0,z0,Radius;
float yBody;
float yHand;
float rBody;
float lBody;

void InitMan();
void InitMan()
{
        Radius =20;
        x0=300;
        z0=200;
        yBody=z0+Radius;
        yHand=z0-0.5*Radius;
        rBody=x0+Radius;
        lBody=x0-Radius;
}
void DrawLine(float x1,float y1, float x2, float y2, int colour);
void DrawCircle(float x, float y, float Radius, int colour);
void PlotPoints(float x, float y, float Radius,int colour);
void DrawMan(int pos);

void DrawMan(int pos)
{
    
    DrawCircle(0,Radius,Radius,BLUE);//face
    DrawLine(x0,yBody,x0,yBody+70, BLUE);//body

    //position 1
    DrawLine(x0,yHand+50,lBody,yHand+30, abs(pos-1));//left hand
    DrawLine(x0,yHand+50,rBody,yHand+(1.5*30),abs(pos-1));// right hand
    DrawLine(x0,yBody+70,lBody,yBody+90,abs(pos-1));//left leg
    DrawLine(x0,yBody+70,rBody,yBody+60,abs(pos-1));// right leg
    
    //position 2
    DrawLine(x0,yHand+50,lBody,yHand+(1.5*30),pos);//left hand
    DrawLine(x0,yHand+50,rBody,yHand+30,pos);// right hand
    DrawLine(x0,yBody+70,lBody,yBody+60,pos);//left leg
    DrawLine(x0,yBody+70,rBody,yBody+90,pos);// right leg
    
    delay(500);
   
}

int main()
{
        
        int gd = DETECT, gm, color;
        initgraph(&gd, &gm, "");
        int i=0;
        InitMan();
        while(i<10)
        {
            DrawMan(0);
            DrawMan(1);
            DrawMan(0);
            i++;
        }
        
        getch();
        closegraph();
        return(0);
}
void DrawLine(float x1,float y1, float x2, float y2,int colour)
{
        float  x,y;
	//	float x1 = 100, y1 = 200, x2 = 100, y2 = 300;
		//float x1,x2,y1,y2;
		//printf("\nEnter the coordinates (x1,y1,x2,y2) for the line: () ");
        //scanf("%f %f %f %f",&x1,&y1,&x2,&y2);
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
        //initgraph(&gd, &gm, "");ignx/
        int i=1;
        if((signx*delx)>=(signy*dely))
        {
            //printf("inside");
        
            while(i<(signx*delx))
            {
                x=x+signx;
                y=y+(signx*slope);
                putpixel(x,y,colour);
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
                putpixel(x,y,colour);
                i++;
                //delay(100);
            }
            
        }
        //getch();
	//getchar();
}

void PlotPoints(float x, float y, float Radius, int colour)
{
    /*
        -> The circle is divided into 8 octants.
        -> Given a point in 1 octant, the other 7 can be found using symmetry.
    */
    
    putpixel(x+x0,y+z0,colour);  //Octant I
    putpixel(y+x0,x+z0,colour);  //Octant II
    putpixel(-y+x0,x+z0,colour);  //Octant III
    putpixel(x+x0,-y+z0,colour); //Octant IV 
    putpixel(-x+x0,-y+z0,colour);  //Octant V
    putpixel(-y+x0,-x+z0,colour);  //Octant VI
    putpixel(y+x0,-x+z0,colour); //Octant VII 
    putpixel(-x+x0,y+z0,colour);  //Octant VIII
       
}

void DrawCircle(float x, float y,float Radius,int colour)
{
    /* Given (x,y) next points could be: 
        -> p1 - (x+1,y)
        -> p2 - (x+1,y-1)
        
        # The algorithm identifies the point closest to the true circle using a decision parameter d 
        and that point is Plotted.
    
        -> d1=pow(x+1,2)+pow(y,2)+pow(Radius,2) //dist(p1 and centre) - dist(true point and centre)
        -> d2=pow(x+1,2)+pow(y-1,2)+pow(Radius,2)//dist(p2 and centre) - dist(true point and centre)
        -> d=d+d1+d2 
        
        -> d1 is always postiive
        -> d2 is always negative

        inital point = (0,Radius)
        => d= 3-2*Radius
    */
    while(x<=y) //(moving from 90 degrees to 45 degrees in the first octant)
    {
        
       
        int d= 3-2*Radius; //initial value of d where x=0, Radius= Radius
        while(x<=y)  
        {  
            if(d<=0)  // => p1 is closer to true point
            {     
                d=d+(4*x)+6; 
                PlotPoints(x+1,y,Radius,colour); 
                /*
                    x is incremented by 1
                    -> d1=pow(x+2,2)+pow(y,2)+pow(Radius,2)
                    -> d2=pow(x+2,2)+pow(y-1,2)+pow(Radius,2)
                    => d=d+(4*x)+6;
                */
            }  
            else  // => p2 is closer to true point
            {  
                d=d+(4*x)-(4*y)+10;  // x is incremented by 1 and y is decremented by 1
                PlotPoints(x+1,y-1,Radius,colour);
                y=y-1;  
            }  
            x=x+1;  
        }
       
    }
}
