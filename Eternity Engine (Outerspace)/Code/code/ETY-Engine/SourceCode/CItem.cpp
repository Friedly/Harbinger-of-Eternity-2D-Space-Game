#include "CItem.hpp"
#include "CModule.hpp"
#include "CIniFile.hpp"

#include <SFML\Graphics\RenderTexture.hpp>


																ety::CItem::CItem								( const std::string& strDirectory, const std::string& strItemname, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
																	: mp_c_etyModuleParent						( NULL )
																{
																	ety::CIniFile c_etyFile;

																	c_etyFile.set_IniFileDirectory( strDirectory );

																	m_strName					= strItemname;

																	m_fMass						= c_etyFile.read_Float		( strItemname, "fMass"				, 0.f		);
																	m_fPrice					= c_etyFile.read_Float		( strItemname, "fPrice"			, 0.f		);

																	m_uiClass					= c_etyFile.read_Integer	( strItemname, "uiClass"			, 0			);
	
																	m_strInformation			= c_etyFile.read_String		( strItemname, "strInformation"	, "????"	);

																	m_c_sfSpriteAppearance		.setTexture	( p_c_etyCurrentRessourceManager->get_Texture( c_etyFile.read_String( strItemname, "sfTextureAppearance"	, "????") ) );
																	
																	m_c_sfSpriteAppearance		.setOrigin	( m_c_sfSpriteAppearance.getTextureRect().width/2.f, m_c_sfSpriteAppearance.getTextureRect().height/2.f );
																	
																	m_c_sfSpriteAppearance		.scale		( 0.6f, 0.6f );

																	m_c_sfSpriteIcon			.setTexture( p_c_etyCurrentRessourceManager->get_Texture( c_etyFile.read_String( strItemname, "sfTextureIcon"		, "????") ) );
																}
																ety::CItem::~CItem								( void )
																{
																}

void															ety::CItem::render_Item							( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
{
	p_c_sfRenderTextureGameScene->draw( m_c_sfSpriteAppearance );
}

//Set-Methoden
void															ety::CItem::set_Mass							( const float fMass )
{
	m_fMass	= fMass;
}	
void															ety::CItem::set_Price							( const float fPrice )
{	
	m_fPrice = fPrice;
}		
void															ety::CItem::set_ParentModule					( CModule* const p_c_etyModuleParent )
{
	mp_c_etyModuleParent = p_c_etyModuleParent;
}
void															ety::CItem::set_Appearance						( const sf::Texture& c_sfTextureAppearance )
{
	m_c_sfSpriteAppearance.setTexture( c_sfTextureAppearance );
}
void															ety::CItem::set_Icon							( const sf::Texture& c_sfTextureIcon )
{
	m_c_sfSpriteAppearance.setTexture( c_sfTextureIcon );
}

//Get-Methoden
const float														ety::CItem::get_Mass							( void )
{
	return m_fMass;
}
const float														ety::CItem::get_Price							( void )
{
	return m_fPrice;
}
const unsigned int												ety::CItem::get_Class							( void )
{
	return m_uiClass;
}	
const sf::Sprite&												ety::CItem::get_Appearance						( void )
{
	return m_c_sfSpriteAppearance;
}
const sf::Sprite&												ety::CItem::get_Icon							( void )
{
	return m_c_sfSpriteIcon;
}
const ety::ModuleType::en_etyModuleType							ety::CItem::get_ItemType						( void )
{
	return m_en_etyModuleType;
}
const std::string&												ety::CItem::get_Name							( void )
{
	return m_strName;
}
const std::string&												ety::CItem::get_Information						( void )
{
	return m_strInformation;
}
const std::string												ety::CItem::get_SpecificInformation				( void )
{
	//Diese Funktion muss von jeder Item-Klasse selbst ausgefüllt werden!
	return "MOIN!";
}
