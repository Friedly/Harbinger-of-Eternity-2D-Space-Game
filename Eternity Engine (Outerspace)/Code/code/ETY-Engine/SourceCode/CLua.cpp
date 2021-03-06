//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////																LUA.cpp																   ///////////
///////////																									                                   ///////////
///////////			Diese Klasse wird zum starten von LUA-Scripts verwendet. Sie bietet Funktionen zur leichteren Verwendung				   ///////////
///////////			der Scripts. Diese Scripts sollen zum leichten modifizieren des Programmes dienen.										   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Includes der Eternity-Engine
#include "CLua.hpp"

#include <sfml\Graphics.hpp>

//Includes des Compilers
#include <iostream>

//Standart Konstruktor und Destruktor.
								ety::CLua::CLua					( void )
					: m_s_Lua			( NULL )
					, m_bLuaInitiated	( false )
{
}
								ety::CLua::~CLua				( void )
{
	if( m_s_Lua != NULL )
	{
		m_s_Lua = NULL;
	}
}

//Ruft eine LUA-Funktion eines LUA-Scripts auf mit angegebener Anzahl von Argumenten und R�ckgabewerten.
const	bool					ety::CLua::call_Function		( const std::string& strKey, int iNumberofArguments, int iNumberofResults )
{
	//Wenn LUA initialisiert worden ist.
	if( m_bLuaInitiated == true )
	{
		//Sucht im Script nach der globalen Variable mit �bergebenen Namen und packt sie auf den Stack.
		lua_getglobal( m_s_Lua, strKey.c_str() );

		//�berpr�ft ob das oberste im Stack eine Funktion ist.
		if( lua_isfunction( m_s_Lua, -1 ) == false )
		{
			//L�scht den obersten Eintrag im Stack.
			lua_pop( m_s_Lua, 1 );

			//Im LUA-Script befindet sich solch eine Funktion nicht.
			return false;
		}

		//Ruft die Funktion auf, wenn ein Fehler entsteht, wird dieser in den Stack geschoben als String.
		lua_pcall( m_s_Lua, iNumberofArguments, iNumberofResults, 0 );
	
		//�berpr�ft ob auf der obersten Position im Stack ein String ist, wenn dies der Fall ist, ist ein Fehler enstanden.
		if( lua_isstring(m_s_Lua, -1) )
		{
			//Den obersten Eintrag im Stack in einen String umwandeln.
			std::string strError = lua_tostring(m_s_Lua, -1);

			//Ausgabe des Fehlers.
			std::cout << "LUA-Error: " + strError << std::endl;

			//L�scht den obersten Eintrag im Stack.
			lua_pop( m_s_Lua, 1 );

			//Ein Fehler ist entstanden beim aufruf der Funktion.
			return false;
		}
	}
	else
	{
		//LUA wurde nicht initialisiert.
		return false;
	}

	return true;
}

//Schlie�t die LUA-Bibliotheken.
		void					ety::CLua::close_Lua			( void )
{
	//Funktion wird nur ausgef�hrt wenn LUA initialisiert worden ist.
	if( m_bLuaInitiated == true )
	{
		//Lua und dessen Bibliotheken werden geschlossen.
		lua_close( m_s_Lua );

		//Lua wurde geschlossen.
		m_bLuaInitiated = false;
	}
}

//Initialisiert LUA und �ffnet die ben�tigten Bibliotheken.
		void					ety::CLua::init_Lua				( void )
{
	//Wenn LUA noch nicht initialisiert worden ist.
	if( m_bLuaInitiated == false )
	{
		//Neue Instanz von Lua.
		m_s_Lua = luaL_newstate();

		//�ffnet die Lua-Bibliotheken.
		luaL_openlibs( m_s_Lua );

		luabind::open( m_s_Lua );

		luabind::module( m_s_Lua )
		[
			luabind::class_<sf::VideoMode>("sfVideomode")
			.def( luabind::constructor< unsigned int, unsigned int, unsigned int >() )
			.def_readwrite( "width"			, &sf::VideoMode::width			)
			.def_readwrite( "height"		, &sf::VideoMode::height		)
			.def_readwrite( "bitsPerPixel"	, &sf::VideoMode::bitsPerPixel	),

			luabind::class_< sf::Vector2f >("sfVector2f")
			.def( luabind::constructor< float, float >() )
			.def_readwrite( "x"				, &sf::Vector2f::x				)
			.def_readwrite( "y"				, &sf::Vector2f::y				),

			luabind::class_< sf::Vector2i >("sfVector2i")
			.def( luabind::constructor< int, int >() )
			.def_readwrite( "x"				, &sf::Vector2i::x				)
			.def_readwrite( "y"				, &sf::Vector2i::y				)
		];

		//Lua wurde initialisiert.
		m_bLuaInitiated = true;
	}
}

//Schiebt einen String auf den Stack, damit man es einer LUA-Funktion �bergeben kann.
		void					ety::CLua::push_String			( const std::string& strString )
{
	if( m_bLuaInitiated == true )
	{
		lua_pushstring( m_s_Lua, strString.c_str() );
	}
}
//Schiebt einen Integer auf den Stack, damit man es einer LUA-Funktion �bergeben kann.
		void					ety::CLua::push_Integer			( int iInteger )
{
	if( m_bLuaInitiated == true )
	{
		lua_pushinteger( m_s_Lua, iInteger );
	}
}

//Startet eine LUA-Scriptdatei.
const	bool					ety::CLua::start_Script			( const std::string& strScriptname )
{
	//Script wird nur gestartet wenn LUA-Initialisiert worden ist.
	if( m_bLuaInitiated == true )
	{
		//Ruft den Script mit �bergebenen Namen auf.
		if( ( luaL_loadfile( m_s_Lua, strScriptname.c_str() ) || lua_pcall( m_s_Lua, 0, 0, 0 ) ) )
		{
			if( lua_isstring(m_s_Lua, -1) )
			{
				//Den obersten Eintrag im Stack in einen String umwandeln.
				std::string strError = lua_tostring(m_s_Lua, -1);

				//Ausgabe des Fehlers.
				std::cout << "LUA-Error: " + strError << std::endl;

				//L�scht den obersten Eintrag im Stack.
				lua_pop( m_s_Lua, 1 );

				//Ein Fehler ist entstanden beim aufruf der Funktion.
				return false;
			}

			//Ein Fehler ist entstanden beim Aufruf des Scripts.
			return false;
		}

		//Script konnte gestartet werden.
		return true;
	}

	//LUA ist nicht initialisiert.
	return false;
}

//Gibt an ob LUA initialisiert worden ist.
const	bool					ety::CLua::get_IsInitiated		( void )
{
	return m_bLuaInitiated;
}
//Holt aus einer LUA-Script Datei aus einer globalen Variable einen Integer.
const	int						ety::CLua::get_Integer			( const std::string& strKey )
{
	//Funktion wird ausgef�hrt wenn LUA initialisiert worden ist.
	if( m_bLuaInitiated == true )
	{
		//Wird nur aufgerufen, wenn ein String �bergeben wurde, welcher nicht leer ist.
		if( strKey != "" )
		{
			//Sucht im Script nach der gesuchten Variable.
			lua_getglobal( m_s_Lua, strKey.c_str() );
		}
		else
		{
			//Ung�ltiger Schl�ssel f�r eine Variable.
			return -99999;
		}

		int iResult = 0;

		//�berpr�ft ob aufm Stack ein Integer ist.
		if( lua_isnumber( m_s_Lua, -1 ) )
		{
			//Holt den Integer vom Stack und speichert sie.
			iResult = lua_tointeger( m_s_Lua, -1 );

			//L�scht den obersten Eintrag im Stack.
			lua_pop( m_s_Lua, 1 );

			//Der Wert der Variable im LUA-Script konnte erfolgreich ausgelesen werden.
			return iResult;
		}
		else
		{
			//Die Variable beinhaltet keinen Integer-Wert.
			return -99999;
		}	
	}
	else
	{
		//LUA ist nicht initialisiert.
		return -99999;
	}
}
//Holt aus einer LUA-Script Datei aus einem globalen Table einen Integer.
const	int						ety::CLua::get_TableInteger		( const std::string& strTable, const std::string& strKey )
{
	return true;
}
//Holt aus einer LUA-Script Datei aus einer Globalen-Variable einen String.
const	std::string				ety::CLua::get_String			( const std::string& strKey )
{
	//Funktion wird ausgef�hrt wenn LUA initialisiert worden ist.
	if( m_bLuaInitiated == true )
	{
		//Wird nur aufgerufen, wenn ein String �bergeben wurde, welcher nicht leer ist.
		if( strKey != "" )
		{
			//Sucht im Script nach der gesuchten Variable.
			lua_getglobal( m_s_Lua, strKey.c_str() );
		}
		else
		{
			//�ng�ltiger Variablen Name.
			return "NULL";
		}

		std::string strResult = "NULL";

		//�erpr�ft ob aufm Stack ein String ist.
		if( lua_isstring( m_s_Lua, -1 ) )
		{
			//Holt den String vom Stack und speichert sie.
			strResult = lua_tostring( m_s_Lua, -1 );

			//L�scht den obersten Eintrag im Stack.
			lua_pop( m_s_Lua, 1 );
		}
		else
		{
			//Die Variable beinhaltet keinen String.
			return "NULL";
		}

		//Der Wert der Variable konnte erfolgreich ausgelesen werden.
		return strResult;
	}
	else
	{
		//LUA wurde nicht initialisiert.
		return "NULL";
	}
}
//Holt aus einer LUA-Script Datei aus einem globalen Table einen String.
const	std::string				ety::CLua::get_TableString		( const std::string& strTable, const std::string& strKey )
{
	if( m_bLuaInitiated == true )
	{
		std::string szResult = "NULL";

		if( strKey != "" &&  strTable != "" )
		{
			lua_getglobal( m_s_Lua, strTable.c_str() );
		}

		if( lua_istable( m_s_Lua, -1) )
		{
			lua_getfield( m_s_Lua, -1, strKey.c_str() );

			if( lua_isstring( m_s_Lua, -1) )
			{
				szResult = std::string( lua_tostring( m_s_Lua, -1 ) );
			}

			lua_pop( m_s_Lua, 1 );
		}

		return szResult;
	}
	else
	{
		return "ERROR!";
	}
}
//Gibt den Lua-State zur�ck f�r eventuelle feinheiten im LUA-Code.
		lua_State*		const	ety::CLua::get_LuaState			( void )
{
	return m_s_Lua;
}