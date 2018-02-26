///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCOMBOBOX.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include "CComboBox.hpp"

#include "CButton.hpp"
#include "CPictureControl.hpp"
#include "CLabel.hpp"
#include "CScrollbar.hpp"




							ety::CComboBox::CComboBox								(void)
				:m_bUnfolded								(false)
				,mp_c_etyButtonHeaderBox					(NULL)
				,mp_c_etyScrollbar							(NULL)
				,m_uiDisabledButtons						(0)
{
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}


							ety::CComboBox::~CComboBox								(void)
{
	//Das richtige Löschen und entfernen der ComboBox-Elemente

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		delete mp_c_etyButtonHeaderBox;
		mp_c_etyButtonHeaderBox = NULL;
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		delete mp_c_etyPictureControlBackground;
		mp_c_etyPictureControlBackground = NULL;
	}

	std::list<CButton*>::iterator itListEntries = m_listBoxEntries.begin();

	for(itListEntries ; itListEntries != m_listBoxEntries.end() ; itListEntries = m_listBoxEntries.begin())
	{
		CButton* p_c_etyButtonTmpPointer = (*itListEntries);
		m_listBoxEntries.erase(itListEntries);
		mp_c_etyDialogParentDialog->delete_Dialogitem(p_c_etyButtonTmpPointer);
		p_c_etyButtonTmpPointer = NULL;
	}
}

							ety::CComboBox::CComboBox								(
																					  bool bComboBox, std::string strCustomID, 
																					  const sf::Texture& c_sfTextureComboBoxTexture, float fWidth, float fHeight, 
																					  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectComboBoxSubRect, 
																					  ety::Color c_etyColorTextcolor, ety::Color c_etyColorTextcolor_Highlighted, 
																					  unsigned int uiTextCharactersize, CDialogitem* p_c_etyDialogitemParent, 
																					  CDialog* p_c_etyDialogParentDialog, float fScrollbarSizePercent, unsigned int uiListBoxEntrySubRectSize
																					)

				:m_bUnfolded									(false)
				,m_bScrollbar									(false)
				,m_fScrollbarSizePercent						(fScrollbarSizePercent)
				,mp_c_etyButtonHeaderBox						(NULL)
				,mp_c_etyPictureControlBackground				(NULL)
				,mp_c_etyScrollbar								(NULL)
				,m_uiUnfoldedEntries							(0)
				,m_c_sfTextureComboxSet							(c_sfTextureComboBoxTexture)
				,m_c_etyColorCaptionTextcolor					(c_etyColorTextcolor)
				,m_c_etyColorCaptionTextcolor_highlighted		(c_etyColorTextcolor_Highlighted)
				,m_uiCurrentSelectedEntry						(0)
				,m_uiDisabledButtons							(0)
				,m_uiTextCharactersize							(uiTextCharactersize)
				,m_bLocalization								(true)
				,m_fOrigin_Width								(fWidth)
				,m_fOrigin_Height								(fHeight)
				,m_iListBoxEntrySize							(0)
				,m_c_sfIntRectComboBoxSubRect					(c_sfIntRectComboBoxSubRect)
{
	sf::VideoMode c_sfVideoModeGamesettings		=	p_c_etyDialogParentDialog->get_VideoMode();

	m_strCustomID								=	strCustomID;
	m_bVisibility								=	true;
	m_bActive									=	true;
	m_bInternActive								=	true;
	m_bAnchorCentered							=	false;
	m_bRealPosition								=	false;
	m_uiDrawPosition							=	0;
	m_en_etyAffinity							=	Affinity::enSTANDARD;
	m_en_etyAnchor								=	Anchor::enTOPLEFT;
	mp_c_etyDialogitemParentDialogitem			=	p_c_etyDialogitemParent;
	mp_c_etyDialogParentDialog					=	p_c_etyDialogParentDialog;
	mp_c_etyDialogitemAnchorOrientation			=	NULL;
	m_en_etyAttachedType						=	AttachedType::enNOTATTACHED;	
	m_fWidth									=	c_sfVideoModeGamesettings.width*float(fWidth/1680.f);
	m_fHeight									=	c_sfVideoModeGamesettings.height*float(fHeight/1050.f);
	
	if(p_c_etyDialogitemParent != NULL)
	{
		m_en_etyAttachedType					=	AttachedType::enCHILDREN;
	}

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;

	calculate_Positions(false);


	if(bComboBox == true)
	{
		//Die spezifischen Vorgänge zum Erstellen einer "richtigen" ComboBox
		m_en_etyDialogitemType							=	DialogitemType::enCOMBOBOX;
		m_c_sfIntRectEntrySubRect						=	m_c_sfIntRectComboBoxSubRect;
		m_c_sfIntRectEntrySubRect.top					=	m_c_sfIntRectEntrySubRect.top + m_c_sfIntRectEntrySubRect.height;

		
		//Anlegen der HeaderBox
		mp_c_etyButtonHeaderBox							=	new CButton(strCustomID + "HeaderBoxButton", c_sfTextureComboBoxTexture, m_fOrigin_Width, m_fOrigin_Height, sf::Vector2f(0,0), 
																		c_sfIntRectComboBoxSubRect, this, mp_c_etyDialogParentDialog);

		//Anlegen der Caption der HeaderBox
		mp_c_etyButtonHeaderBox->create_CaptionLabel(c_etyColorTextcolor_Highlighted, "", float(uiTextCharactersize), c_etyColorTextcolor);

		sf::Vector2f c_sfVector2fNewCaptionPosition = mp_c_etyButtonHeaderBox->get_CaptionLabel()->get_Position();
		c_sfVector2fNewCaptionPosition.x			-=	(m_fWidth * m_fScrollbarSizePercent)/2;
		mp_c_etyButtonHeaderBox->get_CaptionLabel()->set_Position(c_sfVector2fNewCaptionPosition);
	}
	else if(bComboBox == false)
	{
		//Die Vorgänge zum Erstellen einer ListBox

		m_bUnfolded										=	true;
		m_en_etyDialogitemType							=	DialogitemType::enLISTBOX;
		m_c_sfIntRectEntrySubRect						=	m_c_sfIntRectComboBoxSubRect;
		m_c_sfIntRectEntrySubRect.top					=	m_c_sfIntRectEntrySubRect.top + m_c_sfIntRectEntrySubRect.height;
		m_c_sfIntRectEntrySubRect.height				=	uiListBoxEntrySubRectSize;
		//Erstellung des Backgrounds
		mp_c_etyPictureControlBackground				= new CPictureControl(	
																				strCustomID + "Background", c_sfTextureComboBoxTexture, fWidth, fHeight, sf::Vector2f(0,0), 
																				c_sfIntRectComboBoxSubRect, this, mp_c_etyDialogParentDialog
																			  );
																				

	}
	
	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}



bool						ety::CComboBox::add_ListEntry							(std::string strEntry, unsigned int uiPosition)
{
	sf::Font c_sfFont = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardFont();

	//Falls der Eintrag schon in der ComboBox enthalten sein soll, wird er nicht nochmals angelegt!
	if(includes_Entry(strEntry) == true)
	{
		return false;
	}

	//Zusammensetzen der CustomID des neuen Eintrages.
	//Dieser setzt sich aus der CustomID der ComboBox, dem String "EntrieID" und dem Inhalt der Eintrags zusammen
	std::string strBoxEntrieID = m_strCustomID + "EntryID" + strEntry;


	float fNewEntrieWidth = m_fOrigin_Width;
	//Falls eine Scrollbar vorhanden ist muss die Größe der Entries daran angepasst werden
	if(m_bScrollbar == true)
	{
		fNewEntrieWidth = fNewEntrieWidth * (1-m_fScrollbarSizePercent);
	}

	//Anlegen des neuen Eintrages
	CButton* p_c_etyButtonNewListEntry = NULL;

	//Anlegen der Einträge für ComboBox oder ListBox
	//Die Einträge unterscheiden sich auch hier in Höhe und Position
	//Die der ComboBox sind so groß wie der Header und befinden sich unter diesem
	//Die der ListBox sind je nach anzuzeigender Anzahl hoch und positionieren sich an der oberen Kante des Hintergrundes.
	if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
	{
		p_c_etyButtonNewListEntry = new CButton(strBoxEntrieID, m_c_sfTextureComboxSet, fNewEntrieWidth, m_fOrigin_Height, sf::Vector2f(0,0), m_c_sfIntRectEntrySubRect, this, 
												mp_c_etyDialogParentDialog);

		p_c_etyButtonNewListEntry->set_Visibility(false);
		p_c_etyButtonNewListEntry->set_Affinity(Affinity::enFOREGROUND);
		p_c_etyButtonNewListEntry->set_DrawPosition(1);
	}
	else if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
	{
		float fEntryHeight = 0.f;
		if(m_uiUnfoldedEntries == 0)
		{
			fEntryHeight = m_fOrigin_Height;
		}
		else
		{
			fEntryHeight = m_fOrigin_Height/m_uiUnfoldedEntries;
		}


		p_c_etyButtonNewListEntry = new CButton(strBoxEntrieID, m_c_sfTextureComboxSet, fNewEntrieWidth, fEntryHeight, sf::Vector2f(0,0), m_c_sfIntRectEntrySubRect,
												this, mp_c_etyDialogParentDialog);

		sf::IntRect c_sfIntRectHoverSubRect = p_c_etyButtonNewListEntry->get_Background_SubRect();
		c_sfIntRectHoverSubRect.top += c_sfIntRectHoverSubRect.height;
		p_c_etyButtonNewListEntry->set_HoverSprite_SubRect(c_sfIntRectHoverSubRect,false);
		p_c_etyButtonNewListEntry->set_Affinity(Affinity::enFOREGROUND);
		p_c_etyButtonNewListEntry->set_DrawPosition(1);
	}

	
	//Initialisieren des Lua-Scripts
	ety::CLua* const p_c_luaLuaScript = mp_c_etyDialogParentDialog->get_DialogManager()->get_LuaScript();

	if(m_bLocalization == true)
	{
		//Falls die Einträge der ComboBox an die aktuelle Sprache angepasst werden sollen,
		//wird im folgendem Teil noch die richtige Caption aus der Language-Datei heraus geholt
		bool bCloseLuaScript = false;

		if(p_c_luaLuaScript->get_IsInitiated() == false)
		{
			bCloseLuaScript = true;
		}

		p_c_luaLuaScript->init_Lua();
		p_c_luaLuaScript->start_Script("Initialisation/Gamestates/Language.lua");
	
		strBoxEntrieID += "Caption";

		//und dann die Caption angelegt
		std::string lan = mp_c_etyDialogParentDialog->get_DialogManager()->get_Language();
		std::string yoo = p_c_luaLuaScript->get_TableString(strBoxEntrieID,lan);


		p_c_etyButtonNewListEntry->create_CaptionLabel(m_c_etyColorCaptionTextcolor_highlighted, yoo,
			float(m_uiTextCharactersize), m_c_etyColorCaptionTextcolor);
				
		if(bCloseLuaScript == true)
		{
			p_c_luaLuaScript->close_Lua();
		}
	}
	else
	{
		//Falls es keine Lokalisation geben soll, wird die Caption einfach so angelegt
		strBoxEntrieID += "Caption";

		p_c_etyButtonNewListEntry->create_CaptionLabel(m_c_etyColorCaptionTextcolor_highlighted, strEntry, float(m_uiTextCharactersize), m_c_etyColorCaptionTextcolor);
	}


	//Wenn dieser neu angelegte Eintrag der aller erste in der Liste ist, dann wird dieser entsprechend als "ausgewählt" markiert
	if(m_listBoxEntries.empty() == true && m_en_etyDialogitemType == DialogitemType::enLISTBOX)
	{
		//Dafür wird die Caption gehighlighted und das HoverSprite angezeigt
		//Wenn die Caption noch nicht gehighlighted ist, geschieht es an dieser Stelle
		if(p_c_etyButtonNewListEntry->get_CaptionHighlighted() == false)
		{
			p_c_etyButtonNewListEntry->swap_HighlightInformation();
		}
		
		//Die Eigenschaft, dass die Caption "animiert" ist muss noch ausgestellt werden, da sich sonst die Caption wieder zurücksetzen würde,
		//da sie eigentlich nicht gehighlighted sein dürfte, da kein Hover-Event statt gefunden hat. Desweiteren soll nicht die StandardCaption
		//angezeigt werden, sollte ein Hover-Event eintreten, da nur die beiden Eigenschaften der normalen und highlighted Caption vertauscht wurden
		p_c_etyButtonNewListEntry->set_AnimatedCaption(false);

		//An dieser Stelle werden noch HoverSprite und Background getauscht, damit standardmäßig das HoverSprite angezeigt wird
		sf::IntRect c_sfIntRectTmp = p_c_etyButtonNewListEntry->get_Background_SubRect();
		p_c_etyButtonNewListEntry->set_Background_SubRect(p_c_etyButtonNewListEntry->get_HoverSprite_SubRect(),false);
		p_c_etyButtonNewListEntry->set_HoverSprite_SubRect(c_sfIntRectTmp,false);

		//Die Sichtbarkeit des HoverSprite muss auch noch deaktiviert werden, damit nicht dann das eigentliche BackgroundSprite bei einem Hover-Event angezeigt wird
		p_c_etyButtonNewListEntry->set_HoverSprite_Visibility(false);
	}
	else if(uiPosition <= m_uiCurrentSelectedEntry)
	{
		m_uiCurrentSelectedEntry++;
	}
	

	//Das richtige Einfügen in die ComboBox
	std::list<CButton*>::iterator itListEntries = m_listBoxEntries.begin();

	if(uiPosition > m_listBoxEntries.size() - m_uiDisabledButtons)
	{
		uiPosition = m_listBoxEntries.size() - m_uiDisabledButtons;
	}

	for(unsigned int uiCounter = 0; uiCounter != uiPosition; uiCounter++)
	{
		itListEntries++;
	}

	m_listBoxEntries.insert(itListEntries,p_c_etyButtonNewListEntry);

	
	
	//Damit mit dem neuen ListEntry auch interagiert werden kann, muss es dem Dialog hinzugefügt werden
	mp_c_etyDialogParentDialog->add_ChildrenDialogitem(p_c_etyButtonNewListEntry);


	if(mp_c_etyScrollbar != NULL)
	{
		if(m_listBoxEntries.size() < m_uiUnfoldedEntries)
		{
			mp_c_etyScrollbar->set_Active(false);
			if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
			{
				mp_c_etyScrollbar->set_Height(m_fHeight * m_listBoxEntries.size() - m_uiDisabledButtons);
			}
		}
		else
		{
			mp_c_etyScrollbar->set_Active(true);
			if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
			{
				mp_c_etyScrollbar->set_Height(m_fHeight * m_uiUnfoldedEntries);
			}
			else if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
			{
				mp_c_etyScrollbar->set_Height(mp_c_etyPictureControlBackground->get_Height());
			}
		}

		//Anpassen der Einteilung der Scrollbar an die neue Anzahl der Einträge
		mp_c_etyScrollbar->set_AvailableBlocks(m_listBoxEntries.size() - m_uiDisabledButtons + 1 - m_uiUnfoldedEntries);
		mp_c_etyScrollbar->set_CurrentBlock(0);
	}

	return true;
}
void						ety::CComboBox::add_ListEntries							(std::list<std::string> listNewEntries, bool bClearEntries)
{
	if(bClearEntries == true)
	{
		clear_Entries();
	}	

	if(listNewEntries.empty() == true)
	{
		m_uiDisabledButtons = m_listBoxEntries.size();
	}

	std::list<CButton*>::iterator itOldListEntry	= m_listBoxEntries.begin();
	std::list<std::string>::iterator itNewListEntry = listNewEntries.begin();
	
	int iCounter = 0;
	bool bListSizeZero = true;

	if(m_listBoxEntries.size() > 0)
	{
		bListSizeZero = false;
	}

	while(itNewListEntry != listNewEntries.end())
	{
		if(iCounter < int(m_listBoxEntries.size()) && bListSizeZero == false)
		{
			if((*itOldListEntry)->get_CaptionLabel() != NULL)
			{
				(*itOldListEntry)->get_CaptionLabel()->set_Content((*itNewListEntry));
			}
		}
		else
		{
			m_uiDisabledButtons = 0;

			if(iCounter >= int(m_listBoxEntries.size()))
			{
				bListSizeZero = true;
			}
			add_ListEntry((*itNewListEntry), iCounter);
		}

		if(bListSizeZero == false)
		{
			itOldListEntry++;
		}	
		itNewListEntry++;
		iCounter++;
	}

	set_CurrentSelectedEntry(0, true);
	m_uiDisabledButtons = 0;

	if(bListSizeZero == false)
	{
		if(itOldListEntry != m_listBoxEntries.end())
		{
			while(itOldListEntry != m_listBoxEntries.end())
			{
				m_uiDisabledButtons++;
				itOldListEntry++;
			}
		}
	}


	if(mp_c_etyScrollbar != NULL)
	{
		//Anpassen der Einteilung der Scrollbar an die neue Anzahl der Einträge
		mp_c_etyScrollbar->set_AvailableBlocks(m_listBoxEntries.size() - m_uiDisabledButtons + 1 - m_uiUnfoldedEntries);
		mp_c_etyScrollbar->set_CurrentBlock(0);

		if(m_listBoxEntries.size() - m_uiDisabledButtons > m_uiUnfoldedEntries && mp_c_etyScrollbar != NULL)
		{
			//mp_c_etyScrollbar->get_Slider()->set_Visibility(true);
			mp_c_etyScrollbar->set_Active(true);
		}
		else
		{
			//mp_c_etyScrollbar->get_Slider()->set_Visibility(false);
			mp_c_etyScrollbar->set_Active(false);
		}
	}
	
}	
void						ety::CComboBox::adjust_SizeToResolution					( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	//Anpassen der Größe
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	//der Textgröße
	m_uiTextCharactersize	=	unsigned int(m_uiTextCharactersize * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height)));

	//Sowie das Anpassen des Headers
	if(mp_c_etyButtonHeaderBox != NULL )
	{
		mp_c_etyButtonHeaderBox->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	//Anpassen der ListBox-Hintergrundes
	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	//der Position
	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	update_Dialogitem(0);

	set_CurrentSelectedEntry(m_uiCurrentSelectedEntry, false);
}


bool						ety::CComboBox::check_MouseCoordinates					(void)
{
	//Es muss nur eine Mausüberprüfung statt finden bzw. true zurückgeben, wenn der Header der ComboBox angeklickt wurde
	//Da die restlichen Interaktionen mit Combo- bzw. ListBox über deren ListEntries oder die Scrollbar statt finden, welche aber Event-technisch ausgekoppelt sind
	if(mp_c_etyButtonHeaderBox != NULL)
	{
		return mp_c_etyButtonHeaderBox->check_MouseCoordinates();

		/*if(mp_c_etyButtonHeaderBox->check_MouseCoordinates() == false)
		{
			if(mp_c_etyButtonHeaderButton != NULL)
			{
				return mp_c_etyButtonHeaderButton->check_MouseCoordinates();
			}
			else
			{
				return false;
			}
		}

		return true;*/
	}

	return false;
}
void						ety::CComboBox::clear_Entries							(void)
{
	std::list<CButton*>::iterator itEntries	= m_listBoxEntries.begin();

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		mp_c_etyDialogParentDialog->delete_Dialogitem((*itEntries));
	}

	m_listBoxEntries.clear();

	m_uiCurrentSelectedEntry = 0;
	m_uiDisabledButtons = 0;
}
bool						ety::CComboBox::create_Scrollbar						(sf::IntRect c_sfIntRectScrollbarSubRect)
{
	if(mp_c_etyScrollbar == NULL)
	{
		m_bScrollbar = true;

		//wie der Hintergrund hoch ist.
		if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
		{
			mp_c_etyScrollbar							=	new CScrollbar(m_strCustomID + "Scrollbar",  m_c_sfTextureComboxSet, m_fOrigin_Width * m_fScrollbarSizePercent, m_fOrigin_Height,
																		   sf::Vector2f(m_fOrigin_Width * (1 - m_fScrollbarSizePercent), 0), c_sfIntRectScrollbarSubRect, this, 
																		   mp_c_etyDialogParentDialog);

			
		}
		else
		{
			mp_c_etyScrollbar							=	new CScrollbar(m_strCustomID + "Scrollbar",  m_c_sfTextureComboxSet, m_fOrigin_Width * m_fScrollbarSizePercent, 
																		   m_fOrigin_Height * m_uiUnfoldedEntries, 
																		   sf::Vector2f(m_fOrigin_Width * (1 - m_fScrollbarSizePercent), -m_fOrigin_Height), c_sfIntRectScrollbarSubRect, 
																		   this, mp_c_etyDialogParentDialog);

			
			mp_c_etyScrollbar->set_Visibility(false);
			mp_c_etyScrollbar->set_Affinity(Affinity::enFOREGROUND);
			mp_c_etyScrollbar->set_DrawPosition(1);	
		}

		mp_c_etyDialogParentDialog->add_ChildrenDialogitem(mp_c_etyScrollbar);

		mp_c_etyScrollbar->set_CurrentBlock(0);
		mp_c_etyScrollbar->set_AvailableBlocks(m_listBoxEntries.size() - m_uiDisabledButtons - m_uiUnfoldedEntries);	

		return true;
	}

	return false;
}
	

bool						ety::CComboBox::delete_ListEntry						(unsigned int uiPosition)
{
	if(uiPosition > m_listBoxEntries.size() - m_uiDisabledButtons || m_listBoxEntries.empty() == true)
	{
		return false;
	}
	else if(m_listBoxEntries.size() - m_uiDisabledButtons == 1)
	{
		std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();
		CButton* p_c_etyButtonEntrieToDelete = (*itEntries);
		m_listBoxEntries.erase(itEntries);

		m_uiCurrentSelectedEntry = 0;

		return mp_c_etyDialogParentDialog->delete_Dialogitem(p_c_etyButtonEntrieToDelete);
	}
	else
	{
		std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

		for(unsigned int uiLoop = 0; uiLoop != uiPosition ; uiLoop++)
		{
			itEntries++;
		}

		if(uiPosition == m_uiCurrentSelectedEntry)
		{
			if(uiPosition == 0)
			{
				set_CurrentSelectedEntry(1, false);
				m_uiCurrentSelectedEntry = 0;
			}
			else
			{
				set_CurrentSelectedEntry(0, false);
			}	
		}
		else if(uiPosition < m_uiCurrentSelectedEntry)
		{
			m_uiCurrentSelectedEntry--;
		}

		//Der richtige Eintrag wird herrausgesucht und dann ordentlich aus der Liste entfernt
		CButton* p_c_etyButtonEntrieToDelete = (*itEntries);
		m_listBoxEntries.erase(itEntries);

		if(mp_c_etyScrollbar != NULL)
		{
			mp_c_etyScrollbar->set_AvailableBlocks(m_listBoxEntries.size() - m_uiDisabledButtons + 1 - m_uiUnfoldedEntries);
			mp_c_etyScrollbar->set_CurrentBlock(0);
		}

		//Und letztlich auch richtig gelöscht
		return mp_c_etyDialogParentDialog->delete_Dialogitem(p_c_etyButtonEntrieToDelete);
	}

	return false;
}
bool						ety::CComboBox::delete_ListEntry						(std::string strEntry)
{
	if(m_listBoxEntries.empty() == true || (m_listBoxEntries.size() - m_uiDisabledButtons) == 0)
	{
		return false;
	}
	else if(m_listBoxEntries.size() - m_uiDisabledButtons == 1)
	{
		std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();
		CButton* p_c_etyButtonEntrieToDelete = (*itEntries);
		m_listBoxEntries.erase(itEntries);

		m_uiCurrentSelectedEntry = 0;

		return mp_c_etyDialogParentDialog->delete_Dialogitem(p_c_etyButtonEntrieToDelete);
	}

	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();
	unsigned int uiCounter = 0;

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries)->get_CaptionLabel()->get_Content() == strEntry)
		{
			if(uiCounter == m_uiCurrentSelectedEntry)
			{
				if(uiCounter == 0)
				{
					set_CurrentSelectedEntry(1, false);
					m_uiCurrentSelectedEntry = 0;
				}
				else
				{
					set_CurrentSelectedEntry(0, false);
				}
			}
			else if(uiCounter < m_uiCurrentSelectedEntry)
			{
				m_uiCurrentSelectedEntry--;
			}			

			//Der richtige Eintrag wird herrausgesucht und dann ordentlich aus der Liste entfernt
			CButton* p_c_etyButtonEntrieToDelete = (*itEntries);
			m_listBoxEntries.erase(itEntries);

			if(mp_c_etyScrollbar != NULL)
			{
				mp_c_etyScrollbar->set_AvailableBlocks(m_listBoxEntries.size() - m_uiDisabledButtons + 1 - m_uiUnfoldedEntries);
				mp_c_etyScrollbar->set_CurrentBlock(0);
			}

			return mp_c_etyDialogParentDialog->delete_Dialogitem(p_c_etyButtonEntrieToDelete);
		}

		uiCounter++;
	}

	return false;
}
bool						ety::CComboBox::draw_Dialogitem							(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_bVisibility == true)
	{
		if(mp_c_etyButtonHeaderBox != NULL && m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
		{
			if(check_MouseCoordinates() == true)
			{
				(*p_c_sfRenderTextureScene).draw(mp_c_etyButtonHeaderBox->get_HoverSprite());

				CLabel* p_c_etyLabelHeaderBoxCaption = mp_c_etyButtonHeaderBox->get_CaptionLabel();

				p_c_etyLabelHeaderBoxCaption->draw_Dialogitem(p_c_sfRenderTextureScene);
			}
			else
			{
				(*p_c_sfRenderTextureScene).draw(mp_c_etyButtonHeaderBox->get_BackgroundSprite());

				CLabel* p_c_etyLabelHeaderBoxCaption = mp_c_etyButtonHeaderBox->get_CaptionLabel();

				if(p_c_etyLabelHeaderBoxCaption != NULL)
				{
					p_c_etyLabelHeaderBoxCaption->draw_Dialogitem(p_c_sfRenderTextureScene);
				}
			}

		}
		else if(mp_c_etyPictureControlBackground != NULL && m_en_etyDialogitemType == DialogitemType::enLISTBOX)
		{
			mp_c_etyPictureControlBackground->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyScrollbar != NULL)
		{
			mp_c_etyScrollbar->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		return true;
	}

	return false;
}

void						ety::CComboBox::focus_Entry								(unsigned int uiPosition)
{
	if(mp_c_etyScrollbar != NULL)
	{
		if(mp_c_etyScrollbar->get_CurrentBlock() > uiPosition || mp_c_etyScrollbar->get_CurrentBlock() + (m_uiUnfoldedEntries - 1) < uiPosition || uiPosition < mp_c_etyScrollbar->get_CurrentBlock())
		{
			if(int(uiPosition - (m_uiUnfoldedEntries - 1)) <= 0)
			{
				mp_c_etyScrollbar->set_CurrentBlock(0);
			}
			else
			{
				mp_c_etyScrollbar->set_CurrentBlock(uiPosition - (m_uiUnfoldedEntries - 1));
			}
			
		}
	}
}



void						ety::CComboBox::handle_InternEvents						(const sf::Event& c_sfEvent)
{
	if(c_sfEvent.type	==	sf::Event::MouseButtonPressed)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(mp_c_etyScrollbar != NULL)
			{
				if(mp_c_etyScrollbar->get_Slider() != NULL)
				{
					if(mp_c_etyDialogParentDialog->get_DialogManager()->get_MouseEventDialogitem() == mp_c_etyScrollbar->get_Slider())
					{
						m_bSliderActive = true;

						return ;
					}
				}
			}
		}
	}
	else if(c_sfEvent.type	==	sf::Event::MouseButtonReleased || c_sfEvent.type	==	sf::Event::MouseButtonDoubleClick || c_sfEvent.type	==	sf::Event::MouseButtonNoFocusReleased)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(mp_c_etyScrollbar != NULL)
			{
				if(mp_c_etyScrollbar->get_Slider() != NULL)
				{
					if(mp_c_etyDialogParentDialog->get_DialogManager()->get_MouseEventDialogitem() == mp_c_etyScrollbar->get_Slider() || 
						mp_c_etyDialogParentDialog->get_DialogManager()->get_MouseNoFocusEventDialogitem() == mp_c_etyScrollbar->get_Slider())
					{
						m_bSliderActive = false;

						return ;
					}
				}
			}

			if(get_EventSound(ety::SoundType::enCLICK) != NULL)
			{
				get_EventSound(ety::SoundType::enCLICK)->play();
			}

			if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
			{
				if(m_bUnfolded != true)
				{
					m_bUnfolded = true;

					if(mp_c_etyScrollbar != NULL)
					{
						mp_c_etyScrollbar->set_Visibility(true);
					}
				}
				else if(m_bActive == true)
				{
					m_bUnfolded = false;
					
					if(mp_c_etyScrollbar != NULL)
					{
						mp_c_etyScrollbar->set_Visibility(false);
					}

					if(m_listBoxEntries.size() > 0)
					{
						std::list<CButton*>::iterator itEntrieButtons = m_listBoxEntries.begin();

						for(itEntrieButtons ; itEntrieButtons != m_listBoxEntries.end()  ; itEntrieButtons++)
						{
							if((*itEntrieButtons)->get_Visibility() == true)
							{
								(*itEntrieButtons)->set_Visibility(false);
							}
						}
					}

					CDialogitem* p_c_etyDialogitemEventItem = mp_c_etyDialogParentDialog->get_DialogManager()->get_MouseEventDialogitem();
					
					if(p_c_etyDialogitemEventItem != NULL)
					{
						if(p_c_etyDialogitemEventItem->get_ParentDialogitem() != this)
						{
							return ;
						}
					}
			
					unsigned int uiCounter = 0;			
					std::list<CButton*>::iterator itEventButton = m_listBoxEntries.begin();
					for(itEventButton ; itEventButton != m_listBoxEntries.end() ; itEventButton++)
					{
						if(p_c_etyDialogitemEventItem == (*itEventButton))
						{
							mp_c_etyButtonHeaderBox->get_CaptionLabel()->set_Content((*itEventButton)->get_CaptionLabel()->get_Content());
							m_uiCurrentSelectedEntry = uiCounter;
							break;
						}

						uiCounter++;
					}
				}
			}
			else if(m_en_etyDialogitemType == DialogitemType::enLISTBOX && m_bActive == true)
			{
				CDialogitem* p_c_etyDialogitemEventItem = mp_c_etyDialogParentDialog->get_DialogManager()->get_MouseEventDialogitem();

				if(p_c_etyDialogitemEventItem->get_ParentDialogitem() == this)
				{
					unsigned int uiCounter = 0;
					std::list<CButton*>::iterator itEventButton = m_listBoxEntries.begin();
					std::list<CButton*>::iterator itCurrentSelectedEntry = itEventButton;

					for(itEventButton ; itEventButton != m_listBoxEntries.end() ; itEventButton++)
					{
						if(p_c_etyDialogitemEventItem == (*itEventButton))
						{
							for(unsigned int uiLoop = 0 ; uiLoop < m_uiCurrentSelectedEntry ; uiLoop++)
							{
								itCurrentSelectedEntry++;
							}

							if((*itCurrentSelectedEntry)->get_CaptionHighlighted() == false)
							{
								(*itCurrentSelectedEntry)->swap_HighlightInformation();
							}
							
							(*itCurrentSelectedEntry)->set_AnimatedCaption(true);

							sf::IntRect c_sfIntRectTmp = (*itCurrentSelectedEntry)->get_Background_SubRect();
							(*itCurrentSelectedEntry)->set_Background_SubRect((*itCurrentSelectedEntry)->get_HoverSprite_SubRect(),false);
							(*itCurrentSelectedEntry)->set_HoverSprite_SubRect(c_sfIntRectTmp,false);

							(*itCurrentSelectedEntry)->set_HoverSprite_Visibility(true);


							m_uiCurrentSelectedEntry = uiCounter;


							if((*itEventButton)->get_CaptionHighlighted() == false)
							{
								(*itEventButton)->swap_HighlightInformation();
							}
							
							(*itEventButton)->set_AnimatedCaption(false);

							c_sfIntRectTmp = (*itEventButton)->get_Background_SubRect();
							(*itEventButton)->set_Background_SubRect((*itEventButton)->get_HoverSprite_SubRect(),false);
							(*itEventButton)->set_HoverSprite_SubRect(c_sfIntRectTmp,false);

							(*itEventButton)->set_HoverSprite_Visibility(false);

							if((*itEventButton)->get_EventSound(ety::SoundType::enCLICK) != NULL)
							{
								(*itEventButton)->get_EventSound(ety::SoundType::enCLICK)->play();
							}

							break;
						}
						
						uiCounter++;
					}
				}
			}
		}
	}
	else if(c_sfEvent.type	==	sf::Event::MouseMoved)
	{
		if(m_bVisibility == true)
		{
			if(check_MouseCoordinates() == true)
			{		
				
				if(m_bHoverSoundPlayed == false)
				{
					if(get_EventSound(SoundType::enHOVER) != NULL)
					{
						get_EventSound(SoundType::enHOVER)->play();
						m_bHoverSoundPlayed = true;
					}
				}	
			}
			else
			{
				if(m_bHoverSoundPlayed == true)
				{
					m_bHoverSoundPlayed = false;
				}
			}
		}
	}
}


bool						ety::CComboBox::includes_Entry							(std::string strEntry)
{
	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

	for(unsigned int uiLoop = 0 ; uiLoop < m_listBoxEntries.size() - m_uiDisabledButtons ; uiLoop++)
	{
		if((*itEntries)->get_CaptionLabel() != NULL)
		{
			if((*itEntries)->get_CaptionLabel()->get_Content() == strEntry)
			{
				return true;
			}
		}

		itEntries++;
	}

	return false;
}


void						ety::CComboBox::modificate_Colorfilter					(sf::Vector3f c_sfVector3fFactors)
{
	m_c_etyColorComboBoxColorFilter.r	*= c_sfVector3fFactors.x;
	m_c_etyColorComboBoxColorFilter.g	*= c_sfVector3fFactors.y;
	m_c_etyColorComboBoxColorFilter.b	*= c_sfVector3fFactors.z;

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		mp_c_etyButtonHeaderBox->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}


void						ety::CComboBox::reset_FocusedDialogitem					(void)
{
	m_bFocused = false;

	if(mp_c_etyDialogParentDialog->get_DialogManager()->get_FocusedDialogitem() != NULL)
	{
		if(mp_c_etyDialogParentDialog->get_DialogManager()->get_FocusedDialogitem()->get_ParentDialogitem() != this)
		{
			if(mp_c_etyDialogParentDialog->get_DialogManager()->get_FocusedDialogitem()->get_ParentDialogitem() != NULL)
			{
				if(mp_c_etyDialogParentDialog->get_DialogManager()->get_FocusedDialogitem()->get_ParentDialogitem()->get_ParentDialogitem() == this)
				{
					return ;
				}
			}

			if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
			{
				m_bUnfolded = false;

				if(m_listBoxEntries.size() > 0)
				{
					std::list<CButton*>::iterator itEntrieButtons = m_listBoxEntries.begin();

					for(itEntrieButtons ; itEntrieButtons != m_listBoxEntries.end()  ; itEntrieButtons++)
					{
						if((*itEntrieButtons)->get_Visibility() == true)
						{
							(*itEntrieButtons)->set_Visibility(false);
						}
					}
				}
			}
		}
	}	
}


void						ety::CComboBox::unfold_Entries							(bool bUnfoldEntries)
{
	if(bUnfoldEntries == true)
	{
		set_Focus(true);
	}
	else
	{
		set_Focus(false);
		m_bUnfolded = false;
	}
}
void						ety::CComboBox::update_Dialogitem						(const sf::Uint32& uiFrameTime)
{
	//Aktualisiert die ComboBox und überträgt seine Attribute an seinen Button
	if(mp_c_etyDialogParentDialog->get_DialogManager()->check_IsDialogitemActive(this) == false)
	{
		m_bActive = false;
	}
	else
	{
		m_bActive = m_bInternActive;
	}


	if(m_bRealPosition == false)
	{
		if(mp_c_etyDialogitemParentDialogitem == NULL)
		{
			m_c_sfVector2fRealPosition.x = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).x) +  m_c_sfVector2fPosition.x;
			m_c_sfVector2fRealPosition.y = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).y) -  m_c_sfVector2fPosition.y;
		}
		else
		{
			if(mp_c_etyDialogitemAnchorOrientation != NULL)
			{
				m_c_sfVector2fRealPosition.x = (mp_c_etyDialogitemAnchorOrientation->get_Anchor(m_en_etyAnchor).x) +  m_c_sfVector2fPosition.x;
				m_c_sfVector2fRealPosition.y = (mp_c_etyDialogitemAnchorOrientation->get_Anchor(m_en_etyAnchor).y) -  m_c_sfVector2fPosition.y;
			}
			else
			{
				m_c_sfVector2fRealPosition.x = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).x) +  m_c_sfVector2fPosition.x;
				m_c_sfVector2fRealPosition.y = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).y) -  m_c_sfVector2fPosition.y;
			}
		}


		if(m_en_etyAnchor == Anchor::enALIGNEDMIDTOP)
		{
			m_c_sfVector2fRealPosition.x = m_c_sfVector2fRealPosition.x - (m_fWidth / 2);
		}
		else if(m_en_etyAnchor == Anchor::enALIGNEDLEFT)
		{
			m_c_sfVector2fRealPosition.y = m_c_sfVector2fRealPosition.y - (m_fHeight / 2);
		}
		else if(m_bAnchorCentered == true)
		{
			m_c_sfVector2fRealPosition.x		=	m_c_sfVector2fRealPosition.x - (m_fWidth / 2);
			m_c_sfVector2fRealPosition.y		=	m_c_sfVector2fRealPosition.y - (m_fHeight / 2);
		}
	}


	//Aktualisieren des Buttons
	sf::Vector2f c_sfVector2fCaptionBorder;

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		mp_c_etyButtonHeaderBox->update_Dialogitem(uiFrameTime);

		CLabel* p_c_etyLabelHeaderBoxCaption = mp_c_etyButtonHeaderBox->get_CaptionLabel();
		if( p_c_etyLabelHeaderBoxCaption != NULL)
		{
			std::string strAdjustedCaption = p_c_etyLabelHeaderBoxCaption->get_Content();
			int iCounter = 3;
			int iCharactersToRemove = 0;
				
			c_sfVector2fCaptionBorder.x = mp_c_etyButtonHeaderBox->get_RealPosition().x + mp_c_etyButtonHeaderBox->get_BackgroundSprite().getGlobalBounds().left + mp_c_etyButtonHeaderBox->get_BackgroundSprite().getGlobalBounds().width;
			c_sfVector2fCaptionBorder.y = mp_c_etyButtonHeaderBox->get_RealPosition().y;
			
			do
			{
				mp_c_etyButtonHeaderBox->update_Dialogitem(uiFrameTime);
				if( p_c_etyLabelHeaderBoxCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder))
				{
					iCharactersToRemove = strAdjustedCaption.size() - iCounter;
					if(iCharactersToRemove < 0)
					{
						break;
					}
					strAdjustedCaption.erase(iCharactersToRemove);
					strAdjustedCaption += "...";

					p_c_etyLabelHeaderBoxCaption->set_sfTextObjectContent(strAdjustedCaption);
					p_c_etyLabelHeaderBoxCaption->update_Dialogitem(0);

					if(iCounter == 3)
					{
						iCounter++;
					}
				}
				c_sfVector2fCaptionBorder.x = mp_c_etyButtonHeaderBox->get_RealPosition().x + mp_c_etyButtonHeaderBox->get_BackgroundSprite().getGlobalBounds().left + mp_c_etyButtonHeaderBox->get_BackgroundSprite().getGlobalBounds().width;
				c_sfVector2fCaptionBorder.y = mp_c_etyButtonHeaderBox->get_RealPosition().y;
			}while( p_c_etyLabelHeaderBoxCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder));
		}
	}

	if(mp_c_etyScrollbar != NULL)
	{
		if(m_bSliderActive == true)
		{
			mp_c_etyScrollbar->update_SliderPosition();
		}

		mp_c_etyScrollbar->update_Dialogitem(uiFrameTime);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->update_Dialogitem(uiFrameTime);
	}

	if(m_bUnfolded == true && m_listBoxEntries.empty() == false)
	{
		if(m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
		{
			std::list<CButton*>::iterator itAllEntrieButtons = m_listBoxEntries.begin();
			std::list<CButton*>::iterator itEntrieButtons = m_listBoxEntries.begin();
			unsigned int uiLoop = 0;
			unsigned int uiCurrentBlock = 0;
			unsigned int uiEntryCounter							= 0;
		
			if(mp_c_etyScrollbar != NULL)
			{
				mp_c_etyScrollbar->set_Visibility(true);
				uiCurrentBlock = mp_c_etyScrollbar->get_CurrentBlock();
			}

			for(itAllEntrieButtons ; itAllEntrieButtons != m_listBoxEntries.end() ; itAllEntrieButtons++)
			{
				(*itAllEntrieButtons)->set_Visibility(false);

				if(uiLoop == uiCurrentBlock)
				{
					itEntrieButtons = itAllEntrieButtons;
				}

				uiLoop++;
			}
	
			for(uiLoop = uiCurrentBlock ; uiLoop < (uiCurrentBlock + m_uiUnfoldedEntries) ; uiLoop++)
			{	
				if(m_bVisibility == false)
				{
					break;
				}

				if(uiEntryCounter == m_listBoxEntries.size() - m_uiDisabledButtons || itEntrieButtons == m_listBoxEntries.end())
				{
					break;
				}

				sf::Vector2f c_sfVector2fEntrieButtonPosition	=	get_RealPosition();
				c_sfVector2fEntrieButtonPosition.x				=	0.f;
				c_sfVector2fEntrieButtonPosition.y				=	-1*(m_fHeight * ((uiLoop - uiCurrentBlock) + 1));

				(*itEntrieButtons)->set_Position(c_sfVector2fEntrieButtonPosition);
				(*itEntrieButtons)->set_Visibility(true);

				(*itEntrieButtons)->update_Dialogitem(uiFrameTime);

				CLabel* p_c_etyLabelListEntrieCaption = (*itEntrieButtons)->get_CaptionLabel();
				std::string strAdjustedCaption = p_c_etyLabelListEntrieCaption->get_Content();
				int iCounter = 3;
				int iCharactersToRemove = 0;

		

				c_sfVector2fCaptionBorder.x = (*itEntrieButtons)->get_RealPosition().x + (*itEntrieButtons)->get_BackgroundSprite().getGlobalBounds().left + (*itEntrieButtons)->get_BackgroundSprite().getGlobalBounds().width;
				c_sfVector2fCaptionBorder.y = (*itEntrieButtons)->get_RealPosition().y;

				do
				{
					(*itEntrieButtons)->update_Dialogitem(uiFrameTime);

					if(p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder))
					{
						iCharactersToRemove = strAdjustedCaption.size() - iCounter;
						if(iCharactersToRemove < 0)
						{
							break;
						}
						strAdjustedCaption.erase(strAdjustedCaption.size()-iCounter);
						strAdjustedCaption += "...";

						p_c_etyLabelListEntrieCaption->set_sfTextObjectContent(strAdjustedCaption);
						p_c_etyLabelListEntrieCaption->update_Dialogitem(0);

						if(iCounter == 3)
						{
							iCounter++;
						}
					}

					c_sfVector2fCaptionBorder.x = (*itEntrieButtons)->get_RealPosition().x + (*itEntrieButtons)->get_BackgroundSprite().getGlobalBounds().left + (*itEntrieButtons)->get_BackgroundSprite().getGlobalBounds().width;
					c_sfVector2fCaptionBorder.y = (*itEntrieButtons)->get_RealPosition().y;
				}while(p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder));

				itEntrieButtons++;
				uiEntryCounter++;
			}
		}
		else if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
		{
			std::list<CButton*>::iterator itAllEntrieButtons	= m_listBoxEntries.begin();
			std::list<CButton*>::iterator itEntrieButtons		= m_listBoxEntries.begin();
			unsigned int uiLoop									= 0;
			unsigned int uiCurrentBlock							= 0;
			unsigned int uiEntryCounter							= 0;
		
			if(mp_c_etyScrollbar != NULL)
			{
				mp_c_etyScrollbar->set_Visibility(true);
				uiCurrentBlock = mp_c_etyScrollbar->get_CurrentBlock();
			}

			for(itAllEntrieButtons ; itAllEntrieButtons != m_listBoxEntries.end() ; itAllEntrieButtons++)
			{
				(*itAllEntrieButtons)->set_Visibility(false);

				if(uiLoop == uiCurrentBlock)
				{
					itEntrieButtons = itAllEntrieButtons;
				}

				uiLoop++;
			}
	
			for(uiLoop = uiCurrentBlock ; uiLoop < (uiCurrentBlock + m_uiUnfoldedEntries) ; uiLoop++)
			{	
				if(m_bVisibility == false)
				{
					break;
				}

				if(uiEntryCounter == m_listBoxEntries.size() - m_uiDisabledButtons || itEntrieButtons == m_listBoxEntries.end())
				{
					break;
				}

				sf::Vector2f c_sfVector2fEntrieButtonPosition	=	get_RealPosition();
				c_sfVector2fEntrieButtonPosition.x				=	0.f;
				c_sfVector2fEntrieButtonPosition.y				=	-1*((*itEntrieButtons)->get_Height() * ((uiLoop - uiCurrentBlock) ));

				(*itEntrieButtons)->set_Position(c_sfVector2fEntrieButtonPosition);

				(*itEntrieButtons)->set_Visibility(true);			

				(*itEntrieButtons)->update_Dialogitem(uiFrameTime);

				CLabel* p_c_etyLabelListEntrieCaption = (*itEntrieButtons)->get_CaptionLabel();
				std::string strAdjustedCaption = p_c_etyLabelListEntrieCaption->get_Content();
				int iCounter = 3;
				int iCharactersToRemove = 0;
				

		

				c_sfVector2fCaptionBorder.x = (*itEntrieButtons)->get_RealPosition().x + (*itEntrieButtons)->get_Width();
				c_sfVector2fCaptionBorder.y = p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().top;
				do
				{
					(*itEntrieButtons)->update_Dialogitem(uiFrameTime);

					if(p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder))
					{
						iCharactersToRemove = strAdjustedCaption.size() - iCounter;
						if(iCharactersToRemove < 0)
						{
							break;
						}
						strAdjustedCaption.erase(strAdjustedCaption.size()-iCounter);
						strAdjustedCaption += "...";

						p_c_etyLabelListEntrieCaption->set_sfTextObjectContent(strAdjustedCaption);
						p_c_etyLabelListEntrieCaption->update_Dialogitem(0);

						if(iCounter == 3)
						{
							iCounter++;
						}
					}

					c_sfVector2fCaptionBorder.x = (*itEntrieButtons)->get_RealPosition().x + (*itEntrieButtons)->get_Width();
					c_sfVector2fCaptionBorder.y = p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().top;
				}while(p_c_etyLabelListEntrieCaption->get_sfTextObject()->getGlobalBounds().contains(c_sfVector2fCaptionBorder));

				itEntrieButtons++;
				uiEntryCounter++;
			}
		}
	}
}




void						ety::CComboBox::set_CurrentSelectedEntry				(unsigned int uiNewSelectedEntrie, bool bFocusSelectedEntry)
{
	if(m_listBoxEntries.empty() == false)
	{
		if(mp_c_etyButtonHeaderBox != NULL && m_en_etyDialogitemType == DialogitemType::enCOMBOBOX)
		{
			m_uiCurrentSelectedEntry = uiNewSelectedEntrie;

			std::list<CButton*>::iterator itNewSelectedEntrie = m_listBoxEntries.begin();

			for(unsigned int uiLoop = 0 ; uiLoop != uiNewSelectedEntrie ; uiLoop++)
			{
				itNewSelectedEntrie++;
			}

			if(mp_c_etyButtonHeaderBox != NULL)
			{
				mp_c_etyButtonHeaderBox->get_CaptionLabel()->set_Content((*itNewSelectedEntrie)->get_CaptionLabel()->get_Content());
			}
		}
		else if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
		{
			std::list<CButton*>::iterator itNewSelectedEntry = m_listBoxEntries.begin();
			std::list<CButton*>::iterator itCurrentSelectedEntry = itNewSelectedEntry;

			for(unsigned int uiLoop = 0 ; uiLoop < m_uiCurrentSelectedEntry ; uiLoop++)
			{
				itCurrentSelectedEntry++;
			}

			for(unsigned int uiLoop = 0 ; uiLoop < uiNewSelectedEntrie ; uiLoop++)
			{
				itNewSelectedEntry++;
			}

			if((*itCurrentSelectedEntry)->get_CaptionHighlighted() == false)
			{
				(*itCurrentSelectedEntry)->swap_HighlightInformation();
			}
							
			(*itCurrentSelectedEntry)->set_AnimatedCaption(true);

			sf::IntRect c_sfIntRectTmp = (*itCurrentSelectedEntry)->get_Background_SubRect();
			(*itCurrentSelectedEntry)->set_Background_SubRect((*itCurrentSelectedEntry)->get_HoverSprite_SubRect(),false);
			(*itCurrentSelectedEntry)->set_HoverSprite_SubRect(c_sfIntRectTmp,false);

			(*itCurrentSelectedEntry)->set_HoverSprite_Visibility(true);


			m_uiCurrentSelectedEntry = uiNewSelectedEntrie;


			if((*itNewSelectedEntry)->get_CaptionHighlighted() == false)
			{
				(*itNewSelectedEntry)->swap_HighlightInformation();
			}
							
			(*itNewSelectedEntry)->set_AnimatedCaption(false);

			c_sfIntRectTmp = (*itNewSelectedEntry)->get_Background_SubRect();
			(*itNewSelectedEntry)->set_Background_SubRect((*itNewSelectedEntry)->get_HoverSprite_SubRect(),false);
			(*itNewSelectedEntry)->set_HoverSprite_SubRect(c_sfIntRectTmp,false);

			(*itNewSelectedEntry)->set_HoverSprite_Visibility(false);
		}

		if(bFocusSelectedEntry == true && mp_c_etyScrollbar != NULL && uiNewSelectedEntrie > (m_uiUnfoldedEntries - 1))
		{
			mp_c_etyScrollbar->set_CurrentBlock(uiNewSelectedEntrie - (m_uiUnfoldedEntries - 1));
		}
	}
}
void						ety::CComboBox::set_UnfoldedEntries						(unsigned int uiUnfoldedEntries)
{
	if(m_en_etyDialogitemType == DialogitemType::enLISTBOX)
	{
		std::list<CButton*>::iterator itEntries	=	m_listBoxEntries.begin();

		for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
		{
			if(m_uiUnfoldedEntries == 0)
			{
				(*itEntries)->set_Height((*itEntries)->get_Height() * uiUnfoldedEntries);
			}
			else
			{
				(*itEntries)->set_Height((*itEntries)->get_Height() * (uiUnfoldedEntries/m_uiUnfoldedEntries));
			}
		}
	}

	m_uiUnfoldedEntries	= uiUnfoldedEntries;
}
void						ety::CComboBox::set_ColorFilter							(ety::Color c_etyColorFilter)
{
	m_c_etyColorComboBoxColorFilter	=	c_etyColorFilter;

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->set_ColorFilter(m_c_etyColorComboBoxColorFilter);
	}

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		mp_c_etyButtonHeaderBox->set_BackgroundColors(m_c_etyColorComboBoxColorFilter);
	}

	for(std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin() ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		(*itEntries)->set_BackgroundColors(m_c_etyColorComboBoxColorFilter);
	}
}
void						ety::CComboBox::set_TextColor							(ety::Color c_etyColorTextColor)
{
	m_c_etyColorCaptionTextcolor	=	c_etyColorTextColor;

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		if(mp_c_etyButtonHeaderBox->get_CaptionHighlighted() == true)
		{
			mp_c_etyButtonHeaderBox->set_CaptionColor_highlighted(c_etyColorTextColor);
		}
		else
		{
			mp_c_etyButtonHeaderBox->get_CaptionLabel()->set_Textcolor(c_etyColorTextColor);
		}
	}

	for(std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin() ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries)->get_CaptionHighlighted() == true)
		{
			(*itEntries)->set_CaptionColor_highlighted(c_etyColorTextColor);
		}
		else
		{
			(*itEntries)->get_CaptionLabel()->set_Textcolor(c_etyColorTextColor);
		}
	}
}
void						ety::CComboBox::set_TextColorHighlighted				(ety::Color c_etyColorTextColorHighlighted)
{
	m_c_etyColorCaptionTextcolor_highlighted	=	c_etyColorTextColorHighlighted;

	if(mp_c_etyButtonHeaderBox != NULL)
	{
		if(mp_c_etyButtonHeaderBox->get_CaptionHighlighted() == true)
		{
			mp_c_etyButtonHeaderBox->get_CaptionLabel()->set_Textcolor(c_etyColorTextColorHighlighted);
		}
		else
		{
			mp_c_etyButtonHeaderBox->set_CaptionColor_highlighted(c_etyColorTextColorHighlighted);
			
		}
	}

	for(std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin() ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries)->get_CaptionHighlighted() == true)
		{
			(*itEntries)->get_CaptionLabel()->set_Textcolor(c_etyColorTextColorHighlighted);
		}
		else
		{
			(*itEntries)->set_CaptionColor_highlighted(c_etyColorTextColorHighlighted);
		}
	}
}
void						ety::CComboBox::set_Localization						(bool bLocalization)
{
	m_bLocalization = bLocalization;
}
void						ety::CComboBox::set_Active								(bool bActive)
{
	m_bActive		=	bActive;
	m_bInternActive	=	bActive;

	for(std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin() ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		(*itEntries)->set_Active(m_bActive);
	}

	mp_c_etyScrollbar->set_Active(m_bActive);
}
void						ety::CComboBox::set_Focus								(bool bFocus)
{
	m_bFocused	=	bFocus;
	
	if(m_bFocused == true)
	{
		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(this);
	}
	else
	{
		if(mp_c_etyScrollbar != NULL)
		{
			mp_c_etyScrollbar->set_Visibility(false);
		}

		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(NULL);

		if(m_listBoxEntries.size() > 0)
		{
			std::list<CButton*>::iterator itEntrieButtons = m_listBoxEntries.begin();

			for(itEntrieButtons ; itEntrieButtons != m_listBoxEntries.end()  ; itEntrieButtons++)
			{
				if((*itEntrieButtons)->get_Visibility() == true)
				{
					(*itEntrieButtons)->set_Visibility(false);
				}
			}
		}

		if(mp_c_etyScrollbar != NULL)
		{
			mp_c_etyScrollbar->set_Visibility(false);
			mp_c_etyScrollbar->set_CurrentBlock(0);
		}
	}
}
void						ety::CComboBox::set_Height								(float fHeight)
{
	sf::VideoMode c_sfVideoModeCurrentSetting = mp_c_etyDialogParentDialog->get_VideoMode();

	m_fHeight					=	fHeight;
	m_fOrigin_Height			=	float((m_fHeight*1050)/float(c_sfVideoModeCurrentSetting.height));

	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		(*itEntries)->set_Height(m_fOrigin_Height);
	}
}
void						ety::CComboBox::set_Width								(float fWidth)
{
	sf::VideoMode c_sfVideoModeCurrentSetting = mp_c_etyDialogParentDialog->get_VideoMode();

	m_fWidth					=	fWidth;
	m_fOrigin_Width				=	float((m_fWidth*1680)/float(c_sfVideoModeCurrentSetting.width));

	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		(*itEntries)->set_Width(m_fOrigin_Width * (1 - m_fScrollbarSizePercent));
	}
}


bool						ety::CComboBox::get_Localization						(void)
{
	return m_bLocalization;
}
bool						ety::CComboBox::get_Unfolded							(void)
{
	return m_bUnfolded;
}
int							ety::CComboBox::get_PositionofEntry						(std::string strEntry)
{
	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();
	int iCounter = 0;

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries)->get_CaptionLabel() != NULL)
		{
			if((*itEntries)->get_CaptionLabel()->get_Content() == strEntry)
			{
				return iCounter;
			}
		}

		iCounter++;
		if(iCounter == m_listBoxEntries.size() - m_uiDisabledButtons)
		{
			return -1;
		}
	}

	return -1;
}
int							ety::CComboBox::get_PositionofEntry						(const CDialogitem* p_c_etyDialogitemEntry)
{
	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();
	int iCounter = 0;

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries) == p_c_etyDialogitemEntry)
		{
			return iCounter;
		}

		iCounter++;
		if(iCounter == m_listBoxEntries.size() - m_uiDisabledButtons)
		{
			return -1;
		}
	}

	return -1;
}
unsigned int				ety::CComboBox::get_CurrentSelectedEntrie				(void)
{
	return m_uiCurrentSelectedEntry;
}
unsigned int				ety::CComboBox::get_Size								(void)
{
	return m_listBoxEntries.size() - m_uiDisabledButtons;
}
unsigned int				ety::CComboBox::get_UnfoldedEntries						(void)
{
	return m_uiUnfoldedEntries;
}
std::string					ety::CComboBox::get_ListEntry							(unsigned int uiPosition)
{
	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

	for(unsigned int uiLoop = 0 ; uiLoop < uiPosition ; uiLoop++)
	{
		itEntries++;
		if(itEntries == m_listBoxEntries.end())
		{
			return "";
		}
	}

	if((*itEntries)->get_CaptionLabel() != NULL)
	{
		return (*itEntries)->get_CaptionLabel()->get_Content();
	}

	return "";
}
ety::Color&					ety::CComboBox::get_ColorFilter							(void)
{
	return m_c_etyColorComboBoxColorFilter;
}
ety::Color&					ety::CComboBox::get_TextColor							(void)
{
	return m_c_etyColorCaptionTextcolor;
}
ety::Color&					ety::CComboBox::get_TextColor_highlighted				(void)
{
	return m_c_etyColorCaptionTextcolor_highlighted;
}
std::list<ety::CButton*>&	ety::CComboBox::get_ListEntriesButtons									(void)
{
	return m_listBoxEntries;
}
ety::CButton* const			ety::CComboBox::get_ListEntryButton						(std::string strEntry)
{
	std::list<CButton*>::iterator itEntries = m_listBoxEntries.begin();

	for(itEntries ; itEntries != m_listBoxEntries.end() ; itEntries++)
	{
		if((*itEntries)->get_CaptionLabel() != NULL)
		{
			if((*itEntries)->get_CaptionLabel()->get_Content() == strEntry)
			{
				return (*itEntries);
			}
		}
	}

	return NULL;
}
ety::CButton* const			ety::CComboBox::get_ListEntryButton						(unsigned int uiPosition)
{
	if(uiPosition > (m_listBoxEntries.size() - m_uiDisabledButtons) - 1)
	{
		return NULL;
	}

	std::list<CButton*>::iterator itListEntry = m_listBoxEntries.begin();

	for( unsigned int uiLoop = 0 ; uiLoop < uiPosition ; uiLoop++)
	{
		itListEntry++;
	}

	return (*itListEntry);
}
ety::CButton* const			ety::CComboBox::get_HeaderBox							(void)
{
	return mp_c_etyButtonHeaderBox;
}
ety::CPictureControl* const	ety::CComboBox::get_ListBoxBackground					(void)
{
	return mp_c_etyPictureControlBackground;
}
ety::CScrollbar* const		ety::CComboBox::get_Scrollbar							(void)
{
	return mp_c_etyScrollbar;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCOMBOBOX.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////
