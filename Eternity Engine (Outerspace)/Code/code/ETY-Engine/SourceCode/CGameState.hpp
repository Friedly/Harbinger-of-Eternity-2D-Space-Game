//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CGameState.hpp															   ///////////
///////////																									                                   ///////////
///////////						Die Basisklasse eines Spielzustandes. Um ein Spielzustand zu erstellen muss man von ihr ableiten.			   ///////////
///////////						Alle wichtigen Methoden sind virtual deklariert und m�ssen �berschrieben werden.							   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CGamesettings.hpp"
#include "CRessourceManager.hpp"
#include "CFilemanagement.hpp"
#include "CLua.hpp"

//Includes der SFML-Bibliothek
#include <SFML\Graphics.hpp>

//Includes des Compilers
#include <list>

namespace ety
{
	//Vordeklarationen der Klassen, es verhindert mehrfaches Einbinden.
	class CGameStateManager;
	
	//Enum f�r den Status, welchen der Gamestate annehmen kann.
	namespace GamestateStatus
	{
		enum						en_etyGamestateStatus				{ enIDLE, enACTIVE, enBACKGROUND, enLOADING };
	}
	//Enum f�r die aktivit�t des Gamestates.
	namespace GameStateRunning
	{
		enum						en_etyGameStateRunning				{ enFALSE, enTRUE };
	}

	class CGameState
	{
	private:

	protected:
		friend					ety::CGameStateManager;

								//Der Name dieses Spielzustandes
					const		std::string														m_strGameStateName;

								//Gibt den aktuellen Status des Spielzustandes an, je nach Status gib es bei der Ausf�hrung des Spielzustandes beschr�nkungen.
								ety::GamestateStatus::en_etyGamestateStatus						m_en_etyGameStateStatus;

								//Dieser Zeiger verweist auf den GameStateManager der diesen Spielzustand verwaltet.
								ety::CGameStateManager*											mp_c_etyGameStatemanager;

	public:
								//Der Konstruktor initialisiert den Spielzustand mit seinem Namen.
																								CGameState						( const std::string& strStateName );
								//Virtueller Destruktor weil diese Klasse als Basisklasse f�r viele Spielzust�nde dient.
		virtual																					~CGameState						( void );

		virtual					void															on_Enter						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager ) = 0;
		virtual					void															on_Exit							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager ) = 0;


								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Verwaltet alle Events des Spielzustandes.
								///
								///	1P.
								///	2P.
								///
								/// \parameter	const sf::Event& sfEventLastEvent, CDialogitem*
								/// \r�ckgabe	const ety::GameStateRunning::en_etyGameStateRunning
								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual		const		ety::GameStateRunning::en_etyGameStateRunning					handle_GameStateEvents			( const sf::Event& sfEventLastEvent )			= 0;
		

								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Initialisierung des Spielzustandes. Objekte, Dialoge und zum Beispiel Variablen werden initialisiert.
								///
								///	1P.	Der aktuelle Audiomanager.
								///	2P.	Der aktuelle Graphicmanager.
								///	3P.	Die aktuellen Spieleinstellungen.
								///
								/// \parameter	ety::CAudiomanager* const, ety::CGraphicmanager* const, ety::CGamesettings* const
								/// \r�ckgabe	void
								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual					void															init_GameState					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Zeichnet die aktuelle Szene des Spielzustandes in den Zwischenspeicher.
								///
								///	1P.	Der Zwischenspeicher.
								///
								/// \parameter	sf::RenderTexture* const
								/// \r�ckgabe	void
								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual					void															render_GameState				( sf::RenderTexture* const p_c_sfRenderTextureGameScene ) = 0;

		virtual					void															reinit_Gamestate				( const sf::VideoMode& c_sfNewVideoMode, const bool bFullscreen ) = 0;
		virtual					void															reinit_Gamestate				( const std::string strNewLanguage ) = 0;

								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Aktualisiert den Spielzustand.
								///
								///	1P.	Die vergangene Zeit nach einer gezeichneter Szene.
								///
								/// \parameter	const sf::Uint32&
								/// \r�ckgabe	void
								///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual					void															update_GameState				( const sf::Uint32& uiFrameTime ) = 0;
		
								//Die Set-Methoden zum setzen privater Membervariablen.
								void															set_GameStatemanager			( ety::CGameStateManager* const p_c_etyGameStatemanager);
								void															set_GameStateStatus				( const ety::GamestateStatus::en_etyGamestateStatus en_etyGamestateStatus );


								//Die Get-Methoden zur R�ckgabe von privaten Membervariablen.
					const		std::string&													get_GameStateName				( void );
					const		ety::GamestateStatus::en_etyGamestateStatus						get_GameStateStatus				( void );
								ety::CGameStateManager*								const		get_GameStatemanager			( void );
	};
}

