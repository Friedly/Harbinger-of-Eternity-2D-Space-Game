#include "CProfile.hpp"

								ety::CProfile::CProfile			( const std::string& strFilename, const std::string& strDirectory, const unsigned int uiID )
										: m_strFilename		( strFilename	)
										, m_strDirectory	( strDirectory	)
										, m_uiID			( uiID )
{
}
								ety::CProfile::~CProfile		( void )
{
}

void							ety::CProfile::set_ID			( const unsigned int uiID )
{
	m_uiID = uiID;
}

const std::string&				ety::CProfile::get_Filename		( void )
{
	return m_strFilename;
}
const std::string&				ety::CProfile::get_Directory	( void )
{
	return m_strDirectory;
}
const unsigned int				ety::CProfile::get_ID			( void )
{
	return m_uiID;
}


								ety::CETYProfile::CETYProfile	( const std::string& strFilename, const std::string& strDirectory, const unsigned int uiID )
											: CProfile	( strFilename, strDirectory, uiID )
								{
									ety::CIniFile c_etyIniFile;

									const bool bFileExisting = c_etyIniFile.set_IniFileDirectory( ( m_strDirectory + m_strFilename + ".ini" ) );
		
									m_c_etyAttributes.add_Attribute<std::string>							( "strCurrentWorld"				, new std::string	( c_etyIniFile.read_String	( strFilename, "strCurrentWorld"	, "Alpha-Centauri-System"	) )	, true );
		
									m_c_etyAttributes.add_Attribute<unsigned int>							( "uiMoney"						, new unsigned int	( c_etyIniFile.read_Integer	( strFilename, "uiMoney"				, 1500						) )	, true );
									m_c_etyAttributes.add_Attribute<unsigned int>							( "uiSpecialressources"			, new unsigned int	( c_etyIniFile.read_Integer	( strFilename, "uiSpecialressources"	, 0							) )	, true );
									m_c_etyAttributes.add_Attribute<unsigned int>							( "uiFinishedQuestCount"		, new unsigned int	( c_etyIniFile.read_Integer	( strFilename, "uiFinishedQuestCount"	, 0							) )	, true );
									m_c_etyAttributes.add_Attribute<unsigned int>							( "uiSpaceshipCount"			, new unsigned int	( c_etyIniFile.read_Integer	( strFilename, "uiSpaceshipCount"		, 0							) )	, true );
		
									m_c_etyAttributes.add_Attribute<std::vector<std::string>>				( "vecFinishedQuests"			, new std::vector<std::string>()			, true );
									m_c_etyAttributes.add_Attribute<mapItemsBySpaceship>					( "mapItemsBySpaceship"			, new mapItemsBySpaceship()					, true );
									m_c_etyAttributes.add_Attribute<std::map<std::string, std::string>>		( "mapReputationByFaction"		, new std::map<std::string, std::string>()	, true );

									const unsigned int uiSpaceshipCount		= (*m_c_etyAttributes.get_Attribute<unsigned int>( "uiSpaceshipCount"		));
									const unsigned int uiFinishedQuestCount = (*m_c_etyAttributes.get_Attribute<unsigned int>( "uiFinishedQuestCount"	));

									if( uiSpaceshipCount > 0 )
									{
									}

									if( uiFinishedQuestCount > 0 )
									{
									}

									if( bFileExisting == false )
									{
										c_etyIniFile.write_String	( strFilename, "strCurrentWorld"	, (*m_c_etyAttributes.get_Attribute<std::string>	( "strCurrentWorld"	))	);

										c_etyIniFile.write_Integer	( strFilename, "uiMoney"				, (*m_c_etyAttributes.get_Attribute<unsigned int>	( "uiMoney"					))	);
										c_etyIniFile.write_Integer	( strFilename, "uiSpecialressources"	, (*m_c_etyAttributes.get_Attribute<unsigned int>	( "uiSpecialressources"		))	);
										c_etyIniFile.write_Integer	( strFilename, "uiFinishedQuestCount"	, (*m_c_etyAttributes.get_Attribute<unsigned int>	( "uiFinishedQuestCount"	))	);
										c_etyIniFile.write_Integer	( strFilename, "uiSpaceshipCount"		, (*m_c_etyAttributes.get_Attribute<unsigned int>	( "uiSpaceshipCount"		))	);
									}
								}
								ety::CETYProfile::~CETYProfile	( void )
								{
								}