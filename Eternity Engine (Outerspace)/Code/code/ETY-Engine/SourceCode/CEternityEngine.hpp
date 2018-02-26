//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CEternityEngine.hpp														   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse wird zum initialisieren aller wichtigen Daten benötigt, sie ist der Motor des Programms.					   ///////////
///////////			Alle Verbindungen zu den wichtigen Klassen werden hier gesetzt und wichtige Methoden wie das Aktualisieren,				   ///////////
///////////			Zeichnen und die Abfrage von Eingaben bzw. Events.																		   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <sfml\System\NonCopyable.hpp>

namespace ety
{
	class CApplication;
	class CRessourceManager;
	class CGamesettings;
	class CGameStateManager;

	class CEternityEngine : private sf::NonCopyable
	{
	private:
						//Diese Variable speichert, ob die Engine initialisiert worden ist.
						bool								m_bEngineInitialised;

						//Objekte zur Verwaltung von Grafiken, Audiodateien,
						//Spieleinstellungen, Spielzuständen und dem Fenster.
						ety::CRessourceManager*				mp_c_etyRessourceManager;
						ety::CApplication*					mp_c_etyApplication;
						ety::CGamesettings*					mp_c_etyGamesettings;
						ety::CGameStateManager*				mp_c_etyGameStatemanager;

	private:
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// \Beschreibung: 
						///	Diese Methode aktualisiert die aktuelle Eingabe und gibt sie dem Gamestatemanager weiter.
						/// Dieser wiederum gibt es den aktiven Spielzuständen damit sie auf die aktuelle Eingabe reagieren können.
						///
						/// \parameter	void
						/// \rückgabe	void
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void								handle_Events				( void );

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// \Beschreibung: 
						///	Diese Methode aktualisiert alle Spielzustände und deren Objekte.
						///
						/// \parameter	void
						/// \rückgabe	void
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void								update_Engine				( void );

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// \Beschreibung: 
						///	Diese Methode zeichnet alle relevanten Objekte.
						///
						/// \parameter	void
						/// \rückgabe	void
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						void								render_Engine				( void );

	public:
						//Initialisierung der Verbindung zwischen den wichtigen Klassen.
															CEternityEngine				( ety::CApplication& c_etyNewApplication, ety::CGamesettings& c_etyNewGamesettings, ety::CRessourceManager& c_etyNewAudiomanager, ety::CGameStateManager& c_etyNewGameStateManager   );
															~CEternityEngine			( void );

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// \Beschreibung: 
						///	Initialisiert das Fenster und übernimmt somit alle Spieleinstellungen.
						///
						/// \parameter	void
						/// \rückgabe	const bool
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				const	bool								init_Engine					( void );
		
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						/// \Beschreibung: 
						///	Wurde die Engine initialisiert, so wird diese Methode die Hauptschleife des Spiels starten.
						/// Diese verwaltet in jedem Durchlauf die aktualisierungen der Eingabe und Objekte und zeichnet alles Relevante.
						///
						/// \parameter	void
						/// \rückgabe	const bool
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				const	bool								start_Engine				( void );
	};
}

