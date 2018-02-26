#pragma once

#include "CDialogGameState.hpp"


namespace ety
{
	class CGraphicOptionState : public CDialogGameState
	{
	private:
		ety::CGamesettings*											mp_c_ActualGamesettingsManager;

	public:
																	CGraphicOptionState					( const std::string& strStateName );
																	~CGraphicOptionState				( void );

		void														on_Enter							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		//Funktionen, welche Ressourcen initialisieren und ihn wieder freigeben,
		//sowie z.B alle Objekte aktualisieren und zeichnen.
		void														init_GameState						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		const ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents				( const sf::Event& sfEventLastEvent  );
			
		ety::CGamesettings* const									get_GamesettingsManager				( void );

		static ety::GameStateRunning::en_etyGameStateRunning		event_applyGraphicOptions			( int iAmount, ... );
		static ety::GameStateRunning::en_etyGameStateRunning		event_exitGraphicOptionsMenu		( int iAmount, ... );

	};
}

