//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																															   ///////////
///////////														CMouse.hpp															   ///////////
///////////																									                           ///////////
///////////			Diese Klasse dient als Erweiterung zur Klasse sf::Mouse, welche ebenso nur aus static Methoden besteht.            ///////////
///////////			Die Erweiterungen bestehen aus einem sf::Sprite(Bild) um den Mauszeiger für das Spiel zu ändern.				   ///////////
///////////			Ebenso wird in Vollbildmodus nicht mehr möglich sein, wenn man einen anderen Bildschirm angeschlossen hat,	       ///////////
///////////         die Maus auf den anderen Bildschirm zu bewegen, diese Störung wird behoben.							               ///////////
///////////																									                           ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Includes der SFML-Bibliothek
#include <SFML\Graphics.hpp>

namespace ety
{
	class CMouse
	{
	private:
		//Das aktuelle Fenster wird mit diesem Zeiger auf sf::RenderTexture gespeichert.
		//Mit Hilfe diesem Zeiger ist es möglich die Position des Mauszeigers in Bezug auf
		//das Fenstern zu bestimmen.
		static			sf::RenderWindow*	mp_c_sfRenderWindow;

		//Das sf::Sprite(Bild) wir benötigt um den Windows-Mauszeiger zu ersetzen.
		static			sf::Sprite			m_c_SpriteCustomCursor;

		//Um die Erweiterung, der Mauszeiger darf das Fenster im Vollbildmodus nicht verlassen,
		//zu ermöglichen, muss diese Klasse wissen, ob das Fenster sich gerade im Vollbildmodus befindet.
		static			bool				m_bFullscreen;
		//Diese Bool-Variable wird benötigt um zu wissen, ob das Fenster sich im Fokus befindet.
		//Ist das zum Beispiel im Vollbildmodus und ist nicht im Fokus( ALT+TAB ), kann man den
		//Mauszeiger frei bewegen.
		static			bool				m_bWindowFocus;

	public:
		//Standard Konstruktor und Destruktor.
											CMouse					( void );
											~CMouse					( void );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode wird benötigt um das Bild des Mauszeigers zu skalieren.
		///	Mit Hilfe dieser Methode wird das Bild des Mauzeigers für jede Auflösung des Spiels
		///	angepasst.
		///
		/// 1P. Die Angabe der Skalierung der Breite.
		///	2P. Die Angabe der Skalierung der Höhe.
		///
		/// \parameter	const float, const float
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				scale_Size				( const float fScaleX, const float fScaleY );

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode setzt ein Bild fest anstelle des Windows-Mauszeigers.
		///
		/// 1P. Die Textur bzw. das Bild für den Mauszeiger.
		///
		/// \parameter	const sf::Texture&
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				set_CustomCursorSprite	( const sf::Texture& c_sfTextureCustomCursor, const bool bCenter );
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode setzt das aktuelle Fenster fest.
		///
		/// 1P. Das aktuelle Fenster wird hier benötigt.
		///
		/// \parameter	sf::RenderTexture* const
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				set_RenderWindow		( sf::RenderWindow* const p_c_sfRenderWindowStandard );
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode legt fest, ob das Fenster im Vollbildmodus ist.
		///
		/// 1P. Das aktuelle Fenster wird hier benötigt.
		///
		/// \parameter	const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				set_Fullscreen			( const bool bFullscreen );
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode setzt die Position des Mauszeigers.
		///
		/// 1P. Die neue Position des Mauszeigers als integer Vector der SFML.
		///
		/// \parameter	const sf::Vector2i&
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				set_Position			( const sf::Vector2i& c_sfVectorMousePosition );
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode legt fest, ob das Fenster im Fokus liegt.
		///
		/// 1P. Ist das Fenster gerade im Fokus?
		///
		/// \parameter	const bool
		/// \rückgabe	void
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static			void				set_WindowFocus			( const bool bWindowFocus );
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode gibt die aktuelle Position des Mauszeigers zurück.
		///
		/// \parameter	void
		/// \rückgabe	const sf::Vector2i
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static	const	sf::Vector2i		get_Position			( void );
		static  const	sf::Vector2i		get_Position			( const sf::View& c_sfView );
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese statische Methode gibt das Bild des Mauszeigers zurück.
		///	Sie wird gebraucht um den neuen Mauszeiger zu zeichnen,
		///	wenn der Windows-Mauszeiger ausgeschaltet ist.
		///
		/// \parameter	void
		/// \rückgabe	const sf::Sprite&
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static	const	sf::Sprite&			get_CustomCursorSprite	( void );
	};

}