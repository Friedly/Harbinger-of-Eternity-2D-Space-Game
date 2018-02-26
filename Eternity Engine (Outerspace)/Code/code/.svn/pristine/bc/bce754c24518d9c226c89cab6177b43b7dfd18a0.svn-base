#pragma once

#include "CDialogGameState.hpp"
#include "CIniLoader.hpp"

namespace ety
{
	class CProfileState : public CDialogGameState
	{
	private:

				bool														m_bEditProfilEntry;
		//Event-Variablen
				bool														m_bUpdateMouseHoverEvents;

				ety::CETYProfile*											mp_c_etySelectedProfile;

				ety::CIniLoader<CETYProfile>								m_c_etyProfilemanager;

	protected:

	public:
																			CProfileState							( const std::string& strStateName );
																			~CProfileState							( void );

				void														on_Enter								( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
				void														on_Exit									( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void														init_GameState							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, 
																														ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		const	ety::GameStateRunning::en_etyGameStateRunning				handle_GameStateEvents					( const sf::Event& sfEventLastEvent  );	


				void														set_SelectedProfile						( ety::CETYProfile* p_c_etyProfile );
				void														set_UpdateMouseHoverEvent				( bool bMouseHoverEvent );

				ety::CETYProfile*	const									get_SelectedProfile						( void );
				ety::CIniLoader<CETYProfile>&								get_Profilemanager						( void );


		static	ety::GameStateRunning::en_etyGameStateRunning				event_applyDeleteProfile				( int iAmount, ... );	
		static	ety::GameStateRunning::en_etyGameStateRunning				event_cancelDeleteProfile				( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_deleteProfileButtonHover			( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_cancelNewProfile					( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_confirmNewProfile					( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_deleteProfile						( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_exitProfileMenu					( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_newProfile						( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning				event_saveProfiles						( int iAmount, ... );
	};
}

