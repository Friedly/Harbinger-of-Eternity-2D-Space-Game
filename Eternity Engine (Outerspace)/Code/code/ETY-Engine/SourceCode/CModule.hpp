#pragma once

#include <sfml\System\Vector2.hpp>

#include "CItem.hpp"

namespace ety
{
	class CItemModulesComponent;

	class CModule
	{
	private:
				ety::CItemModulesComponent*		mp_c_etyOwnerComponent;

				ModuleType::en_etyModuleType	m_en_etyModuleType;

				sf::Vector2f					m_c_sfVectorPosition;
		
				sf::Vector2i					m_c_sfVectorClassRange;

				ety::CItem*						mp_c_etyItem;

	public:
												CModule					( const ety::ModuleType::en_etyModuleType en_etyModuleType, const sf::Vector2i& c_sfVectorClassRange, const sf::Vector2f& c_sfVectorModulePosition, ety::CItemModulesComponent* const p_c_etyOwnerComponent );
												~CModule				( void );

				void							clear_Item				( void );

				void							update_Module			( const sf::Uint32& uiFrameTime );
				void							render_Module			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       

		const	bool							set_Item				( ety::CItem* const p_c_etyItem );

				ety::CItem*		const			get_Item				( void );
		const	sf::Sprite&						get_Appearance			( void );
	};
}

