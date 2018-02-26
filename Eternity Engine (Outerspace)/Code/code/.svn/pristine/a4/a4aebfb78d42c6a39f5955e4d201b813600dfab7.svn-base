#pragma once

#pragma warning( disable : 4996 )

//Includes des Compilers
#include <direct.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <vector>

namespace ety
{
	class CIniFile
	{
	private:
		std::string					m_strIniFileDirectory;

	protected:

	public:
									CIniFile				( void );
									~CIniFile				( void );

		void						delete_Key				( const std::string& strSection, const std::string& strValueKey );
		void						delete_Section			( const std::string& strSection );

		int							read_Integer			( const std::string& strSection, const std::string& strValueKey, const int iDefaultValue );
		float						read_Float				( const std::string& strSection, const std::string& strValueKey, const float fDefaultValue );
		bool						read_Boolean			( const std::string& strSection, const std::string& strValueKey, const bool bDefaultValue );
		std::string					read_String				( const std::string& strSection, const std::string& strValueKey, const std::string& strDefaultValue );
		std::vector<std::string>	read_Sections			( void );	

		void						write_Integer			( const std::string& strSection, const std::string& strValueKey, const int iValue );
		void						write_Float				( const std::string& strSection, const std::string& strValueKey, const float fValue );
		void						write_Boolean			( const std::string& strSection, const std::string& strValueKey, const bool bValue );
		void						write_String			( const std::string& strSection, const std::string& strValueKey, const std::string& strValue );

		const bool					set_IniFileDirectory	( const std::string& strIniFileDirectory );
	};
}