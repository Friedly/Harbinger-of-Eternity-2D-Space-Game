///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSLIDECONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include "CSlideControl.hpp"
#include "CLabel.hpp"
#include "CPictureControl.hpp"
#include <sstream>

	
									ety::CSlideControl::CSlideControl						(void)
{
}

	
									ety::CSlideControl::~CSlideControl						(void)
{
}


									ety::CSlideControl::CSlideControl						(
																							  std::string strCustomID, const sf::Texture& c_sfTextureBackgroundTexture, float fWidth, 
																							  float fHeight, sf::Vector2f c_sfVector2fPosition,sf::Vector2f c_sfVector2fValueRange, 
																							  float fStartValue, sf::IntRect c_sfIntRectBackgroundSubRect, 
																							  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																							)
				:mp_c_etyLabelValueDisplay												(NULL)
				,mp_c_etyPictureControlBackground										(NULL)
				,mp_c_etyPictureControlAmountBar										(NULL)
				,m_bShowValueDisplay													(false)
				,m_bShowFloat															(false)
				,m_fCurrentValue														(fStartValue)
				,m_c_sfVector2fValueRange												(c_sfVector2fValueRange)
				,m_bPercent																(false)
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

	m_en_etyDialogitemType						=	DialogitemType::enSLIDECONTROL;

	m_c_sfIntRectAmountBarSubRect				=	m_c_sfIntRectAmountBarSubRect;
	m_c_sfIntRectAmountBarSubRect.top			+=	m_c_sfIntRectAmountBarSubRect.height;

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;
	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition				=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition					=	c_sfVector2fPosition;
	}*/
	
	calculate_Positions(false);



	mp_c_etyPictureControlBackground = new CPictureControl(strCustomID + "Background", c_sfTextureBackgroundTexture, fWidth, fHeight, sf::Vector2f(0,0), c_sfIntRectBackgroundSubRect, 
														   this, mp_c_etyDialogParentDialog);



	//Breite = fWidth* (CurrentVlaue/ValueRange.x);
	c_sfIntRectBackgroundSubRect.top	+=	c_sfIntRectBackgroundSubRect.height;
	m_c_sfIntRectAmountBarSubRect		=	c_sfIntRectBackgroundSubRect;

	mp_c_etyPictureControlAmountBar = new CPictureControl(strCustomID + "Bar", c_sfTextureBackgroundTexture, float(fWidth* (m_fCurrentValue/m_c_sfVector2fValueRange.y)), fHeight, 
														  sf::Vector2f(0,0), m_c_sfIntRectAmountBarSubRect, this, mp_c_etyDialogParentDialog);
															


	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}


void								ety::CSlideControl::adjust_SizeToResolution				( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	if(mp_c_etyLabelValueDisplay != NULL)
	{
		mp_c_etyLabelValueDisplay->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyPictureControlAmountBar != NULL)
	{
		mp_c_etyPictureControlAmountBar->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));
}


bool								ety::CSlideControl::check_MouseCoordinates				( void )
{
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

bool								ety::CSlideControl::create_ValueDisplay					( bool bShowFloat, bool bPercent, float fCharactersize, ety::Color c_etyColorTextColor, 
																							  enum ety::Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, 
																							  sf::Vector2f c_sfVector2fPosition)
{
	if(mp_c_etyLabelValueDisplay == NULL)
	{
		m_bShowValueDisplay = true;
		m_bPercent			= bPercent;
		m_bShowFloat		= bShowFloat;

		mp_c_etyLabelValueDisplay = new CLabel(m_strCustomID + "ValueDisplay", "", fCharactersize, c_etyColorTextColor, c_sfVector2fPosition, this, mp_c_etyDialogParentDialog);

		mp_c_etyLabelValueDisplay->set_Anchor(en_etyAnchor);
		mp_c_etyLabelValueDisplay->set_AnchorCentered(bAnchorCentered);

		update_Dialogitem(0);

		return true;
	}

	return false;
}


bool								ety::CSlideControl::draw_Dialogitem						( sf::RenderTexture* p_c_sfRenderTextureScene )
{
	if(m_bVisibility == true)
	{
		if(mp_c_etyPictureControlBackground != NULL)
		{
			mp_c_etyPictureControlBackground->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyPictureControlAmountBar != NULL)
		{
			mp_c_etyPictureControlAmountBar->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyLabelValueDisplay != NULL && m_bShowValueDisplay == true)
		{
			mp_c_etyLabelValueDisplay->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		return true;
	}

	return false;
}


void								ety::CSlideControl::handle_InternEvents					( const sf::Event& c_sfEvent )
{
	if(c_sfEvent.type	==	sf::Event::MouseButtonPressed)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			m_bAmountBarActive = true;
		}
		else
		{

		}		
	}
	else if(c_sfEvent.type	==	sf::Event::MouseButtonReleased || c_sfEvent.type	==	sf::Event::MouseButtonNoFocusReleased)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(m_bAmountBarActive == true)
			{
				m_bAmountBarActive = false;
			}

			if(get_EventSound(ety::SoundType::enCLICK) != NULL)
			{
				get_EventSound(ety::SoundType::enCLICK)->play();
			}
		}
		else
		{

		}		
	}
	else if(c_sfEvent.type	==	sf::Event::MouseMoved)
	{
		if(check_MouseCoordinates() == true)	
		{
			if(m_bHoverSoundPlayed == false)
			{
				if(get_EventSound(SoundType::enHOVER) != NULL)
				{
					//ÄNDERN/ANPASSEN!
					if(get_EventSound(SoundType::enHOVER)->getStatus() != sf::Sound::Playing)
					{
						get_EventSound(SoundType::enHOVER)->play();
						m_bHoverSoundPlayed = true;
					}
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


void								ety::CSlideControl::modificate_Colorfilter				( sf::Vector3f c_sfVector3fFactors )
{
	m_c_etyColorFilter.r			*= c_sfVector3fFactors.x;
	m_c_etyColorFilter.g			*= c_sfVector3fFactors.y;
	m_c_etyColorFilter.b			*= c_sfVector3fFactors.z;


	if(mp_c_etyLabelValueDisplay != NULL)
	{
		mp_c_etyLabelValueDisplay->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyLabelValueDisplay->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyPictureControlAmountBar != NULL)
	{
		mp_c_etyLabelValueDisplay->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}

		
void								ety::CSlideControl::update_Dialogitem					( const sf::Uint32& uiFrameTime )
{
	//Aktualisiert das SlideControl
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

	if(mp_c_etyLabelValueDisplay != NULL)
	{
		std::stringstream ssStream;
		if(m_bShowFloat == true)
		{
			ssStream << m_fCurrentValue;
			std::string strTmp = ssStream.str();		
		}
		else
		{
			int iTmp = int(m_fCurrentValue);
			ssStream << iTmp;
		}

		if(m_bPercent == true)
		{
			mp_c_etyLabelValueDisplay->set_Content(ssStream.str()+ "%");
			mp_c_etyLabelValueDisplay->set_sfTextObjectContent(ssStream.str()+ "%");
		}
		else
		{
			mp_c_etyLabelValueDisplay->set_Content(ssStream.str());
			mp_c_etyLabelValueDisplay->set_sfTextObjectContent(ssStream.str());
		}

		mp_c_etyLabelValueDisplay->update_Dialogitem(uiFrameTime);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->update_Dialogitem(uiFrameTime);
	}

	if(mp_c_etyPictureControlAmountBar != NULL)
	{
		if(m_fCurrentValue <= 0.f)
		{
			m_fCurrentValue = 0.f;
			mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
			mp_c_etyPictureControlAmountBar->set_SubRect(sf::IntRect(m_c_sfIntRectAmountBarSubRect.left,m_c_sfIntRectAmountBarSubRect.top, 0, m_c_sfIntRectAmountBarSubRect.height ),true);
			mp_c_etyPictureControlAmountBar->set_Width(0.f);

			mp_c_etyPictureControlAmountBar->update_Dialogitem(uiFrameTime);
			return ;
		}	

		if(m_bAmountBarActive == true)
		{
			sf::Vector2i c_sfVector2iMouseCoordinates = ety::CMouse::get_Position();

			if(c_sfVector2iMouseCoordinates.x < m_c_sfVector2fRealPosition.x)
			{
				m_fCurrentValue = 0.f;
				mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
				mp_c_etyPictureControlAmountBar->set_SubRect(sf::IntRect(m_c_sfIntRectAmountBarSubRect.left,m_c_sfIntRectAmountBarSubRect.top, 0, m_c_sfIntRectAmountBarSubRect.height ),true);
				mp_c_etyPictureControlAmountBar->set_Width(0.f);
			}
			else if(c_sfVector2iMouseCoordinates.x >= m_c_sfVector2fRealPosition.x + m_fWidth)
			{
				m_fCurrentValue = 100.f;
				mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
				mp_c_etyPictureControlAmountBar->set_SubRect(m_c_sfIntRectAmountBarSubRect,true);
				mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
			}
			else
			{
				m_fCurrentValue = (c_sfVector2iMouseCoordinates.x - m_c_sfVector2fRealPosition.x) / m_fWidth * m_c_sfVector2fValueRange.y;
				mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
				mp_c_etyPictureControlAmountBar->set_SubRect(sf::IntRect(m_c_sfIntRectAmountBarSubRect.left,m_c_sfIntRectAmountBarSubRect.top, int(m_c_sfIntRectAmountBarSubRect.width * (m_fCurrentValue/m_c_sfVector2fValueRange.y)), m_c_sfIntRectAmountBarSubRect.height),true);				
				mp_c_etyPictureControlAmountBar->set_Width(c_sfVector2iMouseCoordinates.x - m_c_sfVector2fRealPosition.x);
			}
		}
		else 
		{
			mp_c_etyPictureControlAmountBar->set_Width(m_fWidth);
			mp_c_etyPictureControlAmountBar->set_SubRect(sf::IntRect(m_c_sfIntRectAmountBarSubRect.left,m_c_sfIntRectAmountBarSubRect.top, int(m_c_sfIntRectAmountBarSubRect.width * (m_fCurrentValue/m_c_sfVector2fValueRange.y)), m_c_sfIntRectAmountBarSubRect.height),true);				
			mp_c_etyPictureControlAmountBar->set_Width((m_fCurrentValue/m_c_sfVector2fValueRange.y) * m_fWidth);
		}

		mp_c_etyPictureControlAmountBar->update_Dialogitem(uiFrameTime);
	}
}



//Set-Methoden

void								ety::CSlideControl::set_AmountBarActive					( bool bAmountBarActive )
{
	m_bAmountBarActive	=	bAmountBarActive;
}

void								ety::CSlideControl::set_Percent							( bool bPercent)
{
	m_bPercent	=	bPercent;
}

void								ety::CSlideControl::set_ShowFloat						( bool bShowFloat)
{
	m_bShowFloat	=	bShowFloat;
}

void								ety::CSlideControl::set_ShowValueDisplay				( bool bShowValueDisplay )
{
	m_bShowValueDisplay	=	bShowValueDisplay;
}

void								ety::CSlideControl::set_CurrentValue					( float fCurrentValue )
{
	if(m_c_sfVector2fValueRange.x <= fCurrentValue || m_c_sfVector2fValueRange.y >= fCurrentValue)
	{
		m_fCurrentValue	=	fCurrentValue;
	}
}

void								ety::CSlideControl::set_ColorFilter						( ety::Color c_etyColorFilter )
{
	m_c_etyColorFilter	= c_etyColorFilter;

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->set_ColorFilter(m_c_etyColorFilter);
	}

	if(mp_c_etyPictureControlAmountBar != NULL)
	{
		mp_c_etyPictureControlAmountBar->set_ColorFilter(m_c_etyColorFilter);
	}
}

void								ety::CSlideControl::set_ValueRange						( sf::Vector2f c_sfVector2fValueRange )
{
	m_c_sfVector2fValueRange	= c_sfVector2fValueRange;

	if(m_fCurrentValue > m_c_sfVector2fValueRange.y)
	{
		m_fCurrentValue	=	m_c_sfVector2fValueRange.y;
	}
	else if(m_fCurrentValue < m_c_sfVector2fValueRange.x)
	{
		m_fCurrentValue	=	m_c_sfVector2fValueRange.x;
	}
}

void								ety::CSlideControl::set_AmountBarStandardSubRect		( sf::IntRect c_sfIntRectAmountBarSubRect )
{
	m_c_sfIntRectAmountBarSubRect	= c_sfIntRectAmountBarSubRect;
}




//Get-Methoden

bool								ety::CSlideControl::get_AmountBarActive					( void )
{
	return m_bAmountBarActive;
}

bool								ety::CSlideControl::get_Percent							( void )
{
	return m_bPercent;
}

bool								ety::CSlideControl::get_ShowFloat						( void )
{
	return m_bShowFloat;
}

bool								ety::CSlideControl::get_ShowValueDisplay				( void )
{
	return m_bShowValueDisplay;
}

float								ety::CSlideControl::get_CurrentValue					( void )
{
	return m_fCurrentValue;
}

ety::Color&							ety::CSlideControl::get_ColorFilter						( void )
{
	return m_c_etyColorFilter;
}

sf::Vector2f						ety::CSlideControl::get_ValueRange						( void )
{
	return m_c_sfVector2fValueRange;
}

sf::IntRect							ety::CSlideControl::get_AmountBarSubRect				( void )
{
	return m_c_sfIntRectAmountBarSubRect;
}

ety::CLabel*			const		ety::CSlideControl::get_ValueDisplay					( void )
{
	return mp_c_etyLabelValueDisplay;
}

ety::CPictureControl*	const		ety::CSlideControl::get_Background						( void )
{
	return mp_c_etyPictureControlBackground;
}

ety::CPictureControl*	const		ety::CSlideControl::get_AmountBar						( void )
{
	return mp_c_etyPictureControlAmountBar;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSLIDECONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////
