/* Shukrithi Rathna
CED16I031
Man
2-8-19
*/
#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define BLACK 0
#define BLUE 1
void drawLine(float x1,float y1, float x2, float y2, int colour);
void drawWindow();
void drawBuilding();
void drawDoor();


int main()
{
        
        int gd = DETECT, gm, color;
        initgraph(&gd, &gm, "");
        int i=0;
        drawBuilding();
        drawDoor();
        drawWindow();
        drawLine(175,400,120,450,1);
        drawLine(440,400,385,450,1);
        getch();
        closegraph();
        return(0);
}
void drawLine(float x1,float y1, float x2, float y2,int colour)
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

void drawWindow()
{
     //WINDOW 1
        drawLine(405,395,405,315,1);//0-1.5 L
        drawLine(375,395,375,315,1);//0-1.5 R
        
        drawLine(400,390,400,320,1);//0-1.5 L
        drawLine(390,390,390,320,1);//0-1.5 M
        drawLine(380,390,380,320,1);//0-1.5 R
        
        drawLine(380,320,400,320,1);//
        drawLine(380,390,400,390,1);//

        drawLine(375,315,405,315,1);//
        drawLine(375,355,405,355,1);//M
        drawLine(375,395,405,395,1);//

        //WINDOW 2
        drawLine(340,395,340,315,1);//0-1.5 L
        drawLine(370,395,370,315,1);//0-1.5 R
        
        drawLine(340+5,395-5,340+5,315+5,1);//0-1.5 L
        drawLine(355,395-5,355,315+5,1);//0-1.5 M
        drawLine(370-5,395-5,370-5,315+5,1);//0-1.5 R
        
        drawLine(365,320,345,320,1);//
        drawLine(365,390,345,390,1);//

        drawLine(370,315,340,315,1);//
        drawLine(370,355,340,355,1);//M
        drawLine(370,395,340,395,1);//
        //WINDOW 3

        drawLine(305,395,305,315,1);//0-1.5 L
        drawLine(335,395,335,315,1);//0-1.5 R

        drawLine(310,390,310,320,1);//0-1.5 L
        drawLine(320,390,320,320,1);//0-1.5 M
        drawLine(330,390,330,320,1);//0-1.5 R

        drawLine(335,315,305,315,1);//
        drawLine(335,395,305,395,1);//

        drawLine(330,320,310,320,1);//
        drawLine(330,355,310,355,1);//M
        drawLine(330,390,310,390,1);//

        //WINDOW 21
        drawLine(405,395-100,405,315-100,1);//0-1.5 L
        drawLine(375,395-100,375,315-100,1);//0-1.5 R
        
        drawLine(400,390-100,400,320-100,1);//0-1.5 L
        drawLine(390,390-100,390,320-100,1);//0-1.5 M
        drawLine(380,390-100,380,320-100,1);//0-1.5 R
       
        drawLine(380,320-100,400,320-100,1);//
        drawLine(380,390-100,400,390-100,1);//

        drawLine(375,315-100,405,315-100,1);//
        drawLine(375,355-100,405,355-100,1);//M
        drawLine(375,395-100,405,395-100,1);//
        //WINDOW 22
        drawLine(340,395-100,340,315-100,1);//0-1.5 L
        drawLine(370,395-100,370,315-100,1);//0-1.5 R
      
        drawLine(345,390-100,345,320-100,1);//0-1.5 L
        drawLine(355,390-100,355,320-100,1);//0-1.5 M
        drawLine(365,395-100,365,320-100,1);//0-1.5 R
       
        drawLine(365,320-100,345,320-100,1);//
        drawLine(365,390-100,345,390-100,1);//

        drawLine(370,315-100,340,315-100,1);//
        drawLine(370,355-100,340,355-100,1);//M
        drawLine(370,395-100,340,395-100,1);//
        //WINDOW 33

        drawLine(305,395-100,305,315-100,1);//0-1.5 L
        drawLine(335,395-100,335,315-100,1);//0-1.5 R

        drawLine(310,390-100,310,320-100,1);//0-1.5 L
        drawLine(320,390-100,320,320-100,1);//0-1.5 M
        drawLine(330,390-100,330,320-100,1);//0-1.5 R

        drawLine(335,315-100,305,315-100,1);//
        drawLine(335,395-100,305,395-100,1);//

        drawLine(330,320-100,310,320-100,1);//
        drawLine(330,355-100,310,355-100,1);//M
        drawLine(330,390-100,310,390-100,1);//

    drawLine(305-75,360-80,305-75,315-80,1);//W L
    drawLine(335-75,360-80,335-75,315-80,1);//W R 
    drawLine(310-75,355-80,310-75,320-80,1);//W I L
    drawLine(330-75,355-80,330-75,320-80,1);//W I R 
    drawLine(335-75,315-80,305-75,315-80,1);// W U
    drawLine(335-75,360-80,305-75,360-80,1);// W B
    drawLine(330-75,355-80,310-75,355-80,1);// W I B
    drawLine(330-75,320-80,310-75,320-80,1);// W I U

        
        
       
}
void drawDoor()
{
    drawLine(195,400,195,315,1);//0-1.5 L
    drawLine(285,400,285,315,1);//0-1.5 R
    drawLine(195,315,285,315,1);//
    
    drawLine(237,395,237,320,1);//Door LR
    drawLine(200,395,200,320,1);//Door LL
    drawLine(243,395,243,320,1);//Door RL
    drawLine(280,395,280,320,1);//Door RR
    drawLine(243,395,280,395,1);//BL
    drawLine(200,395,237,395,1);//BR
    drawLine(243,320,280,320,1);//TL
    drawLine(200,320,237,320,1);//TR
}
void drawBuilding()
{
    //horizontal
        drawLine(150,400,450,400,1);//0
        drawLine(181,300,419,300,1);//1
        drawLine(181,305,419,305,1);//1.5
        drawLine(175,200,425,200,1);//2
        drawLine(175,205,425,205,1);//2.5

        //vertical
        drawLine(185,400,185,305,1);//0-1.5 L
        drawLine(415,400,415,305,1);//0-1.5 R
        
        drawLine(181,300,181,305,1);//1-1.5 L
        drawLine(419,300,419,305,1);//1-1.5 R
        
        drawLine(185,300,185,205,1);//1.5-2 L
        drawLine(415,300,415,205,1);//1.5-2 R

        drawLine(175,200,175,205,1);//2-2.5 L
        drawLine(425,200,425,205,1);//2-2.5 R
        
        //top level
            //vertical
            drawLine(193,150,193,187,1);//Roof-3 L
            drawLine(407,150,407,187,1);//Roof-3 R
            drawLine(196,155,196,185,1);//Roof-3.25 L
            drawLine(404,155,404,185,1);//Roof-3.25 R
            drawLine(185,150,185,119,1);//3.30 - 4 L
            drawLine(416,150,416,119,1);//3.30 -4 R
            
            //horizontal
            drawLine(185,150,245,150,1);//3 L
            drawLine(416,150,355,150,1);//3 R
            drawLine(193,155,239,155,1);//3.25 L
            drawLine(407,155,361,155,1);//3.25 R
            drawLine(185,145,249,145,1);//3.30 L
            drawLine(416,145,351,145,1);//3.30 R
            drawLine(185,119,285,119,1);//4 L
            drawLine(416,119,312,119,1);//4 R
    //roof
        drawLine(175,200,300,110,1);
        drawLine(425,200,300,110,1);
}