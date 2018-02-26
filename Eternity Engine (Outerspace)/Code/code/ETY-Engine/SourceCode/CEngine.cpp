#include "CEngine.hpp"
#include "CIniFile.hpp"


							ety::CEngine::CEngine						( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
							: CItem										( strDirectory, strItemname, p_c_etyCurrentRessourceManager )
							{
								m_en_etyModuleType = ety::ModuleType::enENGINE;

								ety::CIniFile c_etyFile;

								c_etyFile.set_IniFileDirectory( strDirectory );

								m_fThrust				= c_etyFile.read_Float( strItemname, "fThrust"			, 0.f	);
								m_fMaximalVelocity		= c_etyFile.read_Float( strItemname, "fMaximalVelocity"	, 0.f	);
								m_fEnergyPerSecond		= c_etyFile.read_Float( strItemname, "fEnergyPerSecond"	, 0.f	);
							}
							ety::CEngine::~CEngine						( void )
							{
							}

		void				ety::CEngine::update_Item					( const sf::Uint32& uiFrameTime )
{
}

//Set-Methoden
		void				ety::CEngine::set_Thrust					( const float& fThrust )
{
	m_fThrust			=	fThrust;
}
		void				ety::CEngine::set_MaximalVelocity			( const float& fMaximalVelocity )
{
	m_fMaximalVelocity	=	fMaximalVelocity;
}
		void				ety::CEngine::set_EnergyPerSecond			( const float& fEnergyPerSecond )
{
	m_fEnergyPerSecond	=	fEnergyPerSecond;
}

//Get-Methoden
const	float&				ety::CEngine::get_Thrust					( void )
{
	return m_fThrust;
}
const	float&				ety::CEngine::get_MaximalVelocity			( void )
{
	return m_fMaximalVelocity;
}
const	float&				ety::CEngine::get_EnergyPerSecond			( void )
{
	return m_fEnergyPerSecond;
}
const	std::string			ety::CEngine::get_SpecificInformation		( void )
{
	std::stringstream ssStream;
	//String noch �ndern
	std::string strInformation = m_strName + "\n\n\nKlasse: ";
	ssStream << m_uiClass;
	strInformation += ssStream.str() + "\n\nMasse: ";
	ssStream.str("");
	ssStream << m_fMass;
	strInformation += ssStream.str() + " ME\n\nPrice: ";
	ssStream.str("");
	ssStream << m_fPrice;
	strInformation += ssStream.str() + "$\n\nSchub: ";
	ssStream.str("");
	ssStream << m_fThrust;
	strInformation += ssStream.str() + "\n\nMaxGeschw.: ";
	ssStream.str("");
	ssStream << m_fMaximalVelocity;
	strInformation += ssStream.str();
	ssStream.str("");

	return strInformation;
}

