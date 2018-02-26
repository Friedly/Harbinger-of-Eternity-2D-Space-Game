#include "CModule.hpp"

#include "CItemModulesComponent.hpp"
#include "CRenderComponent.hpp"
#include "CEntity.hpp"

											ety::CModule::CModule			( const ety::ModuleType::en_etyModuleType en_etyModuleType, const sf::Vector2i& c_sfVectorClassRange, const sf::Vector2f& c_sfVectorModulePosition, ety::CItemModulesComponent* const p_c_etyOwnerComponent )
												: m_en_etyModuleType		( en_etyModuleType )
												, m_c_sfVectorPosition		( c_sfVectorModulePosition )
												, m_c_sfVectorClassRange	( c_sfVectorClassRange )
												, mp_c_etyItem				( NULL )
												, mp_c_etyOwnerComponent	( p_c_etyOwnerComponent )
											{
											}
											ety::CModule::~CModule			( void )
										{
										}

				void						ety::CModule::clear_Item		( void )
		{
			mp_c_etyItem = NULL;
		}
		
				void						ety::CModule::update_Module		( const sf::Uint32& uiFrameTime )
		{
			if( mp_c_etyItem != NULL )
			{
				mp_c_etyItem->update_Item( uiFrameTime );
			}
		}
				void						ety::CModule::render_Module		( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			if( mp_c_etyItem != NULL )
			{
				mp_c_etyItem->render_Item( p_c_sfRenderTextureGameScene );
			}
		}

		const	bool						ety::CModule::set_Item			( ety::CItem* const p_c_etyItem )
		{
			if( p_c_etyItem != NULL )
			{
				if( p_c_etyItem->get_Class() >= static_cast<unsigned int>(m_c_sfVectorClassRange.x) && p_c_etyItem->get_Class() <= static_cast<unsigned int>(m_c_sfVectorClassRange.y ) )
				{
					if( m_en_etyModuleType == p_c_etyItem->get_ItemType() )
					{
						p_c_etyItem->set_ParentModule( this );
						mp_c_etyItem = p_c_etyItem;

						return true;
					}
				}
			}

			return false;
		}

				ety::CItem*		const		ety::CModule::get_Item			( void )
		{
			return mp_c_etyItem;
		}

		const	sf::Sprite&					ety::CModule::get_Appearance	( void )
		{
			ety::CRenderComponent* p_c_etyRenderComponent = mp_c_etyOwnerComponent->get_Owner()->get_Component<ety::CRenderComponent>("RenderComponent");

			return *p_c_etyRenderComponent->get_Appearance();
		}
