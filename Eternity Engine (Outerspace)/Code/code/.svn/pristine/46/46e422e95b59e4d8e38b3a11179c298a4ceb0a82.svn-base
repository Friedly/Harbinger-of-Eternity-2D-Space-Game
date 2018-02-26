#pragma once

#include "CDialogGameState.hpp"

#include "CIniLoader.hpp"

namespace ety
{
	namespace PadModus
	{
		enum														en_etyPadModus					{ enHANGAR, enSHOP, enMISSION, enLOGBOOK };
	}

	class CSpaceStationState : public CDialogGameState
	{
	private:

				bool												m_bUpdateMouseHoverEvents;

				PadModus::en_etyPadModus							m_en_etyPadModus;

	protected:

	public:
																	CSpaceStationState			( const std::string& strStateName );
																	~CSpaceStationState			( void );

				void												on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
				void												on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void												init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void												update_GameState			( const sf::Uint32& uiFrameTime );

				void												render_GameState			( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		const	ety::GameStateRunning::en_etyGameStateRunning		handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );


				void												set_UpdateMouseHoverEvent	( bool bMouseHoverEvent );
				void												set_PadModus				( enum ety::PadModus::en_etyPadModus en_etyPadModus );


		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitGame				( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_enterHangar			( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_cancelExitGame		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitButtonHover		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openMissionMenu		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPad				( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPadHangar			( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPadShop			( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPadMission		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPadLogbook		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_openPadBack			( int iAmount, ... );

	};
}

