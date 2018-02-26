#pragma once

#include "CSingleton.hpp"

#include <string>
#include <stdio.h>
#include <Windows.h>

//Makro zur einfacheren Verwendung des Singletons
#define	gp_c_etyLogfile ety::CLogfile::get_Singleton()

namespace ety
{
	namespace FontColors
	{	
		enum en_etyFontColor{ enBLACK, enRED, enGREEN, enBLUE, enPURPLE };
	}

	class CLogfile : public CSingleton<ety::CLogfile>
	{
	private:
		bool	m_IsCreated;

		FILE*	mp_s_Logfile;

	protected:

	public:
				CLogfile				( void );
				~CLogfile				( void );

		void	create_Logfile			( const char* szLogfileName );

		void	write_Topic				( const char* szTopicName, const int iSize );
		void	write_Text				( const char* szText );
		void	write_Text				( const FontColors::en_etyFontColor en_etyColor, const char* szText );
		void	write_Text				( const FontColors::en_etyFontColor en_etyColor, const bool bList, const char* szText );
		void	write_FormattedText		( const char* szText, ... );
		void	write_FormattedText		( const FontColors::en_etyFontColor en_etyColor, const char* szText, ... );
		void	write_FormattedText		( const FontColors::en_etyFontColor en_etyColor, const bool bList, const char* szText, ... );
		void	write_FunctionResult	( const bool bResult, const char* szFunctionName );
	};
}

