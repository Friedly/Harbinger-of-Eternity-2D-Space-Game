#include "CColor.hpp"


			ety::Color::Color			(void)
			:r							(255)
			,g							(255)
			,b							(255)
			,a							(255)
{
}


			ety::Color::~Color			(void)
{
}


			ety::Color::Color			(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha)
{
	r	=	float(red);
	g	=	float(green);
	b	=	float(blue);
	a	=	float(alpha);
}

			ety::Color::Color			(float red, float green, float blue, float alpha)
			:r							(red)
			,g							(green)
			,b							(blue)
			,a							(alpha)
{
}
			
			ety::Color::Color			(sf::Color c_sfColor)
{
	r	=	float(c_sfColor.r);
	g	=	float(c_sfColor.g);
	b	=	float(c_sfColor.b);
	a	=	float(c_sfColor.a);
}



sf::Color	ety::Color::get_sfColor		(void)
{
	sf::Color c_sfColor;

	c_sfColor.r	=	sf::Uint8(r);
	c_sfColor.g	=	sf::Uint8(g);
	c_sfColor.b	=	sf::Uint8(b);
	c_sfColor.a	=	sf::Uint8(a);

	return c_sfColor;
}
