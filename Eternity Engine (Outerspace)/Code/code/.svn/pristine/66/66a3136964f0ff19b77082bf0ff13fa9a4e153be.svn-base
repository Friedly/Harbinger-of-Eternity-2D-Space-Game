#pragma once

#include "CItem.hpp"

namespace ety
{
	class CShield : public CItem
	{
	private:

				float				m_fEnergyReservation;
				float				m_fCooldown;
				float				m_fRechargedEnergyPerSecond;
				float				m_fCurrentAbsorbedDamage;
				float				m_fMaximalAbsorbedDamage;

	public:
									CShield								( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
									~CShield							( void );

virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

		//Set-Methoden
				void				set_EnergyReservation				( const float fEnergyReservation );
				void				set_Cooldown						( const float fCooldown );
				void				set_RechargedEnergyPerSecond		( const float fRechargedEnergyPerSecond );
				void				set_CurrentAbsorbedDamage			( const float fCurrentAbsorbedDamage );
				void				set_MaximalAbsorbedDamage			( const float fMaximalAbsorbedDamage );


		//Get-Methoden
		const	float&				get_EnergyReservation				( void );
		const	float&				get_Cooldown						( void );
		const	float&				get_RechargedEnergyPerSecond		( void );
		const	float&				get_CurrentAbsorbedDamage			( void );
		const	float&				get_MaximalAbsorbedDamage			( void );
		const	float				get_ShieldStatus					( void );
		const	std::string			get_SpecificInformation				( void );
	};
}


