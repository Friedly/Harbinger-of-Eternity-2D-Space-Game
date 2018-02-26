#include "CIniFile.hpp"


							ety::CIniFile::CIniFile				( void )
{
}
							ety::CIniFile::~CIniFile			( void )
{
}

void						ety::CIniFile::delete_Key			( const std::string& strSection, const std::string& strValueKey )
{
	WritePrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), NULL, m_strIniFileDirectory.c_str() );
}
void						ety::CIniFile::delete_Section		( const std::string& strSection )
{
	WritePrivateProfileStringA( strSection.c_str(), NULL, NULL, m_strIniFileDirectory.c_str() );
}

int							ety::CIniFile::read_Integer			( const std::string& strSection, const std::string& strValueKey, const int iDefaultValue )
{
	return GetPrivateProfileIntA( strSection.c_str(), strValueKey.c_str(), iDefaultValue, m_strIniFileDirectory.c_str() );
}
float						ety::CIniFile::read_Float			( const std::string& strSection, const std::string& strValueKey, const float fDefaultValue )
{
	char	p_chStringBuffer[255];
	char	strDefaultValue[255];

	DWORD	dwBufferSize = 255;
	
	float	fResult = 0.f;

	sprintf( strDefaultValue, "%f", fDefaultValue );

	GetPrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strDefaultValue, p_chStringBuffer, dwBufferSize, m_strIniFileDirectory.c_str() );

	fResult = float( atof( p_chStringBuffer ) );

	return fResult;
}
bool						ety::CIniFile::read_Boolean			( const std::string& strSection, const std::string& strValueKey, const bool bDefaultValue )
{
	bool b = GetPrivateProfileIntA( strSection.c_str(), strValueKey.c_str(), bDefaultValue, m_strIniFileDirectory.c_str() ) !=0;
	return b;
}
std::string					ety::CIniFile::read_String			( const std::string& strSection, const std::string& strValueKey, const std::string& strDefaultValue )
{
	char			p_chStringBuffer[255];
	DWORD			dwBufferSize = 255;

	GetPrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strDefaultValue.c_str(), p_chStringBuffer, dwBufferSize, m_strIniFileDirectory.c_str() );

	return std::string( p_chStringBuffer );
}
std::vector<std::string>	ety::CIniFile::read_Sections		( void )
{
	unsigned int	iZeroCount = 0;
	char			p_chStringBuffer[1024] ="";
	DWORD			dwBufferSize = 1024;

	GetPrivateProfileSectionNamesA( p_chStringBuffer, dwBufferSize, m_strIniFileDirectory.c_str() );

	std::string					strSection = "";
	std::vector<std::string>	vecSections;

	for( unsigned int iStringIndex = 0; p_chStringBuffer[iStringIndex] != -52; iStringIndex++ )
	{
		if( p_chStringBuffer[iStringIndex] == 0 && strSection != "" )
		{
			vecSections.push_back( strSection );
			strSection.clear();

			iZeroCount = 0;
		}
		else
		{
			if( p_chStringBuffer[iStringIndex] != 0 )
			{
				strSection += p_chStringBuffer[iStringIndex];
			}
			else
			{
				break;
			}
		}
	}

	return vecSections;
}

void						ety::CIniFile::write_Integer		( const std::string& strSection, const std::string& strValueKey, const int iValue )
{
	char strValue[255];

	sprintf( strValue, "%d", iValue );

	WritePrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strValue, m_strIniFileDirectory.c_str() ); 
}
void						ety::CIniFile::write_Float			( const std::string& strSection, const std::string& strValueKey, const float fValue )
{
	char strValue[255];

	sprintf( strValue, "%f", fValue );

	WritePrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strValue, m_strIniFileDirectory.c_str() ); 
}
void						ety::CIniFile::write_Boolean		( const std::string& strSection, const std::string& strValueKey, const bool bValue )
{
	char strValue[255];

	sprintf( strValue, "%d", bValue );

	WritePrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strValue, m_strIniFileDirectory.c_str() ); 
}
void						ety::CIniFile::write_String			( const std::string& strSection, const std::string& strValueKey, const std::string& strValue )
{
	WritePrivateProfileStringA( strSection.c_str(), strValueKey.c_str(), strValue.c_str(), m_strIniFileDirectory.c_str() ); 
}

const bool					ety::CIniFile::set_IniFileDirectory	( const std::string& strIniFileDirectory )
{
	m_strIniFileDirectory = strIniFileDirectory;

	std::ifstream c_stdFileRead;

	c_stdFileRead.open( strIniFileDirectory, std::ios_base::in );

	if( !c_stdFileRead )
	{
		std::ofstream c_stdFileWrite( strIniFileDirectory );

		return false;
	}

	return true;
}