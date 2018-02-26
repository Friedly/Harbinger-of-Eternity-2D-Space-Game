#pragma once

#include "CComponent.hpp"
#include "CModule.hpp"
#include "CItemManagement.hpp"

#include <map>

#include <SFML\Graphics\RenderTexture.hpp>

#include <boost\shared_ptr.hpp>
#include <boost\weak_ptr.hpp>

namespace ety
{
	class CItemModulesComponent : public CComponent
	{
	private:
	protected:
								std::map< ety::ModuleType::en_etyModuleType, boost::shared_ptr<ety::CModule> >		m_c_stdMapEquipmentModuleByType;
								std::map< std::string, boost::shared_ptr<ety::CModule> >							m_c_stdMapWeaponModuleByID;
	public:
																													CItemModulesComponent			( const std::string& c_stdStringEntityKey );
																													~CItemModulesComponent			( void );

					const		bool																				call_ItemScript					( const std::string& c_stdStringTemplate, ety::CItemManagement* const p_c_etyItemManagement );

					const		bool																				create_EquipmentModule			( const sf::Vector2i& c_sfVectorClassRange, const ety::ModuleType::en_etyModuleType en_etyModuleType );
					const		bool																				create_WeaponModule				( const std::string& c_stdStringModuleID, const sf::Vector2f& c_sfVectorPosition, const sf::Vector2i& c_sfVectorClassRange, const ety::ModuleType::en_etyModuleType en_etyModuleType );

		virtual					void																				update_Component				( const sf::Uint32& uiFrameTime );

		virtual					void																				render_Component				( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		static					void																				register_ClassToLuabind			( ety::CLua* const p_c_etyLuaScript );	

					const		bool																				set_EquipmentItemToModule		( ety::CItem* const p_c_etyItem );
					const		bool																				set_WeaponItemToModule			( const std::string& c_stdStringModuleID, ety::CItem* const p_c_etyItem );
								
								ety::CItem*													const					get_EquipmentFromModule			( const ety::ModuleType::en_etyModuleType en_etyModuleType );
								ety::CItem*													const					get_WeaponFromModule			( const std::string& c_stdStringModuleID );

					const		std::string																			get_FamilyID					( void );
		virtual		const		std::string																			get_ComponentID					( void );
	};
}

