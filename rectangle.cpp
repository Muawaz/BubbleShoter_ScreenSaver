#include "rectangle.h"


	Rectangle::Rectangle()
	{
		start_x = 0;
		start_y = 0;
		length = 0;
		width = 0;
	}

	Rectangle::Rectangle(float x, float y, float l, float w)
	{
		start_x = x;
		start_y = y;
		length = l;
		width = w;
	}

	float Rectangle::getl()
	{
		return length;
	}

	void Rectangle::setl(float l)
	{
		length = l;
	}

	float Rectangle::getw()
	{
		return width;
	}

	void Rectangle::setw(float w)
	{
		width = w;
	}

	float Rectangle::getml()
	{
		return (length / 2.0);
	}

	float Rectangle::getmw()
	{
		return (width / 2.0);
	}

	bool Rectangle::getxpos()
	{
		return xpos;
	}

	void Rectangle::setxpos(bool x)
	{
		xpos = x;
	}

	bool Rectangle::getypos()
	{
		return ypos;
	}

	void Rectangle::setypos(bool y)
	{
		ypos = y;
	}



	float Rectangle::getx()
	{
		return start_x;
	}

	float Rectangle::gety()
	{
		return start_y;
	}

	void Rectangle::setx(float x)
	{
		start_x = x;
	}

	void Rectangle::sety(float y)
	{
		start_y = y;
	}

	int Rectangle::getcolor()
	{
		return color;
	}


	
	
	void Rectangle::RandPos()
	{
		start_x = (rand() % 1020) + 10;
		start_y = (rand() % 840) + 10;
		length = (rand() % 20) + 30;
		width = (rand() % 10) + 25;
		color = (rand() % 137);
		
		xpos = true;
		ypos = true;

	}

	void Rectangle::DrawShape()
	{
		DrawRectangle(start_x, start_y, (length / 2.0), (width / 2.0), colors[color]);
	}

	void Rectangle::Move()
	{
		if ((start_x + length / 2.0) < 1010 && xpos == true)
		{
			start_x += 5;

			if ((start_x + length / 2.0) >= 1010)
			{
				xpos = false;
			}
		}

		else if ((start_x + length / 2.0) >= 10 && xpos == false)
		{
			start_x -= 5;
			if ((start_x + length / 2.0) < 10)
			{
				xpos  = true;
			}
		}

		if ((start_y + width / 2.0) < 830 && ypos == true)
		{
			start_y += 5;
			if ((start_y + width / 2.0) >= 830)
			{
				ypos  = false;
			}
		}
		else if ((start_y + width / 2.0) >= 10 && ypos == false)
		{
			start_y -= 5;
			if ((start_y + width / 2.0) <= 10)
			{
				ypos  = true;
			}
		}
	}

	// void Detection();

	// void operator=(Circle&);
	
	// ~Circle();
	
