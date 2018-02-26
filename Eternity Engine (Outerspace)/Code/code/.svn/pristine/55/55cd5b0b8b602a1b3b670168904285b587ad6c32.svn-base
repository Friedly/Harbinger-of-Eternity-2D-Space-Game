//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CEternityEngine.cpp														   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse wird zum initialisieren aller wichtigen Daten benötigt, sie ist der Motor des Programms.					   ///////////
///////////			Alle Verbindungen zu den wichtigen Klassen werden hier gesetzt und wichtige Methoden wie das Aktualisieren,				   ///////////
///////////			Zeichnen und die Abfrage von Eingaben bzw. Events.																		   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Includes der Eternity-Engine
#include "CEternityEngine.hpp"
#include "CLua.hpp"
#include "CApplication.hpp"
#include "CRessourceManager.hpp"
#include "CGamesettings.hpp"
#include "CGameStateManager.hpp"



//Initialisierung der Vergbindung zwischen den wichtigen Klassen.
										ety::CEternityEngine::CEternityEngine				( ety::CApplication& c_etyNewApplication, ety::CGamesettings& c_etyNewGamesettings, ety::CRessourceManager& c_etyNewRessourcemManager, ety::CGameStateManager& c_etyNewGameStateManager   )
											:	m_bEngineInitialised		( false )
											,	mp_c_etyApplication			( &c_etyNewApplication )
											,	mp_c_etyGamesettings		( &c_etyNewGamesettings )
											,	mp_c_etyRessourceManager	( &c_etyNewRessourcemManager )
											,	mp_c_etyGameStatemanager	( &c_etyNewGameStateManager )
{
	mp_c_etyGamesettings		->set_Application		( mp_c_etyApplication		);
	mp_c_etyGamesettings		->set_RessourceManager	( mp_c_etyRessourceManager	);
	mp_c_etyGameStatemanager	->set_Gamesettings		( mp_c_etyGamesettings		);
	mp_c_etyGameStatemanager	->set_RessourceManager	( mp_c_etyRessourceManager	);
}
										ety::CEternityEngine::~CEternityEngine				( void )
{
}

//Diese Methode aktualisiert die aktuelle Eingabe und gibt sie dem Gamestatemanager weiter.
//Dieser wiederum gibt es den aktiven Spielzuständen damit sie auf die aktuelle Eingabe reagieren können.
		void							ety::CEternityEngine::handle_Events					( void )
{
	//Diese IF-Abfrage hat den Grund, wenn man im Ladebalken ist und dieser schon fertig ist mit Laden
	//wird ein Event ausgelöst das zum geladenen Spielzustand führt.
	//Die Funktion von SFML zum Abfragen der Eingaben "poll_Event" blockt gibt niemals
	//true zurück wenn kein Event statt findet, das heißt man müsse eine Eingabe tätigen
	//oder die Maus bewegen um in den nächsten Spielzustand zu gelangen.
	//Deswegen verfälscht diese If-Abfrage ein Event, damit nicht der Gedanke kommt
	//Das Spiel würde sich aufgehangen haben.
	ety::CGameState* p_c_etyTempGameState = mp_c_etyGameStatemanager->get_CurrentGameState();
	if( p_c_etyTempGameState != NULL  )
	{
		if( p_c_etyTempGameState->get_GameStateName() == "LoadingState" )
		{
			sf::Event c_sfFixEvent;
			c_sfFixEvent.type = sf::Event::JoystickDisconnected;
			mp_c_etyGameStatemanager->handle_CurrentGameStateEvents( c_sfFixEvent );
		}
	}
	p_c_etyTempGameState = NULL;

	sf::Event c_sfCurrentEvent;

	//Abfrage ob ein Event stattfand.
	while( mp_c_etyApplication->poll_Event( c_sfCurrentEvent ) )
	{
		//Im Vollbildmodus konnte man auf seinen zweiten Bildschirm wechseln
		//dies musste manuell behoben werden. Dann gab es Probleme, wenn man 
		//aus dem Vollbildmodus auf den Desktop wechselte, dass man seinen Mauszeiger
		//nicht frei bewegen konnte. Dies wird damit behoben, es wird überprüft
		//ob das Fenster im Fokus liegt oder nicht. Je nach dem reagiert die Maus anders.
		if( c_sfCurrentEvent.type == sf::Event::LostFocus )
		{
			ety::CMouse::set_WindowFocus( false );
		}
		else if( c_sfCurrentEvent.type == sf::Event::GainedFocus )
		{
			ety::CMouse::set_WindowFocus( true );
		}

		//Wenn das X im Fenster gedrückt wurde oder kein Spielzustand mehr aktiv ist.
		//Die Methode handle_CurrentGameStateEvents(..) verwaltet die aktuelle Eingabe für jeden
		//aktiven Spielzustand spezifisch.
		if( mp_c_etyGameStatemanager->handle_CurrentGameStateEvents( c_sfCurrentEvent ) == false || c_sfCurrentEvent.type == sf::Event::Closed )
		{
			//Fenster schließen.
			mp_c_etyApplication->close_Application();

			//Event-Schleife verlassen.
			break;
		}
		
		//Die Anzahl der Bilder in der Sekunde anzeigen an-/ausschalten.
		if( c_sfCurrentEvent.type == sf::Event::KeyReleased && c_sfCurrentEvent.key.code == sf::Keyboard::F1 )
		{
			mp_c_etyApplication->show_FramesPerSecond( !mp_c_etyApplication->get_ShowFramesPerSecond() );
		}
	}
}

//Diese Methode aktualisiert alle Spielzustände und deren Objekte.
		void							ety::CEternityEngine::update_Engine					( void )
{
	//Die Zeit für ein Bild wird dem aktuellen Spielzustand gegeben um die aktuelle Szene zu aktualisieren.
	//Das beinhaltet Physik, alle Objekte oder Spezial-Effekte, darunter auch Animationen etc.
	mp_c_etyGameStatemanager->update_CurrentGameStates( mp_c_etyApplication->get_Frametime() );
	
	//Diese Methode berechnet nur die Bilder in der Sekunde.
	mp_c_etyApplication->update_Application();
}

//Diese Methode zeichnet alle relevanten Objekte.
		void							ety::CEternityEngine::render_Engine					( void )
{
	//Alle relevanten Objekte werden in die Render Textur gezeichnet,
	//sie dient als Zwischenspeicher, diese Funktion zeichnet nichts in das Fenster.
	//Dadurch das in das Fenster zeichnen viel Leistung benötigt wird der Zwischenspeicher
	//benutzt um es zu drosseln. Lieber ein einziges Bild zeichnen in dem nur das gezeichnet
	//wird, was man auch wirklich sieht, als 100 Bilder die einzelnt vollständig gezeichnet werden,
	//obwohl sie sie warscheinlich auch überlappen. Somit werden weniger Pixel gezeichnet.
	mp_c_etyGameStatemanager->render_CurrentGameStates( mp_c_etyApplication->get_RenderTextureGameScene() );

	//Zeichnet den Zwischenspeicher auf den Bildschirm.
	mp_c_etyApplication->draw_CurrentScene();
}

//Initialisiert das Fenster und übernimmt somit alle Spieleinstellungen.
const	bool							ety::CEternityEngine::init_Engine					( void )
{	
	//Initialisieren von LUA und LUABIND.
	CLua c_etyLuaScript;
	c_etyLuaScript.init_Lua();

	//Registriere die Klassen mit Hilfe von LUABIND.
	//Diese Klassen können dann im Script benutzt werden.
	ety::CRessourceManager	::register_ClassToLuabind( &c_etyLuaScript );
	ety::CFilemanagement	::register_ClassToLuabind( &c_etyLuaScript );

	//An LUA die gewünschten Objecte zum bearbeiten weiter geben.
	luabind::globals( c_etyLuaScript.get_LuaState() )["c_etyRessourceManager"	]	= mp_c_etyRessourceManager;
	luabind::globals( c_etyLuaScript.get_LuaState() )["c_etyFilemanager"		]	= mp_c_etyGameStatemanager->get_Filemanagement();

	//Starten des LUA-Scriptes.
	c_etyLuaScript.start_Script( "Initialisation/Gamestates/RessourceManagement.lua" );

	//Schließen von LUA.
	c_etyLuaScript.close_Lua();

	//Konnte das Fenster mit allen Einstellungen erstellt werden ist die Engine initialisiert.
	if( mp_c_etyGamesettings->apply_Settings() == true )
	{
		//Die Engine ist initialisiert.
		m_bEngineInitialised = true;

		return true;
	}

	//Das Fenster konnte nicht erstellt werden.
	return false;
}

//Wurde die Engine initialisiert, so wird diese Methode die Hauptschleife des Spiels starten.
//Diese verwaltet in jedem Durchlauf die aktualisierungen der Eingabe und Objekte und zeichnet alles Relevante.
const	bool							ety::CEternityEngine::start_Engine					( void )
{
	//Ist die Engine initialisiert?
	if( m_bEngineInitialised == true )
	{
		//Die Hauptschleife läuft solange, bis das Fenster durch eine Eingabe-Event geschlossen wurde.
		while( mp_c_etyApplication->check_ApplicationIsOpen() )
		{
			//Das aktuelle Event wird ausgewertet.
			handle_Events();	

			//Aktualisierung aller relevanten Dinge für die aktuelle Szene.
			update_Engine();

			//Das Zeichnen der aktuellen Szene.
			render_Engine();

			//Um den CPU nicht zu sehr zu belasten.
			sf::sleep( sf::milliseconds(1) );
		}

		//Das Fenster wurde ordentlich geschlossen.
		return true;
	}

	//Die Engine wurde noch nicht initialisiert.
	return false;
}
