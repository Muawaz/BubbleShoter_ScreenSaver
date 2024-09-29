//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef Bomberman_CPP_
#define Bomberman_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>

#include <fstream>
#include <ctime>
#include <cstdlib>
#include "shape.h"
#include "circle.cpp"
#include "rectangle.cpp"
#include "rectangle.h"
// #include "circle.h"

#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool bombStatus = true;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x/*starting x*/, int y/*starting y*/,
		ColorNames color/*color*/, float gw = 6/*Enemy Width in Units*/,
		float gh = 7/*Enemy Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float) gw / ogw, sy = (float) gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
		float radius/*Radius*/,
		const ColorNames &colorname/*Bomberman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin (GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			radius / 10, colors[BLACK]);
}

Circle *c1[15];
Rectangle *r1[10];

Shape **ptrc1;
Shape **ptrr1;


void DetectCircle()
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			if (i!=j)
			{
				if (ptrc1[i]->getx() + c1[i]->getr() >= ptrc1[j]->getx() - c1[j]->getr() && ptrc1[i]->getx() + c1[i]->getr() <= ptrc1[j]->getx() + c1[j]->getr() && ptrc1[i]->gety() <= ptrc1[j]->gety() + c1[j]->getr() && ptrc1[i]->gety() >= ptrc1[j]->gety() - c1[j]->getr() )
				{
					if (ptrc1[i]->getcolor() == ptrc1[j]->getcolor())
					{
						float tempx = c1[i]->getr();
						float tempy = c1[j]->getr();

						c1[i]->getr() >= c1[j]->getr() ? c1[j]->IncRadius() : c1[j]->IncRadius();

						tempx >= tempy ? c1[j]->setr(0) : c1[i]->setr(0);

						tempx >= tempy ? ptrc1[j]->setx(300000000) : ptrc1[i]->sety(300000000);
					}

					c1[i]->setypos(false);
					c1[j]->setypos(true);
				}

				if (ptrc1[i]->getx() - c1[i]->getr() <= ptrc1[j]->getx() - c1[j]->getr() && ptrc1[i]->getx() - c1[i]->getr() >= ptrc1[j]->getx() + c1[j]->getr() && ptrc1[i]->gety() <= ptrc1[j]->gety() + c1[j]->getr() && ptrc1[i]->gety() >= ptrc1[j]->gety() - c1[j]->getr() )
				{
					if (ptrc1[i]->getcolor() == ptrc1[j]->getcolor())
					{
						float tempx = c1[i]->getr();
						float tempy = c1[j]->getr();

						c1[i]->getr() >= c1[j]->getr() ? c1[j]->IncRadius() : c1[j]->IncRadius();

						tempx >= tempy ? c1[j]->setr(0) : c1[i]->setr(0);

						tempx >= tempy ? ptrc1[j]->setx(300000000) : ptrc1[i]->sety(300000000);
					}

					c1[i]->setypos(true);
					c1[j]->setypos(false);
				}

				if (ptrc1[i]->gety() + c1[i]->getr() >= ptrc1[j]->gety() - c1[j]->getr() && ptrc1[i]->gety() + c1[i]->getr() <= ptrc1[j]->gety() + c1[j]->getr() && ptrc1[i]->getx() <= ptrc1[j]->getx() + c1[j]->getr() && ptrc1[i]->getx() >= ptrc1[j]->getx() - c1[j]->getr() )
				{
					if (ptrc1[i]->getcolor() == ptrc1[j]->getcolor())
					{
						float tempx = c1[i]->getr();
						float tempy = c1[j]->getr();

						c1[i]->getr() >= c1[j]->getr() ? c1[j]->IncRadius() : c1[j]->IncRadius();

						tempx >= tempy ? c1[j]->setr(0) : c1[i]->setr(0);

						tempx >= tempy ? ptrc1[j]->setx(300000000) : ptrc1[i]->sety(300000000);
					}

					c1[i]->setypos(false);
					c1[j]->setypos(true);
				}

				if (ptrc1[i]->gety() - c1[i]->getr() <= ptrc1[j]->gety() - c1[j]->getr() && ptrc1[i]->gety() - c1[i]->getr() >= ptrc1[j]->gety() + c1[j]->getr() && ptrc1[i]->getx() <= ptrc1[j]->getx() + c1[j]->getr() && ptrc1[i]->getx() >= ptrc1[j]->getx() - c1[j]->getr() )
				{
					if (ptrc1[i]->getcolor() == ptrc1[j]->getcolor())
					{
						float tempx = c1[i]->getr();
						float tempy = c1[j]->getr();

						c1[i]->getr() >= c1[j]->getr() ? c1[j]->IncRadius() : c1[j]->IncRadius();

						tempx >= tempy ? c1[j]->setr(0) : c1[i]->setr(0);

						tempx >= tempy ? ptrc1[j]->setx(300000000) : ptrc1[i]->sety(300000000);
					}

					c1[i]->setypos(true);
					c1[j]->setypos(false);
				}

			}
		}
	}
}

void DetectRectangle()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (i!=j)
			{
				if (ptrr1[i]->getx() + r1[i]->getml() >= ptrr1[j]->getx() - r1[j]->getml() && ptrr1[i]->getx() + r1[i]->getml() <= ptrr1[j]->getx() + r1[j]->getml() && ptrr1[i]->gety() <= ptrr1[j]->gety() + r1[j]->getmw() && ptrr1[i]->gety() >= ptrr1[j]->gety() - r1[j]->getmw() )
				{
					r1[i]->setxpos(false);
					r1[j]->setxpos(true);
				}

				if (ptrr1[i]->getx() - r1[i]->getml() <= ptrr1[j]->getx() - r1[j]->getml() && ptrr1[i]->getx() - r1[i]->getml() >= ptrr1[j]->getx() + r1[j]->getml() && ptrr1[i]->gety() <= ptrr1[j]->gety() + r1[j]->getmw() && ptrr1[i]->gety() >= ptrr1[j]->gety() - r1[j]->getmw() )
				{
					r1[i]->setxpos(true);
					r1[j]->setxpos(false);
				}

				if (ptrr1[i]->gety() + r1[i]->getmw() >= ptrr1[j]->gety() - r1[j]->getmw() && ptrr1[i]->gety() + r1[i]->getmw() <= ptrr1[j]->gety() + r1[j]->getmw() && ptrr1[i]->getx() <= ptrr1[j]->getx() + r1[j]->getml() && ptrr1[i]->getx() >= ptrr1[j]->getx() - r1[j]->getml() )
				{
					r1[i]->setypos(false);
					r1[j]->setypos(true);
				}

				if (ptrr1[i]->gety() - r1[i]->getmw() <= ptrr1[j]->gety() - r1[j]->getmw() && ptrr1[i]->gety() - r1[i]->getmw() >= ptrr1[j]->gety() + r1[j]->getmw() && ptrr1[i]->getx() <= ptrr1[j]->getx() + r1[j]->getml() && ptrr1[i]->getx() >= ptrr1[j]->getx() - r1[j]->getml() )
				{
					r1[i]->setypos(true);
					r1[j]->setypos(false);
				}
			}
		}
	}
}

void BugCircleFixing()
{
	for (int i = 0; i < 15; ++i)
	{
		if (ptrc1[i]->gety() >= 820)
		{
			c1[i]->setypos(false);
		}

		if (ptrc1[i]->gety() <= 10)
		{
			c1[i]->setypos(true);
		}

		if (ptrc1[i]->getx() >= 1000)
		{
			c1[i]->setypos(false);
		}

		if (ptrc1[i]->getx() < 10)
		{
			c1[i]->setypos(true);
		}

	}
}

void BugRectangleFixing()
{
	for (int i = 0; i < 10; ++i)
	{
		if ((ptrr1[i]->gety() + r1[i]->getmw()) >= 830)
		{
			r1[i]->setypos(false);
		}

		if ((ptrr1[i]->gety() + r1[i]->getmw()) <= 10)
		{
			r1[i]->setypos(true);
		}

		if ((ptrr1[i]->getx() + r1[i]->getml()) >= 1010)
		{
			r1[i]->setxpos(false);
		}

		if ((ptrr1[i]->getx() + r1[i]->getml()) <= 10)
		{
			r1[i]->setxpos(true);
		}		
	}
}


/*
 * Main Canvas drawing function.
 * */
Board *b;

// Circle c1[15];
// Rectangle r1[10];
// Shape **ptr;

bool menu = false;
bool hs = false;
bool escape = false;

int score = 0;
string sscore;
int high;


fstream ofile, ifile;

int timer1 = 0;
int timer2 = 0;
int timer22 = 0;
int timer23 = 2;



void GameDisplay()/**/{

	if (menu == false && escape == false)
	{
		// set the background color using function glClearColor.
		// to change the background play with the red, green and blue values below.
		// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
				0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

		//

		DrawRectangle(480, 410, 100, 50, colors[10]);

		DrawString(12200, 10700, 50, 50, "PLAY", colors[4]);

		DrawRectangle(435, 350, 200, 50, colors[9]);

		DrawString(11000, 9000, 50, 50, "HIGHEST SCORE", colors[4]);

		
	}

	if (escape == true)
	{
		// set the background color using function glClearColor.
		// to change the background play with the red, green and blue values below.
		// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
				0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

		//

		

		DrawRectangle(480, 410, 120, 50, colors[10]);

		DrawString(12200, 10700, 50, 50, "Score = ", colors[4]);

		DrawString(14200, 10700, 50, 50, sscore, colors[4]);
	
		DrawRectangle(450, 80, 170, 50, colors[10]);

		DrawString(11500, 2500, 50, 50, "PLAY AGAIN", colors[4]);		

	}

	if (hs == true)
	{
		// set the background color using function glClearColor.
		// to change the background play with the red, green and blue values below.
		// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
				0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

		//

		ifile.open("score.txt", ios::in);

		ifile >> high;

		string hhigh = to_string(high);

		ifile.close();

		string temp = "HIGHEST Score =  ";

		temp += hhigh;

		DrawString(12200, 10700, 50, 50, temp, colors[CYAN]);
	}

	if (menu == true && escape == false)
	{
		// set the background color using function glClearColor.
		// to change the background play with the red, green and blue values below.
		// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

		
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
				0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

		//

		timer1++;

		if (timer1 % 100 == 0)
		{
			timer2++;
			timer1 = 0;
		}

		if (timer2 % 60 == 0 && timer1 % 100 == 0)
		{
			timer22++;
			timer2 = 0;
		}

		if (timer22 % 60 == 0 && timer1 % 100 == 0)
		{
			timer23++;
			timer22 = 0;
		}


		
		for (int i = 0; i < 15; ++i)
		{
			ptrc1[i]->DrawShape();
			ptrc1[i]->Move();
		}

		

		for (int i = 0; i < 10; ++i)
		{
			ptrr1[i]->DrawShape();
			ptrr1[i]->Move();
		}

		DetectCircle();

		DetectRectangle();

		BugCircleFixing();

		BugRectangleFixing();

		// b->Draw();
		int x, y;
		// b->GetInitPinkyPosition(x, y);
		// cout << x << "  y= " << y << endl << flush;
		// DrawEnemy(x, y, PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());

		// b->GetInitBombermanPosition(x, y);
		// DrawBomberman(x, y, b->GetCellSize() / 2 - 2, YELLOW);

		b->GetInitTextPosition(x, y);
		// cout << endl <<"Text Position = "<< x << "  y= " << y << endl << flush;
		
		DrawString(20, 800, "Score = ", colors[5]);
		sscore = to_string(score);
		DrawString(150, 800, sscore, colors[5]);	

		DrawString(800, 10, "TIMER: ", colors[5]);

		string ttimer1 = to_string(timer1);

		DrawString(980, 10, ttimer1, colors[5]);

		DrawString(965, 10, " : ", colors[5]);

		string ttimer2 = to_string(timer2);	

		DrawString(950, 10, ttimer2, colors[5]);

		DrawString(930, 10, " : ", colors[5]);


		string ttimer22 = to_string(timer22);	

		DrawString(920, 10, ttimer22, colors[5]);

		// DrawString(910, 10, " : ", colors[5]);

		//	glPopMatrix();
		// if (bombStatus == true) {
		// 	DrawCircle(450, 70, 15, colors[RED]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position
		// 	bombStatus = false;
		// }
	}	

	glutPostRedisplay();

	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	/*
	 glutPostRedisplay();
	 */
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

int count = 0;

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {

		count++;

		menu = false;
		escape = true;

		ofile.open("score.txt", ios::in);

		ofile >> high;

		if (score > high)
		{
			ifile.open("score.txt", ios::out);

			ifile << sscore;

			ifile.close();
		}

		ofile.close();



		if (escape == false && menu == true)
		{
			count = 0;
		}

		if (count >= 2)
		{
			exit(1); // exit the program when escape key is pressed.
		}
	}

	if (key == 'P' || key == 'p'/* Escape key ASCII*/) {
		menu = true; // exit the program when escape key is pressed.
		escape = false;
	}

	if (key == 'h' || key == 'h'/* Escape key ASCII*/) {
		hs = true;
	}




	// if (key == 'b' || key == 'B') //Key for placing the bomb
	// 		{
	// 	bombStatus = true;

	// }
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutPostRedisplay();
	glutTimerFunc(1000.0, Timer, 0);

}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) 
{
	// cout << x << " " << y << endl;

	y = 820 - y;
	// x -= 1020;

	for (int i = 0; i < 15; ++i)
	{
		if (x >= ptrc1[i]->getx() - c1[i]->getr() && x <= ptrc1[i]->getx() + c1[i]->getr() && y <= ptrc1[i]->gety() + c1[i]->getr() && y >= ptrc1[i]->gety() - c1[i]->getr() )
		{
			// score+=2;
			// ptrc1[i]->setr(0);
			ptrc1[i]->setx(x * 1.0);
			ptrc1[i]->sety(y * 1.0);
			
		}

		// if (x <= ptrc1[i]->getx() - ptrc1[i]->getr() && x >= ptrc1[i]->getx() + ptrc1[i]->getr() && y <= ptrc1[i]->gety() + ptrc1[i]->getr() && y >= ptrc1[i]->gety() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

		// if (y >= ptrc1[i]->gety() - ptrc1[i]->getr() && y <= ptrc1[i]->gety() + ptrc1[i]->getr() && x <= ptrc1[i]->getx() + ptrc1[i]->getr() && x >= ptrc1[i]->getx() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

		// if (y <= ptrc1[i]->gety() - ptrc1[i]->getr() && y >= ptrc1[i]->gety() + ptrc1[i]->getr() && x <= ptrc1[i]->getx() + ptrc1[i]->getr() && x >= ptrc1[i]->getx() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

	}

	glutPostRedisplay();
}

void MouseMoved(int x, int y) 
{

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) 
{

	// if (state != 0)
	// {
	// 	cout << x << " " << y << endl;
	// }

	
	// x -= 1020;

	if (x >= 480 && x <= 580 && y >= 335 && y <= 380)
	{
		menu = true;
	}

	if (escape == true)
	{
		if (x > 450 && x < 620 && y > 625 && y < 670)
		{
			menu = true;
			escape = false;
		}
	}

	if (menu == false)
	{
		if (x > 435 && x < 635 && y > 485 && y < 430)
		{
			hs = true;
			menu = false;
			escape = false;
		}
	}

	y = 820 - y;

	for (int i = 0; i < 15; ++i)
	{
		if (x >= ptrc1[i]->getx() - c1[i]->getr() && x <= ptrc1[i]->getx() + c1[i]->getr() && y <= ptrc1[i]->gety() + c1[i]->getr() && y >= ptrc1[i]->gety() - c1[i]->getr() )
		{
			score+=2;
			c1[i]->setr(0);
			ptrc1[i]->setx(300000);
			ptrc1[i]->sety(300000);
			
		}

		// if (x <= ptrc1[i]->getx() - ptrc1[i]->getr() && x >= ptrc1[i]->getx() + ptrc1[i]->getr() && y <= ptrc1[i]->gety() + ptrc1[i]->getr() && y >= ptrc1[i]->gety() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

		// if (y >= ptrc1[i]->gety() - ptrc1[i]->getr() && y <= ptrc1[i]->gety() + ptrc1[i]->getr() && x <= ptrc1[i]->getx() + ptrc1[i]->getr() && x >= ptrc1[i]->getx() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

		// if (y <= ptrc1[i]->gety() - ptrc1[i]->getr() && y >= ptrc1[i]->gety() + ptrc1[i]->getr() && x <= ptrc1[i]->getx() + ptrc1[i]->getr() && x >= ptrc1[i]->getx() - ptrc1[i]->getr() )
		// {
		// 	score+=2;
		// 	ptrc1[i]->setr(0);
		// 	ptrc1[i]->setx(300000);
		// 	ptrc1[i]->sety(300000);
		// }

	}

	// cout << "state: " << state << endl;

	// cout << "button: " << button << endl;
	glutPostRedisplay();

}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	srand(time(NULL));

	


	  for (int i = 0; i < 15; ++i)
	  {
	  	c1[i] = new Circle();
	  }

	  for (int i = 0; i < 10; ++i)
	  {
	  	r1[i] = new Rectangle();
	  }

	  ptrc1 = (Shape ** )c1;
	  ptrr1 = (Shape ** )r1;

	  for (int i = 0; i < 15; ++i)
		{
			ptrc1[i]->RandPos();
		}

		 for (int i = 0; i < 10; ++i)
		{
			ptrr1[i]->RandPos();
		}

	

	// // ptr = new Shape*[3];

	// for (int i = 0; i < 15; ++i)
	// {
	// 	ptr[0][i] = &c1[i];
	// }
	

	// // for (int i = 0; i < 15; ++i)
	// // {
	// // 	ptr[i].RandPos();
	// // }
	
	


	b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Bomber Bomberman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
