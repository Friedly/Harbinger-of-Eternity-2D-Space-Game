#pragma once

#include "CDialogGameState.hpp"


namespace ety
{
	class CIntroState : public CDialogGameState
	{
	private:

	protected:

	public:
																	CIntroState					( const std::string& strStateName );
																	~CIntroState				( void );

		void														on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														cleanup_GameState			( void );

		const ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );
	};
}

