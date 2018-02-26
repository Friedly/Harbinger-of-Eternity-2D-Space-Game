#include "CAmmunitionDump.hpp"


							ety::CAmmunitionDump::CAmmunitionDump			( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
								: CItem( strDirectory, strItemname, p_c_etyCurrentRessourceManager )
							{
								m_en_etyModuleType = ety::ModuleType::enAMMUNITIONDUMP;
							}
							ety::CAmmunitionDump::~CAmmunitionDump			( void )
							{
							}

		void				ety::CAmmunitionDump::update_Item				( const sf::Uint32& uiFrameTime )
		{
		}

//Set-Methoden
		void				ety::CAmmunitionDump::set_AmmoCapacity			( const unsigned int uiAmmoCapacity )
		{
			m_uiAmmoCapacity	=	uiAmmoCapacity;
		}
		void				ety::CAmmunitionDump::set_CurrentAmmo			( const unsigned int uiCurrentAmmo )
		{
			m_uiCurrentAmmo		=	uiCurrentAmmo;
		}

//Get-Methoden
const	unsigned int&		ety::CAmmunitionDump::get_AmmoCapacity			( void )
{
	return m_uiAmmoCapacity;
}
const	unsigned int&		ety::CAmmunitionDump::get_CurrentAmmo			( void )
{
	return m_uiCurrentAmmo;
}
const   std::string			ety::CAmmunitionDump::get_SpecificInformation	( void )
{
	std::stringstream ssStream;
	//String noch ändern
	std::string strInformation = m_strName + "\n\n\nKlasse: ";
	ssStream << m_uiClass;
	strInformation += ssStream.str() + "\n\nMasse: ";
	ssStream.str("");
	ssStream << m_fMass;
	strInformation += ssStream.str() + " ME\n\nPrice: ";
	ssStream.str("");
	ssStream << m_fPrice;
	strInformation += ssStream.str() + "$\n\nAmmoCpcty: ";
	ssStream.str("");
	ssStream << m_uiAmmoCapacity;
	strInformation += ssStream.str();

	return strInformation;
}
