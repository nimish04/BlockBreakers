#include<windows.h>
#include<glut.h>
#include"blockbreaker.h"
#include<stdlib.h>
#include<string.h>


int score=0;
int totaldead=0;
void initialize()	//To set the initial co-ordinates of the objects on the screen //done
{
	for(int n=0,x=4,y=376;n<45;n++,x+=66)
	{
	   if(x>560)
	   {
	     x=4;
	     y-=25;
	   }
	   b[n].x=x;
	   b[n].y=y;
	   b[n].w=60;
	   b[n].h=20;
	   b[n].alive=true;
	}

	block.myx=275;
	block.myy=0;
	block.width=50;
	block.height=20;
	block.lft=false;
	block.rgt=false;

	ball.ballx=300;
	ball.bally=200;
	ball.ballwh=20;
	ball.velx=10;
	ball.vely=10;

	red1=0.96;
 	green1=0.0;
 	blue1=1.0;
 	red2=0.0;
 	green2=0.8;
	blue2=0.196078;

	ball.red=0.65;
	ball.green=0.49;
	ball.blue=0.24;

	block.red=0.137255;
	block.green=0.556863;
	block.blue=0.419608;

}
bool check_collision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh) //Function for checking collision
{  //done
  if ( Ay+Ah < By ) return false; //if A is more to the lft than B
  else if ( Ay > By+Bh ) return false; //if A is more to rgt than B
  else if ( Ax+Aw < Bx ) return false; //if A is higher than B
  else if ( Ax > Bx+Bw ) return false; //if A is lower than B

  return true; //There is a collision because none of above returned false
}

void reshape()		//Modify the co-ordinates according to the key-presses and collisions etc...
{//done
	if(block.myx<0)
	  block.myx=0;
	if(block.myx+block.width>600)
	  block.myx=550;
	if(block.lft==true)
	  block.myx=block.myx-2;
	if(block.rgt==true)
	  block.myx=block.myx+2;



	ball.ballx+=0.067*ball.velx;
	ball.bally+=0.067*ball.vely;

	for(int n=0;n<45;n++)
	{
	   if(b[n].alive==true)
	   {
	   	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,b[n].x,b[n].y,b[n].w,b[n].h)==true)
	   	{
	   	  ball.vely=-ball.vely;
	   	  b[n].alive=false;
	   	  score+=1;
	   	  ball.down=true;
	   	  ball.up=false;
	   	  totaldead+=1;
	   	  break;
	   	}
	   }
	}
	if(ball.ballx<=0)
	{
		ball.velx=-ball.velx;
		ball.right=true;
		ball.left=false;
	}
	if(ball.ballx+ball.ballwh>600)
	{
		ball.right=false;
		ball.left=true;
		ball.velx=-ball.velx;
	}
	if(ball.bally+ball.ballwh>400)
        ball.vely=-ball.vely;
	else if(ball.bally<0)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50]="Your score: ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
    }

	if(check_collision(ball.ballx,ball.bally,ball.ballwh,ball.ballwh,block.myx,block.myy,block.width,block.height)==true)
	{
			ball.vely=-ball.vely;
			ball.up=true;
			ball.down=false;
	}
	draw();
}
void specialUp(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=false;break;
		case (GLUT_KEY_RIGHT): block.rgt=false;break;
	}
}
void specialDown(int key,int x,int y)
{
	switch(key)
	{
		case (GLUT_KEY_LEFT): block.lft=true;break;
		case (GLUT_KEY_RIGHT): block.rgt=true;break;
	}
}
void keyboard(unsigned char key,int x,int y)
{ //done
	if(key==27) 		//27 corresponds to the esc key
	{
		ball.velx=0;
		ball.vely=0;	//To stop the ball from moving
		callMenu();
	}
}
void myinit() //done
{
	glViewport(0,0,600,400);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,600,0,400);
}
void draw()		//Render the objects on the screen using the latest updated co-ordinates //done
{
	for(int i=0;i<45;i++)
	{
		if(b[i].alive==true)
		{
		   if(i%2==0)
            glColor3f(red1,green1,blue1);
		   else
		    glColor3f(red2,green2,blue2);
		   gamedisplay(b[i].x,b[i].y,b[i].x+b[i].w,b[i].y,b[i].x+b[i].w,b[i].y+b[i].h,b[i].x,b[i].y+b[i].h);
		}
	}
    glColor3f(block.red,block.green,block.blue);
    gamedisplay(block.myx,block.myy,block.myx+block.width,block.myy,block.myx+block.width,block.myy+block.height,block.myx,block.myy+block.height);
	glColor3f(ball.red,ball.green,ball.blue);
	gamedisplay(ball.ballx,ball.bally,ball.ballx+ball.ballwh,ball.bally,ball.ballx+ball.ballwh,ball.bally+ball.ballwh,ball.ballx,ball.bally+ball.ballwh);
	glutPostRedisplay();
	glutSwapBuffers();
	if(totaldead==45)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50]="Your score: ";
        strcat(text,_score);
        MessageBox(NULL,text,"You Won!!",0);
        exit(0);
    }

}
void display() //done
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(red,green,blue,1);
	glDisable(GL_DEPTH_TEST);
	draw();
	glFlush();
	reshape();
}
void bg1_menu(int opt)
{
	switch(opt)
	{
		case RED:	red=1.0;
				green=0.0;
				blue=0.0;
				display();
				break;
		case GREEN:	red=0.0;
				green=1.0;
				blue=0.0;
				display();
			 	break;
		case BLUE:	red=0.0;
				green=0.0;
				blue=1.0;
				display();
			 	break;
		case BLACK:	red=0.0;
				green=0.0;
				blue=0.0;
				display();
			 	break;
	}
}
void bg2_menu(int opt)
{
	switch(opt)
	{
		case GOLD:	ball.red=0.858824;
			  	ball.green=0.858824;
			  	ball.blue=0.439216;
			  	break;

		case ORCHID:	ball.red=0.858824;
			    	ball.green=0.439216;
			    	ball.blue=0.858824;
			    	break;
	}
}
void bg3_menu(int opt)
{
	switch(opt)
	{
		case C1:
			red1=0.72;
			green1=0.45;
			blue1=0.20;
			red2=0.42;
			green2=0.26;
			blue2=0.15;
			break;
		case C2:
			red1=1;
			green1=0.5;
			blue1=0;
			red2=0.9;
			green2=0.91;
			blue2=0.98;
			break;
		case C3:
			red1=0.858824;
			green1=0.439216;
			blue1=0.858824;
			red2=0.36;
			green2=0.2;
			blue2=0.09;
			break;
	}
}
void bg4_menu(int opt)
{
	switch(opt)
	{
		case BLACK1:
			block.red=0.0;
			block.green=0.0;
			block.blue=0.0;
			break;
		case WHITE:
			block.red=1;
			block.green=1;
			block.blue=1;
			break;
	}
}
void sp_menu(int opt)
{
	switch(opt)
	{
		case INC:
			ball.velx++;
			ball.vely++;
			break;
		case DEC:
			ball.velx-=0.25;
			ball.vely-=0.25;
			break;

	}
}
void main_menu(int opt)
{
	switch(opt)
	{
		case CONTINUE: revert();
			       break;
		case QUIT: exit(0);
	}
}

void callMenu()
{
	int bg,bg1,bg2,bg3,bg4,sp;
	bg1=glutCreateMenu(bg1_menu);
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Green",GREEN);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Default",BLACK);

	bg2=glutCreateMenu(bg2_menu);
	glutAddMenuEntry("gold",GOLD);
	glutAddMenuEntry("Orchid",ORCHID);

	bg3=glutCreateMenu(bg3_menu);
	glutAddMenuEntry("Combo1",C1);
	glutAddMenuEntry("Combo2",C2);
	glutAddMenuEntry("Combo3",C3);

	bg4=glutCreateMenu(bg4_menu);
	glutAddMenuEntry("Black",BLACK1);
	glutAddMenuEntry("White",WHITE);

	sp=glutCreateMenu(sp_menu);
	glutAddMenuEntry("Increase",INC);
	glutAddMenuEntry("Decrease",DEC);

	bg=glutCreateMenu(main_menu);
	glutAddSubMenu("Background",bg1);
	glutAddSubMenu("Ball",bg2);
	glutAddSubMenu("Brick",bg3);
	glutAddSubMenu("Block",bg4);

	glutCreateMenu(main_menu);
	glutAddMenuEntry("Continue",CONTINUE);
	glutAddSubMenu("Color",bg);
	glutAddSubMenu("Speed",sp);
	glutAddMenuEntry("Quit Game",QUIT);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


}
void processmenu(int opt)
{
	switch(opt)
	{
		case CONTINUE:
			revert();
			break;
		case INC:
			ball.velx++;
			ball.vely++;
			break;

		case QUIT: exit(0);
	}

}
void revert()
{
	ball.velx=10;
	ball.vely=10;
	if(ball.up==true)
	{
		if(ball.right==true)
		{
			ball.velx=ball.velx;
			ball.vely=ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=ball.vely;
		}
	}
	else if(ball.down=true)
	{
		if(ball.right=true)
		{
			ball.velx=ball.velx;
			ball.vely=-ball.vely;
		}
		else if(ball.left==true)
		{
			ball.velx=-ball.velx;
			ball.vely=-ball.vely;
		}
	}
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Block Breaker");
	initialize();
	myinit();
	draw();
	glutDisplayFunc(display);
        glutSpecialFunc(specialDown);
    	glutSpecialUpFunc(specialUp);
    	glutKeyboardFunc(keyboard);
	glutIdleFunc(reshape);
	glutMainLoop();
	return 0;
}
