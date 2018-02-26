#include "CCameraComponent.hpp"
#include "CRenderComponent.hpp"

#include "CEntity.hpp"

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//
							ety::CCameraComponent::CCameraComponent						( const sf::Vector2f& c_sfVectorCameraSize )
							{
								m_c_sfViewCamera.setSize( c_sfVectorCameraSize );

								m_c_sfDrawRect = sf::FloatRect( m_c_sfViewCamera.getCenter().x - ( m_c_sfViewCamera.getSize().x / 2.f ),
																m_c_sfViewCamera.getCenter().y - ( m_c_sfViewCamera.getSize().y / 2.f ), 
																m_c_sfViewCamera.getSize().x,
																m_c_sfViewCamera.getSize().y );
							}
							ety::CCameraComponent::~CCameraComponent					( void )
							{
							}

const		sf::View&		ety::CCameraComponent::get_View								( void )
{
	return m_c_sfViewCamera;
}

const		std::string		ety::CCameraComponent::get_FamilyID							( void )
			{
				return "CameraComponent";
			}
			
//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//

							ety::CCenteredCameraComponent::CCenteredCameraComponent		( const sf::Vector2f& c_sfVectorCameraSize )
								: CCameraComponent( c_sfVectorCameraSize )
							{
							}
							ety::CCenteredCameraComponent::~CCenteredCameraComponent	( void )
							{
							}

			void			ety::CCenteredCameraComponent::update_Component				( const sf::Uint32& uiFrameTime )
			{
				ety::CRenderComponent* p_c_etyRenderComponent = mp_c_Owner->get_Component<ety::CRenderComponent>("RenderComponent");

				if( p_c_etyRenderComponent != NULL )
				{
					m_c_sfViewCamera.setCenter( p_c_etyRenderComponent->get_Position() );
				}

				m_c_sfDrawRect = sf::FloatRect( m_c_sfViewCamera.getCenter().x - ( m_c_sfViewCamera.getSize().x / 2.f ),
								m_c_sfViewCamera.getCenter().y - ( m_c_sfViewCamera.getSize().y / 2.f ), 
								m_c_sfViewCamera.getSize().x,
								m_c_sfViewCamera.getSize().y );
			}

const		std::string		ety::CCenteredCameraComponent::get_ComponentID				( void )
			{
				return "CenteredCameraComponent";
			}
const		sf::FloatRect&	ety::CCenteredCameraComponent::get_IntersectionRect			( void )
{
	return m_c_sfDrawRect;
}

//#########################################################################################################//
//#########################################################################################################//
//#########################################################################################################//
