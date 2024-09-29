#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#include "shape.h"


class Rectangle: public Shape
{
	float length;
	float width;
	
	bool xpos;
	bool ypos;
public:
	Rectangle();

	Rectangle(float x, float y, float l, float w);

	float getl();

	void setl(float l);

	float getw();

	void setw(float w);

	float getml();

	float getmw();

	bool getxpos();

	void setxpos(bool x);

	bool getypos();

	void setypos(bool y);


	float getx();

	float gety();

	void setx(float x);

	void sety(float y);

	int getcolor();


	
	void RandPos();

	void DrawShape();

	void Move();

	// void Detection();

	// void operator=(Circle&);
	
	// ~Circle();
	
};

#endif