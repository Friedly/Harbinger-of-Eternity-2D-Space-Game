//Eternity-Engine Includes
#include "CEternityEngine.hpp"
#include "CIntroState.hpp"
#include "CMenuState.hpp"
#include "CProfileState.hpp"
#include "COptionState.hpp"
#include "CCreditsState.hpp"
#include "CAudioOptionState.hpp"
#include "CGraphicOptionState.hpp"
#include "CSpaceStationState.hpp"
#include "CSpaceStationHangarState.hpp"
#include "CIngameState.hpp"
#include "CApplication.hpp"
#include "CRessourceManager.hpp"
#include "CGamesettings.hpp"
#include "CGameStateManager.hpp"

int main()
{
	//Erstellung aller nötigen Objekte, welche die Eternity-Engine braucht.
	//1. Audiomanager um die Audiodateien verwalten und Lautstärke zu regeln.
	//2. Graphicmanager um die Texturen und Fonts zu verwalten.
	//3. Gamestatemanager verwaltet die Spielzustände.
	//4. Application stellt das Fenster dar, wird zum übernehmen von Einstellungen gebraucht.
	//5. Gamesettings speichert alle Einstellungen zum Spiel
	//	 und über diese Instanz werden die Einstellungen für das Fenster und für die Lautstärke übernommen.
	ety::CRessourceManager	c_etyRessourceManager;
	ety::CGameStateManager	c_etyGameStateManager;
	ety::CApplication		c_etyApplication		( "Outerspace", "Media/Textures/Icon/Outerspace.png" );
	ety::CGamesettings		c_etyGamesettings		( "Initialisation/Gamesettings.ini" );

	//Dem Gamestatemanager die einzelnen Spielzustände hinzufügen, damit dieser diese Verwalten kann.
	//c_etyGameStateManager	.add_GameState( new ety::CIntroState				( "IntroState"				) );
	c_etyGameStateManager.add_GameState( new ety::CMenuState				( "MenuState"				) );
	c_etyGameStateManager.add_GameState( new ety::COptionState				( "OptionState"				) );
	c_etyGameStateManager.add_GameState( new ety::CAudioOptionState			( "AudioOptionState"		) );
	c_etyGameStateManager.add_GameState( new ety::CGraphicOptionState		( "GraphicOptionState"		) );
	c_etyGameStateManager.add_GameState( new ety::CProfileState				( "ProfileState"			) );
	c_etyGameStateManager.add_GameState( new ety::CCreditsState				( "CreditsState"			) );
	c_etyGameStateManager.add_GameState( new ety::CIngameState				( "IngameState"				) );
	c_etyGameStateManager.add_GameState( new ety::CSpaceStationHangarState	( "SpaceStationHangarState"	) );
	c_etyGameStateManager.add_GameState( new ety::CSpaceStationState		( "SpaceStationState"		) );
	
	//Es wird ein Objekt der Eternity-Engine erstellt.
	ety::CEternityEngine c_etyEternityEngine( c_etyApplication, c_etyGamesettings, c_etyRessourceManager, c_etyGameStateManager );

	//Die Eternity-Engine wird mit den vorher definierten Informationen initialisiert,
	//diese Funktion läd die Einstellungen und übernimmt diese, mit Überprüfung ob diese gültig sind, für die Applikation.
	//Wenn die Engine initialisiert werden konnte...
	if( c_etyEternityEngine.init_Engine() )
	{	
		//Hier wird der erste Spielzustand in die Liste geschoben.
		c_etyGameStateManager.pushback_GameState( "MenuState" );

		//Starten der Engine, diese Methode führt zu einer sogenannten Spielschleife, diese wiederholt sich
		//bis das Spiel beendet worden ist.
		 if( c_etyEternityEngine.start_Engine() == false )
		 {
			 //Beim ausführen des Programmes ist ein Fehler aufgetreten.
			 return false;
		 }
	}
	else
	{
		//Programm hatte beim initialisieren Probleme.
		return false;
	}

	//Programm konnte ohne Probleme beendet werden.
	return true;
}
