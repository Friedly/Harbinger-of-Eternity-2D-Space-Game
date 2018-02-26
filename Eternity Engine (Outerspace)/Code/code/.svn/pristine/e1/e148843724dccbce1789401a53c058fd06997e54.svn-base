#pragma once

#include "CDialogGameState.hpp"

#include "CWorld.hpp"

namespace ety
{
	class CUserInterface;

	class CIngameState : public CDialogGameState
	{
	private:
	protected:
		bool														m_bGamePaused;
		CUserInterface*												mp_c_etyUserInterface;

	public:
																	CIngameState				( void );
																	CIngameState				( const std::string& strStateName );
																	~CIngameState				( void );

		void														on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														update_GameState			( const sf::Uint32& uiFrameTime );

		void														render_GameState			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		void														set_GamePaused				( const bool& bGamePaused );

		ety::CUserInterface* const									get_UserInterface			( void );	


		const ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );

		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitIngame			( int iAmount, ... );
	};
}

