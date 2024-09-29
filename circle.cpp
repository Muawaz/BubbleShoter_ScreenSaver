#include "circle.h"



	Circle::Circle()
	{
		start_x = 0;
		start_y = 0;
		radius = 15;
		
	}

	Circle::Circle(float x, float y, float r)
	{
		start_x = x;
		start_y = y;
		radius = r;
	}

	float Circle::getr()
	{
		return radius;
	}

	void Circle::setr(float r)
	{
		radius = r;
	}

	bool Circle::getxpos()
	{
		return xpos;
	}

	void Circle::setxpos(bool x)
	{
		xpos = x;
	}

	bool Circle::getypos()
	{
		return ypos;
	}

	void Circle::setypos(bool y)
	{
		ypos = y;
	}


	float Circle::getx()
	{
		return start_x;
	}

	float Circle::gety()
	{
		return start_y;
	}

	void Circle::setx(float x)
	{
		start_x = x;
	}

	void Circle::sety(float y)
	{
		start_y = y;
	}

	int Circle::getcolor()
	{
		return color;
	}

	
	
	void Circle::RandPos()
	{
		start_x = (rand() % 1020) + 10;
		start_y = (rand() % 840) + 10;
		radius = (rand() % 20) + 15;
		color = (rand() % 20) + 10;
		
		xpos = true;
		ypos = true;

	}

	void Circle::DrawShape()
	{
		
		DrawCircle(start_x, start_y, radius, colors[color]);
	}

	void Circle::Move()
	{
		if (start_x < 1000 && xpos == true)
		{
			start_x += 2;
			if (start_x >= 1000)
			{
				xpos  = false;
			}
		}
		else if (start_x >= 10 && xpos == false)
		{
			start_x -= 2;
			if (start_x < 10)
			{
				xpos  = true;
			}
		}

		if (start_y < 820 && ypos == true)
		{
			start_y += 2;
			if (start_y >= 820)
			{
				ypos  = false;
			}
		}
		else if (start_y >= 10 && ypos == false)
		{
			start_y -= 2;
			if (start_y <= 10)
			{
				ypos  = true;
			}
		}


	}

	void Circle::IncRadius()
	{
		radius += 10;
	}

	// void Detection()
	// {

	// }

	// ~Circle();