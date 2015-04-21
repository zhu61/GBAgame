#include "myLib.h"
#include "title.h"
#include "face.h"
#include "background.h"
#include <stdlib.h>
#include <stdio.h>
#include "DMA.h"
#include "monster.h"
#include "gameover.h"
#include "text.h"
#include "win.h"
//title
void drawTitle() 
{
    drawBackground(background);
}
//draw frog
void drawFrog(Frog *frog)
{
    drawImage3(frog->x,frog->y,FACE_WIDTH, FACE_HEIGHT, face);
}
void drawDevil(Devil *devil)
{
    drawImage3(devil->x,devil->y,MONSTER_WIDTH, MONSTER_HEIGHT, monster);
}
void drawGameOver()
{
    drawBackground(gameover);
}
void drawHappyFace()
{
    drawBackground(win);
}
int collisionCheck(Frog *frog, Devil *devil)
{
    if (frog->x < (devil->x + MONSTER_WIDTH) && (frog->x + FACE_WIDTH) > devil->x
        && frog->y < (devil->y + MONSTER_HEIGHT) && (frog->y + FACE_HEIGHT) > devil->y)
    {
        return 1;
    }
    else if ((frog->x + FACE_WIDTH) < devil->x + MONSTER_WIDTH && frog->x + FACE_WIDTH > devil->x
        && frog->y < (devil->y + MONSTER_HEIGHT) && (frog->y + FACE_HEIGHT) > devil->y)
    {
        return 1;
    }
    else if (frog->x < (devil->x + MONSTER_WIDTH) && (frog->x + FACE_WIDTH) > devil->x
        && frog->y > (devil->y + MONSTER_HEIGHT) && (frog->y + FACE_HEIGHT) < devil->y)
    {
        return 1;
    }
    else if ((frog->x + FACE_WIDTH) < devil->x + MONSTER_WIDTH && frog->x + FACE_WIDTH > devil->x
      && frog->y > (devil->y + MONSTER_HEIGHT) && (frog->y + FACE_HEIGHT) < devil->y)
    {
        return 1;
    }
    return 0;
}
int main(void)
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    int start = 1;
    int end = 0;
    int size = 20;
    int life = 3;
    int win = 0;
    //face
    Frog *frog = malloc(sizeof(frog));
    frog->x = 140; 
    frog->y  = 100;
    int oldx = frog->x;
    int oldy = frog->y;

    //devil
    Devil *devil = malloc(sizeof(devil));
    devil->x =0;
    devil->y =0;
    int olddx = devil->x;
    int olddy = devil->y;
    int xdir =3;
    int ydir =3;


    while(1)
    {
        if (KEY_DOWN_NOW(BUTTON_DOWN) && start == 0)
        {
            start = 1;
            end = 0;
            frog->x = 140; 
            frog->y  = 100;
            oldx = frog->x;
            oldy = frog->y;
            devil->x =0;
            devil->y =0;
            olddx = devil->x;
            olddy = devil->y;
            xdir =3;
            ydir =3;
            life = 3;

        }
        if (start == 1)
        {

            drawTitle();
            if (KEY_DOWN_NOW(BUTTON_START))
            {
                start = 0;
                drawRiver();

            }

        }
        //start playing

        else if (start == 0 && end == 0 && win == 0)
        {    
            drawRect(5,30,10,10,BLACK);
            drawChar(5, 5, 'l', RED);
            drawChar(5, 10, 'i', RED);
            drawChar(5, 15, 'v', RED);
            drawChar(5, 20, 'e', RED);
            drawChar(5, 25, ':', RED);
            drawChar(5, 30, (char)((int)('0')+life), RED);     
            
            if (KEY_DOWN_NOW(BUTTON_UP))
            {
                frog->x--;
                if (frog->x < 0)
                {
                    frog->x = 0;
                }

            }
            else if (KEY_DOWN_NOW(BUTTON_RIGHT))
            {
                frog->y++;
                if (frog->y >220)
                {
                    frog->y= 220;
                }
            }
            else if (KEY_DOWN_NOW(BUTTON_LEFT))
            {
                frog->y--;
                if(frog->y < 0)
                {
                    frog->y =0;
                }
            }
        devil->x += xdir;
        devil->y += ydir;
        //boundsCheck
        boundsCheck(&devil->y, 239, &ydir,size);
        boundsCheck(&devil->x, 159, &xdir,size);
        //collisiondection
        if (collisionCheck(frog, devil)){
            life--;
            frog->x = 140; 
            frog->y  = 100;
            //oldx = frog->x;
            //oldy = frog->y;
            devil->x =0;
            devil->y =0;
            //olddx = devil->x;
            //olddy = devil->y;
            xdir =3;
            ydir =3;
        }
        if (life == 0)
        {
            //drawGameOver();
            end = 1;
        }
        if (frog->x <= 10){
            win = 1;
        }

        WaitForVblank();
        //the face
        drawRect(oldx,oldy,FACE_WIDTH, FACE_HEIGHT,BLACK);
        drawFrog(frog);
        oldx = frog->x;
        oldy = frog->y;
        //the devil
        drawRect(olddx,olddy,MONSTER_WIDTH, MONSTER_HEIGHT,BLACK);
        drawDevil(devil);

        olddx = devil->x;
        olddy = devil->y;

        }
        else if (win == 1)
            drawHappyFace();
        else if (end == 1)
            drawGameOver();
        //changing direction for the devil


    }
    return 0;
}
