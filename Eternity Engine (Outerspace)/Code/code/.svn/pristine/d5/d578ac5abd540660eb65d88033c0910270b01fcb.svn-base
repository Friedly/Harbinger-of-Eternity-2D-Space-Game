#pragma once

#include <map>
#include <string>

#include <boost\weak_ptr.hpp>

#include <SFML\Graphics\RenderTexture.hpp>

namespace ety
{
	class CEntitymanager;
	class CComponent;

	class CComponentsystem
	{
	private:
	protected:
		std::map< std::string, CComponent* >		m_c_stdMapComponentByUniqueEntityID;

		ety::CEntitymanager*						mp_c_etyEntitymanager;

	public:
													CComponentsystem	( ety::CEntitymanager* const p_c_etyEntitymanager );
													~CComponentsystem	( void );

		virtual				void					update_Components	( const sf::Uint32& uiFrameTime ) = 0;
		virtual				void					render_Components	( sf::RenderTexture* const p_c_sfRenderTextureGameScene ) = 0;
	};
}

