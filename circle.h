#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "shape.h"


class Circle: public Shape
{
	float radius;
	
	bool xpos;
	bool ypos;
public:
	Circle();

	Circle(float x, float y, float r);

	float getr();

	void setr(float r);

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

	void IncRadius();



	// void Detection();

	// void operator=(Circle&);
	
	// ~Circle();
	
};

#endif