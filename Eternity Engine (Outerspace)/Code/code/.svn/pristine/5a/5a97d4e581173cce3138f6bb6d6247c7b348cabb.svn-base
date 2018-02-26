#pragma once

//Eternity-Engine
#include "CComponent.hpp"
#include "CAnimatedSprite.hpp"

#include "CMathConvertClasses.hpp"

//SFML-Bibliothek
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Window\VideoMode.hpp>
#include <SFML\Graphics\View.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

namespace ety
{
	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CRenderComponent : public CComponent
	{
	private:
	protected:
		sf::Vector2f									m_c_sfVectorDirection;
		
		float											m_fLayer;
		float											m_fAngle;

		void											scale_SpriteWithLayer	( const sf::Vector2f& c_sfVectorLayerscaling, sf::Sprite* const p_c_sfSpriteAppearance )
		{
			if( c_sfVectorLayerscaling.x != 0.f && c_sfVectorLayerscaling.y != 0.f )
			{
				float fEntityScalingXY		= 1;

				const float fEntityLayer	= m_fLayer;

				if( fEntityLayer > 0 )
				{
					for( int iLayer = 0; iLayer < fEntityLayer; iLayer++ )
					{
						fEntityScalingXY += fEntityScalingXY * c_sfVectorLayerscaling.x;
					}
				}
				else if( fEntityLayer < 0 )
				{
					fEntityScalingXY = pow( c_sfVectorLayerscaling.y, (-1.f * fEntityLayer) );
				}

				p_c_sfSpriteAppearance->scale( fEntityScalingXY, fEntityScalingXY );
			}
		}

	public:
														CRenderComponent	( const float fLayer, const float fAngle );
		virtual											~CRenderComponent	( void );

		virtual					void					render_Component	( sf::RenderTexture* const p_c_sfRenderTextureGameScene ) = 0;

								void					set_Direction		( const sf::Vector2f& c_sfVectorDirection );
		virtual					void					set_Angle			( const float fAngle );

					const		float					get_Angle			( void );
					const		float					get_Layer			( void );
					const		sf::Vector2f&			get_Direction		( void );
		virtual		const		sf::Vector2f&			get_Position		( void ) = 0;
		virtual					sf::Sprite*		const	get_Appearance		( void ) = 0;

					const		std::string				get_FamilyID		( void );
		virtual		const		std::string				get_ComponentID		( void ) = 0;
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CAnimationRenderComponent : public CRenderComponent
	{
	private:
	protected:
								ety::CAnimatedSprite	m_c_etyAnimatedSpriteAppearence;
	public:
														CAnimationRenderComponent	( const sf::Texture& c_sfTextureAppearance, const sf::Vector2f& c_sfVectorPosition, const sf::Vector2f& c_sfVectorLayerscaling, const sf::VideoMode& c_sfVideomode, const bool bCentered, const float fLayer, const float fAngle );
		virtual											~CAnimationRenderComponent	( void );

		virtual					void					update_Component			( const sf::Uint32& uiFrameTime );
		virtual					void					render_Component			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		virtual					void					set_Angle					( const float fAngle );

					const		sf::Vector2f&			get_Position				( void );
		virtual					sf::Sprite*		const	get_Appearance				( void );

		virtual		const		std::string				get_ComponentID				( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CStaticRenderComponent : public CRenderComponent
	{
	private:
	protected:
								sf::Sprite				m_c_sfSpriteAppearance;
	public:
														CStaticRenderComponent		( const sf::Texture& c_sfTextureAppearance, const sf::Vector2f& c_sfVectorPosition, const sf::Vector2f& c_sfVectorLayerscaling, const sf::VideoMode& c_sfVideomode, const bool bCentered, const float fLayer, const float fAngle, const bool bSetNewDirection );
		virtual											~CStaticRenderComponent		( void );

		virtual					void					update_Component			( const sf::Uint32& uiFrameTime );
		virtual					void					render_Component			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		virtual					void					set_Angle					( const float fAngle );

					const		sf::Vector2f&			get_Position				( void );
		virtual					sf::Sprite*		const	get_Appearance				( void );

		virtual		const		std::string				get_ComponentID				( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//

	class CStaticBackgroundRenderComponent : public CRenderComponent
	{
	private:
	protected:
									sf::Sprite					m_c_sfSpriteAppearance;
	public:
																CStaticBackgroundRenderComponent		( const sf::Texture& c_sfTextureAppearance, const sf::VideoMode& c_sfVideomode, const float fLayer );
		virtual													~CStaticBackgroundRenderComponent		( void );

		virtual					void							update_Component						( const sf::Uint32& uiFrameTime );
		virtual					void							render_Component						( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		virtual					void							set_Angle								( const float fAngle );

						const	sf::Vector2f&					get_Position							( void );
		virtual					sf::Sprite*		const			get_Appearance							( void );

		virtual		const		std::string						get_ComponentID							( void );
	};

	//#########################################################################################################//
	//#########################################################################################################//
	//#########################################################################################################//
}

