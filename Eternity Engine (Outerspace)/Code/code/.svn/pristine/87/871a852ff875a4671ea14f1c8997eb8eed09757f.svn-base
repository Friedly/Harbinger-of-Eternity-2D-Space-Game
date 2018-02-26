///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGITEM.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

//Eternity-Includes
#include "CDialogitem.hpp"

												ety::CDialogitem::CDialogitem						(void)
												//Die anderen Variablen werden nicht initialisiert, da sie beim Aufrufen der Konstruktoren
												//der jeweiligen Dialogitems initialisiert werden, da von dieser Klasse kein Objekt angelegt
												//werden soll, weil sie nur als Grundlage/Schablone dient
												:mp_c_etyDialogitemAnchorOrientation			(NULL)
												,mp_c_etyDialogitemParentDialogitem				(NULL)
												,mp_c_etyDialogParentDialog						(NULL)
												,m_bHoverSoundPlayed							(false)
												,m_bFocused										(false)
												,m_uiDrawPosition								(0)
{
}

												ety::CDialogitem::~CDialogitem						(void)
{
	mp_c_etyDialogitemParentDialogitem	= NULL;
	mp_c_etyDialogParentDialog			= NULL;	
}



void											ety::CDialogitem::calculate_Positions				(bool bRealPosition)
{
	if(bRealPosition	==	true)
	{
		if(mp_c_etyDialogitemParentDialogitem != NULL)
		{
			m_c_sfVector2fPosition	=	m_c_sfVector2fPosition - mp_c_etyDialogitemParentDialogitem->get_RealPosition();
		}
		else
		{
			m_c_sfVector2fPosition = m_c_sfVector2fPosition - mp_c_etyDialogParentDialog->get_RealPosition();
		}
	}
	else
	{
		if(mp_c_etyDialogitemParentDialogitem != NULL)
		{
			m_c_sfVector2fRealPosition.x = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).x) +  m_c_sfVector2fPosition.x;
			m_c_sfVector2fRealPosition.y = (mp_c_etyDialogitemParentDialogitem->get_Anchor(m_en_etyAnchor).y) -  m_c_sfVector2fPosition.y;
		}
		else
		{
			m_c_sfVector2fRealPosition.x = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).x) +  m_c_sfVector2fPosition.x;
			m_c_sfVector2fRealPosition.y = (mp_c_etyDialogParentDialog->get_Anchor(m_en_etyAnchor,false).y) -  m_c_sfVector2fPosition.y;
		}

		if(m_bAnchorCentered == true)
		{
			m_c_sfVector2fRealPosition.x = m_c_sfVector2fRealPosition.x - (m_fWidth / 2);
			m_c_sfVector2fRealPosition.y = m_c_sfVector2fRealPosition.y - (m_fHeight / 2);
		}
	}
}
unsigned	int									ety::CDialogitem::check_ValuesAfterDecimalPoint		(float fValue)
{
	unsigned int uiReturnValue = unsigned int(fValue);

	if((fValue - uiReturnValue) >= 0.5)
	{
		uiReturnValue++;
	}

	return uiReturnValue;
}
bool											ety::CDialogitem::check_MouseCoordinates			(void)
{
	//Es wird durch die Position, Höhe und Breite des Dialogitems sozusagen ein Rechteck gebildet und
	//überprüft ob die Mauskoordinaten in diesem Rechteck liegen
	if(m_bVisibility == true)
	{
		sf::Vector2i c_sfVector2iMouseCoordinates = ety::CMouse::get_Position();

		if(c_sfVector2iMouseCoordinates.x >= m_c_sfVector2fRealPosition.x && c_sfVector2iMouseCoordinates.x <= m_c_sfVector2fRealPosition.x + m_fWidth && c_sfVector2iMouseCoordinates.y >= m_c_sfVector2fRealPosition.y && c_sfVector2iMouseCoordinates.y <= m_c_sfVector2fRealPosition.y + m_fHeight)
		{
			return true;
		}
	}

	return false;
}



void											ety::CDialogitem::add_EventSound					(enum SoundType::en_etySoundType en_etySoundType, sf::Sound* p_c_sfSoundNewEventSound)
{
	m_mapEventSounds[en_etySoundType] = 	p_c_sfSoundNewEventSound;
}
void											ety::CDialogitem::adjust_SizeToResolution			( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	//Diese Funktion muss für jedes Dialogitem eingen ausformuliert werden, ob die volle Funktionalität zu gewährleisten!
}


bool											ety::CDialogitem::draw_Dialogitem					(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	return false;
}


void											ety::CDialogitem::handle_InternEvents				(const sf::Event& c_sfEvent)
{
}


void											ety::CDialogitem::modificate_Colorfilter			(sf::Vector3f c_sfVector3fFactors)
{
	//Diese Funktion muss bei jedem Dialogitem selbst formuliert werden!
}


bool											ety::CDialogitem::remove_EventSound					(enum SoundType::en_etySoundType en_etySoundType)
{
	for(std::map<enum SoundType::en_etySoundType,sf::Sound*>::iterator itEventSounds = m_mapEventSounds.begin() ; itEventSounds != m_mapEventSounds.end() ; itEventSounds++)
	{
		if((*itEventSounds).first == en_etySoundType)
		{
			m_mapEventSounds.erase(itEventSounds);

			return true;
		}
	}

	return false;
}
void											ety::CDialogitem::reset_FocusedDialogitem			(void)
{
	m_bFocused = false;
}


void											ety::CDialogitem::update_Dialogitem					(const sf::Uint32& uiFrameTime)
{
	//Jedes Dialogitem muss und hat eine eigene Varinate sich zu aktualisieren
}



//Set-Methoden
void											ety::CDialogitem::set_Active						(bool bActive)
{
	m_bActive		=	bActive;
	m_bInternActive	=	bActive;
}
void											ety::CDialogitem::set_AnchorCentered				(bool bAnchorCentered)
{
	m_bAnchorCentered	=	bAnchorCentered;
}
void											ety::CDialogitem::set_Focus							(bool bFocus)
{
	m_bFocused	=	bFocus;
	
	if(m_bFocused == true)
	{
		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(this);
	}
	else
	{
		mp_c_etyDialogParentDialog->get_DialogManager()->change_FocusedDialogitem(NULL);
	}
}
void											ety::CDialogitem::set_HoverSoundPlayed				(bool bHoverSoundPlayed)
{
	m_bHoverSoundPlayed	=	bHoverSoundPlayed;
}
void											ety::CDialogitem::set_Visibility					(bool bVisibility)
{
	m_bVisibility		=	bVisibility;
}	
void											ety::CDialogitem::set_Affinity						(enum Affinity::en_etyAffinity en_etyAffinity)
{
	m_en_etyAffinity	=	en_etyAffinity;

	//Da das Ändern der Affinity genau den selben Code benutzt, wie das Einfügen eines neuen Dialogitems, wird die add_Dialogitem-Funktion hierfür verwendet.
	mp_c_etyDialogParentDialog->add_Dialogitem(this, false);
}	
void											ety::CDialogitem::set_Anchor						(enum Anchor::en_etyAnchor en_etyAnchor)
{
	m_en_etyAnchor		=	en_etyAnchor;
}
bool											ety::CDialogitem::set_AttachedType					(enum ety::AttachedType::en_etyAttachedType en_etyAttachedType)
{
	//Children-Dialogitems können nicht im AttachedType geändert werden, denn es macht keinen Sinn einem Button seine Caption wegzunehmen!

	if(m_en_etyAttachedType != AttachedType::enCHILDREN && en_etyAttachedType != AttachedType::enCHILDREN)
	{
		m_en_etyAttachedType = en_etyAttachedType;

		return true;
	}

	return false;
}
void											ety::CDialogitem::set_Height						(float fHeight)
{
	m_fHeight		=	fHeight;
}
void											ety::CDialogitem::set_Width							(float fWidth)
{
	m_fWidth		=	fWidth;
}
void											ety::CDialogitem::set_DrawPosition					(unsigned int uiDrawPosition)
{
	m_uiDrawPosition	=	uiDrawPosition;

	//Da das Ändern der DrawPosition genau den selben Code benutzt, wie das Einfügen eines neuen Dialogitems, wird die add_Dialogitem-Funktion hierfür verwendet.
	mp_c_etyDialogParentDialog->add_Dialogitem(this, false);
}
void											ety::CDialogitem::set_Position						(sf::Vector2f c_sfVector2fPosition)
{
	m_c_sfVector2fPosition = c_sfVector2fPosition;
}
void											ety::CDialogitem::set_RealPosition					(sf::Vector2f c_sfVector2fRealPosition)
{
	m_c_sfVector2fRealPosition	=	c_sfVector2fRealPosition;
	m_bRealPosition				=	true;
}
void											ety::CDialogitem::set_RealPosition					(bool bRealPosition)
{
	m_bRealPosition	=	bRealPosition;
}
void											ety::CDialogitem::set_CustomID						(std::string strNewCustomID)
{
	m_strCustomID			=	strNewCustomID;
}
bool											ety::CDialogitem::set_ParentDialogitem				(ety::CDialogitem& p_c_etyDialogitemNewParentDialogitem)
{
	if(m_en_etyAttachedType == AttachedType::enATTACHED || m_en_etyAttachedType == AttachedType::enNOTATTACHED)
	{
		mp_c_etyDialogitemParentDialogitem	=	&p_c_etyDialogitemNewParentDialogitem;
		
		return true;
	}

	return false;
}
void											ety::CDialogitem::set_AnchorOrientation				(CDialogitem* const p_c_etyDialogitemAnchorOrientation)
{
	mp_c_etyDialogitemAnchorOrientation	=	p_c_etyDialogitemAnchorOrientation;
}


//Get-Methoden	
bool											ety::CDialogitem::get_Active						(void)
{
	return	m_bActive;
}
bool											ety::CDialogitem::get_AnchorCentered				(void)
{
	return m_bAnchorCentered;
}
bool											ety::CDialogitem::get_Focus							(void)
{
	return m_bFocused;
}
bool											ety::CDialogitem::get_HoverSoundPlayed				(void)
{
	return m_bHoverSoundPlayed;
}
bool											ety::CDialogitem::get_RealPositionStatus			(void)
{
	return m_bRealPosition;
}
bool											ety::CDialogitem::get_Visibility					(void)
{
	return m_bVisibility;
}
float											ety::CDialogitem::get_Height						(void)
{
	return m_fHeight;
}
float											ety::CDialogitem::get_Width							(void)
{
	return m_fWidth;
}
unsigned int									ety::CDialogitem::get_DrawPosition					(void)
{
	return m_uiDrawPosition;
}
sf::Sound* const								ety::CDialogitem::get_EventSound					(enum SoundType::en_etySoundType en_etySoundType)
{
	std::map<enum SoundType::en_etySoundType,sf::Sound*>::iterator itSound = m_mapEventSounds.find(en_etySoundType);

	if(itSound == m_mapEventSounds.end())
	{
		return NULL;
	}

	return m_mapEventSounds[en_etySoundType];
}
enum ety::Affinity::en_etyAffinity				ety::CDialogitem::get_Affinity						(void)
{
	return m_en_etyAffinity;
}
sf::Vector2f									ety::CDialogitem::get_Anchor						(enum Anchor::en_etyAnchor en_etyAnchor)
{
	//Die gleiche Berechnung wie in CDialog.cpp
	sf::Vector2f c_sfVector2fAnchor;

	if(en_etyAnchor == Anchor::enTOPLEFT)
	{
		c_sfVector2fAnchor		=	m_c_sfVector2fRealPosition;
	}
	else if(en_etyAnchor == Anchor::enTOP || en_etyAnchor == Anchor::enALIGNEDMIDTOP)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x + m_fWidth / 2;
	}
	else if(en_etyAnchor == Anchor::enTOPRIGHT)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x + m_fWidth;
	}
	else if(en_etyAnchor == Anchor::enLEFT || en_etyAnchor == Anchor::enALIGNEDLEFT)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y + m_fHeight / 2;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x;
	}
	else if(en_etyAnchor == Anchor::enMID)
	{
		c_sfVector2fAnchor.x	=	(m_c_sfVector2fRealPosition.x) + (m_fWidth / 2);
		c_sfVector2fAnchor.y	=	(m_c_sfVector2fRealPosition.y) + (m_fHeight / 2);
	}
	else if(en_etyAnchor == Anchor::enRIGHT)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y + m_fHeight / 2;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x + m_fWidth;
	}
	else if(en_etyAnchor == Anchor::enBOTTOMLEFT)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y + m_fHeight;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x;
	}
	else if(en_etyAnchor == Anchor::enBOTTOM)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y + m_fHeight;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x + m_fWidth / 2;
	}
	else if(en_etyAnchor == Anchor::enBOTTOMRIGHT)
	{
		c_sfVector2fAnchor.y	=	m_c_sfVector2fRealPosition.y + m_fHeight;
		c_sfVector2fAnchor.x	=	m_c_sfVector2fRealPosition.x + m_fWidth;
	}

	return c_sfVector2fAnchor;

}
sf::Vector2f									ety::CDialogitem::get_Position						(void)
{
	return m_c_sfVector2fPosition;
}
sf::Vector2f									ety::CDialogitem::get_RealPosition					(void)
{	
	return	m_c_sfVector2fRealPosition;
}
ety::mapSoundTypeSounds* const					ety::CDialogitem::get_EventSoundmap					(void)
{
	return &m_mapEventSounds;
}
const std::string&								ety::CDialogitem::get_CustomID						(void)
{
	return m_strCustomID;
}	
enum ety::Anchor::en_etyAnchor					ety::CDialogitem::get_Anchor						(void)
{
	return m_en_etyAnchor;
}
enum ety::AttachedType::en_etyAttachedType		ety::CDialogitem::get_AttachedType					(void)
{
	return m_en_etyAttachedType;
}
ety::DialogitemType::en_etyDialogitemType		ety::CDialogitem::get_DialogitemType				(void)
{
	return m_en_etyDialogitemType;
}		
ety::CDialog* const								ety::CDialogitem::get_ParentDialog					(void)
{
	return mp_c_etyDialogParentDialog;
}
ety::CDialogitem* const							ety::CDialogitem::get_AnchorOrientation				(void)
{
	return mp_c_etyDialogitemAnchorOrientation;
}
ety::CDialogitem* const							ety::CDialogitem::get_ParentDialogitem				(void)
{
	return	mp_c_etyDialogitemParentDialogitem;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGITEM.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////