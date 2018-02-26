#include "CEntitymanager.hpp"

															ety::CEntitymanager::CEntitymanager				( void )
															{
															}
															ety::CEntitymanager::~CEntitymanager			( void )
															{
																clear_Entities();
															}

const	bool												ety::CEntitymanager::add_Entity					( boost::shared_ptr<ety::CEntity> p_c_etyNewEntity )
		{
			itEntityByUniqueIDTDef itEntityByUniqueID = m_c_stdMapEntityByUniqueID.find( p_c_etyNewEntity->get_UniqueID() );

			if( itEntityByUniqueID != m_c_stdMapEntityByUniqueID.end() )
			{
				return false;
			}

			m_c_stdMapEntityByUniqueID[ p_c_etyNewEntity->get_UniqueID() ] = p_c_etyNewEntity;

			return true;
		}

		boost::weak_ptr<ety::CEntity>						ety::CEntitymanager::create_Entity				( const std::string& c_stdStringUniqueID )
		{
			itEntityByUniqueIDTDef itEntityByUniqueID = m_c_stdMapEntityByUniqueID.find( c_stdStringUniqueID );

			if( itEntityByUniqueID != m_c_stdMapEntityByUniqueID.end() )
			{
				return boost::weak_ptr<ety::CEntity>();
			}

			m_c_stdMapEntityByUniqueID[ c_stdStringUniqueID ] = boost::shared_ptr<ety::CEntity>( new ety::CEntity( c_stdStringUniqueID ) );

			return m_c_stdMapEntityByUniqueID[ c_stdStringUniqueID ];
		}

const	bool												ety::CEntitymanager::remove_Entity				( const std::string& c_stdStringUniqueID )
		{
			itEntityByUniqueIDTDef itEntityByUniqueID = m_c_stdMapEntityByUniqueID.find( c_stdStringUniqueID );

			if( itEntityByUniqueID != m_c_stdMapEntityByUniqueID.end() )
			{
				m_c_stdMapEntityByUniqueID.erase( itEntityByUniqueID );

				return true;
			}

			return false;
		}

		void												ety::CEntitymanager::register_ClassToLuabind	( ety::CLua* const p_c_etyLuaScript )
		{
			ety::CEntity::register_ClassToLuabind( p_c_etyLuaScript );

			luabind::module( p_c_etyLuaScript->get_LuaState() )
			[ 
				luabind::class_<ety::CEntitymanager>("CEntitymanager")
				.def( "get_Entity"		, &CEntitymanager::get_Entity	 )
				.def( "remove_Entity"	, &CEntitymanager::remove_Entity )
			];
		}

		void												ety::CEntitymanager::clear_Entities				( void )
		{
			m_c_stdMapEntityByUniqueID.clear();
		}

		ety::CEntity*			const						ety::CEntitymanager::get_Entity					( const std::string& c_stdStringUniqueID )
		{
			itEntityByUniqueIDTDef itEntityByUniqueID = m_c_stdMapEntityByUniqueID.find( c_stdStringUniqueID );

			if( itEntityByUniqueID != m_c_stdMapEntityByUniqueID.end() )
			{
				return m_c_stdMapEntityByUniqueID[ c_stdStringUniqueID ].get();
			}

			return NULL;
		}

		std::vector< boost::weak_ptr<ety::CEntity> >		ety::CEntitymanager::get_Entities				( const std::string& c_stdStringComponentFamilyID )
		{
			std::vector< boost::weak_ptr<ety::CEntity> > c_stdVectorEntities;

			itEntityByUniqueIDTDef itEntityByUniqueID = m_c_stdMapEntityByUniqueID.begin();

			for( itEntityByUniqueID; itEntityByUniqueID != m_c_stdMapEntityByUniqueID.end(); itEntityByUniqueID++ )
			{
				if( c_stdStringComponentFamilyID == "ALL" || itEntityByUniqueID->second->has_Component( c_stdStringComponentFamilyID ) == true )
				{
					c_stdVectorEntities.push_back( itEntityByUniqueID->second );
				}
			}

			return c_stdVectorEntities;
		}