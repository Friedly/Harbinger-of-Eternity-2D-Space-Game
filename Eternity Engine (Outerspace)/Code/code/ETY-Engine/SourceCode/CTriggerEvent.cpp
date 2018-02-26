#include "CTriggerEvent.hpp"


																ety::CTriggerEvent::CTriggerEvent			( void )
{
}


																ety::CTriggerEvent::~CTriggerEvent			( void )
{
}


		void													ety::CTriggerEvent::set_Active				( bool bActive )
{
	m_bActive	=	bActive;
}
			
const	bool&													ety::CTriggerEvent::get_Active				( void )
{
	return m_bActive;
}
const	enum	ety::TriggerEventType::en_etyTriggerEventType&	ety::CTriggerEvent::get_TriggerEventType	( void )
{
	return m_en_etyTriggerEventType;
}
