#include "CGenerator.hpp"
#include "CIniFile.hpp"


						ety::CGenerator::CGenerator							( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
							: CItem( strDirectory, strItemname, p_c_etyCurrentRessourceManager )
						{
							m_en_etyModuleType = ety::ModuleType::enGENERATOR;

							ety::CIniFile c_etyFile;
							c_etyFile.set_IniFileDirectory( strDirectory );

							m_fRechargedEnergyPerSecond		= c_etyFile.read_Float		( strItemname, "fRechargedEnergyPerSecond"	, 0.f );
							m_fEnergyCapacity				= c_etyFile.read_Float		( strItemname, "fEnergyCapacity"			, 0.f );
							m_fCurrentEnergy				= m_fEnergyCapacity;
						}
						ety::CGenerator::~CGenerator						( void )
						{
						}

		void			ety::CGenerator::update_Item						( const sf::Uint32& uiFrameTime )
		{
		}

//Get-Methoden
void					ety::CGenerator::set_CurrentEnergy					( const float& fCurrentEnergy )
{
	m_fCurrentEnergy			=	fCurrentEnergy;
}
void					ety::CGenerator::set_EnergyCapacity					( const float& fEnergyCapacity )
{
	m_fEnergyCapacity			=	fEnergyCapacity;
}
void					ety::CGenerator::set_RechargedEnergyPerSecond		( const float& fRechargedEnergyPerSecond )
{
	m_fRechargedEnergyPerSecond	=	fRechargedEnergyPerSecond;
}

//Get-Methoden
const	float&			ety::CGenerator::get_CurrentEnergy					( void )
{
	return m_fCurrentEnergy;
}
const	float&			ety::CGenerator::get_EnergyCapacity					( void )
{
	return m_fEnergyCapacity;
}
const	float&			ety::CGenerator::get_RechargedEnergyPerSecond		( void )
{
	return m_fRechargedEnergyPerSecond;
}
const	std::string		ety::CGenerator::get_SpecificInformation			( void )
{
	std::stringstream ssStream;
	//String noch �ndern
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