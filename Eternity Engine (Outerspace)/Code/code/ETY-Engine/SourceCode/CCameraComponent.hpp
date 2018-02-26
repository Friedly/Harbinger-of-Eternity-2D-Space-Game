#pragma once

#include "CComponent.hpp"

#include <SFML\Graphics\View.hpp>

namespace ety
{
	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CCameraComponent : public CComponent
	{
	private:
	protected:
		sf::View								m_c_sfViewCamera;
		sf::FloatRect							m_c_sfDrawRect;

	public:
												CCameraComponent			( const sf::Vector2f& c_sfVectorCameraSize );
		virtual									~CCameraComponent			( void );

					const		sf::View&		get_View					( void );

					const		std::string		get_FamilyID				( void );
		virtual		const		std::string		get_ComponentID				( void ) = 0;
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CCenteredCameraComponent : public CCameraComponent
	{
	private:
	protected:
	public:
												CCenteredCameraComponent	( const sf::Vector2f& c_sfVectorCameraSize );
		virtual									~CCenteredCameraComponent	( void );

		virtual		void						update_Component			( const sf::Uint32& uiFrameTime );

		virtual		const		std::string		get_ComponentID				( void );

					const		sf::FloatRect&	get_IntersectionRect		( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//
}

