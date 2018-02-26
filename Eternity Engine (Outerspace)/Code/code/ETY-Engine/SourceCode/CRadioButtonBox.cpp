#include "CRadioButtonBox.hpp"
#include "CPictureControl.hpp"


								ety::CRadioButtonBox::CRadioButtonBox							(void)
{
}


								ety::CRadioButtonBox::~CRadioButtonBox							(void)
{
}



								ety::CRadioButtonBox::CRadioButtonBox							(
																								  std::string strCustomID, unsigned int uiCurrentSelectedEntrie, unsigned int uiCurrentSelectedButton, 
																								  const sf::Texture& c_sfTextureRadioButtonBoxSetTexture, unsigned int uiDrawPosition, 
																								  Affinity::en_etyAffinity en_etyAffinity, bool bVisibility, bool bActive, 
																								  ety::Color c_etyColorShapeColors,float fWidth, float fHeight, 
																								  enum Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, sf::Vector2f c_sfVector2fPosition, 
																								  bool bRealPosition, sf::Vector2i c_sfVector2iRadioButtonBoxTextureSubRect_Position, 
																								  sf::Vector2i c_sfVector2iRadioButtonBoxTextureSubRect_Size, ety::Color c_etyColorTextcolor, 
																								  ety::Color c_etyColorTextcolor_Highlighted, unsigned int uiTextCharactersize, bool bStandardSounds,
																								  CDialogitem* p_c_etyDialogitemParentDialogitem, CDialogitem* p_c_etyDialogitemAnchorOrientation, 
																								  enum AttachedType::en_etyAttachedType en_etyAttachedType, CDialog* p_c_etyDialogParentDialog, 
																								  const sf::VideoMode& c_sfCurrentVideoMode,std::list<std::string>* p_listBoxEntries,
																								  bool bLocalization, CGamesettings* const p_c_etyGamesettingsManager
																								)
								:m_c_etyColorShapeColors										(c_etyColorShapeColors)
								,mp_c_etyPictureControlBackground								(NULL)
								,m_c_sfTextureRadioButtonBoxSet									(c_sfTextureRadioButtonBoxSetTexture)
								,m_c_etyColorCaptionTextcolor									(c_etyColorTextcolor)
								,m_c_etyColorCaptionTextcolor_highlighted						(c_etyColorTextcolor_Highlighted)
								,m_c_sfVector2iRadioButtonBoxTexturesSubRect_Position			(c_sfVector2iRadioButtonBoxTextureSubRect_Position)
								,m_c_sfVector2iRadioButtonBoxTexturesSubRect_Size				(c_sfVector2iRadioButtonBoxTextureSubRect_Size)
								,m_uiCurrentSelectedButton										(0)
								,m_uiTextCharactersize											(uiTextCharactersize)
								,mp_c_etyGamesettingsManager									(p_c_etyGamesettingsManager)
								,m_bLocalization												(bLocalization)
								,m_fOrigin_Width												(fWidth)
								,m_fOrigin_Height												(fHeight)
{
	sf::VideoMode c_sfVideoModeGamesettings			=	c_sfCurrentVideoMode;

	mp_c_etyDialogitemAnchorOrientation				=	p_c_etyDialogitemAnchorOrientation;
	mp_c_etyDialogitemParentDialogitem				=	p_c_etyDialogitemParentDialogitem;
	m_bRealPosition									=	bRealPosition;
	m_bVisibility									=	bVisibility;
	m_bActive										=	bActive;
	m_bInternActive									=	bActive;
	m_en_etyAnchor									=	en_etyAnchor;
	m_en_etyAttachedType							=	en_etyAttachedType;
	m_fWidth										=	c_sfVideoModeGamesettings.width*float(fWidth/1680.f);
	m_fHeight										=	c_sfVideoModeGamesettings.height*float(fHeight/1050.f);
	mp_c_etyDialogParentDialog						=	p_c_etyDialogParentDialog;
	m_strCustomID									=	strCustomID;
	m_bAnchorCentered								=	bAnchorCentered;
	m_uiDrawPosition								=	uiDrawPosition;
	m_en_etyAffinity								=	en_etyAffinity;

	c_sfVector2fPosition.x							=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y							=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition					=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition						=	c_sfVector2fPosition;
	}

	calculate_Positions(bRealPosition);


	//Anlegen der ListEntries über die add_ListEntry-Funktion
	if(p_listBoxEntries != NULL)
	{
		std::list<std::string>::iterator itNewBoxEntries = p_listBoxEntries->begin();
		int iCounter = 0;

		for(itNewBoxEntries ; itNewBoxEntries != p_listBoxEntries->end() ; itNewBoxEntries++)
		{
			add_ListEntry((*itNewBoxEntries),iCounter);
			iCounter++;
		}
	}
	
	

	set_CurrentSelectedEntry(uiCurrentSelectedEntrie, false);

	if(bStandardSounds == true)
	{
		m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
	}
}




bool							ety::CRadioButtonBox::add_ListEntry								( std::string strEntry, unsigned int uiPosition )
{
	return false;
}

void							ety::CRadioButtonBox::adjust_SizeToResolution					( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	//Anpassen der Größe
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));


	//,des Backgrounds
	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	//und der Position
	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));


	update_Dialogitem(0);
}

bool							ety::CRadioButtonBox::check_MouseCoordinates					( void )
{
	return true;
}

bool							ety::CRadioButtonBox::draw_Dialogitem							( sf::RenderTexture* p_c_sfRenderTextureScene )
{
	if(m_bVisibility == true && mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->draw_Dialogitem(p_c_sfRenderTextureScene);

		return true;
	}

	return false;
}

void							ety::CRadioButtonBox::handle_InternEvents						( const sf::Event& c_sfEvent )
{

}

void							ety::CRadioButtonBox::modificate_Colorfilter					( sf::Vector3f c_sfVector3fFactors )
{
	m_c_etyColorShapeColors.r	*= c_sfVector3fFactors.x;
	m_c_etyColorShapeColors.g	*= c_sfVector3fFactors.y;
	m_c_etyColorShapeColors.b	*= c_sfVector3fFactors.z;

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}

void							ety::CRadioButtonBox::update_Dialogitem							( const sf::Uint32& uiFrameTime )
{
	//Aktualisiert die RadioButtonBox
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


	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->update_Dialogitem(uiFrameTime);
	}
}


//Set-Methoden
void							ety::CRadioButtonBox::set_CurrentSelectedEntry					( unsigned int uiNewSelectedEntrie, bool bFocusSelectedEntry )
{

}

void							ety::CRadioButtonBox::set_ShapeColors							( ety::Color c_etyColorShapeColors )
{
	m_c_etyColorShapeColors = c_etyColorShapeColors;

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->set_ColorFilter(m_c_etyColorShapeColors);
	}
}


//Get-Methoden
ety::Color						ety::CRadioButtonBox::get_ShapeColors							( void )
{
	return m_c_etyColorShapeColors;
}


ety::CPictureControl*	const	ety::CRadioButtonBox::get_Background							( void )
{
	return mp_c_etyPictureControlBackground;
}
