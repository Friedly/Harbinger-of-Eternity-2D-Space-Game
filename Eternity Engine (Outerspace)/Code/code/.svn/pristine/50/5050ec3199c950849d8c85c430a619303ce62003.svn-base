#include "CIntroState.hpp"
#include "CGameStateManager.hpp"

#include "CDialogitem.hpp"
															ety::CIntroState::CIntroState				( const std::string& strStateName )
																: CDialogGameState( strStateName )
{
}
															ety::CIntroState::~CIntroState				( void )
{
}

void														ety::CIntroState::on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
}
void														ety::CIntroState::on_Exit					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
}

void														ety::CIntroState::init_GameState			( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
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
}


const ety::GameStateRunning::en_etyGameStateRunning			ety::CIntroState::handle_GameStateEvents	( const sf::Event& sfEventLastEvent  )
{
	/*if( sfEventLastEvent.type == sf::Event::KeyReleased && sfEventLastEvent.key.code == sf::Keyboard::Escape )
	{
		mp_c_etyGameStatemanager->pushback_GameState( "MenuState" );

		return ety::GameStateRunning::enFALSE;
	}
	else if( sfEventLastEvent.type == sf::Event::MouseButtonReleased && sfEventLastEvent.mouseButton.button == sf::Mouse::Left && p_c_etyDialogitemEventDialogitem != NULL )
	{
		p_c_etyDialogitemEventDialogitem->set_EventDialogitem(false);
	}*/

	return ety::GameStateRunning::enTRUE;
}

