package com.example.shukrithi.breakoutgame;

import android.app.Activity;
import android.content.Context;
//import android.content.res.AssetFileDescriptor;
//import android.content.res.AssetManager;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.RectF;
//import android.media.AudioManager;
//import android.media.SoundPool;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.io.IOException;

public class BreakoutGame extends Activity {

    // gameView will be the view of the game
    // It will also hold the logic of the game
    // and respond to screen touches as well
    BreakoutView breakoutView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Initialize gameView and set it as the view
        breakoutView = new BreakoutView(this);
        setContentView(breakoutView);

    }

    class BreakoutView extends SurfaceView implements Runnable {

        //Main thread
        Thread gameThread = null;

        SurfaceHolder gameHolder;

        // A boolean which we will set and unset when the game is running- or not.
        volatile boolean playing;

        // Game is paused at the start
        boolean paused = true;

        // A Canvas and a Paint object
        Canvas canvas;
        Paint paint;

        // This variable tracks the game frame rate
        long fps;

        // This is used to help calculate the fps
        private long timeThisFrame;

        // The size of the screen in pixels
        int screenX;
        int screenY;

        // The players paddle
        Paddle paddle;

        // A ball
        Ball ball;

        // Up to 200 bricks
        Brick[] bricks = new Brick[200];
        int numBricks = 0;

        //int row2=3;
        int newRow;
       // int broken;
        //int screen[][];

        // The score
        int score = 0;
        int highScore=0;

        // Lives
        int flag=0;
        int lives = 5;
        int hitScreen =0;
        int lastRow=3;
        int hitCount=0;
        int lasthit=0;
        // When the we initialize (call new()) on gameView
        // This special constructor method runs
        public BreakoutView(Context context) {
            super(context);

            // Initialize gameHolder and paint objects
            gameHolder = getHolder();
            paint = new Paint();

            // Get a Display object to access screen details
            Display display = getWindowManager().getDefaultDisplay();
            // Load the resolution into a Point object
            Point size = new Point();
            display.getSize(size);

            screenX = size.x;
            screenY = size.y;

            paddle = new Paddle(screenX, screenY);

            // Create a ball
            ball = new Ball(screenX, screenY);


            createBricksAndRestart();

        }

        public void createBricksAndRestart() {

            // Put the ball back to the start
            ball.reset(screenX, screenY);

            int brickWidth = screenX / 16;
            int brickHeight = screenY / 10;

//            for(int i=0; i<8;i++){
//                for(int j=0;j<8;j++){
//                    screen[i][j]=0;
//                }
//            }
            // Build a wall of bricks
            numBricks = 0;
            for (int column = 0; column < 16; column++) {
                for (int row = 0; row < 3; row++) {
                    bricks[numBricks] = new Brick(row, column, brickWidth, brickHeight);
                    numBricks++;
                    //screen[row][column]=1;
                }
            }
            // if game over reset scores and lives
            if (lives == 0) {
                score = 0;
                lives = 5;
                lastRow=3;
                hitScreen =0;
                hitCount=0;
                //flag=0;
            }

        }

        @Override
        public void run() {
            while (playing) {
                // Capture the current time in milliseconds in startFrameTime
                long startFrameTime = System.currentTimeMillis();
                // Update the frame
                if (!paused) {
                    try {
                        update();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                // Draw the frame
                //draw();
                DrawThread begin = new DrawThread();
                begin.start();
                /* object1.join(); */
                try {
                    begin.join();
                } catch (Exception ex) {
                    System.out.println(ex);
                }
                // Calculate the fps this frame
                // We can then use the result to
                // time animations and more.
                timeThisFrame = System.currentTimeMillis() - startFrameTime;
                if (timeThisFrame >= 1) {
                    fps = 1000 / timeThisFrame;
                }

            }

        }

        // Everything that needs to be updated goes in here
        // Movement, collision detection etc.
        public void update() throws InterruptedException {

            // Move the paddle if required
            paddle.update(fps);

            ball.update(fps);

            // Check for ball colliding with a brick
            for (int i = 0; i < numBricks; i++) {
                if (bricks[i].getVisibility()) {
                    if (RectF.intersects(bricks[i].getRect(), ball.getRect())) {
                        bricks[i].count--;
                        //lasthit=i;
                        if(bricks[i].count==0) {
                            bricks[i].setInvisible();
                            score = score + 10;
                            if(bricks[i].brow==lastRow){
                                hitCount++;
                            }
//                            if(bricks[i].powerUp){
//                                for (int k = 0; k < numBricks; k++){
//                                    bricks[i].count--;
//                                }
//                            }
                        }
                        if(hitCount==16){
                            lastRow--;
                            hitCount=0;
                        }
                        ball.reverseYVelocity();

//                        broken++;
//                        if(broken%8==0){
//                             lastRow--;
//                        }
                    }
                }
            }

            // Check for ball colliding with paddle
            if (RectF.intersects(paddle.getRect(), ball.getRect())) {
                flag=1;
                ball.setRandomXVelocity();
                ball.reverseYVelocity();
                ball.clearObstacleY(paddle.getRect().top - 2);
                //lasthit=0;
            }
            // Bounce the ball back when it hits the bottom of screen
            if (ball.getRect().bottom > screenY) {
                ball.reverseYVelocity();
                ball.clearObstacleY(screenY - 2);
                int brickWidth = screenX / 16;
                int brickHeight = screenY / 10;
                //lasthit=0;
////                for (int i = 0; i < numBricks; i++) {
//                    bricks[i].getRect().bottom=bricks[i].getRect().bottom+1;
//                    bricks[i].getRect().top=bricks[i].getRect().top+1;
//                }


                newRow=0;
//                for (int column = 0; column < 8; column++)  {
////
//                        bricks[numBricks] = new Brick(newrow, column, brickWidth, brickHeight);
//                        numBricks++;
//                        //screen[newrow][column]=1;
//                }

//                //hitscreen=hitscreen+1;
                //flag=1;

                //newrow=0;
                for (int column = 0; column < 16; column++) {
//
                    for ( newRow = lastRow; newRow < lastRow + 1; newRow++) {
                        bricks[numBricks] = new Brick(newRow, column, brickWidth, brickHeight);
                        numBricks++;
                        //screen[newrow][column]=1;
                    }
                }
                lastRow=newRow;
//
//                LostLifeThread lostlife = new LostLifeThread();
//                lostlife.start();
//                /* object1.join(); */
//                try {
//                    lostlife.join();
//                } catch (Exception ex) {
//                    System.out.println(ex);
//                }
                lives--;
//
                if (lives == 0) {
                    paused = true;
                    //draw();
                    LostThread lost = new LostThread();
                    lost.start();
                    /* object1.join(); */
                    try {
                        lost.join();
                    } catch (Exception ex) {
                        System.out.println(ex);
                    }
                    gameThread.sleep(2000);
                    createBricksAndRestart();
                }
            }

            // Bounce the ball back when it hits the top of screen
            if (ball.getRect().top < 0)

            {
                ball.reverseYVelocity();
                ball.clearObstacleY(12);
                //lasthit=0;


            }

            // If the ball hits left wall bounce
            if (ball.getRect().left < 0)

            {
                ball.reverseXVelocity();
                ball.clearObstacleX(2);
                //lasthit=0;

            }

            // If the ball hits right wall bounce
            if (ball.getRect().right > screenX - 10) {

                ball.reverseXVelocity();
                ball.clearObstacleX(screenX - 22);
                //lasthit=0;


            }

//             Pause if cleared screen
            if (score == numBricks * 10){
                paused = true;
                //draw();
                WonThread won = new WonThread();
                won.start();
                /* object1.join(); */
                try {
                    won.join();                } catch (Exception ex) {
                    System.out.println(ex);
                }
                gameThread.sleep(2000);
                createBricksAndRestart();

            }

        }



        class WonThread extends Thread
        {
            public void run()
            {
                //Has the player cleared the screen?
                if (gameHolder.getSurface().isValid()) {
                    // Lock the canvas ready to draw+
                    canvas = gameHolder.lockCanvas();

                    // Draw the background color
                    canvas.drawColor(Color.argb(255, 0, 128, 0));
                    if (score == numBricks * 10) {
                        paint.setTextSize(90);
                        canvas.drawText("Congratulations, you won!", screenX / 4, screenY / 2, paint);
                        if (score > highScore) {
                            highScore = score;
                        }
                        canvas.drawText("Score:" + score + " High Score: " + highScore, screenX / 4, screenY / 2, paint);
                    }
                    gameHolder.unlockCanvasAndPost(canvas);
                }
            }
        }

        class LostThread extends Thread
        {
            public void run()
            {
                if (gameHolder.getSurface().isValid()) {
                    // Lock the canvas ready to draw
                    canvas = gameHolder.lockCanvas();

                    // Draw the background color
                    canvas.drawColor(Color.argb(255, 26, 128, 182));
                    if (lives <= 0) {
                        paint.setTextSize(90);
                        canvas.drawText("Aww, snap! Keep trying :P", screenX / 4, screenY / 3, paint);
                        if (score > highScore) {
                            highScore = score;
                        }
                        canvas.drawText("Score:" + score + " High score: " + highScore, screenX / 4, screenY / 2, paint);

                    }
                    gameHolder.unlockCanvasAndPost(canvas);

                }
            }
        }
        class DrawThread extends Thread {
            public void run() {
                // Make sure our drawing surface is valid or we crash
                if (gameHolder.getSurface().isValid()) {
                    // Lock the canvas ready to draw
                    canvas = gameHolder.lockCanvas();

                    // Draw the background color
//                    if(lives==5) {
                        canvas.drawColor(Color.argb(55, 0, 0, 0));
//                    }
//                    if(lives==4) {
//                        canvas.drawColor(Color.argb(200, 0, 0, 0));
//                    }
//                    if(lives==3) {
//                        canvas.drawColor(Color.argb(155, 0, 0, 0));
//                    }
//                    if(lives==2) {
//                        canvas.drawColor(Color.argb(100, 0, 0, 0));
//                    }
//                    if(lives==1) {
//                        canvas.drawColor(Color.argb(55, 0, 0, 0));
//                    }

                    // Choose the brush color for drawing
                    paint.setColor(Color.argb(255, 255, 255, 255));

                    // Draw the paddle
                    canvas.drawRect(paddle.getRect(), paint);

                    // Draw the ball
                    canvas.drawRect(ball.getRect(), paint);

                    // Change the brush color for drawing
                    paint.setColor(Color.argb(255, 249, 129, 0));

                    // Draw the bricks if visible
                    for (int i = 0; i < numBricks; i++) {
                        if (bricks[i].getVisibility()) {
//                            if(i%27==0)
//                            {
//                                bricks[i].powerUp=true;
//                                paint.setColor(Color.argb(255, 255, 215, 0));
//                                canvas.drawRect(bricks[i].getRect(), paint);
//                            }
//                            else{
                                if(bricks[i].count==5){
                                    paint.setColor(Color.argb(255, 128, 0, 0));
                                    canvas.drawRect(bricks[i].getRect(), paint);
                                }
                                if(bricks[i].count==4){
                                    paint.setColor(Color.argb(255, 139, 0, 0));
                                    canvas.drawRect(bricks[i].getRect(), paint);
                                }
                                if(bricks[i].count==3){
                                    paint.setColor(Color.argb(255, 165, 42, 42));
                                    canvas.drawRect(bricks[i].getRect(), paint);
                                }
                                if(bricks[i].count==2){
                                    paint.setColor(Color.argb(255, 178, 34, 34));
                                    canvas.drawRect(bricks[i].getRect(), paint);
                                }
                                if(bricks[i].count==1){
                                    paint.setColor(Color.argb(255, 220, 20, 60));
                                    canvas.drawRect(bricks[i].getRect(), paint);
                                }
//                                if(bricks[i].powerUp){
//                                    paint.setColor(Color.argb(255, 128, 0, 0));
//                                    canvas.drawRect(bricks[i].getRect(), paint);
//                                }
//                            }


//                            paint.setColor(Color.argb(255, 199, 21, 133));
//                            canvas.drawRect(bricks[i].getRect(), paint);

                            paint.setColor(Color.argb(255, 255, 255, 255));
                            paint.setTextSize(40);
                            canvas.drawText( " " + bricks[i].count , bricks[i].getRect().left+40, bricks[i].getRect().bottom-30, paint);
                            //screen[bricks[i].brow][bricks[i].bcol]=1;
                        }
                    }

                    ScoreThread object1 = new ScoreThread();
                    object1.start();
                    /* object1.join(); */
                    try {
                        object1.join();
                    } catch (Exception ex) {
                        System.out.println(ex);
                    }
//                    //Has the player cleared the screen?
//                    if (score == numBricks * 10) {
//                        paint.setTextSize(90);
//                        canvas.drawText("Congratulations, you won!", screenX/3, screenY / 2, paint);
//                        if(score>highscore){
//                            highscore=score;
//                        }
//                        canvas.drawText("Score:" + score + " High score: " + highscore, screenX/3, screenY / 2, paint);
//                    }
                    //Has the player lost?
//                    if (lives <= 0) {
//                        paint.setTextSize(90);
//                        canvas.drawText("Aww, snap! Keep trying :P", screenX/3, screenY / 3, paint);
//                        if(score>highscore){
//                            highscore=score;
//                        }
//                        canvas.drawText("Score:" + score + " High score: " + highscore, screenX/3, screenY / 2, paint);
//                    }
                    // Draw everything to the screen
                    gameHolder.unlockCanvasAndPost(canvas);
                }
            }
        }
        class ScoreThread extends Thread
        {
            public void run()
            {
                paint.setColor(Color.argb(255, 255, 255, 255));

                // Draw the score
                paint.setTextSize(40);
                canvas.drawText("Score: " + score + "   Lives: " + lives + " lastRow: " + lastRow, 10, 1040, paint);
                //canvas.drawText("Score: " + score + "   Lives: " + lives + "  Number  of Bricks: " +numBricks, 10, 50, paint);
            }
        }

//                    DisplayThread object1 = new DisplayThread();
//                    object1.start();
//                    /* object1.join(); */
//                    try {
//                        object1.join();
//                    } catch (Exception ex) {
//                        System.out.println(ex);
//                    }
//                    //Has the player cleared the screen?
//                    if (score == numBricks * 10) {
//                        paint.setTextSize(90);
//                        canvas.drawText("Congratulations, you won!", 10, screenY / 2, paint);
//                    }
//                    //Has the player lost?
//                    if (lives <= 0) {
//                        paint.setTextSize(90);
//                        canvas.drawText("Aww, snap! Keep trying :P", 10, screenY / 2, paint);
//                    }
//                    // Draw everything to the screen
//                    gameHolder.unlockCanvasAndPost(canvas);
//                }
//            }
//        }
//

        // Draw the newly updated scene
//        public void draw() throws InterruptedException {
//
//            // Make sure our drawing surface is valid or we crash
//            if (gameHolder.getSurface().isValid()) {
//                // Lock the canvas ready to draw
//                canvas = gameHolder.lockCanvas();
//
//                // Draw the background color
//                canvas.drawColor(Color.argb(255, 26, 128, 182));
//
//                // Choose the brush color for drawing
//                paint.setColor(Color.argb(255, 255, 255, 255));
//
//                // Draw the paddle
//                canvas.drawRect(paddle.getRect(), paint);
//
//                // Draw the ball
//                canvas.drawRect(ball.getRect(), paint);
//
//                // Change the brush color for drawing
//                paint.setColor(Color.argb(255, 249, 129, 0));
//
//                // Draw the bricks if visible
//                for (int i = 0; i < numBricks; i++) {
//                    if (bricks[i].getVisibility()) {
//                        canvas.drawRect(bricks[i].getRect(), paint);
//                        //screen[bricks[i].brow][bricks[i].bcol]=1;
//                    }
//                }
//
//                DisplayThread object1 = new DisplayThread();
//                object1.start();
//                /* object1.join(); */
//                try {
//                    object1.join();
//                }
//                catch(Exception ex)
//                {
//                    System.out.println(ex);
//                }
//                //Has the player cleared the screen?
//                if (score == numBricks * 10) {
//                    paint.setTextSize(90);
//                    canvas.drawText("Congratulations, you won!", 10, screenY / 2, paint);
//                }
//                //Has the player lost?
//                if (lives <= 0) {
//                    paint.setTextSize(90);
//                    canvas.drawText("Sorry, Please try again.", 10, screenY / 2, paint);
//                }
//                // Draw everything to the screen
//                gameHolder.unlockCanvasAndPost(canvas);
//            }
//        }

        // If SimpleGameEngine Activity is paused/stopped
        // shutdown our thread.
        public void pause() {
            playing = false;
            try {
                gameThread.join();
            } catch (InterruptedException e) {
                Log.e("Error:", "joining thread");
            }
        }

        // If SimpleGameEngine Activity is started then
        // start our thread.
        public void resume() {
            playing = true;
            gameThread = new Thread(this);
            gameThread.start();
        }

        // The SurfaceView class implements onTouchListener
        // So we can override this method and detect screen touches.
        @Override
        public boolean onTouchEvent(MotionEvent motionEvent) {
            switch (motionEvent.getAction() & MotionEvent.ACTION_MASK) {
                // Player has touched the screen
                case MotionEvent.ACTION_DOWN:
                    paused = false;
                    if (motionEvent.getX() > screenX / 2) {

                        paddle.setMovementState(paddle.RIGHT);
                    } else

                    {
                        paddle.setMovementState(paddle.LEFT);
                    }

                    break;

                // Player has removed finger from screen
                case MotionEvent.ACTION_UP:

                    paddle.setMovementState(paddle.STOPPED);
                    break;
            }

            return true;
        }

    }
    // This is the end of our BreakoutView inner class

    // This method executes when the player starts the game
    @Override
    protected void onResume() {
        super.onResume();

        // Tell the gameView resume method to execute
        breakoutView.resume();
    }

    // This method executes when the player quits the game
    @Override
    protected void onPause() {
        super.onPause();

        // Tell the gameView pause method to execute
        breakoutView.pause();
    }

}
// This is the end of the BreakoutGame class
