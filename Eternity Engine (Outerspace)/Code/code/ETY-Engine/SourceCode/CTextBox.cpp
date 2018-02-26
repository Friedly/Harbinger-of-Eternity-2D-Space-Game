#include "CTextBox.hpp"
#include "CLabel.hpp"
#include "CPictureControl.hpp"
#include "CScrollbar.hpp"


								ety::CTextBox::CTextBox								(void)
								:mp_c_etyLabelText									(NULL)
								,mp_c_etyPictureControlBackground					(NULL)
								,mp_c_etyScrollbar									(NULL)
{
	mp_c_etyDialogitemParentDialogitem	=	NULL;
	mp_c_etyDialogParentDialog			=	NULL;
}


								ety::CTextBox::~CTextBox							(void)
{
	if(mp_c_etyLabelText != NULL)
	{
		delete mp_c_etyLabelText;
		mp_c_etyLabelText = NULL;
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		delete mp_c_etyPictureControlBackground;
		mp_c_etyPictureControlBackground = NULL;
	}

	if(mp_c_etyScrollbar != NULL)
	{
		delete mp_c_etyScrollbar;
		mp_c_etyScrollbar = NULL;
	}
}

								
								ety::CTextBox::CTextBox								( 
																					std::string strCustomID, bool bScrollbar, 
																					const sf::Texture& c_sfTextureTextBoxTexture, float fScrollbarSizePercent, 
																					int uiDrawPosition, Affinity::en_etyAffinity en_etyAffinity, bool bVisibility, 
																					bool bActive, ety::Color c_etyColorTextBoxColorFilter,float fWidth, float fHeight, 
																					enum ety::Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, 
																					sf::Vector2f c_sfVector2fPosition, bool bRealPosition,
																					sf::Vector2i c_sfVector2iTextBoxTexturesSubRect_Position,
																					sf::Vector2i c_sfVector2iTextBoxTexturesSubRect_Size,
																					sf::Vector2i c_sfVector2iScrollbarSubRect_Size, std::string strContent,
																					ety::Color c_etyColorTextcolor, unsigned int uiTextCharactersize, 
																					enum Anchor::en_etyAnchor en_etyTextAnchor, bool bTextAnchorCentered, 
																					sf::Vector2f c_sfVector2fTextPosition,
																					bool bStandardSounds, CDialogitem* p_c_etyDialogitemParentDialogitem, 
																					CDialogitem* p_c_etyDialogitemAnchorOrientation, 
																					enum ety::AttachedType::en_etyAttachedType en_etyAttachedType,
																					CDialog* p_c_etyDialogParentDialog, const sf::VideoMode& c_sfCurrentVideoMode
																					)
								:mp_c_etyLabelText									(NULL)
								,mp_c_etyPictureControlBackground					(NULL)
								,mp_c_etyScrollbar									(NULL)
								,m_strOriginContent									(strContent)
{
	sf::VideoMode c_sfVideoModeGamesettings	=	c_sfCurrentVideoMode;

	mp_c_etyDialogitemAnchorOrientation			=	p_c_etyDialogitemAnchorOrientation;
	mp_c_etyDialogitemParentDialogitem			=	p_c_etyDialogitemParentDialogitem;
	m_bRealPosition								=	bRealPosition;
	m_bVisibility								=	bVisibility;
	m_bActive									=	bActive;
	m_bInternActive								=	bActive;
	m_uiDrawPosition							=	uiDrawPosition;
	m_en_etyAffinity							=	en_etyAffinity;
	m_en_etyAnchor								=	en_etyAnchor;
	m_en_etyAttachedType						=	en_etyAttachedType;
	m_fWidth									=	c_sfVideoModeGamesettings.width*float(fWidth/1680.f);
	m_fHeight									=	c_sfVideoModeGamesettings.height*float(fHeight/1050.f);
	mp_c_etyDialogParentDialog					=	p_c_etyDialogParentDialog;
	m_strCustomID								=	strCustomID;
	m_bAnchorCentered							=	bAnchorCentered;
	m_en_etyDialogitemType						=	DialogitemType::enBUTTON;



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



	/*mp_c_etyLabelText							=	new CLabel(strCustomID + "Label", strContent, mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardFont(), uiTextCharactersize, 
		c_etyColorTextcolor, 0, Affinity::enSTANDARD, true, true,  en_etyTextAnchor,bTextAnchorCentered,c_sfVector2fTextPosition,false,false,TextwriteoutStyle::enSTANDARD,
		0.f,false,this,NULL, AttachedType::enCHILDREN, p_c_etyDialogParentDialog, c_sfCurrentVideoMode);


	mp_c_etyPictureControlBackground			=	new CPictureControl(strCustomID + "Background", c_sfTextureTextBoxTexture, 0, Affinity::enSTANDARD, true, true,
		c_etyColorTextBoxColorFilter, fWidth, fHeight, Anchor::enTOPLEFT, false, sf::Vector2f(0,0), 0, false, c_sfVector2iTextBoxTexturesSubRect_Position, 
		c_sfVector2iTextBoxTexturesSubRect_Size,false, this, NULL, AttachedType::enCHILDREN, p_c_etyDialogParentDialog, c_sfCurrentVideoMode);
	*/

	//Anlegen der Scrollbar
	if(bScrollbar == true)
	{
			/*mp_c_etyScrollbar							=	new CScrollbar( strCustomID + "Scrollbar", c_sfTextureTextBoxTexture, 1, Affinity::enBACKGROUND, false, true, 
																			ety::Color(255,255,255,255),  fWidth * fScrollbarSizePercent, fHeight * uiUnfoldedEntries, 
																			Anchor::enTOPLEFT, false, sf::Vector2f(fWidth * (1 - fScrollbarSizePercent), -fHeight), false, 
																			sf::Vector2i(0,m_c_sfVector2iComboBoxTexturesSubRect_Position.y+m_c_sfVector2iComboBoxTexturesSubRect_Size.y), 
																			m_c_sfVector2iScrollbarSubRect_Size, sf::Vector2i(56,50), this, NULL, AttachedType::enCHILDREN, 
																			mp_c_etyDialogParentDialog, c_sfCurrentVideoMode
																			);*/
			//Die Slider-Größe ist genau so groß wie die Schiene! Das muss noch geändert werden! (sf::Vector2i(56,50))
			
		
		//Damit mit der Scrollbar agiert werden kann, muss sie noch dem Dialog hinzugefügt werden
		//mp_c_etyDialogParentDialog->add_ChildrenDialogitem(mp_c_etyScrollbar);
			
		//mp_c_etyScrollbar->set_CurrentBlock(0);	
	}



	if(bStandardSounds == true)
	{
		m_mapEventSounds = mp_c_etyDialogParentDialog->get_DialogManager()->get_StandardSounds(m_en_etyDialogitemType);
	}
}



void							ety::CTextBox::adjust_TextBorders					(void)
{
	//mp_c_etyLabelText->
}

void							ety::CTextBox::adjust_SizeToResolution				( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings )
{
	m_fWidth	=	m_fWidth * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_fHeight	=	m_fHeight * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));


	if(mp_c_etyLabelText != NULL)
	{
		mp_c_etyLabelText->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	if(mp_c_etyScrollbar != NULL)
	{
		mp_c_etyScrollbar->adjust_SizeToResolution(c_sfVideoModeNewSettings,c_sfVideoModeOldSettings);
	}

	m_c_sfVector2fPosition.x	=	m_c_sfVector2fPosition.x * (float(c_sfVideoModeNewSettings.width)/float(c_sfVideoModeOldSettings.width));
	m_c_sfVector2fPosition.y	=	m_c_sfVector2fPosition.y * (float(c_sfVideoModeNewSettings.height)/float(c_sfVideoModeOldSettings.height));
}


bool							ety::CTextBox::check_MouseCoordinates				(void)
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

bool							ety::CTextBox::draw_Dialogitem						(sf::RenderTexture* p_c_sfRenderTextureScene)
{
	//ANPASSEN

	if(m_bVisibility == true)
	{
		if(mp_c_etyPictureControlBackground != NULL)
		{
			mp_c_etyPictureControlBackground->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyLabelText != NULL)
		{
			mp_c_etyLabelText->draw_Dialogitem(p_c_sfRenderTextureScene);
		}

		if(mp_c_etyScrollbar != NULL)
		{
			mp_c_etyScrollbar->draw_Dialogitem(p_c_sfRenderTextureScene);
		}
	}

	return false;
}

void							ety::CTextBox::handle_InternEvents					(const sf::Event& c_sfEvent)
{
	
}

void							ety::CTextBox::modificate_Colorfilter				(sf::Vector3f c_sfVector3fFactors)
{
	if(mp_c_etyLabelText != NULL)
	{
		mp_c_etyLabelText->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyPictureControlBackground != NULL)
	{
		mp_c_etyPictureControlBackground->modificate_Colorfilter(c_sfVector3fFactors);
	}

	if(mp_c_etyScrollbar != NULL)
	{
		mp_c_etyScrollbar->modificate_Colorfilter(c_sfVector3fFactors);
	}

	update_Dialogitem(0);
}

void							ety::CTextBox::update_Dialogitem					(const sf::Uint32& uiFrameTime)
{
	//ANPASSEN

	
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

	
	mp_c_etyLabelText->update_Dialogitem(uiFrameTime);
	mp_c_etyPictureControlBackground->update_Dialogitem(uiFrameTime);
	mp_c_etyScrollbar->update_Dialogitem(uiFrameTime);
}


//Set-Methoden
void							ety::CTextBox::set_Content							(std::string strNewContent)
{
	if(mp_c_etyLabelText != NULL)
	{
		mp_c_etyLabelText->set_Content(strNewContent);
	}
}

void							ety::CTextBox::set_Active							(bool bActive)
{
	m_bActive		=	bActive;
	m_bInternActive	=	bActive;

	mp_c_etyScrollbar->set_Active(m_bActive);
}


//Get-Methoden
ety::CLabel*			const	ety::CTextBox::get_TextLabel						(void)
{
	return mp_c_etyLabelText;
}

ety::CPictureControl*	const	ety::CTextBox::get_Background						(void)
{
	return mp_c_etyPictureControlBackground;
}

ety::CScrollbar*		const	ety::CTextBox::get_Scrollbar						(void)
{
	return mp_c_etyScrollbar;
}