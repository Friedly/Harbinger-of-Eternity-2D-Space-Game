#include "CFilemanagement.hpp"
#include "CLoadingState.hpp"
#include "CLogfile.hpp"
#include "CLua.hpp"
#include <iostream>

//Standart Konstruktor und Destruktor.
													ety::CFilemanagement::CFilemanagement						( void )
														: m_strScript( "NULL" )
		{
		}
													ety::CFilemanagement::~CFilemanagement						( void )
		{
		}

//Fügt die Informationen einer Ressource, welche noch geladen werden soll, hinzu.
		void										ety::CFilemanagement::add_FileToLoad						( const std::string& strGamestateName, const ety::RessourceType::en_etyRessourceType en_etyRessourceType, const std::string& strFileToLoad, const std::string& strDirectoryKey  )
		{
			//Ausführen wenn der string in ein richtigen Enumtyp umgewandelt werden konnte.
			if( en_etyRessourceType != ety::RessourceType::enERROR )
			{
				//Suchen des Spielzustandes um eine Ressource zum Laden hinzuzufügen.
				mapFilesToLoadbyGamestate::iterator itFileToLoadType = m_mapFilesToLoadbyGamestate.find(strGamestateName);

				//Existiert der Spielzustand...
				if( itFileToLoadType != m_mapFilesToLoadbyGamestate.end() )
				{
					//Suchen des Dateityps...
					mapFileToLoadbyRessourceType::iterator itFileToLoadbyRessourceType = itFileToLoadType->second.find( en_etyRessourceType );

					//Existiert dieser Dateityp im Spielzustand...
					if( itFileToLoadbyRessourceType != itFileToLoadType->second.end() )
					{
						//Untersuchen dieser Dateiname schon unter diesem Dateitypen und unter diesem Spielzustand zu finden ist...
						mapFileToLoad::iterator	itFileToLoad = itFileToLoadbyRessourceType->second.find(strFileToLoad);

						//Existiert dieser Dateiname...
						if( itFileToLoad != itFileToLoadbyRessourceType->second.end() )
						{
							gp_c_etyLogfile->write_FormattedText( ety::FontColors::enPURPLE, true, "File \"%s\" already registered for gamestate \"%s\"!", strFileToLoad.c_str(), strGamestateName.c_str() ); 

							//Diese Ressource wurde schon in diesem Spielzustand registriert.
							return ;
						}
						else
						{
							//Dateiname wird unter dem angegeben Spielzustand und Dateitypen gespeichert.
							itFileToLoadbyRessourceType->second[strFileToLoad]	=	strDirectoryKey;

							//Anzahl der Ressourcen steigt um 1 im angegeben Spielzustand.
							m_mapRessourceCountbyGamestate[strGamestateName]	+=	1;

							gp_c_etyLogfile->write_FormattedText( ety::FontColors::enGREEN, true, "File \"%s\" is now registered to load for gamestate \"%s\"! ", strFileToLoad.c_str(), strGamestateName.c_str() );

							std::cout << "File to load added: " << strFileToLoad << std::endl;
							//Diese Ressource konnte erfolgreich registriert werden.
							return ;
						}
					}
					else
					{
						mapFileToLoad mapFileToLoadbyRessourceType;

						//Dateiname wird unter dem angegeben Spielzustand und Dateitypen gespeichert.
						mapFileToLoadbyRessourceType[strFileToLoad]			=	strDirectoryKey;

						//Dateityp wird unter dem angegeben Spielzustand gespeichert.
						itFileToLoadType->second[en_etyRessourceType]		=	mapFileToLoadbyRessourceType;

						//Anzahl der Ressourcen steigt um 1 im angegeben Spielzustand.
						m_mapRessourceCountbyGamestate[strGamestateName]	+= 1;

						gp_c_etyLogfile->write_FormattedText(ety::FontColors::enGREEN, true, "File \"%s\" is now registered to load for gamestate \"%s\"! ", strFileToLoad.c_str(), strGamestateName.c_str() );

						std::cout << "File to load added: " << strFileToLoad << std::endl;
						//Diese Ressource konnte erfolgreich registriert werden.
						return;
					}
				}
				else
				{
					mapFileToLoadbyRessourceType									mapFileToLoadbyRessourceType;

					mapFileToLoad											mapFileToLoad;	

					//Dateiname wird unter dem angegeben Spielzustand und Dateitypen gespeichert.
					mapFileToLoad[strFileToLoad]						=	strDirectoryKey;

					//Dateityp wird unter dem angegeben Spielzustand gespeichert.
					mapFileToLoadbyRessourceType[en_etyRessourceType]				=	mapFileToLoad;

					//Neuer Spielzustand mit Ressourcen wird registriert.
					m_mapFilesToLoadbyGamestate[strGamestateName]		=	mapFileToLoadbyRessourceType;
				
					//Anzahl der Ressourcen wird auf 1 gesetzt, da es die erste Ressource unter dem Spielzustand ist.
					m_mapRessourceCountbyGamestate[strGamestateName]	=	1;

					gp_c_etyLogfile->write_FormattedText(ety::FontColors::enGREEN, true, "File \"%s\" is now registered to load for gamestate \"%s\"! ", strFileToLoad.c_str(), strGamestateName.c_str() );

					std::cout << "File to load added: " << strFileToLoad << std::endl;
					//Diese Ressource konnte erfolgreich registriert werden.
					return ;
				}
			}
			else
			{
				gp_c_etyLogfile->write_FormattedText( ety::FontColors::enPURPLE, true, "Invalid RessourceType: \"%s\"", en_etyRessourceType );

				//Dateityp existiert nicht.
				return;
			}
		}
//Fügt die Informationen einer Standard-Sounddatei, welche noch geladen werden soll, hinzu.
//Eine Standard-Sounddatei ist eine Sounddatei für einen gewissen Dialogitemtyp z.B. einen Knopf.
//In einem Spielzustand werden diese Standard-Sounddateien für den jeweiligen Dialogitemtyp immer abgespielt.
		void										ety::CFilemanagement::add_StandardSoundToLoad				( const std::string& strGamestateName, const ety::DialogitemType::en_etyDialogitemType en_etyDialogitemType, const ety::SoundType::en_etySoundType en_etySoundType, const std::string& strFileToLoad, const std::string& strDirectoryKey, const bool bLoadSound )
		{
			//Soll die Audiodatei geladen werden?..
			//Somit würde diese Audiodatei nur als Standard-Sound für einen Spielzustand registriert werden.
			if( bLoadSound == true )
			{
				//Audiodatei zum Laden registrieren.
				add_FileToLoad( strGamestateName, ety::RessourceType::enSOUNDBUFFER, strFileToLoad, strDirectoryKey );
			}

			//Ausführen wenn die strings in ein richtigen Enumtyp umgewandelt werden konnte.
			if(	en_etyDialogitemType != ety::DialogitemType::enERROR && en_etySoundType != ety::SoundType::enERROR )
			{
				//Suchen des Spielzustandes, ob dieser schon registriert worden ist.
				mapStandardSoundsbyGamestate::iterator itStandardSoundsbyGamestate = m_mapStandardSoundsbyGamestate.find( strGamestateName );

				//Ist der Spielzustand schon registriert...
				if( itStandardSoundsbyGamestate != m_mapStandardSoundsbyGamestate.end() )
				{
					//Suchen nach dem Dialogitemtyp, ob dieser schon registriert worden ist.
					mapStandardSoundbyDialogitemtype::iterator itSoundTypebyDialogitemType = itStandardSoundsbyGamestate->second.find( en_etyDialogitemType );

					//Ist der Dialogitemtyp unter dem Spielzustand schon registriert...
					if( itSoundTypebyDialogitemType != itStandardSoundsbyGamestate->second.end() )
					{
						//Suchen nach dem Soundtypen, ob dieser schon registriert worden ist.
						mapStandardSoundbySoundtype::iterator itSoundbySountype = itSoundTypebyDialogitemType->second.find( en_etySoundType );

						if( itSoundbySountype != itSoundTypebyDialogitemType->second.end() )
						{
							//Ein Standard-Sound existiert schon für diesen Soundtypen.
							return ;
						}
						else
						{
							//Ein neuer Standard-Sound wird angelegt für ein Dialogitemtyp.
							SStandardSound	s_etyStandardSound;

							//Der Soundname wird gespeichert.
							s_etyStandardSound.m_strSoundname					=   strFileToLoad;
							//Der Sound ist erst auf NULL, dieser wird später gefüllt
							//wenn der Spielzustand geladen wird und mit Hilfe der Methode 
							//assign_StandardSounds wird dieser Sound gesetzt.
							s_etyStandardSound.mp_c_sfSound						=	NULL;

							//Der Standard-Sound wird unter angegebenen Soundtyp, Dialogitemtype und Spielzustand gespeichert.
							itSoundTypebyDialogitemType->second[en_etySoundType]	=   s_etyStandardSound;

							std::cout << "Standard sound added: " << strFileToLoad << " : " << strGamestateName << std::endl;
							//Standard-Sound wurde erfolgreich gespeichert.
							return ;
						}
					}
					else
					{
						mapStandardSoundbySoundtype	mapSoundbySoundtype;

						//Ein neuer Standard-Sound wird angelegt für ein Dialogitemtyp.
						SStandardSound	s_etyStandardSound;

						//Der Soundname wird gespeichert.
						s_etyStandardSound.m_strSoundname						=   strFileToLoad;
						//Der Sound ist erst auf NULL, dieser wird später gefüllt
						//wenn der Spielzustand geladen wird und mit Hilfe der Methode 
						//assign_StandardSounds wird dieser Sound gesetzt.
						s_etyStandardSound.mp_c_sfSound							=	NULL;

						//Der Standard-Sound wird unter angegebenen Soundtyp gespeichert.
						mapSoundbySoundtype[en_etySoundType]						=	s_etyStandardSound;

						//Dieser Soundtyp wird unter angegebenen Dialogitemtyp und Spielzustand gespeichert.
						itStandardSoundsbyGamestate->second[en_etyDialogitemType]	=	mapSoundbySoundtype;

						std::cout << "Standard sound added: " << strFileToLoad << " : " << strGamestateName << std::endl;
						//Standard-Sound wurde erfolgreich gespeichert.
						return ;
					}
				}
				else
				{
					mapStandardSoundbyDialogitemtype					mapSoundTypebyDialogitemType;

					mapStandardSoundbySoundtype							mapSoundbySoundtype;

					SStandardSound										s_etyStandardSound;

					//Der Soundname wird gespeichert.
					s_etyStandardSound.m_strSoundname					=   strFileToLoad;

					//Der Sound ist erst auf NULL, dieser wird später gefüllt
					//wenn der Spielzustand geladen wird und mit Hilfe der Methode 
					//assign_StandardSounds wird dieser Sound gesetzt.
					s_etyStandardSound.mp_c_sfSound						=	NULL;

					//Der Standard-Sound wird unter angegebenen Soundtyp gespeichert.
					mapSoundbySoundtype[en_etySoundType]				=	s_etyStandardSound;

					//Dieser Soundtyp wird unter angegebenen Dialogitemtyp gespeichert.
					mapSoundTypebyDialogitemType[en_etyDialogitemType]	=	mapSoundbySoundtype;

					//Dieser Dialogitemtyp wird unter angegeben Spielzustand gespeichert.
					m_mapStandardSoundsbyGamestate[strGamestateName]	=	mapSoundTypebyDialogitemType;

					std::cout << "Standard sound added: " << strFileToLoad << " : " << strGamestateName << std::endl;
					//Standard-Sound wurde erfolgreich gespeichert.
					return ;
				}
			}
			else
			{
				//Soundtyp oder Dialogitemtyp ist ungültig.
				return ;
			}
		}

//Um den Dialogitems ihre Standard-Sounddateien zu geben, müssen die vorherigen hinzugefügten Standard-Sounddatei-Informationen
//( mit Hilfe der Funktion add_StandardSoundToLoad(..) ) dazu benutzt werden denen die richtigen Sounddateien zu zuweisen.
//Dies erfüllt diese Methode, sie fordert mit Hilfe der Informationen die Sounddateien vom aktuellen Audiomanager an und
//speichert diese zu den Informationen.
		void										ety::CFilemanagement::assign_StandardSounds					( const std::string& strGamestateName, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
		{
			//Suchen nach dem Spielzustand, ob dieser registriert ist.
			mapStandardSoundsbyGamestate::iterator itStandardSoundsbyGamestate = m_mapStandardSoundsbyGamestate.find( strGamestateName );

			//Ist der Spielzustand registriert...
			if( itStandardSoundsbyGamestate != m_mapStandardSoundsbyGamestate.end() )
			{
				//Für jedes Dialogitem...
				for( mapStandardSoundbyDialogitemtype::iterator itStandardSoundbyDialogitemtype = itStandardSoundsbyGamestate->second.begin(); itStandardSoundbyDialogitemtype != itStandardSoundsbyGamestate->second.end(); itStandardSoundbyDialogitemtype++ )
				{
					//Für jeden Soundtypen...
					for( mapStandardSoundbySoundtype::iterator itStandardSoundbySoundtype = itStandardSoundbyDialogitemtype->second.begin(); itStandardSoundbySoundtype != itStandardSoundbyDialogitemtype->second.end(); itStandardSoundbySoundtype++ )
					{
						//Standard-Sound wird mit Hilfe dessen Namens vom aktuellen Audiomanager angefordert.
						itStandardSoundbySoundtype->second.mp_c_sfSound = p_c_etyCurrentRessourceManager->get_Sound( itStandardSoundbySoundtype->second.m_strSoundname );
					}
				}
			}
		}

//Überprüft ob für ein Gamestate Ressourcen zum Laden eingetragen wurden.
const	bool										ety::CFilemanagement::check_ExistsRessources				( const std::string& strGamestateName )
		{
			//Wenn ein Spielzustand registriert worden ist, hat dieser mindestens eine Ressource.
			if(	m_mapFilesToLoadbyGamestate.find(strGamestateName) != m_mapFilesToLoadbyGamestate.end() )
			{
				//Spielzustand hat Ressourcen.
				return true;
			}
			else
			{
				//Spielzustand hat keine Ressourcen.
				return false;
			}
		}

//Diese Methode braucht den Audio- und Graphic-manager um die Ressourcen, welche geladen wurden, wieder aus dem Arbeitsspeicher zu entfernen.
		void										ety::CFilemanagement::cleanup_Ressources					( const std::string& strGamestateName, ety::CRessourceManager* const p_c_etyCurrentRessourceManager )
		{
			//Wenn kein Spielzustand registriert worden ist, wird nach keinem gesucht.
			if( m_mapFilesToLoadbyGamestate.empty() == false )
			{
				//Es wird nach dem Spielzustand gesucht...
				mapFilesToLoadbyGamestate::const_iterator itFilesToLoadbyGamestate = m_mapFilesToLoadbyGamestate.find( strGamestateName );

				//Ist er vorhanden/gefunden...
				if( itFilesToLoadbyGamestate != m_mapFilesToLoadbyGamestate.end() )
				{
					//Für diesem Spielzustand werden alle Dateitypen durchgegangen...
					mapFileToLoadbyRessourceType::const_iterator itFileToLoadbyRessourceType = itFilesToLoadbyGamestate->second.begin();

					for( itFileToLoadbyRessourceType; itFileToLoadbyRessourceType != itFilesToLoadbyGamestate->second.end(); itFileToLoadbyRessourceType++ )
					{
						for( mapFileToLoad::const_iterator itFileToLoad = itFileToLoadbyRessourceType->second.begin(); itFileToLoad != itFileToLoadbyRessourceType->second.end(); itFileToLoad++ )
						{
							p_c_etyCurrentRessourceManager->remove_Ressource( itFileToLoadbyRessourceType->first, ety::DeleteType::enSINGLE, itFileToLoad->first );
						}
					}
				}
			}
		}

//Es werden alle Ressourcen für den gewählten Spielzustand geladen. Wenn man wünscht mit einem Ladebalken.
		void										ety::CFilemanagement::load_Ressources						( std::vector<std::string>* const vecGamestatesToLoad, ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CProgressbar* const p_c_etyCurrentProgressBar )
		{
			//Wenn kein Spielzustand registriert worden ist, wird nach keinem gesucht.
			if( m_mapFilesToLoadbyGamestate.empty() == false )
			{
				for( std::vector<std::string>::iterator itGamestateToLoad = vecGamestatesToLoad->begin(); itGamestateToLoad != vecGamestatesToLoad->end(); itGamestateToLoad++ )
				{
					//Es wird nach dem Spielzustand gesucht...
					mapFilesToLoadbyGamestate::const_iterator itFilesToLoadbyGamestate = m_mapFilesToLoadbyGamestate.find( *itGamestateToLoad );

					//Ist er vorhanden/gefunden...
					if( itFilesToLoadbyGamestate != m_mapFilesToLoadbyGamestate.end() )
					{
						//Für diesem Spielzustand werden alle Dateitypen durchgegangen...
						for( mapFileToLoadbyRessourceType::const_iterator itFileToLoadbyRessourceType = itFilesToLoadbyGamestate->second.begin(); itFileToLoadbyRessourceType != itFilesToLoadbyGamestate->second.end(); itFileToLoadbyRessourceType++ )
						{
							//Für diesem Spielzustand wird für jeden Dateityp alle Ressourcen durchgegangen...
							for( mapFileToLoad::const_iterator itFileToLoad = itFileToLoadbyRessourceType->second.begin(); itFileToLoad != itFileToLoadbyRessourceType->second.end(); itFileToLoad++ )
							{
								p_c_etyCurrentRessourceManager->load_Ressource( itFileToLoad->first, itFileToLoadbyRessourceType->first, itFileToLoad->second );

								//Nach jeder geladenen Ressource wird der Fortschritt des Balkens erhöht.
								if( p_c_etyCurrentProgressBar != NULL )
								{
									p_c_etyCurrentProgressBar->add_Progress();
								}

								sf::sleep( sf::milliseconds(1) );
							}
						}
					}
				}
			}
		}
		void										ety::CFilemanagement::load_Ressources						( const std::string& strGamestatesToLoad, ety::CRessourceManager* const p_c_etyCurrentRessourceManager, CProgressbar* const p_c_etyCurrentProgressBar )
		{
			//Wenn kein Spielzustand registriert worden ist, wird nach keinem gesucht.
			if( m_mapFilesToLoadbyGamestate.empty() == false )
			{
				//Es wird nach dem Spielzustand gesucht...
				mapFilesToLoadbyGamestate::const_iterator itFilesToLoadbyGamestate = m_mapFilesToLoadbyGamestate.find( strGamestatesToLoad );

				//Ist er vorhanden/gefunden...
				if( itFilesToLoadbyGamestate != m_mapFilesToLoadbyGamestate.end() )
				{
					//Für diesem Spielzustand werden alle Dateitypen durchgegangen...
					for( mapFileToLoadbyRessourceType::const_iterator itFileToLoadbyRessourceType = itFilesToLoadbyGamestate->second.begin(); itFileToLoadbyRessourceType != itFilesToLoadbyGamestate->second.end(); itFileToLoadbyRessourceType++ )
					{
						//Für diesem Spielzustand wird für jeden Dateityp alle Ressourcen durchgegangen...
						for( mapFileToLoad::const_iterator itFileToLoad = itFileToLoadbyRessourceType->second.begin(); itFileToLoad != itFileToLoadbyRessourceType->second.end(); itFileToLoad++ )
						{
							p_c_etyCurrentRessourceManager->load_Ressource( itFileToLoad->first, itFileToLoadbyRessourceType->first, itFileToLoad->second );

							//Nach jeder geladenen Ressource wird der Fortschritt des Balkens erhöht.
							if( p_c_etyCurrentProgressBar != NULL )
							{
								p_c_etyCurrentProgressBar->add_Progress();
							}

							sf::sleep( sf::milliseconds(1) );
						}
					}
				}
			}
		}
//Registriert diese Klasse zum Lua-Script.
		void										ety::CFilemanagement::register_ClassToLuabind				( ety::CLua* const p_c_etyLuaScript )
		{
			luabind::module(p_c_etyLuaScript->get_LuaState() )
			[ 
				luabind::class_<CFilemanagement>("CFilemanagement")
				.def( "add_FileToLoad"			, &CFilemanagement::add_FileToLoad			)
				.def( "add_StandardSoundToLoad"	, &CFilemanagement::add_StandardSoundToLoad )
				.def( "get_StandardSounds"		, &CFilemanagement::get_StandardSounds		) 
			];
		}

//Gibt für einen Spielzustand die Anzahl der zu ladenden Ressourcen für diesen zurück.
const	unsigned int								ety::CFilemanagement::get_RessourceCount					( const std::string& strGamestateName )
		{
			//Ist der Spielzustand registriert hat dieser auch eine Anzahl von Ressourcen.
			std::map< std::string, unsigned int >::const_iterator itRessourceCountbyGamestate = m_mapRessourceCountbyGamestate.find(strGamestateName);

			//Spielzustand ist Registriert...
			if( itRessourceCountbyGamestate != m_mapRessourceCountbyGamestate.end() )
			{
				//Rückgabe der Anzahl von Ressourcen im Spielzustand.
				return itRessourceCountbyGamestate->second;
			}

			//Keine Ressourcen für diesen Spielzustand vorhanden.
			return 0;
		}
//Gibt für einen Spielzustand die Standard-Sounds für einen bestimmten Dialogitemtyp zurück.
const	ety::mapSoundsbySoundtype					ety::CFilemanagement::get_StandardSounds					( const std::string& strGamestateName, ety::DialogitemType::en_etyDialogitemType en_etyDialogitemtype )
		{
			mapStandardSoundsbyGamestate::const_iterator itStandardSoundsbyGamestate = m_mapStandardSoundsbyGamestate.find( strGamestateName );
			mapSoundsbySoundtype mapSoundsbySoundtype;

			if( itStandardSoundsbyGamestate != m_mapStandardSoundsbyGamestate.end() )
			{
				mapStandardSoundbyDialogitemtype::const_iterator itStandardSoundbyDialogitemtype = itStandardSoundsbyGamestate->second.find( en_etyDialogitemtype );

				if( itStandardSoundbyDialogitemtype != itStandardSoundsbyGamestate->second.end() )
				{
					mapStandardSoundbySoundtype::const_iterator itStandardSoundbySoundtype = itStandardSoundbyDialogitemtype->second.begin();

					for( itStandardSoundbySoundtype; itStandardSoundbySoundtype != itStandardSoundbyDialogitemtype->second.end(); itStandardSoundbySoundtype++)
					{
						mapSoundsbySoundtype[itStandardSoundbySoundtype->first] = itStandardSoundbySoundtype->second.mp_c_sfSound;
					}
				}
			}

			return mapSoundsbySoundtype;
		}

