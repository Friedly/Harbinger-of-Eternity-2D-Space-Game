//Includes des Compilers

#pragma once

#include <sstream>
#include <cmath>
#include <sfml\System\Vector2.hpp>

#define PI 3.14159265358979323846f

#define sqr(x) ((x)*(x))
#define sin_d(x) (sin((x)*PI/180))
#define cos_d(x) (cos((x)*PI/180))
#define tan_d(x) (tan((x)*PI/180))
#define asin_d(x) (asin(x)*180/PI)
#define acos_d(x) (acos(x)*180/PI)
#define atan_d(x) (atan(x)*180/PI) 

namespace ety
{
	class CConvert
	{
	public:
		static const	float					convert_StringToNumber		( const std::string& strNumber )
		{
			std::stringstream	Stream;
			float				fNumber = 0.f;

			Stream << strNumber;

			Stream >> fNumber;

			return fNumber;
		}

		static const	std::string				convert_NumberToString		( const float fNumber )
		{
			std::ostringstream Stream;

			Stream << fNumber;

			return Stream.str();
		}
	};

	class CMath
	{
	public:
		template < class T >
		static T					calculate_Length			( const sf::Vector2<T>& c_sfVector )
		{
			return static_cast<T>(sqrt( ( pow( c_sfVector.x, 2) ) + ( pow( c_sfVector.y, 2) )));
		}

		template < class T >
		static T					calculate_Scalarproduct		( const sf::Vector2<T>& c_sfVector1, const sf::Vector2<T>& c_sfVector2 )
		{
			return static_cast<T>(c_sfVector1.x * c_sfVector2.x + c_sfVector1.y * c_sfVector2.y);
		}

		template < class T >
		static sf::Vector2<T>		normalize_Vector			( const sf::Vector2<T>& c_sfVectorToNormalize )
		{
			const float fLength = calculate_Length<float>( c_sfVectorToNormalize );

			return sf::Vector2<T>	( 
										c_sfVectorToNormalize.x / fLength,
										c_sfVectorToNormalize.y / fLength
									);
		}

		template < class T >
		static sf::Vector2<T>		rotate_Vector				( const sf::Vector2<T>& c_sfVectorToRotate, const float fAngle )
		{
			sf::Vector2<T> c_sfRotatedVector;

			float fSinus		= sin_d(fAngle);
			float fCosinus		= cos_d(fAngle);

			float fTempX		= ( c_sfVectorToRotate.x * fCosinus ) - ( c_sfVectorToRotate.y * fSinus );
			c_sfRotatedVector.y	= ( c_sfVectorToRotate.y * fCosinus ) + ( c_sfVectorToRotate.x * fSinus );
			c_sfRotatedVector.x	= fTempX;

			return c_sfRotatedVector;
		}

		template < class T >	
		static sf::Vector2<T>		build_DirectionVector		( const sf::Vector2<T>& c_sfEndVector, const sf::Vector2<T>& c_sfStartVector )
		{
			sf::Vector2<T> c_sfVectorDirection( c_sfEndVector.x - c_sfStartVector.x, c_sfEndVector.y - c_sfStartVector.y );

			return c_sfVectorDirection;
		}

		template < class T >	
		static sf::Vector2<T>		build_StraightLine			( const sf::Vector2<T>& c_sfStartPoint, const sf::Vector2<T>& c_sfEndPoint )
		{
			//m = y2-y1/x2-x1
			//b = y1 = m*x1 + b
			sf::Vector2<T> c_sfVectorStraightLine( (c_sfEndPoint.y - c_sfStartPoint.y)/(c_sfEndPoint.x - c_sfStartPoint.x), 0 );
			c_sfVectorStraightLine.y	=	c_sfStartPoint.y - (c_sfVectorStraightLine.x * c_sfStartPoint.x);

			return c_sfVectorStraightLine;
		}

		template < typename T >	
		static T					get_FunctionValue			( const sf::Vector2<T>& c_sfFunctionInfo, const T& TXValue )
		{
			return c_sfFunctionInfo.x * TXValue + c_sfFunctionInfo.y;
		}
	};
}