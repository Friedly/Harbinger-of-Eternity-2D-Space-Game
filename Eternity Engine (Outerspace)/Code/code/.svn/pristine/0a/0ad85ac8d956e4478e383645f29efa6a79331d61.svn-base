#pragma once

#include "CIniFile.hpp"
#include "CMathConvertClasses.hpp"
#include "CProfile.hpp"
#include "CWorld.hpp"
#include "CDialogManager.hpp"
#include "CDialogitem.hpp"
#include "CGameStateManager.hpp"
#include "CItemManagement.hpp"

namespace ety
{
	template<class T> class CIniLoader
	{
	private:
				std::string								m_strSection;
				std::string								m_strDirectory;
				std::string								m_strFilename;
				std::string								m_strCountKey;
				std::string								m_strKeyToIncrement;

				unsigned int							m_uiCount;

				std::map<std::string, T*>				m_mapTByName;

	protected:
	public:
														CIniLoader						( const std::string& strSection, const std::string& strFilename, const std::string& strDirectory, const std::string& strCountKey, const std::string& strKeyToIncrement )
												{
													m_strDirectory		=	strDirectory;			
													m_strFilename		=	strFilename;				
													m_strCountKey		=	strCountKey;				
													m_strKeyToIncrement	=	strKeyToIncrement;		
													m_strSection		=	strSection;				

													ety::CIniFile c_etyIniFile;

													c_etyIniFile.set_IniFileDirectory( ( m_strDirectory + m_strFilename + ".ini" ) );

													int iCount = c_etyIniFile.read_Integer( strSection, m_strCountKey, -1 );

													if( iCount <= -1 )
													{
														m_uiCount = 0;

														std::cout << "Erstellung einer neuen T-Datei." << std::endl;
												
														c_etyIniFile.write_Integer( strSection, m_strCountKey, 0 );
													}
													else if( iCount >= 0 )
													{
														m_uiCount = static_cast<unsigned int>( iCount );

														std::cout << "Erfolgreiche Auslesung - T: " << m_uiCount << "." << std::endl;

														if( m_uiCount > 0 )
														{
															for( unsigned int uiCurrentTID = 1; uiCurrentTID <= m_uiCount; ++uiCurrentTID )
															{
																const std::string strTID	= m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( uiCurrentTID ) );
																const std::string strT		= c_etyIniFile.read_String( strSection, strTID, "T not found!" );

																std::cout << "Loaded T: " << strT << std::endl;

																m_mapTByName[strT] = new T( strT, strDirectory, uiCurrentTID );
															}
														}
													}
												}
												
														~CIniLoader						( void )
												{
													for( std::map<std::string, T*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); ++itTByName )
													{
														if( itTByName->second != NULL )
														{
															delete itTByName->second;
															itTByName->second = NULL;
														}
													}

													m_mapTByName.clear();
												}

		const	bool									delete_T						( const std::string& strTname )
				{
					std::map<std::string, T*>::iterator itTByName = m_mapTByName.find( strTname );

					if( itTByName != m_mapTByName.end() )
					{
						ety::CIniFile c_etyIniFile;

						c_etyIniFile.set_IniFileDirectory( ( m_strDirectory + m_strFilename + ".ini" ) );

						std::remove( (m_strDirectory + m_mapTByName[strTname]->get_Filename() + ".ini").c_str() );

						c_etyIniFile.delete_Key( m_strSection, m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( m_mapTByName[strTname]->get_ID() ) ) );

						delete m_mapTByName[strTname];

						m_mapTByName.erase( m_mapTByName.find( strTname ) );

						c_etyIniFile.write_Integer( m_strSection, m_strCountKey, --m_uiCount );

						unsigned int uiTID = 1;

						for( std::map<std::string, T*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); itTByName++, uiTID++ )
						{
							c_etyIniFile.delete_Key( m_strSection, m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( itTByName->second->get_ID() ) ) );

							itTByName->second->set_ID( uiTID );
						}

						for( std::map<std::string, T*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); itTByName++, uiTID++ )
						{
							c_etyIniFile.write_String( m_strSection, m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( itTByName->second->get_ID() ) ), itTByName->second->get_Filename() );
						}

						return true;
					}

					return false;
				}

		const	bool									create_T						( const std::string& strTname )
				{
					std::map<std::string, T*>::iterator itTByName = m_mapTByName.find( strTname );

					if( itTByName == m_mapTByName.end() )
					{
						m_uiCount++;

						m_mapTByName[strTname] = new T( strTname, m_strDirectory, m_uiCount );

						ety::CIniFile c_etyIniFile;

						c_etyIniFile.set_IniFileDirectory( ( m_strDirectory + m_strFilename + ".ini" ) );

						c_etyIniFile.write_Integer	( m_strSection, m_strCountKey, m_uiCount );
						c_etyIniFile.write_String	( m_strSection, m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( m_uiCount ) ), strTname );

						return true;
					}

					return false;
				}

				T*						const			get_T							( const std::string& strTname )
				{
					std::map<std::string, T*>::iterator itTByName = m_mapTByName.find( strTname );

					if( itTByName != m_mapTByName.end() )
					{
						return static_cast<T*>(itTByName->second);
					}

					return NULL;
				}

				std::list<std::string>					get_TNames						( void )
				{
					std::list<std::string> c_listTNames;

					for( std::map<std::string, T*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); itTByName++ )
					{
						c_listTNames.push_back( itTByName->second->get_Filename() );
					}

					return c_listTNames;
				}
	};

	template<       > class CIniLoader<ety::CWorld>
	{
	private:
				bool											m_bActive;
				bool											m_bInitialized;

				ety::CDialog*									mp_c_etyDialogCelestialMap;

				std::string										m_strSection;
				std::string										m_strDirectory;
				std::string										m_strFilename;
				std::string										m_strCountKey;
				std::string										m_strKeyToIncrement;

				unsigned int									m_uiCount;

				std::map<std::string, ety::CWorld*>				m_mapTByName;

	public:
																CIniLoader					( const std::string& strSection, const std::string& strFilename, const std::string& strDirectory, const std::string& strCountKey, const std::string& strKeyToIncrement, ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettings, ety::CItemManagement* const p_c_etyItemManagement )
		{
			m_bActive					=	false;
			m_strDirectory				=	strDirectory;			
			m_strFilename				=	strFilename;				
			m_strCountKey				=	strCountKey;				
			m_strKeyToIncrement			=	strKeyToIncrement;		
			m_strSection				=	strSection;
			mp_c_etyDialogCelestialMap	=	NULL;
			m_bInitialized				=	false;

			ety::CIniFile c_etyIniFile;

			c_etyIniFile.set_IniFileDirectory( ( m_strDirectory + m_strFilename + ".ini" ) );

			int iCount = c_etyIniFile.read_Integer( strSection, m_strCountKey, -1 );

			if( iCount <= -1 )
			{
				m_uiCount = 0;

				std::cout << "Erstellung einer neuen T-Datei." << std::endl;
												
				c_etyIniFile.write_Integer( strSection, m_strCountKey, 0 );
			}
			else if( iCount >= 0 )
			{
				m_uiCount = static_cast<unsigned int>( iCount );

				std::cout << "Erfolgreiche Auslesung - T: " << m_uiCount << "." << std::endl;

				if( m_uiCount > 0 )
				{
					for( unsigned int uiCurrentTID = 1; uiCurrentTID <= m_uiCount; ++uiCurrentTID )
					{
						const std::string strTID	= m_strKeyToIncrement + ety::CConvert::convert_NumberToString( static_cast<float>( uiCurrentTID ) );
						const std::string strT		= c_etyIniFile.read_String( strSection, strTID, "T not found!" );

						std::cout << "Loaded T: " << strT << std::endl;

						//m_mapTByName[strT] = new ety::CWorld( strT, strDirectory, p_c_etyCurrentRessourceManager, p_c_etyCurrentGamesettings, p_c_etyItemManagement );
					}
				}
			}
		}
																~CIniLoader					( void )
															{
																for( std::map<std::string, ety::CWorld*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); ++itTByName )
																{
																	if( itTByName->second != NULL )
																	{
																		delete itTByName->second;
																		itTByName->second = NULL;
																	}
																}

																m_mapTByName.clear();

																if( mp_c_etyDialogCelestialMap != NULL )
																{
																	delete mp_c_etyDialogCelestialMap;
																	mp_c_etyDialogCelestialMap = NULL;
																}
															}

				void											init_CelestialMap			( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettings, ety::CDialogManager* const p_c_etyCurrentDialogManager )
				{
					if( m_bInitialized == false )
					{
						mp_c_etyDialogCelestialMap = new CDialog( 
							"SpaceStationCelestialMap", p_c_etyCurrentRessourceManager->get_Texture( "MissionMenuBackground.png" ), 1680.f, 1050.f, sf::Vector2f( 0.f, 0.f ), 
							sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1680, 1050)), p_c_etyCurrentDialogManager, p_c_etyCurrentGamesettings->get_Videomode()
							);

						mp_c_etyDialogCelestialMap->set_Visibility(false);
						mp_c_etyDialogCelestialMap->set_Anchor(Anchor::enMID);
						mp_c_etyDialogCelestialMap->set_AnchorCentered(true);
							
						int iStarsytemIndex = 1;
						for( std::map<std::string, ety::CWorld*>::iterator itWorldByName = m_mapTByName.begin(); itWorldByName != m_mapTByName.end(); ++itWorldByName, ++iStarsytemIndex )
						{
							mp_c_etyDialogCelestialMap->createDialogitem_Button( 	
								itWorldByName->first + "WorldButton", p_c_etyCurrentRessourceManager->get_Texture( itWorldByName->second->get_CelestialButtonTexturename() ), 40.f, 40.f, 
								sf::Vector2f(itWorldByName->second->get_CelestialButtonPosition()), sf::IntRect(sf::Vector2i(0,0), sf::Vector2i( 40, 40 ))
								);
						}

						m_bInitialized = true;
					}
				}

				void											show_CelestialMap			( const bool bShow )
				{
					mp_c_etyDialogCelestialMap->set_Active		( bShow );
					mp_c_etyDialogCelestialMap->set_Visibility	( bShow );
					
					mp_c_etyDialogCelestialMap->get_DialogManager()->get_DialogbyCustomID("SpaceStationBar")->set_Active		( !bShow );
					mp_c_etyDialogCelestialMap->get_DialogManager()->get_DialogbyCustomID("SpaceStationBar")->set_Visibility	( !bShow );

					mp_c_etyDialogCelestialMap->set_Modal( true, sf::Vector3f( 1.f, 1.f, 1.f ) );

					m_bActive = bShow;
				}

				void											handle_Events				( const sf::Event& sfEventLastEvent, CDialogitem* const p_c_etyDialogitemEventDialogitem, ety::CGameStateManager* const p_c_etyGameStateManager  )
				{
					if( sfEventLastEvent.type == sf::Event::KeyReleased && sfEventLastEvent.key.code == sf::Keyboard::Escape )
					{
						show_CelestialMap( false );
					}

					if( p_c_etyDialogitemEventDialogitem != NULL && sfEventLastEvent.type == sf::Event::MouseButtonReleased && sfEventLastEvent.mouseButton.button == sf::Mouse::Left )
					{
						std::string strWorld = p_c_etyDialogitemEventDialogitem->get_CustomID();
						std::size_t stButtonIDPos = strWorld.find("WorldButton");

						if( stButtonIDPos != std::string::npos && p_c_etyGameStateManager != NULL )
						{
							strWorld.erase( stButtonIDPos );

							p_c_etyGameStateManager->m_c_etyAttributes.change_Attribute<CWorld>("p_c_etyCurrentWorld", m_mapTByName[strWorld], false );
						}
					}
				}

		const	bool											get_Active					( void )
				{
					return m_bActive;
				}
				ety::CWorld*									get_T						( const std::string& strTname )
				{
					std::map<std::string, CWorld*>::iterator itTByName = m_mapTByName.find( strTname );

					if( itTByName != m_mapTByName.end() )
					{
						return itTByName->second;
					}

					return NULL;
				}
				std::list<std::string>							get_TNames					( void )
				{
					std::list<std::string> c_listTNames;

					for( std::map<std::string, CWorld*>::iterator itTByName = m_mapTByName.begin(); itTByName != m_mapTByName.end(); itTByName++ )
					{
						c_listTNames.push_back( itTByName->second->get_Name() );
					}

					return c_listTNames;
				}
	};
}

