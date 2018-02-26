//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////																																	   ///////////
///////////															CGameState.cpp															   ///////////
///////////																									                                   ///////////
///////////						Die Basisklasse eines Spielzustandes. Um ein Spielzustand zu erstellen muss man von ihr ableiten.			   ///////////
///////////						Alle wichtigen Methoden sind virtual deklariert und müssen überschrieben werden.							   ///////////
///////////																																	   ///////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 #pragma warning( disable : 4503 )

//Includes der Eternity-Engine
#include "CGameState.hpp"
#include "CLogfile.hpp"
#include "CGameStateManager.hpp"

#include "CDialogManager.hpp"
#include "CDialog.hpp"
#include "CButton.hpp"
#include "CCheckbox.hpp"
#include "CComboBox.hpp"
#include "CPictureControl.hpp"
#include "CScrollbar.hpp"
#include "CLabel.hpp"
#include "CEditControl.hpp"



		//Der Konstruktor initialisiert den Spielzustand mit seinem Namen.
																				ety::CGameState::CGameState							( const std::string& strStateName )
	: m_strGameStateName					( strStateName )
	, m_en_etyGameStateStatus				( ety::GamestateStatus::enIDLE )
{
}
		//Virtueller Destruktor weil diese Klasse als Basisklasse für viele Spielzustände dient.
																				ety::CGameState::~CGameState						( void )
{
	mp_c_etyGameStatemanager = NULL;
}


		void																	ety::CGameState::init_GameState						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
	CLua* p_c_etyLuaScript = get_GameStatemanager()->get_LuaScript();

	//Initialisieren von LUA und LUABIND.
	p_c_etyLuaScript->init_Lua();

	//Registriere die Klassen mit Hilfe von LUABIND.
	//Diese Klassen können dann im Script benutzt werden.
	ety::CRessourceManager	::register_ClassToLuabind( p_c_etyLuaScript );
	ety::CGamesettings		::register_ClassToLuabind( p_c_etyLuaScript );

	//An LUA die gewünschten Objecte zum bearbeiten weiter geben.
	luabind::globals( p_c_etyLuaScript->get_LuaState() )["c_etyRessourceManager"	]	= p_c_etyCurrentRessourceManager;
	luabind::globals( p_c_etyLuaScript->get_LuaState() )["c_etyGamesettingsmanager"	]	= p_c_etyCurrentGamesettingManager;

	//Starten des LUA-Scriptes.
	p_c_etyLuaScript->start_Script( ("Scripts/" + m_strGameStateName + ".lua") );

	//Schließen von LUA.
	p_c_etyLuaScript->close_Lua();
}
		//Die Set-Methoden zum setzen privater Membervariablen.
		void																	ety::CGameState::set_GameStatemanager				( ety::CGameStateManager* const p_c_etyGameStatemanager)
{
	mp_c_etyGameStatemanager = p_c_etyGameStatemanager;
	m_en_etyGameStateStatus	 = ety::GamestateStatus::enIDLE;
}
		void																	ety::CGameState::set_GameStateStatus				( const enum ety::GamestateStatus::en_etyGamestateStatus en_etyGamestateStatus )
{
	m_en_etyGameStateStatus = en_etyGamestateStatus;
}

		//Die Get-Methoden zur Rückgabe von privaten Membervariablen.

const	std::string&															ety::CGameState::get_GameStateName					( void )
{
	return m_strGameStateName;
}
const	ety::GamestateStatus::en_etyGamestateStatus								ety::CGameState::get_GameStateStatus				( void )
{
	return m_en_etyGameStateStatus;
}
		ety::CGameStateManager*										 const		ety::CGameState::get_GameStatemanager				( void )
{
	return mp_c_etyGameStatemanager;
}
