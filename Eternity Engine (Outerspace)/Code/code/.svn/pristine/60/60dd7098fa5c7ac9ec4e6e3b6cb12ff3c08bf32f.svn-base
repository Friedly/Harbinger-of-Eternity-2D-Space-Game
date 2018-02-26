#pragma once

#include <string>
#include <map>

#include "CLua.hpp"

#include <boost\shared_ptr.hpp>
#include <boost\weak_ptr.hpp>

namespace ety
{
	class CComponent;

	class CEntity
	{
	public:
	private:
				std::map< std::string, boost::shared_ptr<CComponent> >		m_c_stdMapComponentByFamilyID;

				std::string													m_c_stdStringUniqueID;
	protected:
	public:
																			CEntity						( const std::string& c_stdStringUniqueID );
																			~CEntity					( void );

		const	bool														add_Component				( CComponent* const p_c_etyComponent );

		const	bool														remove_Component			( const std::string& c_stdStringFamilyID );

				void														clear_Components			( void );

		const	bool														has_Component				( const std::string& c_stdStringFamilyID );

		static	void														register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript );

				template< class T >
				T*										const				get_Component				( const std::string& c_stdStringFamilyID )
			{
				if( m_c_stdMapComponentByFamilyID.find( c_stdStringFamilyID ) != m_c_stdMapComponentByFamilyID.end() )
				{
					return static_cast< T* >( m_c_stdMapComponentByFamilyID[ c_stdStringFamilyID ].get() );
				}

				return NULL;
			}
		const	std::string&												get_UniqueID				( void );
	};
}

