#include "CSpaceStationHangarState.hpp"
#include "CGameStateManager.hpp"
#include "CSpaceStationState.hpp"
#include "CIngameState.hpp"
#include "CShop.hpp"

#include "CMouse.hpp"
#include "CButton.hpp"
#include "CComboBox.hpp"
#include "CLabel.hpp"



																ety::CSpaceStationHangarState::CSpaceStationHangarState				( const std::string& strStateName )
																: CDialogGameState													( strStateName )
																, m_bShopOpen														( false )
																{
																	mp_c_etyCShop = new CShop(this);
																}
																ety::CSpaceStationHangarState::~CSpaceStationHangarState			( void )
																{
																}

		void													ety::CSpaceStationHangarState::on_Enter								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}
		void													ety::CSpaceStationHangarState::on_Exit								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}

		void													ety::CSpaceStationHangarState::init_GameState						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			CLua* const p_c_etyLuaScript			= get_GameStatemanager()			->get_LuaScript();

			unsigned int	uiScreen_Height			= p_c_etyCurrentGamesettingManager	->get_Videomode().height;
			unsigned int	uiScreen_Width			= p_c_etyCurrentGamesettingManager	->get_Videomode().width;

			std::string		strLanguage				= p_c_etyCurrentGamesettingManager	->get_Language();

			sf::VideoMode	c_sfCurrentVideomode	= p_c_etyCurrentGamesettingManager	->get_Videomode();
			sf::Font		c_sfCurrentFont			= p_c_etyCurrentRessourceManager	->get_Font("Standard.ttf");

			mp_c_etyDialogManager->set_GamesettingsManager		( p_c_etyCurrentGamesettingManager );
			mp_c_etyDialogManager->set_StandardFont				( c_sfCurrentFont );
			mp_c_etyDialogManager->set_StandardTooltipTexture	( p_c_etyCurrentRessourceManager->get_Texture( "TooltipBackground.png" ), sf::IntRect( 0, 0, 400, 130 ));

			p_c_etyLuaScript->init_Lua();
			p_c_etyLuaScript->start_Script("Initialisation/Gamestates/Language.lua");

			enum EventType::en_etyEventType en_etyEventType = EventType::enNONE;
			std::map<enum EventType::en_etyEventType, p_Function> mapEventTypeFunction;
	
			// Multiplikator = 1.1666666 = x | 1.1666666 = y

			// Hangar 		- Size = 49x177		| Position	= 1285x386	-> Size = 55.1667x206.5		| Position = 1499.17x450.333
			// Shop/Lager	- Size = 155x134	| Position	= 1004x522	-> Size = 180.833x156.333	| Position = 1171.33x609
			// Ingame		- Size = 930x346	| Position	=			-> Size = 1085x403.667		| Position = 

			////////////////////////////////////////////////	*SHOP ANFANG*	////////////////////////////////////////////////

			m_c_etyItemManagement.load_Items( "Initialisation/Items/AmmunitionDumps.ini"		, ety::ModuleType::enAMMUNITIONDUMP		, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/Armors.ini"					, ety::ModuleType::enARMOR				, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/Engines.ini"				, ety::ModuleType::enENGINE				, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/Generators.ini"				, ety::ModuleType::enGENERATOR			, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/LaserWeapons.ini"			, ety::ModuleType::enLASERWEAPON		, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/ProjectileWeapons.ini"		, ety::ModuleType::enPROJECTILEWEAPON	, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/Rocketlauncher.ini"			, ety::ModuleType::enROCKETLAUNCHER		, p_c_etyCurrentRessourceManager );
			m_c_etyItemManagement.load_Items( "Initialisation/Items/Shields.ini"				, ety::ModuleType::enSHIELD				, p_c_etyCurrentRessourceManager );

			mp_c_etyCShop->init_Shop(p_c_etyCurrentRessourceManager, p_c_etyCurrentGamesettingManager);

			//get_GameStatemanager()->m_c_etyAttributes.add_Attribute<ety::CShop>				( "p_c_etyCurrentShop"				,&m_c_etyShop			, false	);
			//get_GameStatemanager()->m_c_etyAttributes.add_Attribute<ety::CRepository>			( "p_c_etyCurrentRepository"		,&m_c_etyRepository		, false	);
			get_GameStatemanager()->m_c_etyAttributes.add_Attribute<ety::CItemManagement>		( "p_c_etyCurrentItemManagement"	,&m_c_etyItemManagement	, false	);

			////////////////////////////////////////////////	*Shop ENDE*		////////////////////////////////////////////////

			////////////////////////////////////////////*HangarBackground ANFANG*////////////////////////////////////////////

			ety::CDialog* p_c_etyDialogSpaceStationHangarBackground = new CDialog(	
				"SpaceStationHangarBackground", p_c_etyCurrentRessourceManager->get_Texture( "HangarBackground.png" ), 1680, 1050, sf::Vector2f( 0.f, 0.f ), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1440, 900)), mp_c_etyDialogManager, c_sfCurrentVideomode
				);

			//mp_c_etyDialogManager->mp_c_sfTextureStandardTooltip = &p_c_etyCurrentRessourceManager->get_Texture( "HangarBackground.png" );
			//mp_c_etyDialogManager->mp_c_sfTextureStandardTooltip = &p_c_etyCurrentRessourceManager->get_Texture( "HangarSaalButton.png" );

			////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////

			p_c_etyDialogSpaceStationHangarBackground->createDialogitem_Button(	
				"HangarBackgroundBarButton", p_c_etyCurrentRessourceManager->get_Texture( "HangarSaalButton.png" ), 55.1667f, 206.5f, sf::Vector2f(1499.17f, -450.333f), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 49, 177 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_exitHangar;

			m_EventMap["HangarBackgroundBarButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
				
			p_c_etyDialogSpaceStationHangarBackground->createDialogitem_Button(	
				"HangarBackgroundShopButton", p_c_etyCurrentRessourceManager->get_Texture( "HangarShopButton.png" ), 180.833f, 156.333f, sf::Vector2f(1171.33f, -609.f), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 155, 134 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_openShop;

			m_EventMap["HangarBackgroundShopButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			p_c_etyDialogSpaceStationHangarBackground->createDialogitem_Button(	
				"HangarBackgroundIngameButton", p_c_etyCurrentRessourceManager->get_Texture( "HangarIngameButton.png" ), 1085.f, 403.667f, sf::Vector2f( 297.5f, 0.f ), 
				sf::IntRect(sf::Vector2i( 0,0 ),sf::Vector2i( 930, 346 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_enterIngame;

			m_EventMap["HangarBackgroundIngameButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
			////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////

			p_c_etyLuaScript->close_Lua();
			////////////////////////////////////////////*HangarBackground ENDE*////////////////////////////////////////////
		}

		void													ety::CSpaceStationHangarState::update_GameState						( const sf::Uint32& uiFrameTime )
		{
			CDialogGameState::update_GameState( uiFrameTime );
		}

		void													ety::CSpaceStationHangarState::render_GameState						( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			CDialogGameState::render_GameState( p_c_sfRenderTextureGameScene );
		}

const	ety::GameStateRunning::en_etyGameStateRunning			ety::CSpaceStationHangarState::handle_GameStateEvents				( const sf::Event& sfEventLastEvent  )
		{
			CDialogitem* p_c_etyDialogitemEvent = mp_c_etyDialogManager->get_MouseEventDialogitem();

			if(sfEventLastEvent.type == sf::Event::KeyReleased)
			{
				if(sfEventLastEvent.key.code == sf::Keyboard::Escape)
				{
					if(m_bShopOpen == true)
					{
						event_closeShop(1, mp_c_etyDialogManager);
					}
					else
					{
						return event_exitHangar(1, mp_c_etyDialogManager);
					}
				}
			}

			sf::Event c_sfEvent = sfEventLastEvent;
			mp_c_etyDialogManager->handle_Events(c_sfEvent);
	
			if(p_c_etyDialogitemEvent != NULL)
			{
				p_Function p_FunctionEvent = get_EventFunction(p_c_etyDialogitemEvent->get_CustomID(), c_sfEvent);

				if(p_FunctionEvent != NULL)
				{
					std::string strCustomID = p_c_etyDialogitemEvent->get_CustomID();

					return p_FunctionEvent(2, mp_c_etyDialogManager, new std::string(strCustomID));
				}
			}

			return ety::GameStateRunning::enTRUE;
		}


ety::GameStateRunning::en_etyGameStateRunning					ety::CSpaceStationHangarState::event_closeShop						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager*				p_c_etyDialogManager				=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	CSpaceStationHangarState*	p_c_etySpaceStationHangarState		=	static_cast<CSpaceStationHangarState*>(p_c_etyDialogManager->get_ParentGameState()); 
	va_CloseArgumentList(va_ALParameter);

	//Shop schlie�en
	p_c_etySpaceStationHangarState->set_ShopVisiblity(false);
	p_c_etyDialogManager->get_DialogbyCustomID( "ShopBackground" )->set_Visibility( false );
	p_c_etyDialogManager->get_DialogbyCustomID( "ShopBackground" )->set_Modal( false, sf::Vector3f(1.f,1.f,1.f) );	

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning					ety::CSpaceStationHangarState::event_exitHangar						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	//Den Hangar verlassen und in die Station zur�ckkehren
	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->popback_GameState();

	return ety::GameStateRunning::enFALSE;
}
ety::GameStateRunning::en_etyGameStateRunning					ety::CSpaceStationHangarState::event_enterIngame					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	//Den Hangar verlassen und in die Station zur�ckkehren
	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->popback_GameState	();
	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->pushback_GameState	( "IngameState" );

	return ety::GameStateRunning::enFALSE;
}
ety::GameStateRunning::en_etyGameStateRunning					ety::CSpaceStationHangarState::event_showButtonTooltip				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager	=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));  
	std::string		strButtonID				=	*static_cast<std::string*>(va_getArgument(va_ALParameter, void*));  
	va_CloseArgumentList(va_ALParameter);
	
	//Tooltip des Buttons anzeigen
	//mp_c_etyCShop->show_ButtonTooltip(strButtonID);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning					ety::CSpaceStationHangarState::event_openShop						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationHangarState*	p_c_etySpaceStationHangarState		=	static_cast<CSpaceStationHangarState*>(p_c_etyDialogManager->get_ParentGameState()); 
	va_CloseArgumentList(va_ALParameter);

	//Shop �ffnen
	p_c_etySpaceStationHangarState->set_ShopVisiblity(true);
	p_c_etyDialogManager->get_DialogbyCustomID("ShopBackground")->set_Visibility(true);
	p_c_etyDialogManager->get_DialogbyCustomID("ShopBackground")->set_Modal(true,sf::Vector3f(1.f,1.f,1.f));

	return ety::GameStateRunning::enTRUE;
}


void															ety::CSpaceStationHangarState::set_ShopVisiblity					( bool bShopVisible )
{
	m_bShopOpen	=	bShopVisible;
}