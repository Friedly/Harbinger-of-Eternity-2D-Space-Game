#include "CMovableComponentSystem.hpp"
#include "CMovableComponent.hpp"
#include "CEntitymanager.hpp"


				ety::CMovableComponentsystem::CMovableComponentsystem	( ety::CEntitymanager* const p_c_etyEntitymanager )
					: CComponentsystem( p_c_etyEntitymanager )
				{
				}
				ety::CMovableComponentsystem::~CMovableComponentsystem	( void )
				{
				}

		void	ety::CMovableComponentsystem::update_Components			( const sf::Uint32& uiFrameTime )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorMovableEntities	= mp_c_etyEntitymanager->get_Entities( "MovableComponent" );
			
			std::vector< boost::weak_ptr<ety::CEntity> >::iterator itMovableEntity = c_stdVectorMovableEntities.begin();

			for( itMovableEntity; itMovableEntity != c_stdVectorMovableEntities.end(); itMovableEntity++ )
			{
				CMovableComponent* p_c_MovableEntity = itMovableEntity->lock()->get_Component<CMovableComponent>( "MovableComponent" );
				
				if( p_c_MovableEntity != NULL )
				{
					p_c_MovableEntity->update_Component( uiFrameTime );
				}
			}
		}
		void	ety::CMovableComponentsystem::render_Components			( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
		}
