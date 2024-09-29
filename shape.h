#ifndef SHAPE_H_
#define SHAPE_H_
#include <iostream>
#include "util.h"
using namespace std;

class Shape
{
protected:

	float start_x;
	float start_y;
	int color;
	
public:
	Shape()
	{
		start_x = 0;
		start_y = 0;
	}

	virtual float getx() = 0;

	virtual float gety() = 0;

	virtual void setx(float x) = 0;

	virtual void sety(float y) = 0;

	virtual int getcolor() = 0;

	virtual void DrawShape() = 0;
	virtual void RandPos() = 0;
	virtual void Move() = 0;

	// virtual void operator=() = 0;

	// virtual void SizeShape() = 0;
	// virtual void ColorShape() = 0;
	// virtual void Detection() = 0;

	// shape();
	// ~shape();
	
};

#endif