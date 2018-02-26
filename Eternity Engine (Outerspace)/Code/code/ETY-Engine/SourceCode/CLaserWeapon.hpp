
#include "CWeapon.hpp"

namespace ety
{
	class CLaserWeapon : public CWeapon
	{
	private:
		
						float				m_fEnergyPerShot;
						float				m_fOverHeatingPerShot;
						float				m_fTotalOverHeating;
						float				m_fCooldownPerSecond;


	public:
											CLaserWeapon						( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
											~CLaserWeapon						( void );

		virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

				//Set-Methoden
						void				set_EnergyPerShot					( const float fEnergyPerShot );
						void				set_OverHeatingPerShot				( const float fOverHeatingPerShot );
						void				set_TotalOverHeating				( const float fTotalOverHeating );
						void				set_CooldownPerSecond				( const float fCooldownPerSecond );

				//Get-Methoden
				const	float&				get_EnergyPerShot					( void );
				const	float&				get_OverHeatingPerShot				( void );
				const	float&				get_TotalOverHeating				( void );
				const	float&				get_CooldownPerSecond				( void );
				const	std::string			get_SpecificInformation				( void );
	};
}
