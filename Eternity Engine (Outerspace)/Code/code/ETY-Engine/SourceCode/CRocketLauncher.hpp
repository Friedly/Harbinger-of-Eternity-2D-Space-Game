#pragma once

#include "CWeapon.hpp"

namespace ety
{
	class CRocketLauncher :	public CWeapon
	{
	private:

				float				m_fExplosionRadius;
				float				m_fMaxDamageRadius;
				float				m_fMinimalDamage;

				unsigned int		m_uiClipSize;

	public:
									CRocketLauncher				( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
									~CRocketLauncher			( void );

virtual			void				update_Item					( const sf::Uint32& uiFrameTime );

		//Set-Methoden
				void				set_ExplosionRadius			( const float fExplosionRadius );
				void				set_MaxDamageRadius			( const float fMaxDamageRadius );
				void				set_MinimalDamage			( const float fMinimalDamage );
				void				set_ClipSize				( const unsigned int uiClipSize );

		//Get-Methoden
		const	float&				get_ExplosionRadius			( void );
		const	float&				get_MaxDamageRadius			( void );
		const	float&				get_MinimalDamage			( void );
		const	unsigned int&		get_ClipSize				( void );
		const	std::string			get_SpecificInformation		( void );
	};
}


