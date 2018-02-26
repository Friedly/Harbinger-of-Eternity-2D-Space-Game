#pragma once

#include "CDialogGameState.hpp"

namespace ety
{
	class CCreditsState : public CDialogGameState
	{
	private:

	protected:

	public:
																	CCreditsState				( const std::string& strStateName );
																	~CCreditsState				( void );

		void														on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		const ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );
	};
}

