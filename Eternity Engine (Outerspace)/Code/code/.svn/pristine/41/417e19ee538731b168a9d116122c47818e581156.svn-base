#pragma once

#include "CComponent.hpp"

#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\RenderTexture.hpp>

namespace ety
{
	class CCollisionComponent : public CComponent
	{
	private:
	protected:
	public:
												CCollisionComponent			( void );
		virtual									~CCollisionComponent		( void );

		virtual					void			render_Component			( sf::RenderTexture* const p_c_sfRenderTextureGameScene ) = 0;
		
					const		std::string		get_FamilyID				( void );
		
	};

	class CCircleCollisionComponent : public CCollisionComponent
	{
	private:
	protected:
								bool					m_bInitialized;

								sf::CircleShape			m_c_sfCircleHitbox;

	public:
														CCircleCollisionComponent	( void );
		virtual											~CCircleCollisionComponent	( void );

		virtual					void					render_Component			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		virtual					void					update_Component			( const sf::Uint32& uiFrameTime );

					const		float					get_Radius					( void );
					const		sf::Vector2f&			get_Center					( void );

		virtual		const		std::string				get_ComponentID				( void );
	};
}

