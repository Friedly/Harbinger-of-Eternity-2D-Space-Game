#pragma once

#include "CComponent.hpp"
#include "CAttribute.hpp"

#include <map>

namespace ety
{
	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CAttribute;

	class CAttributeComponent : public CComponent
	{
	private:
	protected:
	public:
								ety::CAttribute			m_c_etyAttributes;


														CAttributeComponent		( const std::string& c_stdStringEntityKey );
		virtual											~CAttributeComponent	( void );

					const		std::string				get_FamilyID			( void );
		virtual		const		std::string				get_ComponentID			( void ) = 0;
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CSpaceshipAttributeComponent : public CAttributeComponent
	{
	private:
	protected:
	public:
														CSpaceshipAttributeComponent		( const std::string& c_stdStringEntityKey );
		virtual											~CSpaceshipAttributeComponent		( void );

		virtual					void					update_Component					( const sf::Uint32& uiFrameTime );

		virtual		const		std::string				get_ComponentID						( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CEnvironmentAttributeComponent : public CAttributeComponent
	{
	private:
	protected:
	public:
														CEnvironmentAttributeComponent		( const std::string& c_stdStringEntityKey );
		virtual											~CEnvironmentAttributeComponent		( void );

		virtual					void					update_Component					( const sf::Uint32& uiFrameTime );

		virtual		const		std::string				get_ComponentID						( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//
}

