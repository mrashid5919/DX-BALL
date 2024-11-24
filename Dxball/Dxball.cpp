# include "iGraphics.h"
# include "gl.h"
#include<windows.h>
#include<string.h>
#include<stdlib.h>

#define screenwidth 800.0
#define screenheight 600.0
#define base 150.0
#define r 5
#define totalBricks 8*10

FILE *fptr;
int st=0;
int score=0;
int life=3;
int pshow=0;
int pshow2=0;
int pshow3=0;
int bstate=0;
int eb=80;
int tb=2500;

char sc[20];
char timer[20]="00";
char sco[20];
char str[20];
char str2[20];
int len = 0;
int mode = 0;
//char str[0]= '0';
int time_s=0;
int time_m=0;
void drop();
void time();
void change();


double x=(double)screenwidth/2;
double y=base;
double dx=3.0;
double dy=2.0;

double bx=x-50.0;
double by=y-15.0;
double bl=100.0;
double bb=10.0;
double lbx=x-82.0;
double lbl=163.0;

struct _bricks{
    int a;
    int b;
    int da=50;
    int db=15;
    int show=1;
    int red;
    int green;
    int blue;
}bricks[totalBricks];

struct buttoncoordinate
{
    int x;
    int y;
}bcoordinate[3];

struct lifecoordinate
{
    int x;
    int y;
    int sh;
}lc[5];

struct hall_of_fame
{
   char name[50];
   int score;
};

struct hall_of_fame hof[15];

char button[10][50]={"Images/Resume.BMP","Images/Newgame.BMP","Images/Highscores.BMP","Images/Quit.BMP"};

int red=0;
int green=0;
int blue=0;

int start=0;

void definebricks();
void buildbricks();
void showscore();

int px=350;
int py=445;
int px2=450;
int py2=475;
int px3=250;
int py3=400;

void drawTextBox()
{
	iSetColor(150, 150, 150);
	iRectangle(275,285 , 250, 30);
}

void restart()
{
    PlaySound("Music/Beethoven - F�r Elise.wav",NULL,SND_ASYNC);
    FILE *fr;
    fr=fopen("Images/Position.txt","rb");
    fread(&x,sizeof(x),1,fr);
    fread(&y,sizeof(y),1,fr);
    fread(&dx,sizeof(dx),1,fr);
    fread(&dy,sizeof(dy),1,fr);
    fread(&bx,sizeof(bx),1,fr);
    fread(&by,sizeof(by),1,fr);
    fread(&lbx,sizeof(lbx),1,fr);
    fread(&bstate,sizeof(bstate),1,fr);
    fread(&life,sizeof(life),1,fr);
    fread(&score,sizeof(score),1,fr);
    fread(&eb,sizeof(eb),1,fr);
    fread(&time_s,sizeof(time_s),1,fr);
    fread(&time_m,sizeof(time_m),1,fr);
    fread(&py,sizeof(py),1,fr);
    fread(&py2,sizeof(py2),1,fr);
    fread(&py3,sizeof(py3),1,fr);
    fread(&pshow,sizeof(pshow),1,fr);
    fread(&pshow2,sizeof(pshow2),1,fr);
    fread(&pshow3,sizeof(pshow3),1,fr);
    for(int i=0; i<totalBricks; i++)
    {
        fread(&bricks[i],sizeof(bricks[i]),1,fr);
    }
    fclose(fr);

    //start=0;
}

void ng()
{
    PlaySound("Music/Beethoven - F�r Elise.wav",NULL,SND_ASYNC);
    x=(double)screenwidth/2;
    y=base;
    dx=3.0;
    dy=2.0;

    bx=x-50.0;
    by=y-15.0;
    bl=100.0;
    bb=10.0;

    start=0;

    bstate=0;
    life=3;
    score=0;
    eb=totalBricks;
    //itoa(score,sc,10);
    time_s=0;
    time_m=0;
    py=445;
    py2=475;
    py3=400;
    for(int i=0;i<totalBricks;i++)
    {
        bricks[i].show=1;
    }
    for(int i=0;i<=2;i++)
    {
        lc[i].sh=1;
    }
    lc[3].sh=0;
    lc[4].sh=0;
}

void collision()
{
    for(int i=0;i<totalBricks;i++)
        {
            if(bricks[i].show)
            {
                if(x>=bricks[i].a && x<=bricks[i].a+bricks[i].da)
                {
                    if(y>=bricks[i].b && y<=bricks[i].b+bricks[i].db)
                    {
                        dy*=(-1);
                        bricks[i].show=0;
                        if(i==34)
                            pshow=1;
                        if(i==56)
                            pshow2=1;
                        if(i==2)
                            pshow3=1;
                        if(bricks[i].red==255)
                            score+=10;
                        else
                            score+=15;
                        sprintf(sc,"SCORE : %d",score);
                        //itoa(score,sc,10);
                        eb--;
                    }
                }
                else if(y>=bricks[i].b && y<=bricks[i].b+bricks[i].db)
                {
                    if(x>=bricks[i].a && x<=bricks[i].a+bricks[i].da)
                    {
                        dx*=(-1);
                        if(i==34)
                            pshow=1;
                        if(i==56)
                            pshow2=1;
                        if(i==2)
                            pshow3=1;
                        bricks[i].show=0;
                        if(bricks[i].red==255)
                            score+=10;
                        else
                            score+=15;
                        sprintf(sc,"SCORE : %d",score);
                        //itoa(score,sc,10);
                        eb--;
                    }
                }
            }
        }
}

void change()
{
    if(start==1)
    {
        dx*=1.0002;
        dy*=1.0002;
        x+=dx;
        y+=dy;
        if(x+5>=screenwidth || x-5<=0)
            dx=(-1)*dx;
        if(y+5>=screenheight || y-5<=0)
            dy=(-1)*dy;
        if(y<=base && y>=base-bb)
        {
            if(bstate==0)
            {
                if(x+5>=bx && x-5<=bx+bl)
                    dy=(-1)*dy;
            }
            else
            {
                if(x+5>=lbx && x-5<=lbx+lbl)
                    dy=(-1)*dy;
            }
        }
        collision();
        if(py==base)
        {
            if(bstate==0)
            {
                if(px>=bx-25 && px<=(bx+bl-5))
                {
                    life++;
                    py=0;
                    lc[life-1].sh=1;
                }
            }
            else
            {
                if(px>=lbx-25 && px<=(lbx+lbl-5))
                {
                    life++;
                    py=0;
                    lc[life-1].sh=1;
                }
            }
        }
        if(py2==base)
        {
            if(bstate==0)
            {
                if(px2>=bx-25 && px2<=(bx+bl-5))
                {
                    bstate=1;
                    py2=0;
                }
            }
        }
        if(py3==base)
        {
            if(bstate==0)
            {
                if(px3>=bx-25 && px3<=(bx+bl-5))
                {
                    dx*=2;
                    dy*=2;
                    py3=0;
                }
            }
            else
            {
                if(px3>=lbx-25 && px3<=(lbx+lbl-5))
                {
                    dx*=2;
                    dy*=2;
                    py3=0;
                }
            }
        }
        if(y<base-bb)
        {
            life--;
            if(life>0)
            {
                lc[life].sh=0;
                bstate=0;
                x=(double)screenwidth/2;
                y=base;
                dx=3.0;
                dy=2.0;

                bx=x-50.0;
                by=y-15.0;
                bl=100.0;
                bb=10.0;

                start=0;
            }
            else
            {
                if(st==1)
                    st=3;
            }
        }
        if(eb==0)
        {
            if(st==1)
                st=4;
        }
    }
}

void drop()
{
    if(st==1)
    {
        if(pshow==1)
        {
            if(py>0)
                py-=5;
            else
                pshow=0;
        }
        if(pshow2==1)
        {
            if(py2>0)
                py2-=5;
            else
                pshow2=0;
        }
        if(pshow3==1)
        {
            if(py3>0)
                py3-=5;
            else
                pshow3=0;
        }
    }
}

void cursor()
{
    if(bstate==0)
        iShowBMP2(bx-10,by,"Images/Board.BMP",0x000000);
    else
        iShowBMP2(lbx-18,by,"Images/Longboard.BMP",0x000000);
}

void definebricks()
{
    int sumx=150;
    int sumy=400;
    for(int i=0;i<totalBricks;i++)
    {
        /*bricks[i].red=rand()%255;
        bricks[i].green=rand()%255;
        bricks[i].blue=rand()%255;*/
        if(i%2==0)
        {
            if((i/10)%2==0)
            {
                bricks[i].red=0;
                bricks[i].green=0;
                bricks[i].blue=0;
            }
            else
            {
                bricks[i].red=255;
                bricks[i].green=255;
                bricks[i].blue=255;
            }
        }
        else
        {
            if((i/10)%2==0)
            {
                bricks[i].red=255;
                bricks[i].green=255;
                bricks[i].blue=255;
            }
            else
            {
                bricks[i].red=0;
                bricks[i].green=0;
                bricks[i].blue=0;
            }
        }
        bricks[i].a=sumx;
        bricks[i].b=sumy;
        sumx+=50;
        if(sumx>screenwidth-200)
        {
            sumx=150;
            sumy+=15;
        }

    }
}

void buildbricks()
{
    for(int i=0;i<totalBricks;i++)
    {
        if(bricks[i].show)
        {
            iSetColor(bricks[i].red,bricks[i].green,bricks[i].blue);
            iFilledRectangle(bricks[i].a,bricks[i].b,bricks[i].da,bricks[i].db);
        }
    }
}

void definebp()
{
    int u=300;
    for(int i=0;i<4;i++)
    {
        bcoordinate[i].x=275;
        bcoordinate[i].y=u;
        u-=100;
    }
}

void homepage()
{
    iShowBMP(0,0,"Images/Homepage.BMP");
    for(int i=0;i<4;i++)
    {
        iShowBMP2(bcoordinate[i].x,bcoordinate[i].y,button[i],0);
    }
    iSetColor(0,255,255);
    iFilledRectangle(10,280,150,40);
    iSetColor(0,0,0);
    iText(20,290,"Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
}

void showscore()
{
    iSetColor(0,255,255);
    iFilledRectangle(620,540,160,50);
    iSetColor(0,0,0);
    sprintf(sc,"SCORE : %d",score);
    iText(630,550,sc,GLUT_BITMAP_TIMES_ROMAN_24);
}

void lp()
{
    int u=500;
    for(int i=4;i>=0;i--)
    {
        lc[i].x=u;
        lc[i].y=530;
        if(i<life)
            lc[i].sh=1;
        else
            lc[i].sh=0;
        u+=60;
    }
}

void showhighscore()
{
    PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
    iShowBMP(0,0,"Images/HOF.BMP");
    fptr = fopen("Highscore.txt", "rb");
    for(int i=0; i<10; i++)
    {
        fread(&hof[i],sizeof(hof[0]),1,fptr);
    }
    iSetColor(0,0,0);
    iFilledRectangle(185,540,100,50);
    iFilledRectangle(585,540,100,50);
    iSetColor(255,0,0);
    iText(195,550,"Name",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(595,550,"Score",GLUT_BITMAP_TIMES_ROMAN_24);
    int tx1=200;
    int ty=500;
    int tx2=600;
    iSetColor(0,255,255);
    iFilledRectangle(350,0,160,50);
    iSetColor(0,0,0);
    iText(360,10,"Press m",GLUT_BITMAP_TIMES_ROMAN_24);
    for(int i=0; i<10; i++)
    {
        iSetColor(0,0,0);
        iFilledRectangle(tx1-10,ty-10,110,30);
        iFilledRectangle(tx2-10,ty-10,110,30);
        iSetColor(255,255,255);
        iText(tx1,ty,hof[i].name,GLUT_BITMAP_HELVETICA_18);
        sprintf(sco,"%d",hof[i].score);
        iText(tx2,ty,sco,GLUT_BITMAP_HELVETICA_18);
        ty-=50;
        fclose(fptr);
    }
}

void showl()
{
    if(st==1)
    {
        for(int i=0;i<=4;i++)
        {
            if(lc[i].sh==1)
            {
                iShowBMP2(lc[i].x,lc[i].y,"Images/Life.BMP",0);
            }
        }
    }
}

void time()
{
    if(st==1)
    {
        time_s++;
        if(time_s==60)
        {
            time_s=0;
            time_m++;
        }
        tb-=10;
    }
}

void timedisplay()
{
    sprintf(timer,"TIME : %02d : %02d",time_m,time_s);
    iSetColor(0,255,255);
    iFilledRectangle(40,540,160,50);
    iSetColor(0,0,0);
    iText(50,550,timer,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0,255,255);
    iFilledRectangle(250,540,100,50);
    iSetColor(0,0,0);
    iText(260,550,"PAUSE",GLUT_BITMAP_TIMES_ROMAN_24);
}

void over()
{
    iShowBMP2(0,0,"Images/gameover.BMP",0x000000);
    //itoa(score,sc,10);
    showscore();
    iSetColor(0,255,255);
    iFilledRectangle(10,10,250,40);
    iSetColor(0,0,0);
    iText(20,20,"Press 'e' to continue",GLUT_BITMAP_TIMES_ROMAN_24);
}

void win()
{
    iShowBMP(0,0,"Images/Win.BMP");
    iSetColor(0,255,255);
    iFilledRectangle(620,540,160,50);
    iSetColor(0,0,0);
    score=tb+1000;
    sprintf(sc,"SCORE : %d",score);
    iText(630,550,sc,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(0,255,255);
    iFilledRectangle(10,10,250,40);
    iSetColor(0,0,0);
    iText(20,20,"Press 'e' to continue",GLUT_BITMAP_TIMES_ROMAN_24);
}

void iDraw()
{
    iClear();
    if(st==0 || st==2)
    {
        homepage();
    }
    else if(st==1)
    {
        iShowBMP(0,0,"Images/Bg.BMP");
        if(pshow==1)
        {
            iShowBMP(px,py-30,"Images/Lifegain.BMP");
        }
        if(pshow2==1)
        {
            iShowBMP(px2,py2-30,"Images/Longpaddle.BMP");
        }
        if(pshow3==1)
        {
            iShowBMP(px3,py3-30,"Images/Fastball.BMP");
        }
        buildbricks();
        cursor();
        showscore();
        showl();
        timedisplay();
        iSetColor(255,0,255);
        iFilledCircle(x,y,r);
    }
    else if(st==3)
    {
        over();
    }
    else if(st==4)
    {
        win();
    }
    else if(st==5)
    {
        PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
        showhighscore();
    }
    else if(st==6)
    {
        iSetColor(255,255,255);
        iText(275,320,"Enter your name",GLUT_BITMAP_TIMES_ROMAN_24);
        drawTextBox();
        if(mode==0)
            iText(160,20,"Click inside the box",GLUT_BITMAP_TIMES_ROMAN_24);
        else if(mode == 1)
        {
            iSetColor(255, 255, 255);
            iText(300, 300, str);
            iSetColor(0,255,255);
            iFilledRectangle(150,10,500,40);
            iSetColor(0,0,0);
            iText(160,20,"Write your name and press ENTER to continue",GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
    else if(st==7)
    {
        iShowBMP(0,0,"Images/Inst1.BMP");
        iSetColor(0,255,255);
        iFilledRectangle(620,540,160,50);
        iSetColor(0,0,0);
        iText(630,550,"NEXT",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if(st==8)
    {
        iShowBMP(0,0,"Images/Inst2.BMP");
        iSetColor(0,255,255);
        iFilledRectangle(620,540,160,50);
        iSetColor(0,0,0);
        iText(630,550,"NEXT",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else if(st==9)
    {
        iShowBMP(0,0,"Images/Inst3.BMP");
        iSetColor(0,255,255);
        iFilledRectangle(620,540,160,50);
        iSetColor(0,0,0);
        iText(630,550,"MENU",GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void iKeyboard(unsigned char key)
{
    int i;
    if(st==6)
    {
        if(mode == 1)
        {
            if(key == '\r')
            {
                mode = 0;
                strcpy(str2,str);
                //printf("%s\n", str2);
                for(i = 0; i < len; i++)
                    str[i] = 0;
                len = 0;
                FILE *fo;
                fo=fopen("Highscore.txt","rb");
                for(i=0;i<10;i++)
                    fread(&hof[i],sizeof(hof[0]),1,fo);
                fclose(fo);
                for(i=0;i<10;i++)
                {
                    if(score>hof[i].score)
                    {
                        for(int j=10;j>i;j--)
                        {
                            hof[j].score=hof[j-1].score;
                            strcpy(hof[j].name,hof[j-1].name);
                        }
                        hof[i].score=score;
                        strcpy(hof[i].name,str2);
                        fo=fopen("Highscore.txt","wb");
                        for(int j=0;j<10;j++)
                        {
                            fwrite(&hof[j],sizeof(hof[j]),1,fo);
                        }
                        fclose(fo);
                        break;
                    }
                }
                st=5;
            }
            else
            {
                str[len] = key;
                len++;
            }
        }
    }
    else
    {
        switch(key)
        {
        case ' ':
        {
            start=1;
            break;
        }
        case 'e':
        {
            if(st==4 || st==3)
                st=6;
            break;
        }
        case 'm':
        {
                st=2;
                PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
                break;
        }
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
    switch(key){
        case GLUT_KEY_END:
        {
            exit(0);
        }
        case GLUT_KEY_LEFT:
        {
            if(bstate==0)
            {
                if(bx>=30)
                    bx-=20;
                if(start==0)
                {
                    x=bx+50;
                }
            }
            else
            {
                if(lbx>=38)
                    lbx-=20;
                if(start==0)
                {
                    x=lbx+82;
                }
            }
            break;
        }
        case GLUT_KEY_RIGHT:
        {
            if(bstate==0)
            {
                if(bx<=screenwidth-120)
                    bx+=20;
                if(start==0)
                {
                    if(x<=screenwidth-70)
                    {
                        x+=20;
                    }
                }
            }
            else
            {
                if(lbx<=screenwidth-200)
                    lbx+=20;
                if(start==0)
                {
                    x=lbx+82;
                }
            }
            break;
        }
    }
    //place your codes for other keys here
}

void iMouseMove(int mx, int my)
{
    //place your codes here
}

void iPassiveMouseMove(int mx, int my)
{
    if(st==1)
    {
        if(bstate==0)
        {
            if(mx>=60 && mx<=screenwidth-50)
                bx=mx-50;
            if(start==0)
            {
                x=bx+50;
            }
        }
        else
        {
            if(mx>=100 && mx<=screenwidth-82)
                lbx=mx-82;
            if(start==0)
            {
               x=lbx+82;
            }
        }
    }
}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        if(mx>=310 && mx<=495 && my>=255 && my<=295)
        {
            if(st==0)
            {
                st=1;
                PlaySound("Music/Beethoven - F�r Elise.wav",NULL,SND_ASYNC);
            }
            else if(st==2)
            {
                st=1;
                ng();
                iResumeTimer(0);
            }
        }
        else if(mx>=310 && mx<=495 && my>=355 && my<=395)
        {
            if(st==2)
            {
                st=1;
                restart();
                iResumeTimer(0);
            }
            else if(st==0)
            {
                st=1;
                restart();
                iResumeTimer(0);
            }
        }
        else if(mx>=310 && mx<=495 && my>=155 && my<=195)
        {
            if(st==2 || st==0)
            {
                PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
                st=5;
            }
        }
        else if(mx>=310 && mx<=495 && my>=55 && my<=95)
        {
            if(st==2)
                exit(0);
        }
        else if(mx>=250 && mx<=350 && my>=540 && my<=590)
        {
            if(st==1)
            {
                FILE *fh;
                fh=fopen("Position.txt","wb");
                fwrite(&x,sizeof(x),1,fh);
                fwrite(&y,sizeof(y),1,fh);
                fwrite(&dx,sizeof(dx),1,fh);
                fwrite(&dy,sizeof(dy),1,fh);
                fwrite(&bx,sizeof(bx),1,fh);
                fwrite(&by,sizeof(by),1,fh);
                fwrite(&lbx,sizeof(lbx),1,fh);
                fwrite(&bstate,sizeof(bstate),1,fh);
                fwrite(&life,sizeof(life),1,fh);
                fwrite(&score,sizeof(score),1,fh);
                fwrite(&eb,sizeof(eb),1,fh);
                fwrite(&time_s,sizeof(time_s),1,fh);
                fwrite(&time_m,sizeof(time_m),1,fh);
                fwrite(&py,sizeof(py),1,fh);
                fwrite(&py2,sizeof(py2),1,fh);
                fwrite(&py3,sizeof(py3),1,fh);
                fwrite(&pshow,sizeof(pshow),1,fh);
                fwrite(&pshow2,sizeof(pshow2),1,fh);
                fwrite(&pshow3,sizeof(pshow3),1,fh);
                for(int i=0;i<totalBricks;i++)
                {
                    fwrite(&bricks[i],sizeof(bricks[i]),1,fh);
                }
                fclose(fh);
                st=2;
                PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
                iPauseTimer(0);
            }
        }
        else if(mx>=10 && mx<=160 && my>=280 && my<=320)
        {
            if(st==0 || st==2)
                st=7;
        }
        else if(mx>=620 && mx<=780 && my>=540 && my<=590)
        {
            if(st==7)
                st=8;
            else if(st==8)
                st=9;
            else if(st==9)
                st=2;
        }
        else if(mx>=275 && mx<=525 && my>=285 && my<=315)
        {
            if(st==6)
                mode=1;
        }
        //place your codes here
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

int main()
{
    iSetTimer(2,change);
    iSetTimer(2,drop);
    iSetTimer(1000,time);
    definebricks();
    definebp();
    lp();
    str[0]=0;
    if(st==0)
        PlaySound("Music/Intro.wav",NULL,SND_ASYNC);
    iInitialize(screenwidth, screenheight, "DX-BALL");
    return 0;
}

