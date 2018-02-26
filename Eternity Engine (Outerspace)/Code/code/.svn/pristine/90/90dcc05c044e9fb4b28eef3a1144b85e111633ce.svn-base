#pragma once

#include <map>
#include <vector>

#include <boost\shared_ptr.hpp>
#include <boost\weak_ptr.hpp>

#include "CEntity.hpp"

namespace ety
{
	typedef std::map< std::string, boost::shared_ptr<ety::CEntity> >::iterator itEntityByUniqueIDTDef;

	class CEntitymanager
	{
	private:
					std::map< std::string, boost::shared_ptr<ety::CEntity> >		m_c_stdMapEntityByUniqueID;

	protected:

	public: 
																					CEntitymanager				( void );
																					~CEntitymanager				( void );

			const	bool															add_Entity					( boost::shared_ptr<ety::CEntity> p_c_etyNewEntity );

					boost::weak_ptr<ety::CEntity>									create_Entity				( const std::string& c_stdStringUniqueID );

			const	bool															remove_Entity				( const std::string& c_stdStringUniqueID );

			static	void															register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript );

					void															clear_Entities				( void );

					ety::CEntity*			const									get_Entity					( const std::string& c_stdStringUniqueID );

					std::vector< boost::weak_ptr<ety::CEntity> >					get_Entities				( const std::string& c_stdStringComponentFamilyID );
	};
}

