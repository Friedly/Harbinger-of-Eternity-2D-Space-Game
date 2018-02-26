//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CApplication.hpp														   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse dient zum initialisieren und erstellen des Fensters. 														   ///////////
///////////			Berechnung der Bilder pro Sekunde und das Zeichnen der gesamten Szene werden in dieser Klasse abgedeckt.				   ///////////
///////////																									                                   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Includes der Eternity-Engine
#include "CGamesettings.hpp"
#include "CMouse.hpp"

//Includes der SFML-Bibliothek
#include <SFML\Graphics.hpp>

namespace ety
{
	class CGamesettings;

	class CApplication : private sf::NonCopyable
	{
	private:
		//Die Information ob die Bilder in der Sekunde angezeigt werden sollen.
		bool						m_bShowFramesPerSecond;
		//Die Information ob der Windows-Mauszeiger angezeigt werden sollen.
		bool						m_bShowWindowsCursor;

		//Sie addiert die vergangene Zeit nach jedem gezeichneten Bild.
		//Nach einer bestimmten Zeit wird sie wieder auf 0.f gesetzt und die
		//Bilder in der Sekunde werden aktualisiert.
		double						m_dFramesPerSecondTimer;

		//Der Titel des Fensters.
		const std::string			m_strApplicationTitle;

		//Das Fenster in dem alles gezeichnet wird.
		sf::RenderWindow			m_c_sfRenderWindowApplication;

		//Der Zwischenspeicher der aktuellen Szene.
		sf::RenderTexture			m_c_sfRenderTextureGameScene;

		//Die Bilder in der Sekunde als Text zum anzeigen.
		sf::Text					m_c_sfTextFramesPerSecond;

		//Die Uhr zum bemessen der Zeit nach jedem Bild.
		sf::Clock					m_c_sfClockFrametime;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode berechnet in gewissen Zeitabständen die Bilder in der Sekunde.
		///
		/// \parameter	void
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						calculate_FramesPerSecond		( void );

	protected:

	public:
		//Konstruktor der den Titel des Fensters initialisiert und der standart Destruktor.
									CApplication					( const std::string strApplicationTitle );
									CApplication					( const std::string strApplicationTitle, const std::string strApplicationIcon );
									~CApplication					( void );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Die Methode überprüft, ob das Fenster noch offen ist.
		///
		/// \parameter	void
		/// \rückgabe	const bool
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const bool					check_ApplicationIsOpen			( void );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode schließt das Fenster.
		///
		/// \parameter	void
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						close_Application				( void );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode erstellt ein Fenster.
		///
		///	1P. Die gewünschte Auflösung.
		/// 2P. Vollbildmodus an/aus.
		///
		/// \parameter	const sf::VideoMode&, const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						create_RenderWindow				( const sf::VideoMode& c_sfVideomode, const bool bFullscreenStatus );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Mehode zeichnet die aktuelle Szene.
		///
		/// \parameter	void
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						draw_CurrentScene				( void );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode schaltet die vertikale Synchronisation an/aus.
		///
		/// 1P. Vertikale Synchronisation an/aus.
		///
		/// \parameter	const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						enable_VerticalSync				( const bool bEnableVerticalSync );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Mit dieser Methode schaltet die Anzeige der Bilder in der Sekunde an/aus.
		///
		/// 1P. Anzeiger der Bilder in der Sekune an/aus.
		///
		/// \parameter	const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						show_FramesPerSecond			( const bool bShowFramesPerSecond );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode schaltet den Windows-Mauszeiger an/aus.
		///
		/// 1P. Windows-Mauzeiger an/aus.
		///
		/// \parameter	const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						show_WindowsMouseCursor			( const bool bShowWindowsMouseCursor );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Methode speichert das aktuellste Event in den übergebenen Parameter.
		///
		/// 1P. Variable zum speichern des aktuellsten Events.
		///
		/// \parameter	sf::Event&
		/// \rückgabe	const bool
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const bool					poll_Event						( sf::Event& c_sfCurrentEvent );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Aktualisiert das Fenster.
		///
		/// \parameter	void
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void						update_Application				( void );

		//Die Set-Methoden zum setzen privater Membervariablen.
		void						set_FramerateLimit				( const unsigned short usFramesPerSecondLimit );

		void						set_Icon						( const std::string& strIconTextureDirectory );

		//Die Get-Methoden zur Rückgabe von privaten Membervariablen.
		const bool					get_ShowFramesPerSecond			( void );
		const std::string&			get_ApplicationTitle			( void );
		const sf::Uint32			get_Frametime					( void );
		sf::RenderTexture*	const	get_RenderTextureGameScene		( void );
	};
}
