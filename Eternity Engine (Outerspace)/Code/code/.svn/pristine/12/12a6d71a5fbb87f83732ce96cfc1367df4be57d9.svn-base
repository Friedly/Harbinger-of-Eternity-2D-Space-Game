///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CPICTURECONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include "CMouse.hpp"
#include "CPictureControl.hpp"

				ety::CPictureControl::CPictureControl								(void)
{
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}

				ety::CPictureControl::~CPictureControl								(void)
{
}


				ety::CPictureControl::CPictureControl								(
																					  std::string strCustomID, const sf::Texture& c_sfTexturePictureSprite,  float fWidth, float fHeight, 
																					  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectPictureSubRect, 
																					  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																					)
				
				:m_c_sfIntRectSubRect												(c_sfIntRectPictureSubRect)
				,m_fRotationAngle													(0.f)
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

	m_en_etyDialogitemType						=	DialogitemType::enPICTURECONTROL;

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;

	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition		=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition			=	c_sfVector2fPosition;
	}*/
	
	calculate_Positions(false);

	m_c_sfSpritePicture.setTexture(c_sfTexturePictureSprite);
	m_c_sfSpritePicture.setTextureRect(m_c_sfIntRectSubRect);
	m_c_sfSpritePicture.setScale(m_fWidth/m_c_sfSpritePicture.getLocalBounds().width,m_fHeight/m_c_sfSpritePicture.getLocalBounds().height);
	m_c_sfSpritePicture.setRotation(m_fRotationAngle);

 	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}


void			ety::CPictureControl::adjust_SizeToResolution						( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	update_Dialogitem(0);
}


bool			ety::CPictureControl::check_MouseCoordinates						(void)
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


bool			ety::CPictureControl::draw_Dialogitem								(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_bVisibility == true)
	{
		(*p_c_sfRenderTextureScene).draw(m_c_sfSpritePicture);

		return true;
	}

	return false;
}


void			ety::CPictureControl::modificate_Colorfilter						(sf::Vector3f c_sfVector3fFactors)
{
	m_c_etyColorFilter.r	*= c_sfVector3fFactors.x;
	m_c_etyColorFilter.g	*= c_sfVector3fFactors.y;
	m_c_etyColorFilter.b	*= c_sfVector3fFactors.z;

	update_Dialogitem(0);
}

void			ety::CPictureControl::update_Dialogitem								(const sf::Uint32& uiFrameTime)
{
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

	//Aktualisieren der Sprites
	m_c_sfSpritePicture.setColor(m_c_etyColorFilter.get_sfColor());
	m_c_sfSpritePicture.setScale(m_fWidth/m_c_sfSpritePicture.getLocalBounds().width,m_fHeight/m_c_sfSpritePicture.getLocalBounds().height);
	m_c_sfSpritePicture.setPosition(m_c_sfVector2fRealPosition);
	m_c_sfSpritePicture.setRotation(m_fRotationAngle);
}



//Set-Methoden
void			ety::CPictureControl::set_RotationAngle								(float fRotationAngle)
{
	m_fRotationAngle	=	fRotationAngle;
}
void			ety::CPictureControl::set_ColorFilter								(ety::Color c_etyColorFilter)
{
	m_c_etyColorFilter	=	c_etyColorFilter;
	m_c_sfSpritePicture.setColor(m_c_etyColorFilter.get_sfColor());
}
void			ety::CPictureControl::set_PictureSprite								(const sf::Texture& sfTexturePicture, bool bUpdateSubRect)
{
	m_c_sfSpritePicture.setTexture(sfTexturePicture);

	if(bUpdateSubRect == true)
	{
		m_c_sfSpritePicture.setTextureRect(m_c_sfIntRectSubRect);
		m_c_sfSpritePicture.setScale(m_fWidth/m_c_sfSpritePicture.getLocalBounds().width,m_fHeight/m_c_sfSpritePicture.getLocalBounds().height);
	}
}
void			ety::CPictureControl::set_PictureSprite								(const sf::Sprite& c_sfSpriteHoverSprite, bool bUpdateSubRect)
{
	m_c_sfSpritePicture	=	c_sfSpriteHoverSprite;

	if(bUpdateSubRect == true)
	{
		m_c_sfSpritePicture.setTextureRect(m_c_sfIntRectSubRect);
		m_c_sfSpritePicture.setScale(m_fWidth/m_c_sfSpritePicture.getLocalBounds().width,m_fHeight/m_c_sfSpritePicture.getLocalBounds().height);
	}
}
void			ety::CPictureControl::set_SubRect									(sf::IntRect c_sfIntRectSubRect, bool bUpdateSprite)
{
	m_c_sfIntRectSubRect		=	c_sfIntRectSubRect;

	if(bUpdateSprite == true)
	{
		m_c_sfSpritePicture.setTextureRect(m_c_sfIntRectSubRect);
		m_c_sfSpritePicture.setScale(m_fWidth/m_c_sfSpritePicture.getLocalBounds().width,m_fHeight/m_c_sfSpritePicture.getLocalBounds().height);
	}
}
void			ety::CPictureControl::set_RealPosition								(sf::Vector2f c_sfVector2fRealPosition)
{
	m_c_sfVector2fRealPosition	=	c_sfVector2fRealPosition;

	m_c_sfSpritePicture.setPosition(m_c_sfVector2fRealPosition);
}



//Get-Methoden
float			ety::CPictureControl::get_RotationAngle								(void)
{
	return m_fRotationAngle;
}
ety::Color		ety::CPictureControl::get_ColorFilter								(void)
{
	return	m_c_etyColorFilter;
}
sf::Sprite&		ety::CPictureControl::get_PictureSprite								(void)
{
	return	m_c_sfSpritePicture;
}
sf::IntRect		ety::CPictureControl::get_SubRect									(void)
{
	return	m_c_sfIntRectSubRect;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CPICTURECONTROL.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////