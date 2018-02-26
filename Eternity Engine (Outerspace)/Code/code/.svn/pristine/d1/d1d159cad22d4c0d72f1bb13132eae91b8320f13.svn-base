#pragma once
#include <string>
#include <vector>
#include <SFML\System\Time.hpp>

#include "CLua.hpp"

namespace ety
{
	namespace TimeEventType
	{
		enum	en_etyTimeEventType {enELAPSEDTIME, enPERIODIC};
	}

	namespace UnitEventType
	{
		enum en_etyUnitEventType {enDIES, enTAKEDAMAGE, enISATTACKED, enATTACKS, enNOTICESENEMYINRANGE, enATTRIBUTE, enENTERSREGION, enLEAVESREGION, enWITHINRANGE, enNOTHING};
	}

	class CTriggerEvent;
	class CEntity;

	class CTrigger
	{
	private:

	protected:

		bool							m_bActive;
		std::string						m_strTriggerID;
		std::vector<CTriggerEvent*>		m_vectorTriggerEvents;
		ety::CEntity*					mp_c_etyEntityTriggeringUnit;
		ety::CTriggerEvent*				mp_c_etyTriggerEventTriggeringEvent;

	public:

										CTrigger					( void );
										~CTrigger					( void );

										CTrigger					( std::string strTriggerID );
										CTrigger					( std::string strTriggerID, bool bActive );

		void							add_TriggerEvent			( CTriggerEvent* p_c_etyTriggerEvent );
		void							add_UnitEvent				( enum UnitEventType::en_etyUnitEventType en_etyUnitEventType, std::string strEntityID, bool bActive );
		void							add_TimeEvent				( enum TimeEventType::en_etyTimeEventType en_etyTimeEventType, float fTime, bool bActive );

		void							update_Trigger				( const sf::Uint32& uiFrameTime );

		static	void					register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript );

		const bool&						get_Active					( void );
		const std::string&				get_TriggerID				( void );
		std::vector<CTriggerEvent*>&	get_TriggerEvents			( void );
		ety::CEntity*		const		get_TriggeringUnit			( void );
		ety::CTriggerEvent*	const		get_TriggeringEvent			( void );
	};
}
