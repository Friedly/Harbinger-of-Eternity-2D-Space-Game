#pragma once

#pragma warning( disable : 4503 )

//Includes der Eternity-Engine
#include "CLogfile.hpp"
#include "CRessourceManager.hpp"

//Includes der SFML-Bibliothek
#include <SFML\Audio\Sound.hpp>

//Includes des Compilers
#include <map>

namespace ety
{
	//Dieses Enum gibt den Typ, zu welchem Zweck dieser Sound abgespielt werden soll, an.
	namespace SoundType
	{
		enum en_etySoundType		{ enCLICK, enDOUBLECLICK, enHOVER, enWRITEOUT, enSCROLL, enAPPEAR, enDISAPPEAR, enINPUT, enERROR };
	}
	//Dieses Enum gibt an, zu welchem Dialogitemtyp der Sound gehört.
	namespace DialogitemType
	{
		enum en_etyDialogitemType	{ enBUTTON, enCHECKBOX, enCOMBOBOX, enEDITCONTROL, enLABEL, enLISTBOX, enPICTURECONTROL, enSCROLLBAR, enSLIDECONTROL, enTEXTBOX, enALL, enERROR };
	}

	//Diese Struktur behinhaltet einen Zeiger auf eine Sounddatei
	//und der Name dieser Datei.
	struct SStandardSound
	{
		std::string		m_strSoundname;
		sf::Sound*		mp_c_sfSound;
	};

	//Typedefs für die STL-Map^3 der Dateien zum Laden um die Übersicht zu bewahren.
	typedef std::map< std::string, std::string >													mapFileToLoad;
	typedef	std::map< ety::RessourceType::en_etyRessourceType, mapFileToLoad >						mapFileToLoadbyRessourceType;	
	typedef std::map< std::string, mapFileToLoadbyRessourceType >									mapFilesToLoadbyGamestate;

	//Typedefs für die STL-Map^4 der Standard-Sounds um die Übersicht zu bewahren.
	typedef std::map< ety::SoundType::en_etySoundType, sf::Sound*>									mapSoundsbySoundtype;
	typedef std::map< ety::SoundType::en_etySoundType, SStandardSound >								mapStandardSoundbySoundtype;
	typedef std::map< ety::DialogitemType::en_etyDialogitemType, mapStandardSoundbySoundtype >		mapStandardSoundbyDialogitemtype;
	typedef std::map< std::string, mapStandardSoundbyDialogitemtype >								mapStandardSoundsbyGamestate;

	//Vordeklarationen der Klassen um mehrfach Einbindungen zu verhindern.
	class CRessourceManager;
	class CGamesettings;
	class CProgressbar;
	class CLua;

	class CFilemanagement
	{
	private:
		//Dieser String bewahrt den Namen der Scriptdatei, welche aufgerufen wird um das Objekt zu initialisieren.
				std::string										m_strScript;
		
		//Diese Map speichert zu jedem Spielzustand(String-Schlüssel)
		//die Anzahl der zu ladenden Dateien.
				std::map< std::string, unsigned int >			m_mapRessourceCountbyGamestate;
		//Diese Map speichert für jeden Gamestate jeweils alle Ressourcen die es benötigt 
		//und mit den nötigen Informationen um sie zu laden.
				mapFilesToLoadbyGamestate						m_mapFilesToLoadbyGamestate;
		//Diese Map speichert für jeden Gamestate die Standard-Sounddateien mit den jeweils
		//nötigen Informationen, zu welchen Dialogitem sie gehören und bei welchen Soundtyp
		//sie abgespielt werden.
				mapStandardSoundsbyGamestate					m_mapStandardSoundsbyGamestate;

	protected:

	public:
		//Standart Konstruktor und Destruktor.
																CFilemanagement						( void );
																~CFilemanagement					( void );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Fügt die Informationen einer Ressource, welche noch geladen werden soll, hinzu.
		///
		/// 1P. Es wird der Gamestate-Name benötigt, um die Ressource einem Gamestate zuweisen zu können.
		/// 2P. Der Typ der Datei muss angegeben werden, denn Bilder müssen anders geladen werden als Audiodateien.
		/// 3P. Name der Datei.
		/// 4P. Der Ordnername in der sich die Datei befindet, erleichtert und verschnellert das finden der Datei.
		/// 
		/// \parameter	const std::string&, const std::string&, const std::string&, const std::string&
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				void											add_FileToLoad						( const std::string& strGamestateName, const ety::RessourceType::en_etyRessourceType en_etyRessourceType, const std::string& strFileToLoad, const std::string& strDirectoryKey = ""  );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Fügt die Informationen einer Standard-Sounddatei, welche noch geladen werden soll, hinzu.
		/// Eine Standard-Sounddatei ist eine Sounddatei für einen gewissen Dialogitemtyp z.B. einen Knopf.
		/// In einem Spielzustand werden diese Standard-Sounddateien für den jeweiligen Dialogitemtyp immer abgespielt.
		///
		/// 1P. Es wird der Gamestate-Name benötigt, um die Sounddatei einem Gamestate zuweisen zu können.
		/// 2P. Der Dialogitemtyp muss angegeben werden. ( Button, Combobox etc. )
		/// 3P. Ein Soundtyp muss ebenfalls angegeben sein, denn ein Dialogitemtyp kann mehrere Sounds für verschiedene
		///		Zwecke abspielen. ( Beispiele: Beim Klicken und beim drüber fahren mit der Maus etc. )
		/// 4P. Name der Sounddatei.
		/// 5P. Der Ordnername in der sich die Datei befindet, erleichtert und verschnellert das finden der Datei.
		/// 6P. Soll die Sounddatei geladen werden, es kann sein das ein State diese Sounddatei schon geladen hat.
		///
		/// \parameter	const std::string&, const std::string&, const std::string&, const std::string&, const std::string&
		///				const bool
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				void											add_StandardSoundToLoad				( const std::string& strGamestateName, const ety::DialogitemType::en_etyDialogitemType en_etyDialogitemType, const ety::SoundType::en_etySoundType en_etySoundType, const std::string& strFileToLoad, const std::string& strDirectoryKey, const bool bLoadSound = true );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Um den Dialogitems ihre Standard-Sounddateien zu geben, müssen die vorherigen hinzugefügten Standard-Sounddatei-Informationen
		/// ( mit Hilfe der Funktion add_StandardSoundToLoad(..) ) dazu benutzt werden denen die richtigen Sounddateien zu zuweisen.
		/// Dies erfüllt diese Methode, sie fordert mit Hilfe der Informationen die Sounddateien vom aktuellen Audiomanager an und
		/// speichert diese zu den Informationen.
		///
		/// 1P. Der Spielzustandsname für welchen die Standart-Sounds bereit gestellt werden sollen.
		/// 2P. Der aktuelle Audiomanager.
		/// 
		/// \parameter	const std::string&, ety::CAudiomanager* const
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				void											assign_StandardSounds				( const std::string& strGamestateName, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Überprüft ob für ein Gamestate Ressourcen zum Laden eingetragen wurden.
		///
		/// 1P. Der Spielzustandsname der überprüft werden soll.
		/// 
		/// \parameter	const std::string&
		/// \rückgabe	const bool
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const	bool											check_ExistsRessources				( const std::string& strGamestateName );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Diese Methode braucht den Audio- und Graphic-manager um die Ressourcen, welche geladen wurden, wieder aus dem Arbeitsspeicher zu entfernen.
		///
		/// 1P. Der Spielzustandsname dessen Ressourcen wieder entfernt werden sollen.
		/// 2P. Der aktuelle Audiomanager.
		/// 3P. Der aktuelle Graphicmanager.
		/// 
		/// \parameter	const std::string&, CAudiomanager* const, CGraphicmanager* const
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				void											cleanup_Ressources					( const std::string& strGamestateName, ety::CRessourceManager* const p_c_etyCurrentRessourceManager );
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Es werden alle Ressourcen für den gewählten Spielzustand geladen. Wenn man wünscht mit einem Ladebalken.
		///
		/// 1P. Der Spielzustandsname dessen Ressourcen geladen werden sollen.
		/// 2P. Der aktuelle Audiomanager.
		/// 3P. Der aktuelle Graphicmanager.
		/// 4P. Ein schon initialisierter Ladebalken.
		/// 
		/// \parameter	const std::string&, CAudiomanager* const, CGraphicmanager*, const CProgressbar* const  
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				void											load_Ressources						( std::vector<std::string>* const vecGamestatesToLoad, ety::CRessourceManager* const p_c_etyCurrentRessourceManager, CProgressbar* const p_c_etyCurrentProgressBar = NULL );
				void											load_Ressources						( const std::string& strGamestatesToLoad, ety::CRessourceManager* const p_c_etyCurrentRessourceManager, CProgressbar* const p_c_etyCurrentProgressBar = NULL );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Registriert diese Klasse zum Lua-Script.
		///
		///	1P. Das Lua-Script.
		///
		/// \parameter	ety::CLua* const
		/// \rückgabe	void
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static	void											register_ClassToLuabind				( ety::CLua* const p_c_etyLuaScript );	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Gibt für einen Spielzustand die Anzahl der zu ladenden Ressourcen für diesen zurück.
		///
		/// 1P. Der Spielzustandsname.
		/// 
		/// \parameter	const std::string&
		/// \rückgabe	const unsigned int
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const	unsigned int									get_RessourceCount					( const std::string& strGamestateName );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Gibt für einen Spielzustand die Standard-Sounds für einen bestimmten Dialogitemtyp zurück.
		///
		/// 1P. Der Spielzustande wessen Standard-Sounds geladen werden sollen.
		/// 2P. Der Dialogitemtyp zu dem die Standard-Sounds gehören.
		/// 
		/// \parameter	const std::string&, const ety::DialogitemType::en_etyDialogitemType
		/// \rückgabe	const mapSoundsbySoundtype
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		const	mapSoundsbySoundtype							get_StandardSounds					( const std::string& strGanestateName, const ety::DialogitemType::en_etyDialogitemType en_etyDialogitemtype );
	};
}