///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGITEM.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CDialog.hpp"


namespace ety
{	
	class CDialog;
	

	//Diese Klasse ist die Grundlage für alle Dialogitems, daher werden alle von ihr abgeleitet
	//Alle Methoden sind virtual, wodurch es möglich ist alle Methoden auf das jeweilige 
	//Dialogitem umzuschreiben
	class CDialogitem
	{
	private:
				//Es gibt keine privates, da die Klasse nur dazu ist abgeleitet zu werden

	protected:
				
				//Dieses Arribut gibt an, ob das Dialogitem auf Events reagieren soll
				bool										m_bActive;
				//Ob der Ankerpunkt zentriert werden soll, dies bedeutet,
				//dass das Objekt was letztlich vom Dialogitem gezeichnet wird
				//z.B. ein Sprite nicht mit seiner linken oberen Ecke auf dem
				//Ankerpunkt, sondern mit seiner Mitte liegt
				bool										m_bAnchorCentered;
				//Diese Variable gibt an, ob das Dialogitem gefocused ist. Es kann immer nur ein Dialogitem gefocused sein!
				bool										m_bFocused;
				//Diese Variable gibt an, ob der HoverSound schon abgespielt wurde, damit dieser nicht ständig abgespielt wird,
				//wenn die Maus auf einem Dialogitem liegt
				bool										m_bHoverSoundPlayed;
				//Diese Variable zeigt an, ob ein Dialogitem eigentlich aktiviert bzw. deaktiviert ist
				//Denn es kann sein, das ein m_bActive zwar true ist, aber ein Dialogitem dennoch nicht ansprechbar ist, weil z.B. ein Dialog modal ist
				bool										m_bInternActive;
				//Gibt an, ob die Positionberechnung über die Real- oder die "normale" Position erfolgen soll
				bool										m_bRealPosition;
				//Gibt an, ob das Dialogitem sichtbar ist
				bool										m_bVisibility;
				//Gibt die Affinität des Dialogitems an (näheres im Affinitäts-System)
		enum	Affinity::en_etyAffinity					m_en_etyAffinity;
				//Ankerpunkt
		enum	Anchor::en_etyAnchor						m_en_etyAnchor;
				//Diese Variable gibt an, wie das Dialogitem an ein anderes gebunden ist
		enum	AttachedType::en_etyAttachedType			m_en_etyAttachedType;
				//Höhe
				float										m_fHeight;
				//Breite
				float										m_fWidth;
				//Gibt die Position in der Zeichenreihenfolge der Dialogitems an.
				unsigned int								m_uiDrawPosition;	
				//In diesem Vector steht die relative Position des Dialogitems zu einem anderen oder dem ParentDialog
				sf::Vector2f								m_c_sfVector2fPosition;
				//In diesem Vector steht die absolute Position des Dialogitems
				sf::Vector2f								m_c_sfVector2fRealPosition;
				//In dieser Map sind alle verfügbaren Sounds des Dialogitems gespeichert
				mapSoundTypeSounds							m_mapEventSounds;
				//Die CustomID ist die einzigartige ID jedes Dialogitems, damit man leicht auf das
				//beliebige zugreifen kann. Aus programmiertechnischen Gründen ist es schon möglich,
				//dass mehrere Dialogitems die gleiche ID tragen, dies sollte aber innerhalb eines
				//Dialogs vermieden werden, weil es sonst zu Fehlern kommen kann
				std::string									m_strCustomID;
				//Gibt den DialogitemType an z.B. enBUTTON
		enum	DialogitemType::en_etyDialogitemType		m_en_etyDialogitemType;
				//Pointer auf den Parent-Dialog.
				CDialog*									mp_c_etyDialogParentDialog;
				//Legt das Dialogitem fest, an dessen Ankerpunkt sich dieses Dialogitem orinentieren soll
				CDialogitem*								mp_c_etyDialogitemAnchorOrientation;
				//Pointer auf das Parent-Dialogitem, da ein Dialogitem auch aus mehreren verschiedenen
				//zusammen gesetzt sein kann
				CDialogitem*								mp_c_etyDialogitemParentDialogitem;

		virtual	void										calculate_Positions						(bool bRealPosition);

	public:
				
		
															//Kon- und Destruktor
															CDialogitem								(void);
		virtual												~CDialogitem							(void);


		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Fügt der Eventsoundmap einen weiteren Sound hinzu
		///
		/// \parameter	std::string strNewEventSound
		///
		/// \rückgabe	void
		///////////////////////////////////////////////////////////////////////////////////
		virtual void										add_EventSound							(enum SoundType::en_etySoundType en_etySoundType, sf::Sound* p_c_sfSoundNewEventSound);
		virtual	void										adjust_SizeToResolution					( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual unsigned	int								check_ValuesAfterDecimalPoint			(float fValue);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Überprüft ob der Maustreiger über dem Dialogitem ist. Standartmäßig wird verglichen
		/// ob der Maustreiger innerhalb der angebenen Position mit Höhe und Breite, was zusammen
		/// ein Rechteck bildet, liegt.
		///
		/// \parameter	sf::RenderTexture& p_sfRenderWindowApplication
		///
		/// \rückgabe	void
		///////////////////////////////////////////////////////////////////////////////////
		virtual	bool										check_MouseCoordinates					(void);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Zeichnet das Dialogitem in das RenderTexture, jede draw-Funktion ist von Dialogitem
		///	zu Dialogitem unterschiedlich. Diese Variante gibt einfach "false", weil nichts
		///	gezeichnet wurde, es gibt schließlich aber auch nichts, was in der Basisklasse
		///	gezeichnet werden könnte.
		///
		/// \parameter	sf::RenderTexture* p_c_sfRenderTextureScene -> In dieses Bild/Szene werden
		///	alle darzustellenden Objekte gezeichnet. In diesem Fall das Dialogitem
		///
		/// \rückgabe	bool -> Ob das Dialogitem gezeichnet wurde
		/////////////////////////////////////////////////////////////////////////////////// 
		virtual	bool										draw_Dialogitem							(sf::RenderTexture* p_c_sfRenderTextureScene);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Verwaltet die Events jedes einzelnen Dialogitemtypes. Die Funktion in der 
		///	Basisklasse ist leer!
		///
		/// \parameter	sf::Event c_sfEvent
		///				-> Der EventType der ausgeführt werden soll
		///
		/// \rückgabe	void
		/////////////////////////////////////////////////////////////////////////////////// 
		virtual void										handle_InternEvents						(const sf::Event& c_sfEvent);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		///	Diese Funktion passt den Colorfilter des Dialogitems an
		///
		/// \parameter	sf::Vector3f c_sfVector3fFactors
		///				-> Die 3 Porzentsätze für die Veränderung des Colorfilters
		///
		/// \rückgabe	void
		/////////////////////////////////////////////////////////////////////////////////// 
		virtual void										modificate_Colorfilter					(sf::Vector3f c_sfVector3fFactors);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Entfernt einen Sound aus der Eventsoundmap
		///
		/// \parameter	std::string strEventSound
		///
		/// \rückgabe	bool -> Ob der Sound gelöscht wurde
		/////////////////////////////////////////////////////////////////////////////////// 
		virtual bool										remove_EventSound						(enum SoundType::en_etySoundType en_etySoundType);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Setzt den Focus eines Dialogitems zurück
		///
		/// \parameter	/
		///
		/// \rückgabe	/
		/////////////////////////////////////////////////////////////////////////////////// 
		virtual void										reset_FocusedDialogitem					(void);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Updatet das Dialogitem
		///
		/// \parameter	void
		///
		/// \rückgabe	void
		///////////////////////////////////////////////////////////////////////////////////
		virtual	void										update_Dialogitem						(const sf::Uint32& uiFrameTime);



		//Set-Methoden
		virtual void										set_Active								(bool bActive);
		virtual void										set_AnchorCentered						(bool bAnchorCentered);
		virtual	void										set_Focus								(bool bFocus);
		virtual void										set_HoverSoundPlayed					(bool bHoverSoundPlayed);
		virtual void										set_Visibility							(bool bVisibility);
		virtual	void										set_Affinity							(enum Affinity::en_etyAffinity en_etyAffinity);
		virtual void										set_Anchor								(enum Anchor::en_etyAnchor en_etyAnchor);	
		virtual bool										set_AttachedType						(enum AttachedType::en_etyAttachedType en_etyAttachedType);
		virtual void										set_Height								(float fHeight);
		virtual void										set_Width								(float fWidth);
		virtual void										set_DrawPosition						(unsigned int uiDrawPosition);
		virtual void										set_Position							(sf::Vector2f c_sfVector2fPosition);
		virtual	void										set_RealPosition						(sf::Vector2f c_sfVector2fRealPosition);
		virtual	void										set_RealPosition						(bool bRealPosition);
		virtual	void										set_CustomID							(std::string strNewCustomID);
		virtual	bool										set_ParentDialogitem					(CDialogitem& p_c_etyDialogitemNewParentDialogitem);
		virtual	void										set_AnchorOrientation					(CDialogitem* const p_c_etyDialogitemAnchorOrientation);
						

		//Get-Methoden
		virtual bool										get_Active								(void);
		virtual	bool										get_AnchorCentered						(void);
		virtual	bool										get_Focus								(void);
		virtual bool										get_HoverSoundPlayed					(void);
		virtual bool										get_RealPositionStatus					(void);
		virtual bool										get_Visibility							(void);
		virtual float										get_Height								(void);
		virtual float										get_Width								(void);	
		virtual unsigned int								get_DrawPosition						(void);
		virtual sf::Sound* const							get_EventSound							(enum SoundType::en_etySoundType en_etySoundType);
		//Get-Methoden

		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Berechnet den übergebenen Ankerpunkt auf dem Dialogitem.
		/// Falls ein Dialogitem aus mehreren Dialogitems besteht.
		///
		/// \parameter	enum Anchor::en_etyAnchor en_etyAnchor -> Ankerpunkt des Dialogitems
		///
		/// \rückgabe	sf::Vector2f -> Vector mit der Position des Dialogitems
		///////////////////////////////////////////////////////////////////////////////////
		virtual	sf::Vector2f								get_Anchor								(enum Anchor::en_etyAnchor en_etyAnchor);
		///////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Da die Position des Dialogitems sich immer auf die Position innerhalb des Dialogs
		/// bezieht, beschreibt sie nicht die "wahre" Position auf dem Fenster. Durch diese
		/// Methode ist es möglich sich die "wahre" Position zuholen.
		///
		/// \parameter	void
		///
		/// \rückgabe	sf::Vector2f -> Vector mit Position des Dialogitems
		///////////////////////////////////////////////////////////////////////////////////
		virtual sf::Vector2f								get_RealPosition						(void);		
		virtual sf::Vector2f								get_Position							(void);	
		virtual mapSoundTypeSounds*	const					get_EventSoundmap						(void);
		virtual	const std::string&							get_CustomID							(void);
		virtual	enum Affinity::en_etyAffinity				get_Affinity							(void);
		virtual enum Anchor::en_etyAnchor					get_Anchor								(void);
		virtual enum AttachedType::en_etyAttachedType		get_AttachedType						(void);
		virtual enum DialogitemType::en_etyDialogitemType	get_DialogitemType						(void);
		virtual CDialog* const								get_ParentDialog						(void);
		virtual CDialogitem* const							get_AnchorOrientation					(void);
		virtual CDialogitem* const							get_ParentDialogitem					(void);
		
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGITEM.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////