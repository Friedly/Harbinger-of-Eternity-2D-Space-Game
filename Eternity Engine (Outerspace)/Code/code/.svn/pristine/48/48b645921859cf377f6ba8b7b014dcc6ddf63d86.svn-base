#pragma once
#include "CTrigger.hpp"
#include "CTriggerEvent.hpp"


namespace ety
{
	class CTimeEvent :	public CTriggerEvent
	{
	private:

	protected:

		float												m_fTime;
		float												m_fTimeBuffer;
		enum TimeEventType::en_etyTimeEventType				m_en_etyTimeEventType;

	public:
															CTimeEvent			(void);
															~CTimeEvent			(void);

															CTimeEvent			(enum TimeEventType::en_etyTimeEventType en_etyTimeEventType, float fTime, bool bActive, 
																				CTrigger* p_c_etyTriggerParent);


		virtual	bool										update_Event		( const sf::Uint32& uiFrameTime );


		const	float&										get_Time			(void);
		const	enum TimeEventType::en_etyTimeEventType		get_TimeEventType	(void);
	};
}
