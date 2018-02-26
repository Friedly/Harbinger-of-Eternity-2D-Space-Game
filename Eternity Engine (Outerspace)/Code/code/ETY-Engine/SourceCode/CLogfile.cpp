#include "CLogfile.hpp"


		ety::CLogfile::CLogfile					( void )
			: m_IsCreated( false )
{
}
		ety::CLogfile::~CLogfile				( void )
{
	if( m_IsCreated == true)
	{
		write_Text	("<br><br><html><head><title>Logfile</title></head>");
		write_Text	("<body><font face='courier new'>");
		write_Topic	("End of Eternity-Engine-Logfile", 3);

		fclose(mp_s_Logfile);
	}
}

void	ety::CLogfile::create_Logfile			( const char* szLogfileName )
{
	if( m_IsCreated == false)
	{
		fopen_s( &mp_s_Logfile, szLogfileName, "w" );

		write_Text	("<html><head><title>Logfile</title></head>");
		write_Text	("<body><font face='courier new'>");
		write_Topic	("Begin of Eternity-Engine-Logfile", 3);

		#ifdef _DEBUG
			write_Text("BUILD: DEBUG<br>");
		#else
			write_Text("BUILD: RELEASE<br>");
		#endif

		write_Text( "<a href='mailto:Julien.Saevecke@gmx.de?subject=Eternity-Engine-Logfile'>");
		write_Text( "Send E-Mail to me: Julien Saevecke </a><br><br>");

		fclose( mp_s_Logfile );

		fopen_s( &mp_s_Logfile, szLogfileName, "a" );
	}
}

void	ety::CLogfile::write_Topic				( const char* szTopicName, const int iSize )
{
	if( m_IsCreated == true )
	{
		write_Text("<table cellspacing='0' cellpadding='0' width='100%%' ");
		write_Text("bgcolor='#DFDFE5'>\n<tr>\n<td>\n<font face='arial' ");
	
		write_FormattedText("size='+%i'>\n", iSize);

		write_Text(szTopicName);
		write_Text("</font>\n</td>\n</tr>\n</table>\n<br>");

		fflush( mp_s_Logfile );
	}
}
void	ety::CLogfile::write_Text				( const char* szText )
{
	if( m_IsCreated == true )
	{
		fprintf(mp_s_Logfile, szText);
		fflush(mp_s_Logfile);
	}
}
void	ety::CLogfile::write_Text				( const FontColors::en_etyFontColor en_etyColor, const char* szText )
{
	if( m_IsCreated == true )
	{
		write_Text( en_etyColor, false, szText );
	}
}
void	ety::CLogfile::write_Text				( const FontColors::en_etyFontColor en_etyColor, const bool bList, const char* szText )
{	
	if( m_IsCreated == true )
	{
		if( bList == true )
		{
			write_Text("<li>");
		}

		switch( en_etyColor )
		{
		case ety::FontColors::enBLACK:
			write_Text("<font color=black>");	break;
		case ety::FontColors::enRED:
			write_Text("<font color=red>");		break;
		case ety::FontColors::enGREEN:
			write_Text("<font color=green>");	break;
		case ety::FontColors::enBLUE:
			write_Text("<font color=blue>");	break;
		case ety::FontColors::enPURPLE:
			write_Text("<font color=purple>");	break;
		};

		write_Text( szText );
		write_Text( "</font>" );

		if( bList == false )
		{
			write_Text ("<br>");
		}
		else
		{
			write_Text ("</li>");
		}
	}
}
void	ety::CLogfile::write_FormattedText		( const char* szText, ... )
{
	if( m_IsCreated == true )
	{
		char* p_chBuffer = new char[4096];

		va_list pArgList;

		va_start(pArgList, szText);
		vsprintf_s(p_chBuffer, 4096, szText, pArgList);
		va_end(pArgList);

		write_Text(p_chBuffer);

		free(p_chBuffer);
	}
}
void	ety::CLogfile::write_FormattedText		( const FontColors::en_etyFontColor en_etyColor, const char* szText, ... )
{
	if( m_IsCreated == true )
	{
		char* p_chBuffer = new char[4096];
		va_list pArgList;

		va_start(pArgList, szText);
		vsprintf_s(p_chBuffer, 4096, szText, pArgList);
		va_end(pArgList);

		write_Text(en_etyColor, p_chBuffer);

		free(p_chBuffer);
	}
}
void	ety::CLogfile::write_FormattedText		( const FontColors::en_etyFontColor en_etyColor, const bool bList, const char* szText, ... )
{
	if( m_IsCreated == true )
	{
		char* p_chBuffer = new char[4096];
		va_list pArgList;

		va_start(pArgList, szText);
		vsprintf_s(p_chBuffer, 4096, szText, pArgList);
		va_end(pArgList);

		write_Text( en_etyColor, bList, p_chBuffer );

		free(p_chBuffer);
	}
}
void	ety::CLogfile::write_FunctionResult		( const bool bResult, const char* szFunctionName )
{
	if( m_IsCreated == true )
	{
		if( bResult == true )
		{
			write_Text("<table width='100%%' cellSpacing='1' cellPadding='5'");
			write_Text(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");

			write_FormattedText("'#FFFFFF' width='35%%'>%s</TD>", szFunctionName);

			write_Text("<td bgcolor='#FFFFFF' width='20%%'><font color =");
			write_Text("'green'>OK</FONT></TD><td bgcolor='#FFFFFF' ");
			write_Text("width='35%%'>-/-</TD></tr></table>");
		}
		else
		{
			write_Text("<table width='100%%' cellSpacing='1' cellPadding='5'");
			write_Text(" border='0' bgcolor='#C0C0C0'><tr><td bgcolor=");

			write_FormattedText("'#FFFFFF' width='35%%'>%s</TD>", szFunctionName);

			write_Text("<td bgcolor='#FFFFFF' width='20%%'><font color =");
			write_Text("'red'>ERROR</FONT></TD><td bgcolor='#FFFFFF' ");
			write_Text("width='35%%'>-/-</TD></tr></table>");
		}
	}
}