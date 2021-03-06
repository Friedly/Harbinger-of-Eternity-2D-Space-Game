#include "CSpaceStationState.hpp"
#include "CSpaceStationHangarState.hpp"
#include "CGameStateManager.hpp"
#include "CIngameState.hpp"

#include "CButton.hpp"
#include "CLabel.hpp"


															ety::CSpaceStationState::CSpaceStationState				( const std::string& strStateName )
																: CDialogGameState									( strStateName )
																, m_bUpdateMouseHoverEvents							( true )
															{
															}
															ety::CSpaceStationState::~CSpaceStationState			( void )
															{
															}

		void												ety::CSpaceStationState::on_Enter						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}
		void												ety::CSpaceStationState::on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}

		void												ety::CSpaceStationState::init_GameState					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			CLua* const p_c_etyLuaScript			= get_GameStatemanager()			->get_LuaScript();

			unsigned int	uiScreen_Height			= p_c_etyCurrentGamesettingManager	->get_Videomode().height;
			unsigned int	uiScreen_Width			= p_c_etyCurrentGamesettingManager	->get_Videomode().width;

			std::string		strLanguage				= p_c_etyCurrentGamesettingManager	->get_Language();

			sf::VideoMode	c_sfCurrentVideomode	= p_c_etyCurrentGamesettingManager	->get_Videomode();
			sf::Font		c_sfCurrentFont			= p_c_etyCurrentRessourceManager	->get_Font("Standard.ttf");

			mp_c_etyDialogManager->set_GamesettingsManager	( p_c_etyCurrentGamesettingManager );
			mp_c_etyDialogManager->set_StandardFont			( c_sfCurrentFont );

			p_c_etyLuaScript->init_Lua();
			p_c_etyLuaScript->start_Script("Initialisation/Gamestates/Language.lua");

			enum EventType::en_etyEventType en_etyEventType = EventType::enNONE;
			std::map<enum EventType::en_etyEventType, p_Function> mapEventTypeFunction;

			////////////////////////////////////////////////*Hinzuf�gen der Attribute ANFANG*////////////////////////////////////////////////

			m_en_etyPadModus = PadModus::enHANGAR;
			mp_c_etyDialogManager->set_GamesettingsManager( p_c_etyCurrentGamesettingManager );
			get_GameStatemanager()->m_c_etyAttributes.add_Attribute<PadModus::en_etyPadModus>( "p_en_etyPadModus" , &m_en_etyPadModus, false );

			////////////////////////////////////////////////*Hinzuf�gen der Attribute ENDE*////////////////////////////////////////////////

			//Multiplikator = 1.1666666 = x | 1.1666666 = y

			//Hangar 	- Size = 164x461 | Position = 59x114 -> Size = 191.333x537.833 | Position = 68.8333x133
			//Pad		- Size = 84x97 | Position = 553x734 -> Size = 98x113.167 | Position = 645.167x856.333
			//Mission	- Size = 121x153 | Position = 644x242 -> Size = 141.167x178.5 | Position = 751.333x282.333
	
			////////////////////////////////////////////*SpaceStationBar ANFANG*////////////////////////////////////////////
			ety::CDialog* p_c_etyDialogSpaceStationBar = new CDialog(	
				"SpaceStationBar", p_c_etyCurrentRessourceManager->get_Texture( "BarBackground.png" ), 1680.f, 1050.f, sf::Vector2f( 0.f, 0.f ), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1440, 900)), mp_c_etyDialogManager, c_sfCurrentVideomode
				);		

			////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////

			p_c_etyDialogSpaceStationBar->createDialogitem_Button( 
				"BarPadButton", p_c_etyCurrentRessourceManager->get_Texture( "Pad.png" ), 98.f, 113.167f, sf::Vector2f(645.167f, -856.333f), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(84, 97))
				);

			//////////////////////////EVENTS/////////////////////////////////
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_openPad;

			m_EventMap["BarPadButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
		
			p_c_etyDialogSpaceStationBar->createDialogitem_Button( 
				"BarHangarButton", p_c_etyCurrentRessourceManager->get_Texture( "Hangar.png" ), 191.333f, 537.833f, sf::Vector2f(68.8333f, -133.f), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(164, 461))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_enterHangar;

			m_EventMap["BarHangarButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
		
			p_c_etyDialogSpaceStationBar->createDialogitem_Button( 
				"BarMissionButton", p_c_etyCurrentRessourceManager->get_Texture( "Missionen.png" ), 141.167f, 178.5f, sf::Vector2f(751.333f, -282.333f), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(121, 153))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openMissionMenu;

			m_EventMap["BarMissionButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////

			////////////////////////////////////////////*SpaceStationPad ANFANG*////////////////////////////////////////////
	
			ety::CDialog* p_c_etyDialogSpaceStationPad = new CDialog( 
				"SpaceStationPad", p_c_etyCurrentRessourceManager->get_Texture( "BarPad.png" ), 700.f, 850.f, sf::Vector2f( -100 ,0 ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 748, 942 )), mp_c_etyDialogManager, c_sfCurrentVideomode
				);

			p_c_etyDialogSpaceStationPad->set_Visibility(false);
			p_c_etyDialogSpaceStationPad->set_Affinity(Affinity::enFOREGROUND);
			p_c_etyDialogSpaceStationPad->set_Anchor(Anchor::enMID);
			p_c_etyDialogSpaceStationPad->set_AnchorCentered(true);
		
			////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////
			p_c_etyDialogSpaceStationPad->createDialogitem_Button( 
				"PadHangarButton", p_c_etyCurrentRessourceManager->get_Texture( "PadHangarButton.png" ), 136.631f, 80.3078f, sf::Vector2f( 54.f, -5.f ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 146, 89 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openPadHangar;

			m_EventMap["PadHangarButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
		
			p_c_etyDialogSpaceStationPad->createDialogitem_Button( 
				"PadShopButton", p_c_etyCurrentRessourceManager->get_Texture( "PadShopButton.png" ), 136.631f, 80.3078f, sf::Vector2f( 193.f, -5.f ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 146, 89 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openPadShop;

			m_EventMap["PadShopButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			p_c_etyDialogSpaceStationPad->createDialogitem_Button(	
				"PadMissionButton", p_c_etyCurrentRessourceManager->get_Texture( "PadMissionButton.png" ), 136.631f, 80.3078f, sf::Vector2f( 332.f, -5.f ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 146, 89 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openPadMission;

			m_EventMap["PadMissionButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
		
			p_c_etyDialogSpaceStationPad->createDialogitem_Button(	
				"PadLogbookButton", p_c_etyCurrentRessourceManager->get_Texture( "PadLogbookButton.png" ), 136.631f, 80.3078f, sf::Vector2f( 471.f, -5.f ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 146, 89 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openPadLogbook;

			m_EventMap["PadLogbookButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			p_c_etyDialogSpaceStationPad->createDialogitem_Button(	
				"PadBackButton", p_c_etyCurrentRessourceManager->get_Texture( "PadBackButton.png" ), 79.545f, 80.3078f, sf::Vector2f( 611.f, -5.f ), 
				sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 85, 90 ))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_openPadBack;

			m_EventMap["PadBackButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////
		
			p_c_etyDialogSpaceStationPad->createDialogitem_TextButton(	
				"PadEnterHangarButton", sf::Vector2f( 115.f, -155.f ), p_c_etyLuaScript->get_TableString( "PadEnterHangarButtonCaption", strLanguage ), 20.f, ety::Color( 85.f, 85.f, 85.f ),
				ety::Color( 8.f, 201.f, 206.f )
				);

			p_c_etyDialogSpaceStationPad->createDialogitem_TextButton(	
				"PadEnterShopButton", sf::Vector2f( 115.f, -155.f ), p_c_etyLuaScript->get_TableString( "PadEnterShopButtonCaption", strLanguage ), 20.f, ety::Color( 85.f, 85.f, 85.f ),
				ety::Color( 8.f, 201.f, 206.f )
				); 

			CButton* p_c_etyButtonTmp = p_c_etyDialogSpaceStationPad->get_DialogitemByCustomID<CButton*>("PadEnterShopButton");
			p_c_etyButtonTmp->set_Visibility(false);
		
			p_c_etyDialogSpaceStationPad->createDialogitem_TextButton(	
				"PadCelestialMapButton", sf::Vector2f( 115.f, -255.f ), p_c_etyLuaScript->get_TableString( "PadCelestialMapButtonCaption", strLanguage ), 20.f, ety::Color( 85.f, 85.f, 85.f ),
				ety::Color( 8.f, 201.f, 206.f )
				); 
		
			////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////

			////////////////////////////////////////////*SpaceStationBar ENDE*////////////////////////////////////////////

			////////////////////////////////////////////*MissionMenu ANFANG*////////////////////////////////////////////

			ety::CDialog* p_c_etyDialogSpaceStationMissionMenu = new CDialog( 
				"SpaceStationMissionMenu", p_c_etyCurrentRessourceManager->get_Texture( "MissionMenuBackground.png" ), 1000.f, 700.f, sf::Vector2f( 0.f, 0.f ), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1680, 1050)), mp_c_etyDialogManager, c_sfCurrentVideomode
				);

			p_c_etyDialogSpaceStationMissionMenu->set_Visibility(false);
			p_c_etyDialogSpaceStationMissionMenu->set_Anchor(Anchor::enMID);
			p_c_etyDialogSpaceStationMissionMenu->set_AnchorCentered(true);
			p_c_etyDialogSpaceStationMissionMenu->set_Affinity(Affinity::enFOREGROUND);
			////////////////////////////////////////////*MissionMenu ENDE*////////////////////////////////////////////

			////////////////////////////////////////////*ExitMenu ANFANG*////////////////////////////////////////////
			ety::CDialog* p_c_etyDialogExitMenu = new CDialog(
				"SpaceStationExitMenu", p_c_etyCurrentRessourceManager->get_Texture( "ExitMenuSet.png" ), 600.f, 350.f, sf::Vector2f( 0.f, 0.f ), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(600,350)), mp_c_etyDialogManager, c_sfCurrentVideomode
				);

			p_c_etyDialogExitMenu->set_Visibility(false);
			p_c_etyDialogExitMenu->set_Anchor(Anchor::enMID);
			p_c_etyDialogExitMenu->set_AnchorCentered(true);
			p_c_etyDialogExitMenu->set_Affinity(Affinity::enFOREGROUND);

			////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////

			p_c_etyDialogExitMenu->createDialogitem_Button(	
				"ExitYesButton", p_c_etyCurrentRessourceManager->get_Texture( "transparentBackground.png" ), 137.f, 74.f, sf::Vector2f(161.f, -205.f), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(0,0))
				);

			//////////////////////////EVENTS/////////////////////////////////
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_exitGame;
			en_etyEventType = EventType::enMOUSEHOVER;
			mapEventTypeFunction[en_etyEventType] = &event_exitButtonHover;

			m_EventMap["ExitYesButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			p_c_etyDialogExitMenu->createDialogitem_Button(	
				"ExitCancelButton", p_c_etyCurrentRessourceManager->get_Texture( "transparentBackground.png" ), 137.f, 74.f, sf::Vector2f(305.f, -205.f), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(0,0))
				);

			//////////////////////////EVENTS/////////////////////////////////
			mapEventTypeFunction[en_etyEventType] = &event_exitButtonHover;
			en_etyEventType = EventType::enMOUSELEFTRELEASED;
			mapEventTypeFunction[en_etyEventType] = &event_cancelExitGame;

			m_EventMap["ExitCancelButton"] = mapEventTypeFunction;
			mapEventTypeFunction.clear();
			//////////////////////////EVENTS/////////////////////////////////

			////////////////////////////////////////////*Captions ANFANG*////////////////////////////////////////////

			p_c_etyDialogExitMenu->get_DialogitemByCustomID<ety::CButton*>( "ExitYesButton" )
							 ->create_CaptionLabel(
							 ety::Color( 8.f, 201.f, 206.f ), p_c_etyLuaScript->get_TableString( "ExitYesButtonCaption", strLanguage ), 25.f, ety::Color( 85.f, 85.f, 85.f )
							 );

			p_c_etyDialogExitMenu->get_DialogitemByCustomID<ety::CButton*>( "ExitCancelButton" )
							 ->create_CaptionLabel(
							 ety::Color( 8.f, 201.f, 206.f ), p_c_etyLuaScript->get_TableString( "ExitCancelButtonCaption", strLanguage ), 25.f, ety::Color( 85.f, 85.f, 85.f )
							 );

			////////////////////////////////////////////*Captions ENDE*////////////////////////////////////////////
			////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////
		
			////////////////////////////////////////////*Labels ANFANG*////////////////////////////////////////////

			p_c_etyDialogExitMenu->createDialogitem_Label(	
				"ExitTitleLabel",p_c_etyLuaScript->get_TableString("ExitTitleLabel",strLanguage), 25.f, sf::Color(255,255,255,200), sf::Vector2f(0,60)
				);

			p_c_etyDialogExitMenu->get_DialogitemByCustomID<CLabel*>("ExitTitleLabel")->set_Anchor(Anchor::enMID);
			p_c_etyDialogExitMenu->get_DialogitemByCustomID<CLabel*>("ExitTitleLabel")->set_AnchorCentered(true);

			////////////////////////////////////////////*Labels ENDE*////////////////////////////////////////////

			////////////////////////////////////////////*ExitMenu ENDE*////////////////////////////////////////////
	
			p_c_etyLuaScript->close_Lua();
		}

		void												ety::CSpaceStationState::update_GameState				( const sf::Uint32& uiFrameTime )
		{
			CDialogGameState::update_GameState( uiFrameTime );
		}

		void												ety::CSpaceStationState::render_GameState				( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			CDialogGameState::render_GameState( p_c_sfRenderTextureGameScene );
		}

const	ety::GameStateRunning::en_etyGameStateRunning		ety::CSpaceStationState::handle_GameStateEvents			( const sf::Event& sfEventLastEvent  )
{
	CDialogitem* p_c_etyDialogitemEvent = mp_c_etyDialogManager->get_MouseEventDialogitem();

	if(sfEventLastEvent.type == sf::Event::KeyReleased)
	{
		if(sfEventLastEvent.key.code == sf::Keyboard::Escape)
		{
			if( mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->get_Visibility() == true )
			{
				//Schlie�en des Pads
				mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->set_Visibility			( false );
				mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->set_Modal					( false, sf::Vector3f(1.f,1.f,1.f) );	
			}	
			else if( mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->get_Visibility() == true )
			{
				//Schlie�en des MissionMen�s
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Visibility		( false );
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Modal			( false, sf::Vector3f( 1.25f, 1.25f, 1.25f ) );	
			}
			else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Visibility() == true)
			{
				//Schlie�en des ExitMen�s
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility			( false );
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal				( false, sf::Vector3f( 1.3333333f, 1.3333333f, 1.3333333f ) );	
			}
			else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Visibility() == true)
			{
				//Schlie�en des Exit-Men�s
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(false);
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));		
			}
			else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Visibility() == false && mp_c_etyDialogManager->get_ModalDialog() == false)
			{
				//�ffnen des Exit-Men�s
				CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
				sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
				c_sfIntRectSubRect.left = 0;
				c_sfIntRectSubRect.top = 0;
				p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);

				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(true);
				mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(true,sf::Vector3f(0.75f,0.75f,0.75f));


				if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_DialogitemByCustomID<CButton*>("ExitYesButton")->check_MouseCoordinates() == true)
				{
					event_exitButtonHover(2, mp_c_etyDialogManager, new int(350));
				}
				else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_DialogitemByCustomID<CButton*>("ExitCancelButton")->check_MouseCoordinates() == true)
				{
					event_exitButtonHover(2, mp_c_etyDialogManager, new int(700));
				}
			}
		}
	}
	else if(sfEventLastEvent.type == sf::Event::MouseMoved && p_c_etyDialogitemEvent == NULL)
	{
		if( m_bUpdateMouseHoverEvents == true )
		{
			if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Modal() == true)
			{
				CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
				sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
				c_sfIntRectSubRect.left = 0;
				c_sfIntRectSubRect.top = 0;
				p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
				m_bUpdateMouseHoverEvents = false;
			}
		}
	}	


	sf::Event c_sfEvent = sfEventLastEvent;
	mp_c_etyDialogManager->handle_Events(c_sfEvent);
	
	if(p_c_etyDialogitemEvent != NULL)
	{
		p_Function p_FunctionEvent = get_EventFunction(p_c_etyDialogitemEvent->get_CustomID(), c_sfEvent);
		std::string strCustomID = p_c_etyDialogitemEvent->get_CustomID();

		if(p_FunctionEvent != NULL)
		{
			if(strCustomID == "ExitYesButton" && c_sfEvent.type == sf::Event::MouseMoved)
			{
				return p_FunctionEvent(2, mp_c_etyDialogManager, new int(350));
			}
			else if(strCustomID == "ExitCancelButton" && c_sfEvent.type == sf::Event::MouseMoved)
			{
				return p_FunctionEvent(2, mp_c_etyDialogManager, new int(700));
			}
			else
			{
				return p_FunctionEvent(1, mp_c_etyDialogManager);
			}
		}
	}
	

	return ety::GameStateRunning::enTRUE;
	
	
	
	
	
	
	/*if( p_c_etyDialogitemEventDialogitem != NULL )
	{
		////std::cout << p_c_etyDialogitemEventDialogitem << std::endl << p_c_etyDialogitemEventDialogitem->get_Active() << std::endl << p_c_etyDialogitemEventDialogitem->get_CustomID() << std::endl;
	}

	if( mp_c_etyWorldManager->get_Active() == true )
	{
		mp_c_etyWorldManager->handle_Events( sfEventLastEvent, p_c_etyDialogitemEventDialogitem, mp_c_etyGameStatemanager );

		return ety::GameStateRunning::enTRUE;
	}

	if( sfEventLastEvent.type == sf::Event::KeyReleased && sfEventLastEvent.key.code == sf::Keyboard::Escape )
	{
		if( mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->get_Visibility() == true )
		{
			mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->set_Visibility			( false );
			mp_c_etyDialogManager->get_DialogbyCustomID( "SpaceStationPad" )->set_Modal					( false, sf::Vector3f(1.f,1.f,1.f) );	
		}	
		else if( mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->get_Visibility() == true )
		{
			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Visibility		( false );
			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Modal			( false, sf::Vector3f( 1.25f, 1.25f, 1.25f ) );	
		}
		else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Visibility() == true)
		{
			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility			( false );
			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal				( false, sf::Vector3f( 1.3333333f, 1.3333333f, 1.3333333f ) );	
		}	
		else if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Visibility() == false && mp_c_etyDialogManager->get_ModalDialog() == false)
		{
			CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
			sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
			c_sfIntRectSubRect.left = 0;
			c_sfIntRectSubRect.top = 0;

			p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);

			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility			( true );
			mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal				( true, sf::Vector3f( 0.75f, 0.75f, 0.75f ) );
		}
	}
	else if(sfEventLastEvent.type == sf::Event::MouseButtonReleased)
	{
		if(sfEventLastEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(p_c_etyDialogitemEventDialogitem != NULL)
			{
				p_c_etyDialogitemEventDialogitem->set_EventDialogitem(false);

				if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "ExitYesButton")
				{
					CButton* p_c_etyButtonEventButton	=	static_cast< CButton* >(p_c_etyDialogitemEventDialogitem);

					if( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK) != NULL)
					{
						while( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK)->getStatus() == sf::Sound::Playing )
						{
						}
					}
					
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(false);
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));	

					//Die Raumstation verlassen
					get_GameStatemanager()->pushback_GameState( "MenuState" );

					return ety::GameStateRunning::enFALSE;
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "ExitCancelButton")
				{
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(false);
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "BarPadButton")
				{
					//Pad �ffnen
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Visibility(true);
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Modal(true,sf::Vector3f(1.f,1.f,1.f));
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "BarHangarButton")
				{
					//In den Hangar wechseln
					m_en_etyPadModus = PadModus::enHANGAR;
					get_GameStatemanager()->pushback_GameState( "SpaceStationHangarState", ety::GamestateStatus::enBACKGROUND );
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "BarMissionButton")
				{
					//MissionMen� �ffnen
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Visibility(true);
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Modal(true,sf::Vector3f(0.8f,0.8f,0.8f));
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadHangarButton")
				{
					m_en_etyPadModus = PadModus::enHANGAR;

					CButton* p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(true);

					p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadShopButton")
				{
					m_en_etyPadModus = PadModus::enSHOP;

					CButton* p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);

					p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(true);
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadMissionButton")
				{
					m_en_etyPadModus = PadModus::enMISSION;

					CButton* p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);

					p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadLogbookButton")
				{
					m_en_etyPadModus = PadModus::enLOGBOOK;

					CButton* p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);

					p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
					p_c_etyButtonMenuTmpPointer->set_Visibility(false);
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadBackButton")
				{
					//Pad schlie�en
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Visibility(false);
					mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Modal(false,sf::Vector3f(1.f,1.f,1.f));	
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadEnterHangarButton")
				{
					//In den Hangar wechseln
					get_GameStatemanager()->pushback_GameState( "SpaceStationHangarState", ety::GamestateStatus::enBACKGROUND );
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadEnterShopButton")
				{
					//In den Hangar wechseln
					get_GameStatemanager()->pushback_GameState( "SpaceStationHangarState", ety::GamestateStatus::enBACKGROUND );
				}
				else if(p_c_etyDialogitemEventDialogitem->get_CustomID() == "PadCelestialMapButton")
				{
					mp_c_etyWorldManager->show_CelestialMap( true );
				}
			}
		}
	}
	else if(sfEventLastEvent.type == sf::Event::MouseMoved)
	{
		if(p_c_etyDialogitemEventDialogitem	==	NULL)
		{
			if(m_bUpdateMouseHoverEvents == true)
			{
				if(mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_Modal() == true)
				{
					CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
					sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
					c_sfIntRectSubRect.left = 0;
					c_sfIntRectSubRect.top = 0;

					p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
				}

				m_bUpdateMouseHoverEvents = false;
			}
		}
		else if(p_c_etyDialogitemEventDialogitem->get_CustomID()	==	"ExitYesButton")
		{
			CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
			sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
			c_sfIntRectSubRect.left = 0;
			c_sfIntRectSubRect.top = 350;

			p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
			m_bUpdateMouseHoverEvents = true;
		}
		else if(p_c_etyDialogitemEventDialogitem->get_CustomID()	==	"ExitCancelButton")
		{
			CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
			sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
			c_sfIntRectSubRect.left = 0;
			c_sfIntRectSubRect.top = 700;

			p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
			m_bUpdateMouseHoverEvents = true;
		} 
	}

	return ety::GameStateRunning::enTRUE;*/
}

void														ety::CSpaceStationState::set_UpdateMouseHoverEvent		( bool bMouseHoverEvent )
{
	m_bUpdateMouseHoverEvents = bMouseHoverEvent;
}
void														ety::CSpaceStationState::set_PadModus					( enum ety::PadModus::en_etyPadModus en_etyPadModus )
{
	m_en_etyPadModus = en_etyPadModus;
}
		
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_exitGame					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	CButton* p_c_etyButtonEventButton	=	static_cast< CButton* >(p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->get_DialogitemByCustomID<CButton*>("ExitYesButton"));

	if( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK) != NULL)
	{
		while( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK)->getStatus() == sf::Sound::Playing )
		{
		}
	}
					
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(false);
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));	

	//Die Raumstation verlassen
	//p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->popback_GameState();
	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->pushback_GameState( "MenuState" );

	return ety::GameStateRunning::enFALSE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_enterHangar				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	//In den Hangar wechseln
	//m_en_etyPadModus = PadModus::enHANGAR;
	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->pushback_GameState( "SpaceStationHangarState", ety::GamestateStatus::enBACKGROUND );

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_cancelExitGame			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Visibility(false);
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));

	va_CloseArgumentList(va_ALParameter);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_exitButtonHover			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager					=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*)); 
	CSpaceStationState*		p_c_etySpaceStationState		=	static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());
	

	CDialog* p_c_etyDialogTmp = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationExitMenu");
	sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
	c_sfIntRectSubRect.left = 0;
	c_sfIntRectSubRect.top = *static_cast<int*>(va_getArgument(va_ALParameter, void*)); ;
	p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
	va_CloseArgumentList(va_ALParameter);

	p_c_etySpaceStationState->set_UpdateMouseHoverEvent(true);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openMissionMenu			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	//MissionMen� �ffnen
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Visibility(true);
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationMissionMenu")->set_Modal(true,sf::Vector3f(0.8f,0.8f,0.8f));

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPad					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	va_CloseArgumentList(va_ALParameter);

	//Pad �ffnen
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Visibility(true);
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Modal(true,sf::Vector3f(1.f,1.f,1.f));

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPadHangar			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager			= static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationState* p_c_etySpaceStationState	= static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());   
	va_CloseArgumentList(va_ALParameter);

	p_c_etySpaceStationState->set_PadModus(PadModus::enHANGAR);

	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(true);

	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPadShop				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager			= static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationState* p_c_etySpaceStationState	= static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());   
	va_CloseArgumentList(va_ALParameter);

	p_c_etySpaceStationState->set_PadModus(PadModus::enSHOP);

	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(true);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPadMission			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager			= static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationState* p_c_etySpaceStationState	= static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());   
	va_CloseArgumentList(va_ALParameter);

	p_c_etySpaceStationState->set_PadModus(PadModus::enMISSION);

	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPadLogbook			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager			= static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationState* p_c_etySpaceStationState	= static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());   
	va_CloseArgumentList(va_ALParameter);

	p_c_etySpaceStationState->set_PadModus(PadModus::enLOGBOOK);

	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterHangarButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->get_DialogitemByCustomID<ety::CButton*>("PadEnterShopButton");
	p_c_etyButtonMenuTmpPointer->set_Visibility(false);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning				ety::CSpaceStationState::event_openPadBack				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager			= static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));   
	CSpaceStationState* p_c_etySpaceStationState	= static_cast<CSpaceStationState*>(p_c_etyDialogManager->get_ParentGameState());   
	va_CloseArgumentList(va_ALParameter);

	//Pad schlie�en
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Visibility(false);
	p_c_etyDialogManager->get_DialogbyCustomID("SpaceStationPad")->set_Modal(false,sf::Vector3f(1.f,1.f,1.f));	

	return ety::GameStateRunning::enTRUE;
}