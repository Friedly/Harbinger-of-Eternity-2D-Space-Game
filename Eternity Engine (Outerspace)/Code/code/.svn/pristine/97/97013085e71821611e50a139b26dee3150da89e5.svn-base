#pragma once

//Eternity-Engine Includes
#include "CDialogGameState.hpp"


namespace ety
{
	class COptionState : public CDialogGameState
	{
	private:
		ety::CGamesettings* mp_c_ActualGamesettingsManager;

		std::string			m_strTempLanguage;

	protected:

	public:
																	COptionState				( const std::string& strStateName );

																	~COptionState				( void );

		void														on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		const	ety::GameStateRunning::en_etyGameStateRunning		handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );

		void														set_TempLanguage			( std::string strTempLanguage );

		const std::string&											get_TempLanguage			( void );
		ety::CGamesettings*	const									get_GamesettingsManager		( void );

		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitOptionsMenu		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_changeGameState		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_changeLanguage		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_changeTempLanguage	( int iAmount, ... );
	};
}

