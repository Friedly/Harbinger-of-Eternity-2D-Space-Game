#pragma once

#include <SFML\System\Vector2.hpp>

namespace ety
{
	class CCollision
	{
	private:
	protected:
	public:
								CCollision						( void );
								~CCollision						( void );

		static	const	bool	check_BoundingCircleCollision	( const sf::Vector2f& c_stdVectorCenter1, const sf::Vector2f& c_stdVectorCenter2, const float fRadius1, const float fRadius2 );
	};
}

