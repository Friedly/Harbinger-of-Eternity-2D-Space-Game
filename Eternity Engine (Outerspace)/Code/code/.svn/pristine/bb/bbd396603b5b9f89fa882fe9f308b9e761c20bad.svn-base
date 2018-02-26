///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCHECKBOX.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include "CCheckbox.hpp"

						ety::CCheckbox::CCheckbox					(void)
{
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}
							
						ety::CCheckbox::~CCheckbox					(void)
{
}


						ety::CCheckbox::CCheckbox					(
																	  std::string strCustomID, const sf::Texture& c_sfTextureCheckboxSet, bool bStatus_checked, float fWidth, 
																	  float fHeight, sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectCheckbocSubRect, 
																	  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																	)
						:m_bStatus_checked							(bStatus_checked)
						,m_c_sfIntRectCheckboxSubRect				(c_sfIntRectCheckbocSubRect)
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

	m_en_etyDialogitemType						=	DialogitemType::enCHECKBOX;

	c_sfVector2fPosition.x						=	c_sfVideoModeGamesettings.width*float(c_sfVector2fPosition.x/1680.f);
	c_sfVector2fPosition.y						=	c_sfVideoModeGamesettings.height*float(c_sfVector2fPosition.y/1050.f);

	m_c_sfVector2fPosition						=	c_sfVector2fPosition;
	/*if(bRealPosition == true)
	{
		m_c_sfVector2fRealPosition			=	c_sfVector2fPosition;
	}
	else
	{
		m_c_sfVector2fPosition				=	c_sfVector2fPosition;
	}*/

	calculate_Positions(false);


	m_c_sfSpriteCheckboxSprite.setTexture(c_sfTextureCheckboxSet);
	m_c_sfSpriteCheckboxSprite.setTextureRect(m_c_sfIntRectCheckboxSubRect);
	m_c_sfSpriteCheckboxSprite.setScale(m_c_sfIntRectCheckboxSubRect.left/m_fWidth,m_c_sfIntRectCheckboxSubRect.top/m_fHeight);
	m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height);

	m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
}



		bool			ety::CCheckbox::check_MouseCoordinates		(void)
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


		void			ety::CCheckbox::adjust_SizeToResolution		( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));

	update_Dialogitem(0);
}

		bool			ety::CCheckbox::draw_Dialogitem				(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	if(m_bVisibility == true)
	{
		//Jeh nach Status muss ein anderes Bild der Checkbox gezeichnet werden
		if(m_bStatus_checked == true)
		{
			(*p_c_sfRenderTextureScene).draw(m_c_sfSpriteCheckboxSprite);

			return true;
		}
		else if(m_bStatus_checked == false)
		{	
			//m_c_sfSpriteCheckboxSprite.setTextureRect(sf::IntRect(m_c_sfVector2iCheckboxSpriteSubRect_Position.x,m_c_sfVector2iCheckboxSpriteSubRect_Position.y,m_c_sfVector2iCheckboxSpriteSubRect_Size.x/2,m_c_sfVector2iCheckboxSpriteSubRect_Size.y/2));
			(*p_c_sfRenderTextureScene).draw(m_c_sfSpriteCheckboxSprite);

			return true;
		}
	}

	return false;
}

		void			ety::CCheckbox::handle_InternEvents			(const sf::Event& c_sfEvent)
{
	if(c_sfEvent.type	==	sf::Event::MouseButtonReleased)
	{
		if(c_sfEvent.mouseButton.button == sf::Mouse::Left)
		{
			if(get_EventSound(ety::SoundType::enCLICK) != NULL)
			{
				get_EventSound(ety::SoundType::enCLICK)->play();
			}

			if(m_bStatus_checked == true)
			{
				m_bStatus_checked = false;
			}
			else
			{
				m_bStatus_checked = true;
			}
		}
	}
}

		void			ety::CCheckbox::modificate_Colorfilter		(sf::Vector3f c_sfVector3fFactors)
{
	m_c_etyColorCheckboxSpriteColors.r	*= c_sfVector3fFactors.x;
	m_c_etyColorCheckboxSpriteColors.g	*= c_sfVector3fFactors.y;
	m_c_etyColorCheckboxSpriteColors.b	*= c_sfVector3fFactors.z;

	update_Dialogitem(0);
}

		void			ety::CCheckbox::update_Dialogitem			(const sf::Uint32& uiFrameTime)
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

	m_c_sfSpriteCheckboxSprite.setColor(m_c_etyColorCheckboxSpriteColors.get_sfColor());
	m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width * 2,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height * 2);
	m_c_sfSpriteCheckboxSprite.setPosition(m_c_sfVector2fRealPosition);


	if(m_bVisibility == true)
	{
		//Jeh nach Status muss ein anderes Bild der Checkbox gezeichnet werden
		if(m_bStatus_checked == true)
		{
			m_c_sfSpriteCheckboxSprite.setTextureRect(sf::IntRect(m_c_sfIntRectCheckboxSubRect.left + m_c_sfIntRectCheckboxSubRect.width,m_c_sfIntRectCheckboxSubRect.top,m_c_sfIntRectCheckboxSubRect.width,m_c_sfIntRectCheckboxSubRect.height));
		}
		else if(m_bStatus_checked == false)
		{
			m_c_sfSpriteCheckboxSprite.setTextureRect(m_c_sfIntRectCheckboxSubRect);
		}

		m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height);
	}
}



//Set-Methoden
		void			ety::CCheckbox::set_Status					(bool bStatus_checked)
{
	m_bStatus_checked					=	bStatus_checked;
}

		void			ety::CCheckbox::set_CheckboxSpriteColors	(ety::Color c_etyColorCheckboxSpriteColors)
{
	m_c_etyColorCheckboxSpriteColors	=	c_etyColorCheckboxSpriteColors;
	m_c_sfSpriteCheckboxSprite.setColor(m_c_etyColorCheckboxSpriteColors.get_sfColor());
}

		void			ety::CCheckbox::set_CheckboxSprite			(const sf::Sprite& c_sfSpriteCheckboxSprite, bool bUpdateSubRect)
{
	m_c_sfSpriteCheckboxSprite = c_sfSpriteCheckboxSprite;

	if(bUpdateSubRect == true)
	{
		m_c_sfSpriteCheckboxSprite.setTextureRect(m_c_sfIntRectCheckboxSubRect);
		m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height);
	}
}

		void			ety::CCheckbox::set_CheckboxSprite			(const sf::Texture& sfTextureCheckboxSprite, bool bUpdateSubRect)
{
	m_c_sfSpriteCheckboxSprite.setTexture(sfTextureCheckboxSprite);

	if(bUpdateSubRect == true)
	{
		m_c_sfSpriteCheckboxSprite.setTextureRect(m_c_sfIntRectCheckboxSubRect);
		m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height);
	}	
}

		void			ety::CCheckbox::set_SubRect				(sf::IntRect m_c_sfIntRectSubRect, bool bUpdateSprite)
{
	m_c_sfIntRectCheckboxSubRect	=	m_c_sfIntRectSubRect;

	if(bUpdateSprite == true)
	{
		m_c_sfSpriteCheckboxSprite.setTextureRect(m_c_sfIntRectCheckboxSubRect);
		m_c_sfSpriteCheckboxSprite.setScale(m_fWidth/m_c_sfSpriteCheckboxSprite.getLocalBounds().width,m_fHeight/m_c_sfSpriteCheckboxSprite.getLocalBounds().height);
	}	
}
			


//Get-Methoden
		bool			ety::CCheckbox::get_Status					(void)
{
	return m_bStatus_checked;
}

		ety::Color		ety::CCheckbox::get_CheckboxSpriteColors	(void)
{
	return	m_c_etyColorCheckboxSpriteColors;
}

const	sf::Sprite&		ety::CCheckbox::get_CheckboxSprite			(void)
{
	return m_c_sfSpriteCheckboxSprite;
}
	
		sf::IntRect	ety::CCheckbox::get_SubRect						(void)
{
	return m_c_sfIntRectCheckboxSubRect;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCHECKBOX.CPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////
