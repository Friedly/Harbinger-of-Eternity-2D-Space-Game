#pragma once

//Eternity-Engine Includes
#include "CDialogGameState.hpp"


namespace ety
{
	

	class CMenuState : public CDialogGameState
	{
	private:

		//Event-Variablen
		bool														m_bUpdateMouseHoverEvents;
		bool														m_bColorfilterChanged;
		std::string													m_strModificatedButtonID;

	protected:
		//Wird nicht abgeleitet.

	public:
		//Überladener Konstruktor, welcher nen Zeiger auf den Statemanager setzt.
																	CMenuState					( const std::string& strStateName );
		//Default Destruktor.
																	~CMenuState					( void );

		void														on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
		void														on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		//Funktionen, welche Ressourcen initialisieren und ihn wieder freigeben,
		//sowie z.B alle Objekte aktualisieren und zeichnen.
		void														init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		void														update_GameState			( const sf::Uint32& uiFrameTime );

		const ety::GameStateRunning::en_etyGameStateRunning			handle_GameStateEvents		( const sf::Event& sfEventLastEvent  );


		void														set_UpdateMouseHoverEvent	( bool bMouseHoverEvent );
		void														set_ColorfilterChanged		( bool bColorfilterChanged );
		void														set_ModificatedButtonID		( std::string strButtonID );

		bool														get_UpdateMouseHoverEvent	( void );
		bool														get_ColorfilterChanged		( void );
		std::string													get_ModificatedButtonID		( void );


		static	ety::GameStateRunning::en_etyGameStateRunning		event_startGame				( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_enterOptionsMenu		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_enterProfileMenu		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_enterCreditsMenu		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitGame				( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_cancelExitGame		( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_PadStartButtonHover	( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_PadOptionsButtonHover	( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_PadProfileButtonHover	( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_PadCreditsButtonHover	( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_PadExitButtonHover	( int iAmount, ... );
		static	ety::GameStateRunning::en_etyGameStateRunning		event_exitButtonHover		( int iAmount, ... );
	};
}