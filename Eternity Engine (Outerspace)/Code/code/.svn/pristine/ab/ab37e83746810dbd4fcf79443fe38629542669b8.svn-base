//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CRessourceManager.cpp														   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse dient als Verwaltung von Texturen und Schriftarten. Mithilfe dieser Verwaltung können sie geladen             ///////////
///////////			und gespeichert werden. Sie hält sie im Arbeitsspeicher um sie für Objekte weiter verwenden zu können,					   ///////////
///////////			deswegen kann man Texturen und Schriftarten von dieser Klasse anfordern.												   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Includes der Eternity-Engine
#include "CRessourceManager.hpp"
#include "CLogfile.hpp"
#include <iostream>

		//Standart Konstruktor und Destruktor
										ety::CRessourceManager::CRessourceManager		( void )
		{
			//Diese Einträge werden gebraucht, wenn ein Benutzer eine Ressource anfordert
			//die es nicht gibt, so bekommt er eine leere Ressource zurück um Abstürze zu
			//vermeiden.
			m_mapTexturesbyString		["EMPTY"]	=	sf::Texture();
			m_mapFontsbyString			["EMPTY"]	=	sf::Font::getDefaultFont();
			m_mapSoundbufferbyString	["EMPTY"]	=	sf::SoundBuffer();
			m_mapMusicbyString			["EMPTY"]	=	new sf::Music();
			m_mapSoundsbyString			["EMPTY"]	=	new sf::Sound();
		}
										ety::CRessourceManager::~CRessourceManager		( void )
		{
			remove_Ressource( ety::RessourceType::enSOUND, ety::DeleteType::enALL );
			remove_Ressource( ety::RessourceType::enMUSIC, ety::DeleteType::enALL );
		}

		//Diese Methode übernimmt eine gewünschte Lautstärke.
		void							ety::CRessourceManager::apply_Volume			( const unsigned short usVolume, ety::VolumeType::en_etyVolumeType en_etyVolumeType )
		{
			if( usVolume >= 0 && usVolume <= 100 )
			{
				switch( en_etyVolumeType )
				{
				case ety::VolumeType::enMASTERVOLUME	:			// Setzt die globale Lautstärke auf die übergebene Lautstärke

					m_usMastervolume = usVolume;
					sf::Listener::setGlobalVolume( usVolume );
					break;

				case ety::VolumeType::enMUSICVOLUME		:			// Setzt die Lautstärke aller Musikdateien auf die übergebene Lautstärke.

					m_usMusicvolume = usVolume;
					for( std::map< std::string, sf::Music* >::iterator itMusicbyString = m_mapMusicbyString.begin(); itMusicbyString != m_mapMusicbyString.end(); itMusicbyString++ )
					{
						itMusicbyString->second->setVolume( usVolume );
					}
					break;

				case ety::VolumeType::enSOUNDVOLUME		:			//Setzt die Lautstärke aller Sounddateien auf die übergebene Lautstärke.

					m_usSoundvolume = usVolume;
					for( std::map< std::string, sf::Sound* >::iterator itSoundbyString = m_mapSoundsbyString.begin(); itSoundbyString != m_mapSoundsbyString.end(); itSoundbyString++ )
					{
						itSoundbyString->second->setVolume( usVolume );
					}
					break;
				}
			}
		}

		//Diese Methode fügt ein Datei-Pfad für Ressourcen hinzu.
		void							ety::CRessourceManager::add_Directory			( const std::string& strRessourceDirectory, ety::RessourceType::en_etyRessourceType en_etyRessourceType )
		{
			std::vector<std::string>::iterator	itRessourceDirectory;
			std::vector<std::string>*			p_vectorRessourceDirectories = NULL;
			
			//Den gewünschten Ressourcen-Container raussuchen. 
			switch( en_etyRessourceType )
			{
			case ety::RessourceType::enTEXTURE		:

				p_vectorRessourceDirectories = &m_vectorTextureDirectories;
				break;

			case ety::RessourceType::enFONT			:

				p_vectorRessourceDirectories = &m_vectorFontDirectories;
				break;

			case ety::RessourceType::enMUSIC		:

				p_vectorRessourceDirectories = &m_vectorMusicDirectories;
				break;

			case ety::RessourceType::enSOUNDBUFFER	:

				p_vectorRessourceDirectories = &m_vectorSoundDirectories;
				break;
			}

			//Durchsucht den Container ob dieser Pfad schon existiert.
			for( std::vector<std::string>::iterator itRessourceDirectory = p_vectorRessourceDirectories->begin(); itRessourceDirectory != p_vectorRessourceDirectories->end(); itRessourceDirectory++ )
			{
				//Wenn der Pfad schon existiert wird die Methode abgebrochen.
				if( (*itRessourceDirectory) == strRessourceDirectory )
				{
					return ;
				}
			}

			std::cout << "Directory added: " << strRessourceDirectory << std::endl;

			//Der Pfad existiert nicht, so wird dieser hinzugefügt.
			p_vectorRessourceDirectories->push_back( strRessourceDirectory );
		}

const	bool							ety::CRessourceManager::load_Texture			( const std::string& strTexturename, const std::string& strDirectoryKey )
		{
			if( m_mapTexturesbyString.find( strTexturename ) != m_mapTexturesbyString.end() )
			{
				//Diese Textur wurde schon geladen!
				return true;
			}

			sf::Texture c_sfTexture;

			//Wenn strDirectoryKey == NULL ist, will der Benutzer keinen Ordner-Schlüssel benutzen
			//und dieser Abschnitt wird übersprungen.
			if( strDirectoryKey != "NULL" )
			{
				//Es werden alle gespeicherten Pfade durchgegangen und werden auf den Ordner-Schlüssel untersucht.
				for( std::vector<std::string>::iterator itTextureDirectory = m_vectorTextureDirectories.begin(); itTextureDirectory != m_vectorTextureDirectories.end(); itTextureDirectory++ )
				{
					//Wenn der Ordner-Schlüssel im Pfad gefunden wurde, wird die Anfangsposition des Ordner-Schlüssel im Pfad gespeichert.
					//Diese Anfangsposition ist < 0 wenn der Ordner-Schlüssel nicht gefunden wurde, aber >= 0 wenn dieser gefunden wurde.
					if( int( ( *itTextureDirectory ).find( strDirectoryKey ) ) >= 0 )
					{
						//Die Textur wird nun durch den gefundenen Pfad geladen.
						if( c_sfTexture.loadFromFile( (*itTextureDirectory) + strTexturename ) == true )
						{
							//Die | 255, 0, 255 | farbigen Pixel im Bild werden ausgeblendet.
							//c_sfTexture.copyToImage().createMaskFromColor( sf::Color( 255, 0, 255 ) );

							//Textur wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
							m_mapTexturesbyString[strTexturename] = c_sfTexture;

							std::cout << "Texture loaded: " << strTexturename << std::endl;

							//Textur konnte geladen werden.
							return true;
						}
					}
				}
			}

			//Dieser Teil lädt einfach eine Textur im Ordner in der die Exe steht.
			if( c_sfTexture.loadFromFile(strTexturename) == true )
			{
				//Die | 255, 0, 255 | farbigen Pixel im Bild werden ausgeblendet.
				//c_sfTexture.copyToImage().createMaskFromColor( sf::Color( 255, 0, 255, 0 ) );

				//Textur wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
				m_mapTexturesbyString[strTexturename] = c_sfTexture;

				std::cout << "Texture loaded: " << strTexturename << std::endl;

				//Textur konnte geladen werden.
				return true;
			}

			//Es werden alle gespeicherten Pfade durchgegangen um die Textur zu finden, die geladen werden muss.
			for( std::vector<std::string>::iterator itTextureDirectory = m_vectorTextureDirectories.begin(); itTextureDirectory != m_vectorTextureDirectories.end(); itTextureDirectory++ )
			{
				//Die Textur wird nun durch einen Pfade geladen.
				if( c_sfTexture.loadFromFile( (*itTextureDirectory) + strTexturename ) == true )
				{
					//Farbe RGB( 255 , 0 , 255 ) -> Lila ausblenden.
					//c_sfTexture.copyToImage().createMaskFromColor( sf::Color( 255, 0, 255 ) );

					//Textur wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
					m_mapTexturesbyString[strTexturename] = c_sfTexture;

					std::cout << "Texture loaded: " << strTexturename << std::endl;

					//Textur konnte geladen werden.
					return true;
				}
			}

			//Textur konnte nicht geladen werden.
			return false;
		}
const	bool							ety::CRessourceManager::load_Font				( const std::string& strFontname, const std::string& strDirectoryKey )
		{
			if( m_mapFontsbyString.find( strFontname ) != m_mapFontsbyString.end() )
			{
				//Diese Textur wurde schon geladen!
				return true;
			}

			sf::Font c_sfFont;

			//Wenn strDirectoryKey == NULL ist, will der Benutzer keinen Ordner-Schlüssel benutzen
			//und dieser Abschnitt wird übersprungen.
			if( strDirectoryKey != "NULL" )
			{
				//Es werden alle gespeicherten Pfade durchgegangen und werden auf den Ordner-Schlüssel untersucht.
				for( std::vector<std::string>::iterator itFontDirectory = m_vectorFontDirectories.begin(); itFontDirectory != m_vectorFontDirectories.end(); itFontDirectory++ )
				{
					//Wenn der Ordner-Schlüssel im Pfad gefunden wurde, wird die Anfangsposition des Ordner-Schlüssel im Pfad gespeichert.
					//Diese Anfangsposition ist < 0 wenn der Ordner-Schlüssel nicht gefunden wurde, aber >= 0 wenn dieser gefunden wurde.
					if( int( ( *itFontDirectory ).find( strDirectoryKey ) ) >= 0 )
					{
						//Die Font wird nun durch den gefundenen Pfad geladen.
						if( c_sfFont.loadFromFile( (*itFontDirectory) + strFontname ) == true )
						{
							//Font wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
							m_mapFontsbyString[strFontname] = c_sfFont;

							//Font konnte geladen werden.
							return true;
						}
					}
				}
			}

			//Dieser Teil lädt einfach eine Font im Ordner in der die Exe steht.
			if( c_sfFont.loadFromFile(strFontname) == true )
			{
				//Font wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
				m_mapFontsbyString[strFontname] = c_sfFont;

				//Font konnte geladen werden.
				return true;
			}

			//Es werden alle gespeicherten Pfade durchgegangen um die Font zu finden, die geladen werden muss.
			for( std::vector<std::string>::iterator itFontDirectory = m_vectorFontDirectories.begin(); itFontDirectory != m_vectorFontDirectories.end(); itFontDirectory++ )
			{
				//Die Font wird nun durch einen Pfade geladen.
				if( c_sfFont.loadFromFile( (*itFontDirectory) + strFontname ) == true )
				{
					//Font wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
					m_mapFontsbyString[strFontname] = c_sfFont;

					//Font konnte geladen werden.
					return true;
				}
			}

			//Font konnte nicht geladen werden.
			return false;
		}
const	bool							ety::CRessourceManager::load_Music				( const std::string& strMusicname, const std::string& strDirectoryKey )
		{
			if( m_mapMusicbyString.find( strMusicname ) != m_mapMusicbyString.end() )
			{
				//Diese Audiodatei wurde schon geladen!
				return true;
			}

			sf::Music* p_c_sfMusic = new sf::Music();

			//Wenn strDirectoryKey == NULL ist, will der Benutzer keinen Ordner-Schlüssel benutzen
			//und dieser Abschnitt wird übersprungen.
			if( strDirectoryKey != "NULL" )
			{
				//Es werden alle gespeicherten Pfade durchgegangen und werden auf den Ordner-Schlüssel untersucht.
				for( std::vector<std::string>::const_iterator itMusicDirectory = m_vectorMusicDirectories.begin(); itMusicDirectory != m_vectorMusicDirectories.end(); itMusicDirectory++ )
				{
					//Wenn der Ordner-Schlüssel im Pfad gefunden wurde, wird die Anfangsposition des Ordner-Schlüssel im Pfad gespeichert.
					//Diese Anfangsposition ist < 0 wenn der Ordner-Schlüssel nicht gefunden wurde, aber >= 0 wenn dieser gefunden wurde.
					if( int( ( *itMusicDirectory ).find( strDirectoryKey ) ) >= 0 )
					{
						//Die Audiodatei wird nun durch den gefundenen Pfad geladen.
						if( p_c_sfMusic->openFromFile( (*itMusicDirectory) + strMusicname ) == true )
						{
							//Die Lautstärke der neuen Audiodatei wird auf die aktuelle Lautstärke aktualisiert.
							p_c_sfMusic->setVolume( m_usMusicvolume );

							//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
							m_mapMusicbyString[strMusicname] = p_c_sfMusic;

							//Musikstück konnte geladen werden.
							return true;
						}
					}
				}
			}

			//Dieser Teil lädt einfach ein Musikstück im Ordner in der die Exe steht.
			if( p_c_sfMusic->openFromFile(strMusicname) == true )
			{
				//Die Lautstärke der neuen Audiodatei wird auf die aktuelle Lautstärke aktualisiert.
				p_c_sfMusic->setVolume( m_usMusicvolume );

				//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
				m_mapMusicbyString[strMusicname] = p_c_sfMusic;

				//Musikstück konnte geladen werden.
				return true;
			}

	
			//Es werden alle gespeicherten Pfade durchgegangen um die Audiodatei zu finden, die geladen werden muss.
			for( std::vector<std::string>::const_iterator itMusicDirectory = m_vectorMusicDirectories.begin(); itMusicDirectory != m_vectorMusicDirectories.end(); itMusicDirectory++ )
			{
				//Die Audiodatei wird nun durch einen Pfade geladen.
				if( p_c_sfMusic->openFromFile( (*itMusicDirectory) + strMusicname ) == true )
				{
					//Die Lautstärke der neuen Audiodatei wird auf die aktuelle Lautstärke aktualisiert.
					p_c_sfMusic->setVolume( m_usMusicvolume );

					//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
					m_mapMusicbyString[strMusicname] = p_c_sfMusic;

					//Musikstück konnte geladen werden.
					return true;
				}
			}

			//Speicher wieder freigeben, den wir für eine potentielle neue Audiodatei reserviert hatten.
			delete p_c_sfMusic;
	
			//Audiodatei konnte nicht geladen werden.
			return false;
		}
const	bool							ety::CRessourceManager::load_Soundbuffer		( const std::string& strSoundbuffername, const std::string& strDirectoryKey )
		{
			if( m_mapSoundbufferbyString.find( strSoundbuffername ) != m_mapSoundbufferbyString.end() )
			{
				//Diese Audiodatei wurde schon geladen!
				return true;
			}

			sf::SoundBuffer c_sfSoundbuffer;

			//Wenn strDirectoryKey == NULL ist, will der Benutzer keinen Ordner-Schlüssel benutzen
			//und dieser Abschnitt wird übersprungen.
			if( strDirectoryKey != "NULL" )
			{
				//Es werden alle gespeicherten Pfade durchgegangen und werden auf den Ordner-Schlüssel untersucht.
				for( std::vector<std::string>::iterator itSoundDirectory = m_vectorSoundDirectories.begin(); itSoundDirectory != m_vectorSoundDirectories.end(); itSoundDirectory++ )
				{
					//Wenn der Ordner-Schlüssel im Pfad gefunden wurde, wird die Anfangsposition des Ordner-Schlüssel im Pfad gespeichert.
					//Diese Anfangsposition ist < 0 wenn der Ordner-Schlüssel nicht gefunden wurde, aber >= 0 wenn dieser gefunden wurde.
					if( int( ( *itSoundDirectory ).find( strDirectoryKey ) ) >= 0 )
					{
						//Die Audiodatei wird nun durch den gefundenen Pfad geladen.
						if( c_sfSoundbuffer.loadFromFile( ( *itSoundDirectory ) + strSoundbuffername ) == true )
						{
							//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
							m_mapSoundbufferbyString[strSoundbuffername] = c_sfSoundbuffer;

							//Musikstück konnte geladen werden.
							return true;
						}
					}
				}
			}

			//Dieser Teil lädt einfach ein Musikstück im Ordner in der die Exe steht.
			if( c_sfSoundbuffer.loadFromFile( strSoundbuffername ) == true )
			{
				//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
				m_mapSoundbufferbyString[strSoundbuffername] = c_sfSoundbuffer;

				//Musikstück konnte geladen werden.
				return true;
			}

			//Es werden alle gespeicherten Pfade durchgegangen um die Audiodatei zu finden, welche geladen werden muss.
			for( std::vector<std::string>::iterator itSoundDirectory = m_vectorSoundDirectories.begin(); itSoundDirectory != m_vectorSoundDirectories.end(); itSoundDirectory++ )
			{
				//Die Audiodatei wird nun durch einen Pfade geladen.
				if( c_sfSoundbuffer.loadFromFile( (*itSoundDirectory) + strSoundbuffername ) == true )
				{
					//Audiodatei wird in die Map hinzugefügt und somit gespeichert zum weiterverwenden.
					m_mapSoundbufferbyString[strSoundbuffername] = c_sfSoundbuffer;

					//Musikstück konnte geladen werden.
					return true;
				}
			}

			//Musikstück konnte nicht geladen werden.
			return false;
		}

const	bool							ety::CRessourceManager::load_Ressource			( const std::string& strRessourceName, ety::RessourceType::en_etyRessourceType en_etyRessourceType, const std::string& strDirectoryKey )
		{
			switch( en_etyRessourceType )
			{
			case ety::RessourceType::enTEXTURE	:

				return load_Texture		( strRessourceName, strDirectoryKey );
				break;

			case ety::RessourceType::enFONT		:

				return load_Font		( strRessourceName, strDirectoryKey );
				break;

			case ety::RessourceType::enMUSIC	:

				return load_Music		( strRessourceName, strDirectoryKey );
				break;

			case ety::RessourceType::enSOUNDBUFFER	:

				return load_Soundbuffer	( strRessourceName, strDirectoryKey );
				break;
			}

			return false;
		}

		void							ety::CRessourceManager::register_ClassToLuabind	( ety::CLua* const p_c_etyLuaScript )
		{
			luabind::module(p_c_etyLuaScript->get_LuaState() )
			[ 
				luabind::class_< CRessourceManager >("CRessourceManager")
				.def( "get_Texture"			, &CRessourceManager::get_Texture		)
				.def( "get_Font"			, &CRessourceManager::get_Font			)
				.def( "get_Music"			, &CRessourceManager::get_Music			) 
				.def( "get_Sound"			, &CRessourceManager::get_Sound			)
				.def( "get_Soundbuffer"		, &CRessourceManager::get_Soundbuffer	)
				.def( "add_Directory"		, &CRessourceManager::add_Directory		)
			];
		}

const	bool							ety::CRessourceManager::remove_Ressource		( ety::RessourceType::en_etyRessourceType en_etyRessourceType, ety::DeleteType::en_etyDeleteType en_etyDeleteType, const std::string& strRessourceName )
		{
			if( en_etyRessourceType == ety::RessourceType::enTEXTURE )
			{
				if( en_etyDeleteType == ety::DeleteType::enSINGLE )
				{
					std::map< std::string, sf::Texture >::const_iterator itTexturebyString = m_mapTexturesbyString.find( strRessourceName );
					if( itTexturebyString != m_mapTexturesbyString.end() )
					{
						std::cout << "Deleted texture " << strRessourceName << "!" << std::endl;
						m_mapTexturesbyString.erase( itTexturebyString );
						return true;
					}
				}
				else
				{
					std::cout << "All textures deleted! " << std::endl;
					m_mapTexturesbyString.clear();
					return true;
				}
			}
			else if( en_etyRessourceType == ety::RessourceType::enFONT )
			{
				if( en_etyDeleteType == ety::DeleteType::enSINGLE )
				{
					std::map< std::string, sf::Font	>::const_iterator itFontbyString = m_mapFontsbyString.find( strRessourceName );
					if( itFontbyString != m_mapFontsbyString.end() )
					{
						std::cout << "Deleted font " << strRessourceName << "!" << std::endl;
						m_mapFontsbyString.erase( itFontbyString );
						return true;
					}
				}
				else
				{
					std::cout << "All fonts deleted! " << std::endl;
					m_mapFontsbyString.clear();
					return true;
				}
			}
			else if( en_etyRessourceType == ety::RessourceType::enMUSIC )
			{
				if( en_etyDeleteType == ety::DeleteType::enSINGLE )
				{
					std::map< std::string, sf::Music* >::const_iterator itMusicbyString = m_mapMusicbyString.find( strRessourceName );
					if( itMusicbyString != m_mapMusicbyString.end() )
					{
						delete itMusicbyString->second;
						std::cout << "Deleted music " << strRessourceName << "!" << std::endl;
						m_mapMusicbyString.erase( itMusicbyString );
						return true;
					}
				}
				else
				{
					for( std::map< std::string, sf::Music* >::const_iterator itMusicbyString = m_mapMusicbyString.begin(); itMusicbyString != m_mapMusicbyString.end(); itMusicbyString++ )
					{
						delete itMusicbyString->second;
					}
					std::cout << "All music deleted! " << std::endl;
					m_mapMusicbyString.clear();
				}
			}
			else if( en_etyRessourceType == ety::RessourceType::enSOUND )
			{
				if( en_etyDeleteType == ety::DeleteType::enSINGLE )
				{
					std::map< std::string, sf::Sound* >::const_iterator itSoundbyString = m_mapSoundsbyString.find( strRessourceName );
					if( itSoundbyString != m_mapSoundsbyString.end() )
					{
						delete itSoundbyString->second;
						std::cout << "Deleted sound " << strRessourceName << "!" << std::endl;
						m_mapSoundsbyString.erase( itSoundbyString );
						return true;
					}
				}
				else
				{
					for( std::map< std::string, sf::Sound* >::const_iterator itSoundbyString = m_mapSoundsbyString.begin(); itSoundbyString != m_mapSoundsbyString.end(); itSoundbyString++ )
					{
						delete itSoundbyString->second;
					}
					std::cout << "All sound deleted! " << std::endl;
					m_mapSoundsbyString.clear();
				}
			}
			else if( en_etyRessourceType == ety::RessourceType::enSOUNDBUFFER )
			{
				if( en_etyDeleteType == ety::DeleteType::enSINGLE )
				{
					std::map< std::string, sf::SoundBuffer >::const_iterator itSoundbufferbyString = m_mapSoundbufferbyString.find( strRessourceName );
					if( itSoundbufferbyString != m_mapSoundbufferbyString.end() )
					{
						remove_Ressource( ety::RessourceType::enSOUND, ety::DeleteType::enSINGLE, strRessourceName );
						std::cout << "Deleted soundbuffer " << strRessourceName << "!" << std::endl;
						m_mapSoundbufferbyString.erase( itSoundbufferbyString );
						return true;
					}
				}
				else
				{
					remove_Ressource( ety::RessourceType::enSOUND, ety::DeleteType::enALL );
					std::cout << "All soundbuffer deleted! " << std::endl;
					m_mapSoundbufferbyString.clear();
				}
			}

			return false;
		}

const	bool							ety::CRessourceManager::remove_Directory		( const std::string& strDirectoryName, ety::RessourceType::en_etyRessourceType en_etyRessourceType )
		{
			std::vector<std::string>::iterator	itRessourceDirectory;
			std::vector<std::string>*			p_vectorRessourceDirectories = NULL;

			//Den gewünschten Ressourcen-Container raussuchen. 
			switch( en_etyRessourceType )
			{
			case ety::RessourceType::enTEXTURE	:

				p_vectorRessourceDirectories = &m_vectorTextureDirectories;
				break;

			case ety::RessourceType::enFONT		:

				p_vectorRessourceDirectories = &m_vectorFontDirectories;
				break;

			case ety::RessourceType::enMUSIC	:

				p_vectorRessourceDirectories = &m_vectorMusicDirectories;
				break;

			case ety::RessourceType::enSOUND	:

				p_vectorRessourceDirectories = &m_vectorSoundDirectories;
				break;
			}

			//Durchsucht den Container ob dieser Pfad schon existiert.
			for( std::vector<std::string>::iterator itRessourceDirectory = p_vectorRessourceDirectories->begin(); itRessourceDirectory != p_vectorRessourceDirectories->end(); itRessourceDirectory++ )
			{
				//Wenn der Pfad schon existiert wird die Methode abgebrochen.
				if( (*itRessourceDirectory) == strDirectoryName )
				{
					p_vectorRessourceDirectories->erase( itRessourceDirectory );
					return true;
				}
			}

			return false;
		}

		//Diese Methode gibt ein Musikstück zurück mit dem übergebenden Musiknamen.
		sf::Music*			const		ety::CRessourceManager::get_Music				( const std::string& strMusicname )
		{
			//Die angeforderte Audiodatei wird gesucht.
			std::map< std::string, sf::Music* >::iterator itMusicbyString = m_mapMusicbyString.find( strMusicname );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itMusicbyString != m_mapMusicbyString.end() )
			{
				//Die angeforderte Audiodatei wird zurück gegeben.
				return itMusicbyString->second;
			}
	
			//Die angeforderte Audiodatei wurde nicht gefunden, so wird eine leere Audiodatei zurück gegeben.
			return m_mapMusicbyString["EMPTY"];
		}
		//Diese Methode gibt ein Soundstück zurück mit dem übergebenden Soundnamen, dadurch dass ein Zeiger
		//auf eine Sounddatei zurückgegeben wird, kann diese Sounddatei nur einmal zur gleichen Zeit gespielt werden.
		//Anwendungsbeispiel: Buttons ( Dort will man nicht jeden Klick hören! )
		sf::Sound*			const		ety::CRessourceManager::get_Sound				( const std::string& strSoundname )
		{
			//Die angeforderte Audiodatei wird gesucht.
			std::map<std::string, sf::Sound* >::iterator itSoundbyString = m_mapSoundsbyString.find( strSoundname );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itSoundbyString != m_mapSoundsbyString.end() )
			{
				//Die angeforderte Audiodatei wird zurück gegeben.
				return itSoundbyString->second;
			}

			//Die angeforderte Audiodatei wird gesucht.
			std::map< std::string, sf::SoundBuffer >::const_iterator itSoundbufferbyString = m_mapSoundbufferbyString.find( strSoundname );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itSoundbufferbyString != m_mapSoundbufferbyString.end() )
			{
				//Existiert ein Soundbuffer mit dem Namen der angeforderten Audiodatei,
				//wird ein neuer Sound angelegt.
				m_mapSoundsbyString[strSoundname] = new sf::Sound( itSoundbufferbyString->second );

				//Die Lautstärke wird auf die aktuelle aktualisiert.
				m_mapSoundsbyString[strSoundname]->setVolume( m_usSoundvolume );
		
				//Die angeforderte Audiodatei wird zurück gegeben.
				return m_mapSoundsbyString[strSoundname];
			}
	
			//Die angeforderte Audiodatei wurde nicht gefunden, so wird eine leere Audiodatei zurück gegeben.
			return m_mapSoundsbyString["EMPTY"];
		}
		//Diese Methode gibt ein Soundbuffer zurück mit dem übergebenen Soundbuffer namen, mit dieser Methode
		//ist es Möglich mehrere Soundstücke zu erstellen und gleichzeitig abzuspielen.
		//Anwendungsbeispiel: Raumschiffe ( Dort will man jeden Schuss hören! )
const	sf::SoundBuffer&				ety::CRessourceManager::get_Soundbuffer			( const std::string& strSoundbuffername )
		{
			//Die angeforderte Audiodatei wird gesucht.
			std::map< std::string, sf::SoundBuffer >::const_iterator itSoundbufferbyString = m_mapSoundbufferbyString.find( strSoundbuffername );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itSoundbufferbyString != m_mapSoundbufferbyString.end() )
			{
				//Die angeforderte Audiodatei wird zurück gegeben.
				return itSoundbufferbyString->second;
			}
	
			//Die angeforderte Audiodatei wurde nicht gefunden, so wird eine leere Audiodatei zurück gegeben.
			return m_mapSoundbufferbyString["EMPTY"];
		}
		//Diese Methode gibt eine Font zurück mit dem übergebenen Fontnamen.
const	sf::Font&						ety::CRessourceManager::get_Font				( const std::string& strFontname )
		{
			//Die angeforderte Font wird gesucht.
			std::map< std::string, sf::Font >::iterator itFontbyString = m_mapFontsbyString.find( strFontname );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itFontbyString != m_mapFontsbyString.end() )
			{
				//Die angeforderte Font wird zurück gegeben.
				return itFontbyString->second;
			}
	
			//Die angeforderte Font wurde nicht gefunden, so wird eine standart Font zurück gegeben.
			return sf::Font::getDefaultFont();
		}
		//Diese Methode gibt eine Textur zurück mit dem übergebenen Texturnamen.
const	sf::Texture&					ety::CRessourceManager::get_Texture				( const std::string& strTexturename )
		{
			//Die angeforderte Textur wird gesucht.
			std::map< std::string, sf::Texture >::iterator itTexturebyString = m_mapTexturesbyString.find( strTexturename );

			//Zeigt der Iterator nicht auf das Ende der Map, so ist das gesuchte Objekt
			//gefunden worden.
			if( itTexturebyString != m_mapTexturesbyString.end() )
			{
				std::cout << "Could find texture " << strTexturename << "!" << std::endl;

				//Die angeforderte Textur wird zurück gegeben.
				return itTexturebyString->second;
			}
	
			std::cout << "Couldnt find texture " << strTexturename << "!" << std::endl;
			//Die angeforderte Textur wurde nicht gefunden, so wird eine leere Textur zurück gegeben.
			return m_mapTexturesbyString["EMPTY"];
		}