#pragma once
#include <SFML\Graphics.hpp>

//Diese Klasse wird gebraucht, da die sf::Color Klasse von SFML für manche Zwecke zu ungenau ist.
//Die Variablennamen unterliegen diesmal nicht unseren eigentlichen Konvetionen, damit diese parktisch genauso aussieht wie die von SFML!
namespace ety
{
	class Color
	{
	private:
	protected:
	public:
					Color			(void);
					~Color			(void);

					Color			(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255);
					Color			(float red, float green, float blue, float alpha = 255);
					Color			(sf::Color c_sfColor);

		float		r;
		float		g;
		float		b;
		float		a;

		//Diese Funktion konvertiert die float Werte in ein sf::Color-Objekt und gibt diese zurück
		sf::Color	get_sfColor		(void);
	};
}

