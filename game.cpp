
//PINGPONG Game

#include<graphics.h>
#include<conio.h>
#include<iostream.h>
#include<dos.h>

void barMovement();

int maxx ,maxy, isCrossed = 1, ballpx, ballpy, barpx, hit = 1, barx, hitCount = 0, points;

char btpress, lbtpress;

void score(){
  points = hitCount * 10;
  settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
  outtextxy(20,20,"SCORE : ");
  gotoxy(12,2);
  cout<<points;
}

void checking(){

  if(ballpy>=(maxy-49))
  {
    for(int i=0;i<=150;i++)
    {
      if(ballpx - i == barpx)
      {
	if(hit == 1)
	  hit=2;
	else
	  hit = 3;
	sound(400);
	delay(35);
	nosound();
	isCrossed = 1;
	hitCount++;
	break;
      }
      else
	isCrossed = 0;
    }
  }

  if(ballpx >= maxx)
    if(hit == 2)
      hit = 3;
    else
      hit = 4;
  if(ballpy == 0)
    if(hit == 3)
      hit = 4;
    else
      hit = 1;
  if(ballpx == 0)
    if(hit == 4)
      hit = 1;
    else
      hit = 2;

  score();

}

void ballMovement(){

  int ballx = 0, bally = 0, speed = 0, speedPoints = 50;

  while(isCrossed != 0 && btpress != ' '){

    delay(70 - speed);

    cleardevice();

    rectangle(0,0,maxx,maxy);

    setcolor(15);

    if(points == speedPoints){
      speed += 10;
      speedPoints += 50;
    }
    switch(hit){

      case 1:ballx += 10;
	     bally += 10;
	  break;

      case 2:ballx += 10;
	     bally -= 10;
	  break;

      case 3:ballx -= 10;
	     bally -= 10;
	  break;

      case 4:ballx -= 10;
	     bally += 10;

    }

    ballpx = 200+ballx;
    ballpy = 200+bally;

    pieslice(ballpx,ballpy,0,360,10);

    if(kbhit()){
      switch(getch()){
	case 75 :lbtpress = 'a';
	  break;
	case 77 :lbtpress = 'd';
	  break;
	case ' ':lbtpress = ' ';
	  break;
	default :lbtpress = 'z';
      }
    }

    barMovement();

  }

}

void barMovement(){

  if(lbtpress == 'd' || lbtpress == 'a' || lbtpress == 'D' || lbtpress == 'A' || lbtpress == ' ')
    btpress = lbtpress;

  switch(btpress){

    case 'a':
    case 'A':barx -= 10;
	   break;

    case 'd':
    case 'D':barx += 10;
	     break;

  }

  if(barpx <= -10)
    lbtpress = 'd';
  else if(barpx >= maxx-139)
    lbtpress = 'a';

  barpx = maxx/2-75+barx;

  bar(barpx,maxy-35,maxx/2+75+barx,maxy-25);

  checking();

}

void main()
{
  clrscr();

  int gd = DETECT, gm;   /*Graphic Mode Declaration with Auto DETECT Function
			  & Declaration of Graphic Mode*/
  initgraph(&gd, &gm, "c:\\turboc3\\bgi");

  maxx = getmaxx();       //639
  maxy = getmaxy();       //479

  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
  outtextxy(maxx/2-200, maxy/2, "Press any key to continue..");
  getch();

  cleardevice();

  outtextxy(maxx/2-200, maxy/2, "Use arrow keys to move bar");
  delay(2000);

  ballMovement();

  cleardevice();

  settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

  outtextxy(maxx/2-75,maxy/2,"Game Over");

  getch();

  closegraph();
}