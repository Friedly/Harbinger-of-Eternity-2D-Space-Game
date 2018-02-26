#include "CCollisionComponentsystem.hpp"
#include "CCollisionComponent.hpp"
#include "CRenderComponent.hpp"
#include "CEntitymanager.hpp"
#include "CCollision.hpp"


				ety::CCollisionComponentsystem::CCollisionComponentsystem	( ety::CEntitymanager* const p_c_etyEntitymanager )
					: CComponentsystem( p_c_etyEntitymanager )
				{
				}
				ety::CCollisionComponentsystem::~CCollisionComponentsystem	( void )
				{
				}

		void	ety::CCollisionComponentsystem::update_Components			( const sf::Uint32& uiFrameTime )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorCollidableEntities	= mp_c_etyEntitymanager->get_Entities( "CollisionComponent"	);
			
			std::vector< boost::weak_ptr<ety::CEntity> >::iterator	itCollidableEntity	= c_stdVectorCollidableEntities.begin();

			for( std::vector< boost::weak_ptr<ety::CEntity> >::iterator itCollidableUpdateEntity = itCollidableEntity; itCollidableUpdateEntity != c_stdVectorCollidableEntities.end(); itCollidableUpdateEntity++  )
			{
				CCollisionComponent* p_c_CollidableComponent	= itCollidableUpdateEntity->lock()->get_Component<CCollisionComponent>("CollisionComponent");

				if( p_c_CollidableComponent != NULL )
				{
					p_c_CollidableComponent->update_Component( uiFrameTime );
				}
			}

			for( itCollidableEntity; itCollidableEntity != c_stdVectorCollidableEntities.end(); itCollidableEntity++ )
			{
				for( std::vector< boost::weak_ptr<ety::CEntity> >::iterator itCollidableOtherEntity = itCollidableEntity+1; itCollidableOtherEntity != c_stdVectorCollidableEntities.end(); itCollidableOtherEntity++)
				{
					ety::CCollisionComponent* p_c_etyCollisionComponent			= itCollidableEntity		->lock()->get_Component<ety::CCollisionComponent>("CollisionComponent");
					ety::CCollisionComponent* p_c_etyCollisionOtherComponent	= itCollidableOtherEntity	->lock()->get_Component<ety::CCollisionComponent>("CollisionComponent");

					float fLayerFirst	= p_c_etyCollisionComponent			->get_Owner()->get_Component<ety::CRenderComponent>( "RenderComponent" )->get_Layer();
					float fLayerSecond	= p_c_etyCollisionOtherComponent	->get_Owner()->get_Component<ety::CRenderComponent>( "RenderComponent" )->get_Layer();

					if( p_c_etyCollisionComponent->get_ComponentID() == "CircleCollisionComponent" && p_c_etyCollisionOtherComponent->get_ComponentID() == "CircleCollisionComponent" )
					{
						ety::CCircleCollisionComponent* p_c_etyCircleCollisionComponent			= static_cast<CCircleCollisionComponent*>( p_c_etyCollisionComponent );
						ety::CCircleCollisionComponent* p_c_etyCircleCollisionOtherComponent	= static_cast<CCircleCollisionComponent*>( p_c_etyCollisionOtherComponent );

						if( fLayerFirst == fLayerSecond && CCollision::check_BoundingCircleCollision( p_c_etyCircleCollisionComponent->get_Center(), p_c_etyCircleCollisionOtherComponent->get_Center(), p_c_etyCircleCollisionComponent->get_Radius(), p_c_etyCircleCollisionOtherComponent->get_Radius() ) )
						{
							//Reaktion
						}
					}
				}
			}
		}
		void	ety::CCollisionComponentsystem::render_Components			( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorCollidableEntities	= mp_c_etyEntitymanager->get_Entities( "CollisionComponent"	);
			
			std::vector< boost::weak_ptr<ety::CEntity> >::iterator	itCollidableEntity	= c_stdVectorCollidableEntities.begin();

			for( itCollidableEntity; itCollidableEntity != c_stdVectorCollidableEntities.end(); itCollidableEntity++ )
			{
				ety::CCollisionComponent* p_c_etyCollisionComponent = itCollidableEntity->lock()->get_Component<ety::CCollisionComponent>( "CollisionComponent" );

				if( p_c_etyCollisionComponent != NULL )
				{
					p_c_etyCollisionComponent->render_Component( p_c_sfRenderTextureGameScene );
				}
			}

		}
