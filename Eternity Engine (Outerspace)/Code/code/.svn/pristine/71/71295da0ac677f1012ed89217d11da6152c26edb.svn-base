//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CRessourceManager.hpp													   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse dient als Verwaltung von Texturen und Schriftarten. Mithilfe dieser Verwaltung können sie geladen             ///////////
///////////			und gespeichert werden. Sie hält sie im Arbeitsspeicher um sie für Objekte weiter verwenden zu können,					   ///////////
///////////			deswegen kann man Texturen und Schriftarten von dieser Klasse anfordern.												   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CLua.hpp"

//Includes der SFML-Bibliothek
#include <sfml\Graphics\Texture.hpp>
#include <sfml\Graphics\Font.hpp>
#include <sfml\Audio\Listener.hpp>
#include <sfml\Audio\Music.hpp>
#include <sfml\Audio\Sound.hpp>
#include <sfml\Audio\SoundBuffer.hpp>

//Includes des Compilers
#include <map>
#include <vector>

namespace ety
{
	namespace RessourceType
	{
		enum en_etyRessourceType	{ enTEXTURE, enFONT, enSOUND, enMUSIC, enSOUNDBUFFER, enERROR };
	}

	namespace VolumeType
	{
		enum en_etyVolumeType		{ enMASTERVOLUME, enMUSICVOLUME, enSOUNDVOLUME, enERROR	};
	}

	namespace DeleteType
	{
		enum en_etyDeleteType		{ enSINGLE, enALL, enERROR };
	}

	class CRessourceManager : private sf::NonCopyable
	{
	private:
					//Die Lautstärken für die Audiodateien
					unsigned short								m_usMastervolume;
					unsigned short								m_usMusicvolume;
					unsigned short								m_usSoundvolume;

					//Diese Maps beinhaltet alle Ressourcen und diese sind jeweils 
					//mit ihren Namen als String-Schlüssel ansprechbar.
					std::map< std::string, sf::Texture		>	m_mapTexturesbyString;
					std::map< std::string, sf::Font			>	m_mapFontsbyString;
					std::map< std::string, sf::SoundBuffer	>	m_mapSoundbufferbyString;
					std::map< std::string, sf::Music*		>	m_mapMusicbyString;
					std::map< std::string, sf::Sound*		>	m_mapSoundsbyString;

					//Diese zwei Vektoren speichern Pfade als String, diese werden zum Laden
					//der Dateien benötigt.
					std::vector< std::string >					m_vectorTextureDirectories;
					std::vector< std::string >					m_vectorFontDirectories;
					std::vector< std::string >					m_vectorMusicDirectories;
					std::vector< std::string >					m_vectorSoundDirectories;


		const		bool										load_Texture				( const std::string& strTexturename		, const std::string& strDirectoryKey = "NULL" );
		const		bool										load_Font					( const std::string& strFontname		, const std::string& strDirectoryKey = "NULL" );
		const		bool										load_Music					( const std::string& strMusicname		, const std::string& strDirectoryKey = "NULL" );
		const		bool										load_Soundbuffer			( const std::string& strSoundbuffername	, const std::string& strDirectoryKey = "NULL" );

	protected:
					//Klasse wird nicht abgeleitet.

	public:
					//Standart Konstruktor und Destruktor
																CRessourceManager			( void );
																~CRessourceManager			( void );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode übernimmt eine gewünschte Lautstärke.
					///
					/// 1P. Die zu übernehmende Lautstärke, diese muss sich zwischen 0-100 bewegen.
					///
					/// \parameter	const unsigned short
					/// \rückgabe	void
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					void										apply_Volume				( const unsigned short usVolume, ety::VolumeType::en_etyVolumeType en_etyVolumeType );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode fügt ein Datei-Pfad für eine Ressource hinzu.
					///
					/// 1P. Der Pfad in dem sich Dateien befinden.
					///
					/// \parameter	const std::string&
					/// \rückgabe	void
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					void										add_Directory				( const std::string& strRessourceDirectory, ety::RessourceType::en_etyRessourceType en_etyRessourceType );
					
		const		bool										load_Ressource				( const std::string& strRessourceName, ety::RessourceType::en_etyRessourceType en_etyRessourceType, const std::string& strDirectoryKey = "NULL" );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Registriert diese Klasse zum Lua-Script.
					///
					///	1P. Das Lua-Script.
					///
					/// \parameter	ety::CLua* const
					/// \rückgabe	void
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static		void										register_ClassToLuabind		( ety::CLua* const p_c_etyLuaScript );


		const		bool										remove_Ressource			( ety::RessourceType::en_etyRessourceType en_etyRessourceType, ety::DeleteType::en_etyDeleteType en_etyDeleteType, const std::string& strRessourceName = "NULL" );

		const		bool										remove_Directory			( const std::string& strDirectoryName, ety::RessourceType::en_etyRessourceType en_etyRessourceType );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode gibt eine Font zurück mit dem übergebenen Fontnamen.
					///
					/// 1P. Der Name der Font.
					///
					/// \parameter	const std::string&
					/// \rückgabe	const sf::Font&
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const		sf::Font&									get_Font				( const std::string& strFontname );
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode gibt eine Textur zurück mit dem übergebenen Texturnamen.
					///
					/// 1P. Der Name der Textur.
					///
					/// \parameter	const std::string&
					/// \rückgabe	const sf::Texture&
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const		sf::Texture&								get_Texture				( const std::string& strTexturename );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode gibt ein Musikstück zurück mit dem übergebenden Musiknamen.
					///
					/// 1P. Der Name des Musikstückes.
					///
					/// \parameter	const std::string&
					/// \rückgabe	const sf::Music&
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					sf::Music*			const					get_Music				( const std::string& strMusicname );
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode gibt ein Soundstück zurück mit dem übergebenden Soundnamen, dadurch dass ein Zeiger
					///	auf eine Sounddatei zurückgegeben wird, kann diese Sounddatei nur einmal zur gleichen Zeit gespielt werden.
					///	Anwendungsbeispiel: Buttons ( Dort will man nicht jeden Klick hören! )
					///
					/// 1P. Der Name des Soundstückes.
					///
					/// \parameter	const std::string&
					/// \rückgabe	sf::Sound* const
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					sf::Sound*			const					get_Sound				( const std::string& strSoundname );
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					///	Diese Methode gibt ein Soundbuffer zurück mit dem übergebenen Soundbuffer namen, mit dieser Methode
					///	ist es Möglich mehrere Soundstücke zu erstellen und gleichzeitig abzuspielen.
					///	Anwendungsbeispiel: Raumschiffe ( Dort will man jeden Schuss hören! )
					///
					/// 1P. Der Name des Soundbuffer.
					///
					/// \parameter	const std::string&
					/// \rückgabe	const sf::SoundBuffer&
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const		sf::SoundBuffer&							get_Soundbuffer			( const std::string& strSoundbuffername );
	};			
}

