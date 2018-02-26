#include "CShop.hpp"
#include "CDialogitem.hpp"
#include "CDialog.hpp"
#include "CSpaceStationHangarState.hpp"
#include "CGameStateManager.hpp"
#include "CWorld.hpp"
#include "CGamesettings.hpp"
#include "CSlideControl.hpp"
#include "CLabel.hpp"
#include "CButton.hpp"

									ety::CShop::CShop						(void)
									:mp_c_etySpaceStationHangarState		(NULL)
									,mp_c_etyEntityPlayer					(NULL)
{
}
									ety::CShop::~CShop						(void)
{
}

									ety::CShop::CShop						( CSpaceStationHangarState* const p_c_etySpaceStationHangarState )
									:mp_c_etySpaceStationHangarState		( p_c_etySpaceStationHangarState )
{
	mp_c_etyEntityPlayer =	gp_c_etyWorld->get_Entitymanager()->get_Entity("Player");
}


void								ety::CShop::add_Dialog					( CDialog* const p_c_etyDialog )
{
	m_mapDialogs[p_c_etyDialog->get_DialogID()]	=	p_c_etyDialog;
}

void								ety::CShop::init_Shop					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, 
																			  ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{	
	sf::VideoMode	c_sfCurrentVideomode	=	p_c_etyCurrentGamesettingManager	->get_Videomode();
	sf::Font		c_sfCurrentFont			=	p_c_etyCurrentRessourceManager		->get_Font("Standard.ttf");
	CDialogManager* p_c_etyDialogManager	=	mp_c_etySpaceStationHangarState		->get_DialogManager();

	CLua* const		p_c_etyLuaScript		=	mp_c_etySpaceStationHangarState		->get_GameStatemanager()->get_LuaScript();
	std::string		strLanguage				=	p_c_etyCurrentGamesettingManager	->get_Language();
	
	p_c_etyLuaScript->init_Lua();
	p_c_etyLuaScript->start_Script("Initialisation/Gamestates/Language.lua");

	enum EventType::en_etyEventType en_etyEventType = EventType::enNONE;
	std::map<enum EventType::en_etyEventType, p_Function> mapEventTypeFunction;

	const sf::Texture& c_sfTextureButtonSet	=	p_c_etyCurrentRessourceManager->get_Texture( "ShopButtonSet.png" );
	
	////////////////////////////////////////////*ShopBackground ANFANG*////////////////////////////////////////////
	ety::CDialog* p_c_etyDialogShopBackground = new CDialog(	
		"ShopBackground", p_c_etyCurrentRessourceManager->get_Texture( "ShopBackground.png" ), 1680, 1050, sf::Vector2f( 0.f, 0.f ), 
		sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1680, 1050)), p_c_etyDialogManager, c_sfCurrentVideomode
		);

	p_c_etyDialogShopBackground->set_Affinity(Affinity::enFOREGROUND);
	p_c_etyDialogShopBackground->set_DrawPosition(10);
	p_c_etyDialogShopBackground->set_Visibility(false);

	m_mapDialogs["ShopBackground"]	=	p_c_etyDialogShopBackground;


	////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////
			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopRepositoryButton", c_sfTextureButtonSet, 250.f, 87.f, sf::Vector2f(1082.f, -63.f), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 250, 87 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopRepositoryButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopRepositoryButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopShopButton", c_sfTextureButtonSet, 248.f, 87.f, sf::Vector2f(1360.f, -63.f), 
				sf::IntRect(sf::Vector2i( 0, 87 ), sf::Vector2i( 248, 87 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopShopButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopShopButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopLaserButton", c_sfTextureButtonSet, 89.f, 75.f, sf::Vector2f(1068.f, -159.f), 
				sf::IntRect(sf::Vector2i( 0, 176 ), sf::Vector2i( 89, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopLaserButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopLaserButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopSpaceshipButton", c_sfTextureButtonSet, 114.f, 75.f, sf::Vector2f(1163.f, -159.f), 
				sf::IntRect(sf::Vector2i( 0, 252 ), sf::Vector2i( 114, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopSpaceshipButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopSpaceshipButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopProjectileWeaponButton", c_sfTextureButtonSet, 124.f, 75.f, sf::Vector2f(1283.f, -159.f), 
				sf::IntRect(sf::Vector2i( 0, 328 ), sf::Vector2i( 124, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopProjectileWeaponButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopProjectileWeaponButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopRocketLauncherButton", c_sfTextureButtonSet, 114.f, 75.f, sf::Vector2f(1413.f, -159.f), 
				sf::IntRect(sf::Vector2i( 0, 404 ), sf::Vector2i( 114, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopRocketLauncherButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopRocketLauncherButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopShieldButton", c_sfTextureButtonSet, 88.f, 75.f, sf::Vector2f(1534.f, -159.f), 
				sf::IntRect(sf::Vector2i( 0, 480 ), sf::Vector2i( 88, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopShieldButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopShieldButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopGeneratorButton", c_sfTextureButtonSet, 134.f, 75.f, sf::Vector2f(1068.f, -240.f), 
				sf::IntRect(sf::Vector2i( 0, 556 ), sf::Vector2i( 134, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopGeneratorButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopGeneratorButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopAmmunitionButton", c_sfTextureButtonSet, 133.f, 75.f, sf::Vector2f(1209.f, -240.f), 
				sf::IntRect(sf::Vector2i( 0, 632 ), sf::Vector2i( 133, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopAmmunitionButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopAmmunitionButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopEngineButton", c_sfTextureButtonSet, 136.f, 75.f, sf::Vector2f(1348.f, -240.f), 
				sf::IntRect(sf::Vector2i( 0, 708 ), sf::Vector2i( 136, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopEngineButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopEngineButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopArmorButton", c_sfTextureButtonSet, 131.f, 75.f, sf::Vector2f(1491.f, -240.f), 
				sf::IntRect(sf::Vector2i( 0, 784 ), sf::Vector2i( 131, 75 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopArmorButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopArmorButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			p_c_etyDialogShopBackground->createDialogitem_Button(	
				"ShopSearchButton", c_sfTextureButtonSet, 45.f, 59.f, sf::Vector2f(1587.f, -328.f), 
				sf::IntRect(sf::Vector2i( 0, 859 ), sf::Vector2i( 45, 59 ))
				);

			p_c_etyDialogShopBackground->get_DialogitemByCustomID<ety::CButton*>( "ShopSearchButton" )
					->create_Tooltip(p_c_etyLuaScript->get_TableString( "ShopSearchButtonTooltip", strLanguage ), 14.f, ety::Color(255.f,255.f,255.f));

			
	////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////
	////////////////////////////////////////////*ShopBackground ENDE*////////////////////////////////////////////
}

void								ety::CShop::show_ButtonTooltip			( std::string strButtonID )
{
	/*ety::CLua* const p_c_luaLuaScript = mp_c_etySpaceStationHangarState->get_DialogManager()->get_LuaScript();
	CLabel* p_c_etyLabelTooltip	=	m_mapDialogs["ShopTooltip"]->get_DialogitemByCustomID<CLabel*>("ShopTooltipLabel");

	p_c_luaLuaScript->init_Lua();
	p_c_luaLuaScript->start_Script("Initialisation/Gamestates/Language.lua");

	p_c_etyLabelTooltip->set_Content(p_c_luaLuaScript->get_TableString(strButtonID + "Tooltip",mp_c_etySpaceStationHangarState->get_DialogManager()->get_Language()));
	p_c_etyLabelTooltip->update_Dialogitem(0);

	p_c_luaLuaScript->close_Lua();

	m_mapDialogs["ShopTooltip"]->set_Width(p_c_etyLabelTooltip->get_Width(), false);
	m_mapDialogs["ShopTooltip"]->set_Height(p_c_etyLabelTooltip->get_Height(), false);

	sf::Vector2i	c_sfVector2iMousePos	=	ety::CMouse::get_Position();
	
	m_mapDialogs["ShopTooltip"]->set_Position(sf::Vector2f(c_sfVector2iMousePos.x,c_sfVector2iMousePos.y));
	m_mapDialogs["ShopTooltip"]->set_Visibility(true);*/
}

void								ety::CShop::update_Shop					( const sf::Uint32& uiFrameTime )
{
	
}

ety::CDialog*	const				ety::CShop::get_DialogByID				( std::string strDialogID )
{
	if(m_mapDialogs.find(strDialogID) != m_mapDialogs.end())
	{
		return	m_mapDialogs[strDialogID];
	}
	
	return NULL;
}
