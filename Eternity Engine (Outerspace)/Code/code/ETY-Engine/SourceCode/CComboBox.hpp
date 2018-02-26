///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCOMBOBOX.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "CDialogitem.hpp"

namespace ety
{
	class CPictureControl;
	class CScrollbar;
	class CButton;
	class CGamesettings;
	//Diese Klasse hat die Funktion einer konventionellen ComboBox.
	//Sie besteht aus einem Header in dem der aktuell ausgewählte Eintrag steht und diesen kann mann anwählen,
	//um die ComboBox zu öffnen. Im geöffneten ("unfolded") Zustand werden eine gewisse Anzahl von Einträgen in Form von Buttons angezeigt.
	//Desweiteren ist das Anlegen einer Scrollbar möglich, um durch die Einträge zuscrollen. Dadurch können mehr Einträge "angezeigt"/verwaltet
	//werden, als die ComboBox eigentlich gleichzeitig anzeigen kann!
	//Die ComboBox kann aber auch als ListBox angelegt werden!!!
	//Dies hat nun die Folge, dass der Dialogitemtype der Klasse zwar DialogitemType::enLISTBOX ist, aber die Klasse dennoch CComboBox!
	//Eine ListBox besteht aus einem Hintergrund und mehreren Einträgen in Form von Buttons. Desweiteren kann eine Scrollbar für die ListBox angelegt werden.

	//Viele Teile des Codes sind für Combo- und ListBox gleich aus diesem Grund habe ich mich dazu entschieden beide Dialogitems über die selbe Klasse laufen zulassen.
	class CComboBox :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann


	protected:
					
					//Dieses Attribut gibt an, ob die Einträge der ComboBox immer an die aktuelle Sprache angepasst werden sollen
					bool					m_bLocalization;
					//Dieses Attribut gibt an, ob die ComboBox eine Scrollbar besitzen soll
					bool					m_bScrollbar;
					//Gibt an ob der Slider der Scrollbar aktiv, also benutzbar ist
					bool					m_bSliderActive;
					//Wenn dieses Attribut true ist, dann ist die ComboBox geöffnet, wenn fals ist folded, also geschlossen
					bool					m_bUnfolded;
					//Gibt den prozentualen Anteil des HeaderButtons an der ComboBox an
					//Was für die Aufteilung in HeaderBox und HeaderButton sehr wichtig ist
					//Da sich beide das selbe Bild teilen und zusammen die ComboBox darstellen
					//Und damit auch die Größe der Scrollbar
					float					m_fScrollbarSizePercent;
					//Die beiden unteren Attribute geben die ursprüngliche, noch nicht auf die Auflösung angepasste, Größe der
					//ComboBox an. Da im Konstruktor die übergebenen Ursprungsgrößen geändert wurden, können sie nicht mehr
					//Für die Erstellung neuer Einträge verwendet werden, deswegen muss die "Origin-Size" gespeichert werden
					float					m_fOrigin_Width;
					float					m_fOrigin_Height;
					int						m_iListBoxEntrySize;
					unsigned int			m_uiDisabledButtons;
					//Gibt die Größe der Schrift in der ComboBox an
					unsigned int			m_uiTextCharactersize;
					//Gibt die Position des Entries an der momenttan ausgewählt ist und in der HeaderBox angezeigt wird
					unsigned int			m_uiCurrentSelectedEntry;
					//Gibt die Anzahl der Entries an, welche beim öffnen angezeigt werden sollen
					unsigned int			m_uiUnfoldedEntries;
					unsigned int			m_uiVisiblityRange;
					//Diese Liste speichert alle ComboBox-Einträge
					std::list<CButton*>		m_listBoxEntries;
					//Die beiden unteren Zeiger beschreiben den "Header" der ComboBox
					CButton*				mp_c_etyButtonHeaderBox;
					//Dieses PictureControl stellt den Hintergrund der ListBox da! Bei einer ComboBox ist er unbenutzt!
					CPictureControl*		mp_c_etyPictureControlBackground;
					//Dieser Zeiger beschreibt die mögliche Scrollbar der ComboBox
					CScrollbar*				mp_c_etyScrollbar;
					//Der Farbfilter der ComboBox
					ety::Color				m_c_etyColorComboBoxColorFilter;
					//Die Textfarben der ComboBox
					ety::Color				m_c_etyColorCaptionTextcolor;
					ety::Color				m_c_etyColorCaptionTextcolor_highlighted;
					//Diese Textur enthält alle Teilbilder der ComboBox, dies bedeutet: ComboBoxHeaderBox, ComboBoxHeaderButton,Entrie, jeweils auch
					//gehighlighted sowie die Teilbilder der Scrollbar
					sf::Texture				m_c_sfTextureComboxSet;
					//Diese beiden Attribute geben die Größe und Position der ComboBox in der oberen Textur an
					//Es wird nur die Größe und Position des HeaderBoxButtons angegeben, bei der ComboBox
					sf::IntRect				m_c_sfIntRectComboBoxSubRect;
					sf::IntRect				m_c_sfIntRectEntrySubRect;


	public:
											//Kon- und Destruktor
											CComboBox												(void);
											~CComboBox												(void);

											//Überladene Konstruktoren
											CComboBox												(
																									  bool bComboBox, std::string strCustomID, 
																									  const sf::Texture& c_sfTextureComboBoxTexture, float fWidth, float fHeight, 
																									  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectComboBoxSubRect, 
																									  ety::Color c_etyColorTextcolor, ety::Color c_etyColorTextcolor_Highlighted, 
																									  unsigned int uiTextCharactersize, CDialogitem* p_c_etyDialogitemParent, 
																									  CDialog* p_c_etyDialogParentDialog, float fScrollbarSizePercent = 0.f,
																									  unsigned int uiListBoxEntrySubRectSize = 0
																									);



																									/*std::list<std::string>* p_listBoxEntries, 
																									int iListBoxEntrySize = 0*/

																									//CGamesettings* const p_c_etyGamesettingsManager, 
												
													
					///////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					/// Fügt der ComboBox einen neuen Eintrag an der angegebenen Position hinzu
					///
					/// \parameter	std::string strEntry -> Inhalt der Eintrags, 
					///				unsigned int uiPosition -> Position des Eintrags
					///
					/// \rückgabe	bool -> Da jeder Eintrag nur einmal in der ComboBox vorkommen kann
					///				wird zurück gegeben ob das Einfügen funktioniert hat oder nicht
					///////////////////////////////////////////////////////////////////////////////////
					bool					add_ListEntry											(std::string strEntry, unsigned int uiPosition);
					void					add_ListEntries											(std::list<std::string> listNewEntries, bool bClearEntries = false);
		virtual		void					adjust_SizeToResolution									( 
																									  const sf::VideoMode& c_sfVideoModeNewSettings, 
																									  const sf::VideoMode& c_sfVideoModeOldSettings 
																									);

		virtual		bool					check_MouseCoordinates									(void);
					void					clear_Entries											(void);
					bool					create_Scrollbar										(sf::IntRect c_sfIntRectScrollbarSubRect);

						
					///////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					/// Diese Funktion löscht einen Eintrag aus der ComboBox, entweder über den Inhalt
					///	des Eintrags oder die Position
					///
					/// \parameter	std::string strEntry -> Inhalt der Eintrags, 
					///				unsigned int uiPosition -> Position des Eintrags
					///
					/// \rückgabe	bool -> Gibt zurück ob das Löschen funktioniert hat
					///////////////////////////////////////////////////////////////////////////////////
					bool					delete_ListEntry										(unsigned int uiPosition);
					bool					delete_ListEntry										(std::string strEntry);
		virtual		bool					draw_Dialogitem											(sf::RenderTexture* p_c_sfRenderTextureScene);
					void					focus_Entry												(unsigned int uiPosition);

		virtual		void					handle_InternEvents										(const sf::Event& c_sfEvent);
					
					///////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					/// Gibt an ob der übergebene Eintrag schon in der ComboBox vorhanden ist
					///
					/// \parameter	std::string strEntry -> Inhalt der Eintrags 
					///
					/// \rückgabe	bool -> Gibt zurück ob sich der Eintrag in der ComboBox befindet
					///////////////////////////////////////////////////////////////////////////////////
					bool					includes_Entry											(std::string strEntry);

		virtual		void					modificate_Colorfilter									(sf::Vector3f c_sfVector3fFactors);

					//Um die richtige Funktionsweise der ComboBox zugewährleisten musste diese Funktion überschrieben werden
		virtual		void					reset_FocusedDialogitem									(void);

					///////////////////////////////////////////////////////////////////////////////////
					/// \Beschreibung: 
					/// Durch diese Funktion kann die ComboBox geöffnet oder geschlossen werden
					///
					/// \parameter	bool bUnfoldEntries -> Ob die ComboBox geöffnet oder geschlossen
					///				werden soll
					///
					/// \rückgabe	void
					///////////////////////////////////////////////////////////////////////////////////
					void					unfold_Entries											(bool bUnfoldEntries);
		virtual		void					update_Dialogitem										(const sf::Uint32& uiFrameTime);


		//Set-Methoden	
					void					set_CurrentSelectedEntry								(unsigned int uiNewSelectedEntrie, bool bFocusSelectedEntry);
					void					set_UnfoldedEntries										(unsigned int uiUnfoldedEntries);
					void					set_ColorFilter											(ety::Color c_etyColorFilter);
					void					set_TextColor											(ety::Color c_etyColorTextColor);
					void					set_TextColorHighlighted								(ety::Color c_etyColorTextColorHighlighted);
					void					set_Localization										(bool bLocalization);
		virtual		void					set_Active												(bool bActive);
		virtual		void					set_Focus												(bool bFocus);
		virtual		void					set_Height												(float fHeight);
		virtual		void					set_Width												(float fWidth);


		//Get-Methoden
					bool					get_Localization										(void);
					bool					get_Unfolded											(void);
					int						get_PositionofEntry										(std::string strEntry);
					int						get_PositionofEntry										(const CDialogitem* p_c_etyDialogitemEntry);
					unsigned int			get_CurrentSelectedEntrie								(void);
					unsigned int			get_Size												(void);
					unsigned int			get_UnfoldedEntries										(void);
					std::string				get_ListEntry											(unsigned int uiPosition);
					ety::Color&				get_ColorFilter											(void);
					ety::Color&				get_TextColor											(void);
					ety::Color&				get_TextColor_highlighted								(void);
					std::list<CButton*>&	get_ListEntriesButtons									(void);
					CButton* const			get_ListEntryButton										(std::string strEntry);
					CButton* const			get_ListEntryButton										(unsigned int uiPosition);
					CButton* const			get_HeaderBox											(void);
					CPictureControl* const	get_ListBoxBackground									(void);
					CScrollbar* const		get_Scrollbar											(void);
	};
} 

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCOMBOBOX.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////