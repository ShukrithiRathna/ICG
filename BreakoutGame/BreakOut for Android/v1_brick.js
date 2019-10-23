package com.example.shukrithi.breakoutgame;

import android.graphics.RectF;
import java.util.Random;



public class Brick {

    //public boolean powerUp;
    private RectF rect;

    private boolean isVisible;
    public boolean powerUp;

    public int brow, bcol;
    public Brick(int row, int column, int width, int height){

        isVisible = true;
        powerUp=false;

        int padding = 1;
        brow=row;
        bcol=column;
        rect = new RectF(column * width + padding,
                row * height + padding,
                column * width + width - padding,
                row * height + height - padding);
    }

    public RectF getRect(){
        return this.rect;
    }
    Random rand = new Random();

    int  n = rand.nextInt(5) + 1;
    public int count=n;
    public void setInvisible(){

        isVisible = false;
    }

    public void setVisible(){

        isVisible = true;
    }
    public boolean getVisibility(){
        return isVisible;
    }
}


