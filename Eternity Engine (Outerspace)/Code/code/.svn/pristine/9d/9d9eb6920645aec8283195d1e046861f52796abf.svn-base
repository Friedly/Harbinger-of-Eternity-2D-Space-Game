#pragma once

#include <string>

#include "CItem.hpp"

namespace ety
{
	typedef std::map< ety::ModuleType::en_etyModuleType, std::vector<CItem*> > mapItemsByType;

	class CItemManagement
	{
	private:
		std::map<unsigned int, mapItemsByType>		m_stdMapItemTypebByClass;
		std::map<std::string, CItem*>				m_stdMapItemByName;

	public:
													CItemManagement			( void );
													~CItemManagement		( void );

		void										clear_Items				( void );

		void										load_Items				( const std::string& strDirectory, const ety::ModuleType::en_etyModuleType en_etyModuleType, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );

		CItem*					const				get_Item				( const std::string& c_stdStringItemID );
		std::vector<CItem*>*	const				get_Items				( const unsigned int uiClass , const ety::ModuleType::en_etyModuleType en_etyModuleType );
	};
}

