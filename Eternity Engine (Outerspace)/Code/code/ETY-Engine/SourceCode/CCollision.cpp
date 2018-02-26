#include "CCollision.hpp"


				ety::CCollision::CCollision							( void )
{
}
				ety::CCollision::~CCollision						( void )
{
}

const	bool	ety::CCollision::check_BoundingCircleCollision		( const sf::Vector2f& c_sfVectorCenterPosition1, const sf::Vector2f& c_sfVectorCenterPosition2, const float fRadius1, const float fRadius2 )
{
	const sf::Vector2f c_sfVectorDifference = c_sfVectorCenterPosition1 - c_sfVectorCenterPosition2;

	const float fDistance = ( c_sfVectorDifference.x * c_sfVectorDifference.x ) + ( c_sfVectorDifference.y * c_sfVectorDifference.y );

	return fDistance <= ( fRadius1 + fRadius2 )*( fRadius1 + fRadius2 );
}