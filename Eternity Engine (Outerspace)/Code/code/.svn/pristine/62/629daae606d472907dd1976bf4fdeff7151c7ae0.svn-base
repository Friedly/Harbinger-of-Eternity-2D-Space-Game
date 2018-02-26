#pragma once
#include <map>
#include <vector>
#include <string>
#include <SFML\System\Time.hpp>

namespace ety
{
	namespace TriggerEventType
	{
		enum en_etyTriggerEventType		{enTIMEEVENT, enUNITEVENT};
	}

	class CTrigger;

	class CTriggerEvent
	{
	private:

	protected:
				bool												m_bActive;
		enum	TriggerEventType::en_etyTriggerEventType			m_en_etyTriggerEventType;
				CTrigger*											mp_c_etyTriggerParent;


	public:		
																	CTriggerEvent				( void );
																	~CTriggerEvent				( void );


		virtual	bool												update_Event				( const sf::Uint32& uiFrameTime ) = 0;


				void												set_Active					( bool bActive );
			
		const	bool&												get_Active					( void );
		const	enum	TriggerEventType::en_etyTriggerEventType&	get_TriggerEventType		( void );
	};
}
