#pragma once
#include "CItem.hpp"

namespace ety
{
	class CEngine : public CItem
	{
	private:
					
					float				m_fThrust;
					float				m_fMaximalVelocity;
					float				m_fEnergyPerSecond;
					sf::Uint32			m_sfUint32PastFrameTime;

	public:
										CEngine								( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
										~CEngine							( void );

	virtual			void				update_Item							( const sf::Uint32& uiFrameTime );

		//Set-Methoden
					void				set_Thrust							( const float& fThrust );
					void				set_MaximalVelocity					( const float& fMaximalVelocity );
					void				set_EnergyPerSecond					( const float& fEnergyPerSecond );

		//Get-Methoden
			const	float&				get_Thrust							( void );
			const	float&				get_MaximalVelocity					( void );
			const	float&				get_EnergyPerSecond					( void );
			const	std::string			get_SpecificInformation				( void );
	};
}


