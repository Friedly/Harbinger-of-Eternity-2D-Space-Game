#include "CRocketLauncher.hpp"


							ety::CRocketLauncher::CRocketLauncher							( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
								:CWeapon( strDirectory, strItemname, p_c_etyCurrentRessourceManager)
							{
								m_en_etyModuleType = ety::ModuleType::enROCKETLAUNCHER;
							}
							ety::CRocketLauncher::~CRocketLauncher							( void )
							{
							}

		void				ety::CRocketLauncher::update_Item								( const sf::Uint32& uiFrameTime )
		{
		}

//Get-Methoden
const	float&				ety::CRocketLauncher::get_ExplosionRadius						( void )
{
	return m_fExplosionRadius;
}
const	float&				ety::CRocketLauncher::get_MaxDamageRadius						( void )
{
	return m_fMaxDamageRadius;
}
const	float&				ety::CRocketLauncher::get_MinimalDamage							( void )
{
	return m_fMinimalDamage;
}
const	unsigned int&		ety::CRocketLauncher::get_ClipSize								( void )
{
	return m_uiClipSize;
}
const	std::string			ety::CRocketLauncher::get_SpecificInformation					( void )
{
	std::stringstream ssStream;
	//String noch ändern
	std::string strInformation = m_strName + "\n\n\nKlasse: ";
	/*ssStream << m_uiClass;
	strInformation += ssStream.str() + "\n\nMasse: ";
	ssStream.str("");
	ssStream << m_fMass;
	strInformation += ssStream.str() + " ME\n\nPrice: ";
	ssStream.str("");
	ssStream << m_fPrice;
	strInformation += ssStream.str() + "$\n\nTotal Armor: ";
	ssStream.str("");
	ssStream << m_fTotalArmor;
	strInformation += ssStream.str() + "\n\nDmgRedctn.: ";
	ssStream.str("");
	ssStream << m_fDamageReductionPerShot;
	strInformation += ssStream.str();
	ssStream.str("");*/

	return strInformation;
}

