#include "CTrigger.hpp"
#include "CTriggerEvent.hpp"
#include "CUnitEvent.hpp"
#include "CTimeEvent.hpp"
#include "CLua.hpp"
#include "CWorld.hpp"
#include "CEntity.hpp"


									ety::CTrigger::CTrigger						( void )
									:m_bActive									( false )
									,mp_c_etyEntityTriggeringUnit				( NULL )
									,mp_c_etyTriggerEventTriggeringEvent		( NULL )
{
}


									ety::CTrigger::~CTrigger					( void )
{
}

									ety::CTrigger::CTrigger						( std::string strTriggerID )
									:m_strTriggerID								( strTriggerID )
									,m_bActive									( false )
									,mp_c_etyEntityTriggeringUnit				( NULL )
									,mp_c_etyTriggerEventTriggeringEvent		( NULL )
									
{
}
									ety::CTrigger::CTrigger						( std::string strTriggerID, bool bActive )
									:m_strTriggerID								( strTriggerID )
									,m_bActive									( bActive )
									,mp_c_etyEntityTriggeringUnit				( NULL )
									,mp_c_etyTriggerEventTriggeringEvent		( NULL )
{
}



void								ety::CTrigger::add_TriggerEvent				( CTriggerEvent* p_c_etyTriggerEvent )
{
	m_vectorTriggerEvents.push_back(p_c_etyTriggerEvent);
}

void								ety::CTrigger::add_UnitEvent				( enum UnitEventType::en_etyUnitEventType en_etyUnitEventType, std::string strEntityID, bool bActive )
{
	CUnitEvent* p_c_etyUnitEventTmp = new CUnitEvent(en_etyUnitEventType, strEntityID, bActive, this);

	m_vectorTriggerEvents.push_back(p_c_etyUnitEventTmp);
}
void								ety::CTrigger::add_TimeEvent				( enum TimeEventType::en_etyTimeEventType en_etyTimeEventType, float fTime, bool bActive )
{
	CTimeEvent* p_c_etyTimeEventTmp = new CTimeEvent(en_etyTimeEventType, fTime, bActive, this);

	m_vectorTriggerEvents.push_back(p_c_etyTimeEventTmp);
}

void								ety::CTrigger::update_Trigger				( const sf::Uint32& uiFrameTime )
{
	std::vector<CTriggerEvent*>::iterator itEvents = m_vectorTriggerEvents.begin();

	for(itEvents ; itEvents != m_vectorTriggerEvents.end() ; itEvents++)
	{
		mp_c_etyTriggerEventTriggeringEvent	=	NULL;
		mp_c_etyEntityTriggeringUnit		=	NULL;

		if((*itEvents)->get_Active() == true)
		{
			if((*itEvents)->update_Event(uiFrameTime) == true)
			{
				mp_c_etyTriggerEventTriggeringEvent	=	(*itEvents);

				if((*itEvents)->get_TriggerEventType() == TriggerEventType::enUNITEVENT)
				{
					mp_c_etyEntityTriggeringUnit	=	static_cast<CUnitEvent*>((*itEvents))->get_TriggeringUnit();
				}

				//Trigger ausf�hren
				CLua c_etyLuaScript;
				c_etyLuaScript.init_Lua();

				ety::CWorld::register_ClassToLuabind( &c_etyLuaScript );
				luabind::globals( c_etyLuaScript.get_LuaState() )["c_etyTrigger"]		= this;
				luabind::globals( c_etyLuaScript.get_LuaState() )["c_etyWorld"]			= gp_c_etyWorld;
				luabind::globals( c_etyLuaScript.get_LuaState() )["c_etyEntitymanager"]	= gp_c_etyWorld->get_Entitymanager();

				c_etyLuaScript.start_Script( "Scripts/Trigger/" + m_strTriggerID + ".lua" );
				c_etyLuaScript.call_Function( "Conditions", 0, 1 );		
				c_etyLuaScript.close_Lua();	
			}
		}
	}

	mp_c_etyTriggerEventTriggeringEvent	=	NULL;
	mp_c_etyEntityTriggeringUnit		=	NULL;
}

void								ety::CTrigger::register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript )
{
	luabind::module( p_c_etyLuaScript->get_LuaState() )
	[ 
		luabind::class_<ety::CTrigger>("CTrigger")
		.def( luabind::constructor< std::string >() )
		.def( "add_UnitEvent"				, &CTrigger::add_UnitEvent					)		
		.def( "add_TimeEvent"				, &CTrigger::add_TimeEvent					)
		.def( "get_TriggerID"				, &CTrigger::get_TriggerID					)
		.def( "get_Active"					, &CTrigger::get_Active						)
		.def( "get_TriggerID"				, &CTrigger::get_TriggerID					)
		.def( "get_TriggeringUnit"			, &CTrigger::get_TriggeringUnit				)
		.def( "get_TriggeringEvent"			, &CTrigger::get_TriggeringEvent			)
	];
}

const bool&							ety::CTrigger::get_Active					( void )
{
	return m_bActive;
}
const std::string&					ety::CTrigger::get_TriggerID				( void )
{
	return m_strTriggerID;
}
std::vector<ety::CTriggerEvent*>&	ety::CTrigger::get_TriggerEvents			( void )
{
	return m_vectorTriggerEvents;
}
ety::CEntity*	const				ety::CTrigger::get_TriggeringUnit			( void )
{
	return mp_c_etyEntityTriggeringUnit;
}
ety::CTriggerEvent*	const			ety::CTrigger::get_TriggeringEvent			( void )
{
	return mp_c_etyTriggerEventTriggeringEvent;
}