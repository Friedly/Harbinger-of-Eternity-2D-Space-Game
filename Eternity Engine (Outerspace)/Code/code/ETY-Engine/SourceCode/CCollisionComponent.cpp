#include "CCollisionComponent.hpp"
#include "CRenderComponent.hpp"
#include "CEntity.hpp"

#include <SFML\Graphics\Sprite.hpp>


//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

							ety::CCollisionComponent::CCollisionComponent				( void )
{
}
							ety::CCollisionComponent::~CCollisionComponent				( void )
{
}

const		std::string		ety::CCollisionComponent::get_FamilyID						( void )
{
	return "CollisionComponent";
}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

							ety::CCircleCollisionComponent::CCircleCollisionComponent	( void )
								: m_bInitialized ( false )
							{
							}
							ety::CCircleCollisionComponent::~CCircleCollisionComponent	( void )
							{
							}

			void			ety::CCircleCollisionComponent::render_Component			( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
			{
				p_c_sfRenderTextureGameScene->draw( m_c_sfCircleHitbox );
			}

			void			ety::CCircleCollisionComponent::update_Component			( const sf::Uint32& uiFrameTime )
			{
				ety::CRenderComponent* p_c_RenderComponent = mp_c_Owner->get_Component<ety::CRenderComponent>("RenderComponent");

				if( p_c_RenderComponent != NULL )
				{
					m_c_sfCircleHitbox.setPosition( p_c_RenderComponent->get_Position() );

					m_bActive = true;

					if( m_bInitialized == false )
					{
						sf::Sprite c_sfSpriteForRadius = *p_c_RenderComponent->get_Appearance();

						c_sfSpriteForRadius.setRotation( 0.f );

						if( c_sfSpriteForRadius.getGlobalBounds().width > c_sfSpriteForRadius.getGlobalBounds().height )
						{
							m_c_sfCircleHitbox.setRadius( c_sfSpriteForRadius.getGlobalBounds().width/2.f );
						}
						else
						{
							m_c_sfCircleHitbox.setRadius( c_sfSpriteForRadius.getGlobalBounds().height/2.f );
						}
						
						m_c_sfCircleHitbox.setFillColor			( sf::Color::Transparent );
						m_c_sfCircleHitbox.setOutlineColor		( sf::Color( 255, 0, 0 ) );
						m_c_sfCircleHitbox.setOutlineThickness	( 1.f );
						m_c_sfCircleHitbox.setOrigin			( m_c_sfCircleHitbox.getRadius(), m_c_sfCircleHitbox.getRadius() );

						m_bInitialized = true;
					}
				}
				else
				{
					m_bActive = false;
				}
			}

const		float			ety::CCircleCollisionComponent::get_Radius					( void )
			{
				return m_c_sfCircleHitbox.getRadius();
			}
const		sf::Vector2f&	ety::CCircleCollisionComponent::get_Center					( void )
			{
				return m_c_sfCircleHitbox.getPosition();
			}

const		std::string		ety::CCircleCollisionComponent::get_ComponentID				( void )
			{
				return "CircleCollisionComponent";
			}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//
