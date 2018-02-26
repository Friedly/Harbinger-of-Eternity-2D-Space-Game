#include "CProfileState.hpp"
#include "CGameStateManager.hpp"
#include "CWorld.hpp"

#include "CButton.hpp"
#include "CComboBox.hpp"
#include "CEditControl.hpp"
#include "CLabel.hpp"

#include "CScrollbar.hpp"

#include "CMathConvertClasses.hpp"

#include "CMenuState.hpp"

																	ety::CProfileState::CProfileState							( const std::string& strStateName )
																		: CDialogGameState								( strStateName )
																		, m_bEditProfilEntry						( false )
																		, m_bUpdateMouseHoverEvents					( true )
																		, mp_c_etySelectedProfile					( NULL )
																		, m_c_etyProfilemanager						( "Profiles", "Profiles", "Profiles/", "uiProfileCount", "strProfile" )
{
}
																	ety::CProfileState::~CProfileState							( void )
{
}

		void														ety::CProfileState::on_Enter								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
}
		void														ety::CProfileState::on_Exit									( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
}

		void														ety::CProfileState::init_GameState							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
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

	////////////////////////////////////////////////*Hinzufügen der Attribute ANFANG*////////////////////////////////////////////////

	get_GameStatemanager()->m_c_etyAttributes.add_Attribute<ety::CETYProfile>( "p_c_etyCurrentProfile", mp_c_etySelectedProfile, false );

	////////////////////////////////////////////////*Hinzufügen der Attribute ENDE*////////////////////////////////////////////////

	////////////////////////////////////////////*ProfileMenu ENDE*////////////////////////////////////////////

	ety::CDialog* p_c_etyDialogProfileMenu = new CDialog(
		"ProfileMenu", p_c_etyCurrentRessourceManager->get_Texture( "ProfileBackgroundAlpha.png" ), 716.25, 711.f, sf::Vector2f( -43.f, -36.f ), 
		sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 955, 948 )), mp_c_etyDialogManager, c_sfCurrentVideomode
		);
		
	
	////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////

	p_c_etyDialogProfileMenu->createDialogitem_TextButton(
		"ProfileNewButton", sf::Vector2f( 585.f, -262.5f ), p_c_etyLuaScript->get_TableString( "ProfileNewButtonCaption", strLanguage ), 16.f, ety::Color( 85.f, 85.f, 85.f ),
		ety::Color( 8.f, 201.f, 206.f )
		);

	CButton* p_c_etyButtonTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CButton*>("ProfileNewButton");
	p_c_etyButtonTmp->set_AnchorCentered(true);

	//////////////////////////EVENTS/////////////////////////////////
	en_etyEventType = EventType::enMOUSELEFTRELEASED;
	mapEventTypeFunction[en_etyEventType] = &event_newProfile;

	m_EventMap["ProfileNewButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////

	p_c_etyDialogProfileMenu->createDialogitem_TextButton(
		"ProfileDeleteButton", sf::Vector2f( 585.f, -422.5f ), p_c_etyLuaScript->get_TableString( "ProfileDeleteButtonCaption", strLanguage ), 16.f, ety::Color( 85.f, 85.f, 85.f ),
		ety::Color( 8.f, 201.f, 206.f )
		);

	p_c_etyButtonTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CButton*>("ProfileDeleteButton");
	p_c_etyButtonTmp->set_AnchorCentered(true);

	//////////////////////////EVENTS/////////////////////////////////
	mapEventTypeFunction[en_etyEventType] = &event_deleteProfile;

	m_EventMap["ProfileDeleteButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////

	
	p_c_etyDialogProfileMenu->createDialogitem_Button(
		"ProfileBackButton", p_c_etyCurrentRessourceManager->get_Texture( "Zurück.png" ), 35.25f, 36.75f, sf::Vector2f( 636.f, -579.75f ), 
		sf::IntRect(sf::Vector2i( 100, 0 ), sf::Vector2i( 47, 49 ))
		);

	p_c_etyButtonTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CButton*>("ProfileBackButton");
	p_c_etyButtonTmp->set_HoverSprite_Width(c_sfCurrentVideomode.width*float(75.f/1680.f));
	p_c_etyButtonTmp->set_HoverSprite_Height(c_sfCurrentVideomode.height*float(75.f/1050.f));
	p_c_etyButtonTmp->set_HoverSprite_SubRect(sf::IntRect(0, 0, 100, 100), true);

	//////////////////////////EVENTS/////////////////////////////////
	mapEventTypeFunction[en_etyEventType] = &event_exitProfileMenu;

	m_EventMap["ProfileBackButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////


	p_c_etyDialogProfileMenu->createDialogitem_Button(
		"ProfileSaveButton", p_c_etyCurrentRessourceManager->get_Texture( "Diskette.png" ), 37.5f, 37.5f, sf::Vector2f( 580.5f, -631.f ), 
		sf::IntRect(sf::Vector2i( 141 ,2 ), sf::Vector2i( 50, 50 ))
		);

	p_c_etyButtonTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CButton*>("ProfileSaveButton");
	p_c_etyButtonTmp->set_HoverSprite_Width(c_sfCurrentVideomode.width*float(105.75f/1680.f));
	p_c_etyButtonTmp->set_HoverSprite_Height(c_sfCurrentVideomode.height*float(106.f/1050.f));
	p_c_etyButtonTmp->set_HoverSprite_SubRect(sf::IntRect(0, 0, 141, 141), true);

	//////////////////////////EVENTS/////////////////////////////////
	mapEventTypeFunction[en_etyEventType] = &event_saveProfiles;

	m_EventMap["ProfileSaveButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////


	////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////

	
	////////////////////////////////////////////*EditControls ANFANG*////////////////////////////////////////////

	p_c_etyDialogProfileMenu->createDialogitem_EditControl(	
		"ProfileNewProfileEditControl", p_c_etyCurrentRessourceManager->get_Texture( "ProfileBildschirmButton.png" ), true, 347.625f, 47.25f, sf::Vector2f( 91.f, -244.f ), 
		sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 485, 75 )), p_c_etyLuaScript->get_TableString( "ProfileNewProfileEditControl", strLanguage ), 20.f, ety::Color( 8.f, 201.f, 206.f )
		);

	CEditControl* p_c_etyEditControlTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CEditControl*>("ProfileNewProfileEditControl");
	p_c_etyEditControlTmp->set_Visibility(false);
	p_c_etyEditControlTmp->set_Affinity(Affinity::enFOREGROUND);

	

	////////////////////////////////////////////*EditControls ENDE*////////////////////////////////////////////


	////////////////////////////////////////////*Labels ANFANG*////////////////////////////////////////////

	p_c_etyDialogProfileMenu->createDialogitem_Label(	
		"ProfileTitleLabel", p_c_etyLuaScript->get_TableString( "ProfileTitleLabel", strLanguage ), 32.f, ety::Color( 255.f, 255.f, 255.f ), sf::Vector2f( 20, -140 )
		);

	CLabel* p_c_etyLabelTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CLabel*>("ProfileTitleLabel");
	p_c_etyLabelTmp->set_Anchor(Anchor::enALIGNEDMIDTOP);

	p_c_etyDialogProfileMenu->createDialogitem_Label(
		"SelectedProfileLabel", p_c_etyLuaScript->get_TableString( "SelectedProfileLabel", strLanguage ), 16.f,ety::Color( 8.f, 201.f, 206.f ), sf::Vector2f( ( 525.f+55.f ), -502.f ) 
		);

	p_c_etyLabelTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CLabel*>("SelectedProfileLabel");
	p_c_etyLabelTmp->set_TextwriteoutStyle(TextwriteoutStyle::enSTANDARD);
	p_c_etyLabelTmp->set_Textwriteout(true);
	p_c_etyLabelTmp->set_TextwriteoutDuration(500.f);

	p_c_etyLabelTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CLabel*>("SelectedProfileLabel");
	p_c_etyLabelTmp->set_AnchorCentered(true);

	////////////////////////////////////////////*Labels ENDE*////////////////////////////////////////////



	////////////////////////////////////////////*ComboBoxes ANFANG*////////////////////////////////////////////

	std::list<std::string> listProfileComboBoxCaptions = m_c_etyProfilemanager.get_TNames();

	p_c_etyDialogProfileMenu->createDialogitem_ListBox(	
		"ProfileListBox", p_c_etyCurrentRessourceManager->get_Texture("TestListBox.png"), 386.25f, 283.5f, sf::Vector2f( 91.f, -244.f ), 
		sf::IntRect(sf::Vector2i( 0, 0 ), sf::Vector2i( 515, 378 )), ety::Color( 85.f, 85.f, 85.f ), ety::Color( 8.f, 201.f, 206.f ), 20, 0.10f, 74
		);
		
	CComboBox* p_c_etyComboBoxTmp = p_c_etyDialogProfileMenu->get_DialogitemByCustomID<CComboBox*>("ProfileListBox");
	p_c_etyComboBoxTmp->set_Localization(false);
	p_c_etyComboBoxTmp->set_UnfoldedEntries(6);
	p_c_etyComboBoxTmp->create_Scrollbar(sf::IntRect(sf::Vector2i(0, 526), sf::Vector2i(50,200)));
	p_c_etyComboBoxTmp->add_ListEntries(listProfileComboBoxCaptions);

	////////////////////////////////////////////*ComboBoxes ENDE*////////////////////////////////////////////
	
	////////////////////////////////////////////*ProfileMenu ENDE*////////////////////////////////////////////


	////////////////////////////////////////////*Deletemenu ANFANG*////////////////////////////////////////////
	ety::CDialog* p_c_etyDialogDeleteMenu = new CDialog(
		"ProfileDeleteMenu", p_c_etyCurrentRessourceManager->get_Texture( "ExitMenuSet.png" ), 600.f, 350.f, sf::Vector2f( 0.f, 0.f ), 
		sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(600,350)), mp_c_etyDialogManager, c_sfCurrentVideomode
		);


	////////////////////////////////////////////*Buttons ANFANG*////////////////////////////////////////////

	p_c_etyDialogDeleteMenu->set_Visibility(false);
	p_c_etyDialogDeleteMenu->set_Anchor(Anchor::enMID);
	p_c_etyDialogDeleteMenu->set_AnchorCentered(true);
	p_c_etyDialogDeleteMenu->set_Affinity(Affinity::enFOREGROUND);


	p_c_etyDialogDeleteMenu->createDialogitem_Button(	
		"DeleteYesButton", p_c_etyCurrentRessourceManager->get_Texture( "transparentBackground.png" ), 137.f, 74.f, sf::Vector2f(161.f, -205.f), 
		sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(0,0))
		);

	//////////////////////////EVENTS/////////////////////////////////
	mapEventTypeFunction[en_etyEventType] = &event_applyDeleteProfile;
	en_etyEventType = EventType::enMOUSEHOVER;
	mapEventTypeFunction[en_etyEventType] = &event_deleteProfileButtonHover;

	m_EventMap["DeleteYesButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////

	p_c_etyDialogDeleteMenu->createDialogitem_Button(	
		"DeleteCancelButton", p_c_etyCurrentRessourceManager->get_Texture( "transparentBackground.png" ), 137.f, 74.f, sf::Vector2f(305.f, -205.f), 
		sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(0,0))
		);

	//////////////////////////EVENTS/////////////////////////////////
	mapEventTypeFunction[en_etyEventType] = &event_deleteProfileButtonHover;
	en_etyEventType = EventType::enMOUSELEFTRELEASED;
	mapEventTypeFunction[en_etyEventType] = &event_cancelDeleteProfile;
	

	m_EventMap["DeleteCancelButton"] = mapEventTypeFunction;
	mapEventTypeFunction.clear();
	//////////////////////////EVENTS/////////////////////////////////

	////////////////////////////////////////////*Captions ANFANG*////////////////////////////////////////////

	p_c_etyDialogDeleteMenu->get_DialogitemByCustomID<ety::CButton*>( "DeleteYesButton" )
					 ->create_CaptionLabel(
					 ety::Color( 8.f, 201.f, 206.f ), p_c_etyLuaScript->get_TableString( "DeleteYesButtonCaption", strLanguage ), 25.f, ety::Color( 85.f, 85.f, 85.f )
					 );

	p_c_etyDialogDeleteMenu->get_DialogitemByCustomID<ety::CButton*>( "DeleteCancelButton" )
					 ->create_CaptionLabel(
					 ety::Color( 8.f, 201.f, 206.f ), p_c_etyLuaScript->get_TableString( "DeleteCancelButtonCaption", strLanguage ), 25.f, ety::Color( 85.f, 85.f, 85.f )
					 );

	////////////////////////////////////////////*Captions ENDE*////////////////////////////////////////////
	////////////////////////////////////////////*Buttons ENDE*////////////////////////////////////////////
	

	////////////////////////////////////////////*Labels ANFANG*////////////////////////////////////////////

	p_c_etyDialogDeleteMenu->createDialogitem_Label(	
		"DeleteTitleLabel",p_c_etyLuaScript->get_TableString("DeleteTitleLabel",strLanguage), 20.f, sf::Color(255,255,255,200), sf::Vector2f(0,45)
		);

	p_c_etyLabelTmp = p_c_etyDialogDeleteMenu->get_DialogitemByCustomID<CLabel*>("DeleteTitleLabel");
	p_c_etyLabelTmp->set_Anchor(Anchor::enMID);
	p_c_etyLabelTmp->set_AnchorCentered(true);

	////////////////////////////////////////////*Labels ENDE*////////////////////////////////////////////

	////////////////////////////////////////////*Deletemenu ENDE*////////////////////////////////////////////

	p_c_etyLuaScript->close_Lua();
}


const	ety::GameStateRunning::en_etyGameStateRunning				ety::CProfileState::handle_GameStateEvents					( const sf::Event& sfEventLastEvent  )
{
	CDialogitem* p_c_etyDialogitemEvent = mp_c_etyDialogManager->get_MouseEventDialogitem();

	if(sfEventLastEvent.type == sf::Event::KeyReleased)
	{
		if(sfEventLastEvent.key.code == sf::Keyboard::Return)
		{
			ety::CDialogitem* p_c_etyDialogitemTmpPointer = mp_c_etyDialogManager->get_FocusedDialogitem();

			if( p_c_etyDialogitemTmpPointer != NULL )
			{
				if(	p_c_etyDialogitemTmpPointer->get_CustomID() == "ProfileNewProfileEditControl")
				{
					return event_confirmNewProfile(1, mp_c_etyDialogManager);
				}
			}
		}
		else if(sfEventLastEvent.key.code == sf::Keyboard::Escape)
		{
			if(mp_c_etyDialogManager->get_ModalDialog() == false)
			{
				CButton* p_c_etyButtonMenuTmpPointer = mp_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileNewButton");
				if(p_c_etyButtonMenuTmpPointer->get_Active() == false && m_bEditProfilEntry == false)
				{
					return event_cancelNewProfile(1, mp_c_etyDialogManager);
				}
				else
				{
					return event_exitProfileMenu(1, mp_c_etyDialogManager);
				}
			}
		}
	}
	else if(sfEventLastEvent.type == sf::Event::MouseMoved && p_c_etyDialogitemEvent == NULL)
	{
		if( m_bUpdateMouseHoverEvents == true )
		{
			if(m_bUpdateMouseHoverEvents == true)
			{
				if(mp_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->get_Modal() == true)
				{
					CDialog* p_c_etyDialogTmp = mp_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu");
					sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
					c_sfIntRectSubRect.left = 0;
					c_sfIntRectSubRect.top = 0;
					p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
					m_bUpdateMouseHoverEvents = false;
				}
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
			if(strCustomID == "DeleteYesButton" && c_sfEvent.type == sf::Event::MouseMoved)
			{
				return p_FunctionEvent(2, mp_c_etyDialogManager, new int(350));
			}
			else if(strCustomID == "DeleteCancelButton" && c_sfEvent.type == sf::Event::MouseMoved)
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
}


void																ety::CProfileState::set_SelectedProfile							( ety::CETYProfile* p_c_etyProfile )
{
	mp_c_etySelectedProfile = p_c_etyProfile;
}
void																ety::CProfileState::set_UpdateMouseHoverEvent					( bool bMouseHoverEvent )
{
	m_bUpdateMouseHoverEvents	=	bMouseHoverEvent;
}


ety::CETYProfile*	const											ety::CProfileState::get_SelectedProfile							( void )
{
	return mp_c_etySelectedProfile;
}
ety::CIniLoader<ety::CETYProfile>&									ety::CProfileState::get_Profilemanager							( void )
{
	return m_c_etyProfilemanager;
}



ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_applyDeleteProfile				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	CProfileState* p_c_etyProfileState = static_cast<CProfileState*>(p_c_etyDialogManager->get_ParentGameState());

	//Bestätigen der Delete-Abfrage
	CComboBox* p_c_etyComboBoxProfiles = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CComboBox*>("ProfileListBox");
					
	const std::string strProfileToDelete = p_c_etyComboBoxProfiles->get_ListEntry( p_c_etyComboBoxProfiles->get_CurrentSelectedEntrie() );

	p_c_etyComboBoxProfiles->delete_ListEntry( p_c_etyComboBoxProfiles->get_CurrentSelectedEntrie() );
	p_c_etyProfileState->get_Profilemanager().delete_T( strProfileToDelete );

	//Schließen der Delete-Abfrage
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Visibility(false);
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));	


	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_cancelDeleteProfile				( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	//Schließen der Delete-Abfrage
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Visibility(false);
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Modal(false,sf::Vector3f(1.3333333f,1.3333333f,1.3333333f));		
	
	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_deleteProfileButtonHover			( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager	=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*)); 
	CProfileState*	p_c_etyProfileState		=	static_cast<CProfileState*>(p_c_etyDialogManager->get_ParentGameState());

	CDialog* p_c_etyDialogTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu");
	sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
	c_sfIntRectSubRect.left = 0;
	c_sfIntRectSubRect.top = *static_cast<int*>(va_getArgument(va_ALParameter, void*)); ;
	p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);
	va_CloseArgumentList(va_ALParameter);

	p_c_etyProfileState->set_UpdateMouseHoverEvent(true);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_cancelNewProfile					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);

    CDialogManager* p_c_etyDialogManager	=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*)); 
	va_CloseArgumentList(va_ALParameter);

	//An diese Stelle wird gesprungen, wenn bei der Eingabe eines neuen Profils die Escape-Taste gedrückt wurde
	//Die Profilaktionsbuttons werden wieder aktiviert
	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileNewButton");
	p_c_etyButtonMenuTmpPointer->set_Active(true);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileDeleteButton");
	p_c_etyButtonMenuTmpPointer->set_Active(true);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileBackButton");
	p_c_etyButtonMenuTmpPointer->set_Active(true);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileSaveButton");
	p_c_etyButtonMenuTmpPointer->set_Active(true);

	//Das EditControl ausgebelendet
	CEditControl* p_c_etyEditControlNewProfile = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CEditControl*>("ProfileNewProfileEditControl");
	p_c_etyEditControlNewProfile->set_Visibility(false);


	//Und der Standardtext des EditControls wieder auf den Standardmäßigen gesetzt
	ety::CLua* const p_c_luaScript = p_c_etyDialogManager->get_LuaScript();
	p_c_luaScript->init_Lua();

	p_c_luaScript->start_Script("Initialisation/Gamestates/Language.lua");

	p_c_etyEditControlNewProfile->set_EditControlContent(p_c_luaScript->get_TableString("ProfileNewProfileEditControl",p_c_etyDialogManager->get_Language()));
	p_c_luaScript->close_Lua();	

	//Der neu angelegte ListEntry wird wieder gelöscht und die ListBox wieder aktiviert
	CComboBox* p_c_etyComboBoxProfiles = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CComboBox*>("ProfileListBox");
	p_c_etyComboBoxProfiles->delete_ListEntry(0);
	p_c_etyComboBoxProfiles->set_Active(true);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_confirmNewProfile					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	CProfileState* p_c_etyProfileState = static_cast<CProfileState*>(p_c_etyDialogManager->get_ParentGameState());

	//Wenn die Return-Taste, also Enter gedrückt wurde und das Profile-Eingabe-EditControl gefocused war, wird an diese Stelle gesprungen
	//Im Folgendem wird verwaltet, was passiert wenn der Name für ein neues Profil bestätigt wurde oder die Änderung eines bestehenden!

	//Als erstes verliert das EditControl den Focus, da es nicht mehr gebraucht wird und später eh ausgeblendet wird
	p_c_etyDialogManager->change_FocusedDialogitem(NULL);

	//Anlegen für Pointer auf die ListBox und das EditControl, damit auf beide Klassen richtig zugegriffen werden kann
	CComboBox* p_c_etyComboBoxProfiles = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CComboBox*>("ProfileListBox");
	CEditControl* p_c_etyEditControlProfileInput = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CEditControl*>("ProfileNewProfileEditControl");

	const std::string strNewProfile	= p_c_etyEditControlProfileInput->get_EditControlContent();
	p_c_etyProfileState->get_Profilemanager().create_T( strNewProfile );
	p_c_etyComboBoxProfiles->get_ListEntryButton(0)->get_CaptionLabel()->set_Content( strNewProfile );
					

	//Die Profilaktionsbuttons werden wieder aktiviert
	CButton* p_c_etyButtonTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileNewButton");
	p_c_etyButtonTmp->set_Active(true);
	p_c_etyButtonTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileDeleteButton");
	p_c_etyButtonTmp->set_Active(true);
	p_c_etyButtonTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileBackButton");
	p_c_etyButtonTmp->set_Active(true);
	p_c_etyButtonTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileSaveButton");
	p_c_etyButtonTmp->set_Active(true);

	//Die ListBox wird wieder aktiviert
	p_c_etyComboBoxProfiles->set_Active(true);
	p_c_etyComboBoxProfiles->get_ListEntryButton(0)->set_Visibility(true);
	p_c_etyEditControlProfileInput->set_Visibility(false);


	//Und der Standardtext des EditControls wieder auf den Standardmäßigen gesetzt
	ety::CLua* const p_c_luaScript = p_c_etyDialogManager->get_LuaScript();
	p_c_luaScript->init_Lua();

	p_c_luaScript->start_Script("Initialisation/Gamestates/Language.lua");

	p_c_etyEditControlProfileInput->set_EditControlContent( p_c_luaScript->get_TableString( "ProfileNewProfileEditControl", p_c_etyDialogManager->get_Language() ) );
				
	p_c_luaScript->close_Lua();	
	
	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_deleteProfile						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	//Beim Drücken des Löschenbuttons wird noch abgefragt, ob das Profil wirklich gelöscht werden soll, da mit ihm auch seine gespeicherten Spieltstände
	//verloren gehen, wenn bejaht wurde, wird das Profil gelöscht
	CDialog* p_c_etyDialogTmp = p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu");
	sf::IntRect c_sfIntRectSubRect = p_c_etyDialogTmp->get_SubRect();
	c_sfIntRectSubRect.left = 0;
	c_sfIntRectSubRect.top = 0;
	p_c_etyDialogTmp->set_SubRect(c_sfIntRectSubRect,true);

	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Visibility(true);
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileDeleteMenu")->set_Modal(true,sf::Vector3f(0.75f,0.75f,0.75f));
	sf::Event sfEventDisplayFix;
	sfEventDisplayFix.type = sfEventDisplayFix.MouseMoved;
	p_c_etyDialogManager->get_ParentGameState()->handle_GameStateEvents(sfEventDisplayFix);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_exitProfileMenu					( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->popback_GameState();

	return ety::GameStateRunning::enFALSE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_newProfile						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	//Wenn der NewProfileButton gedrückt wurde wird das EditControl zur Eingabe eines neuen Profils am Anfang der ListBox angezeigt
	//Es wird ein neuer ListEntry für das neue Profil angelegt
	CComboBox* p_c_etyComboBoxProfiles = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CComboBox*>("ProfileListBox");
	p_c_etyComboBoxProfiles->add_ListEntry("",0);
	p_c_etyComboBoxProfiles->get_ListEntryButton(0)->set_Visibility(false);

	//Sichtbarmachung des EditControls
	CEditControl* p_c_etyEditControlNewProfile = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CEditControl*>("ProfileNewProfileEditControl");
	p_c_etyEditControlNewProfile->set_Visibility(true);

	//Die Profilaktionsbuttons werden deaktiviert
	CButton* p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileNewButton");
	p_c_etyButtonMenuTmpPointer->set_Active(false);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileDeleteButton");
	p_c_etyButtonMenuTmpPointer->set_Active(false);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileBackButton");
	p_c_etyButtonMenuTmpPointer->set_Active(false);
	p_c_etyButtonMenuTmpPointer = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CButton*>("ProfileSaveButton");
	p_c_etyButtonMenuTmpPointer->set_Active(false);

	//Sowie die ListBox, damit während der Eingabe keine Änderung an ihn durch den Benutzer vorgenommen werden können
	p_c_etyComboBoxProfiles->set_Active(false);

	return ety::GameStateRunning::enTRUE;
}
ety::GameStateRunning::en_etyGameStateRunning						ety::CProfileState::event_saveProfiles						( int iAmount, ... )
{
	va_ArgumentList va_ALParameter;
    va_OpenArgumentList(va_ALParameter, iAmount);
	CDialogManager* p_c_etyDialogManager = static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));
	va_CloseArgumentList(va_ALParameter);

	CGameStateManager* p_c_etyGameStateManager = static_cast<CGameStateManager*>(p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager());
	CProfileState* p_c_etyProfileState = static_cast<CProfileState*>(p_c_etyDialogManager->get_ParentGameState());

	CComboBox* p_c_etyComboBoxProfiles = p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CComboBox*>("ProfileListBox");

	p_c_etyProfileState->set_SelectedProfile(p_c_etyProfileState->get_Profilemanager().get_T( p_c_etyComboBoxProfiles->get_ListEntryButton(p_c_etyComboBoxProfiles->get_CurrentSelectedEntrie())->get_CaptionLabel()->get_Content()));
	
	p_c_etyDialogManager->get_DialogbyCustomID("ProfileMenu")->get_DialogitemByCustomID<ety::CLabel*>("SelectedProfileLabel")->set_Content(p_c_etyProfileState->get_SelectedProfile()->get_Filename());

	CLabel* p_c_etyProfileLabel = p_c_etyGameStateManager->get_GamestateByGamestateName<CMenuState>("MenuState")->get_DialogManager()->get_DialogbyCustomID("MainMenuBackground")->get_DialogitemByCustomID<CLabel*>("SelectedProfileLabel");
	p_c_etyProfileLabel->set_Content( p_c_etyProfileState->get_SelectedProfile()->get_Filename() );

	CButton* p_c_etyStartButton = p_c_etyGameStateManager->get_GamestateByGamestateName<CMenuState>("MenuState")->get_DialogManager()->get_DialogbyCustomID("MainMenuPad")->get_DialogitemByCustomID<CButton*>("PadStartButton");
			
	p_c_etyGameStateManager->m_c_etyAttributes.change_Attribute<CETYProfile>("p_c_etyCurrentProfile", p_c_etyProfileState->get_SelectedProfile(), false );

	p_c_etyStartButton->set_Active( true );
	p_c_etyStartButton->get_CaptionLabel()->set_Textcolor( ety::Color( 63.75f, 63.75f, 63.75f ) );
	
	return ety::GameStateRunning::enTRUE;
}