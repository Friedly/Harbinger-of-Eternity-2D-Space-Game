#pragma once

#include "CComponentsystem.hpp"

namespace ety
{
	class CMovableComponentsystem : public CComponentsystem
	{
	private:
	protected:
	public:
					CMovableComponentsystem		( ety::CEntitymanager* const p_c_etyEntitymanager );
					~CMovableComponentsystem	( void );

		void		update_Components			( const sf::Uint32& uiFrameTime );
		void		render_Components			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );
	};
}

