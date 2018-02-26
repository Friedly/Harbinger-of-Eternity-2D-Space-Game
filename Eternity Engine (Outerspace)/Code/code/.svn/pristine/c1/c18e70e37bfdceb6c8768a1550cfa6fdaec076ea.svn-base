#pragma once
#include "CItem.hpp"

namespace ety
{
	class CAmmunitionDump : public CItem
	{
	private:

						unsigned int		m_uiAmmoCapacity;
						unsigned int		m_uiCurrentAmmo;

	public:
											CAmmunitionDump						( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
											~CAmmunitionDump					( void );

		virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

		//Set-Methoden
						void				set_AmmoCapacity					( const unsigned int uiAmmoCapacity );
						void				set_CurrentAmmo						( const unsigned int uiCurrentAmmo );

		//Get-Methoden
				const	unsigned int&		get_AmmoCapacity					( void );
				const	unsigned int&		get_CurrentAmmo						( void );
				const	std::string			get_SpecificInformation				( void );
	};
}


