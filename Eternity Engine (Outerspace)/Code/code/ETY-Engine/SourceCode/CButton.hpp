///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CBUTTON.HPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"


namespace ety
{
	class		CLabel;
	class		CPictureControl;
	//Dies ist ein Dialogitem, der die Funktion eines normalen Buttons übernimmt.
	//Ein Button besteht aus einer Caption, einem BackgroundSprite und einem HoverSprite
	//Es ist möglich nur einen Textbutton zuerstellen, was bedeutet, das der Button nur aus
	//der Caption und nicht aus einem Bild entsteht
	//Das HoverSprite ist ein Bild, welches angezeigt wird, wenn man mit der Maus über bzw.
	//auf den Button geht
	class CButton :	  public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann

	protected:

				bool					m_bAnimatedCaption;
				bool					m_bCaptionHighlighted;
				bool					m_bHoverSprite_Visibility;
				bool					m_bTextButton;
				float					m_fHoverSprite_Height;
				float					m_fHoverSprite_Width;
				//Die Attribute mit der Endung _highlighted,
				//sind die Attribute des Labels, wie es aussehen soll
				//wenn es "markiert", also die Maus auf der Caption ist, ist
				sf::Vector2u			m_c_sfVector2uCharactersize_highlighted;
				//Ein Button kann auch ein Label und dadruch eine Caption haben
				ety::CLabel*			mp_c_etyLabelCaptionLabel;
				ety::CLabel*			mp_c_etyLabelTooltipText;
				ety::Color				m_c_etyColorBackgroundColors;
				ety::Color				m_c_etyColorCaptionColor_highlighted;
				ety::Color				m_c_etyColorHoverSpriteColors;
				ety::CPictureControl*	mp_c_etyPictureControlTooltipBackground;
				sf::Sprite				m_c_sfSpriteButton;
				//Da sich z.B. alle Bilder der Steuerelemente auf einem sf::Texture befinden,
				//muss man herausfiltern, welches man "Subbild" davon man letztlich als z.B.
				//ButtonSprite festlegen möchte.
				//SubRect_Size darin steht die Größe des Steuerelements auf dem Bild
				//Das Hoverbild liegt immer rechts neben dem 'normalen'S
				sf::IntRect				m_c_sfIntRectButtonSubRect;
				sf::IntRect				m_c_sfIntRectHoverSpriteSubRect;

				
				void					change_SpriteStyle								(bool bHoverSprite);
				void					set_CaptionHighlighted							(bool bCaptionHighlighted);

	public:

										//Kon- und Destruktor
										CButton													(void); 
										~CButton												(void);
																
								
										//Überladene Konstruktoren
										//Für einen normalen Button
										CButton													(
																								 std::string strCustomID, const sf::Texture& c_sfTextureButtonSet, 
																								 float fWidth, float fHeight, sf::Vector2f c_sfVector2fPosition, 
																								 sf::IntRect c_sfIntRectButtonSubRect, CDialogitem* p_c_etyDialogitemParent, 
																								  CDialog* p_c_etyDialogParentDialog
																								);


										//Textbutton
										CButton													(
																								 std::string strCustomID, sf::Vector2f c_sfVector2fPosition, 
																								 std::string strContent, float fCharactersize, ety::Color c_etyColorTextcolor, 
																								 ety::Color c_etyColorCaptionColor_highlighted, CDialogitem* p_c_etyDialogitemParent, 
																								 CDialog* p_c_etyDialogParentDialog
																								);

																						  
																						  

																						  
	 

		virtual	void					adjust_SizeToResolution									( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool					check_MouseCoordinates									(void);
										///////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Erstellt ein Label bzw. die Caption für den Button
								///
								/// \parameter	[...]
								///
								/// \rückgabe	void
								///////////////////////////////////////////////////////////////////////////////////
				bool					create_CaptionLabel										(
																								  ety::Color c_etyColorCaptionColor_highlighted, std::string strContent, float fCharactersize, 
																								  ety::Color c_etyColorTextcolor
																								);

				bool					create_Tooltip											( std::string strContent, float fCharactersize, ety::Color c_etyColorTextcolor );

										///////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Löscht das Label bzw. die Caption des Buttons ordnungsgemäß
								///
								/// \parameter	void
								///
								/// \rückgabe	void
								///////////////////////////////////////////////////////////////////////////////////
				bool					delete_CaptionLabel										(void);
		virtual	bool					draw_Dialogitem											(sf::RenderTexture* p_c_sfRenderTextureScene);
		virtual void					handle_InternEvents										(const sf::Event& c_sfEvent);
		virtual void					modificate_Colorfilter									(sf::Vector3f c_sfVector3fFactors);
										///////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Schreibt die Gestaltungsattribute der Caption, wenn sie "markiert" ist, in das Label
								/// und umgekehrt
								///
								/// \parameter	void
								///
								/// \rückgabe	void
								///////////////////////////////////////////////////////////////////////////////////
				void					swap_HighlightInformation								(void);
		virtual	void					update_Dialogitem										(const sf::Uint32& uiFrameTime);


				//Set-Methoden
				void					set_AnimatedCaption										(bool bAnimatedCaption);
				void					set_TextButton											(bool bTextButton);
				void					set_HoverSprite_Visibility								(bool bHoverSprite_Visibility);
				void					set_Charactersize_highlighted							(sf::Vector2u c_sfVector2uCharactersize_highlighted);
				void					set_BackgroundColors									(ety::Color c_etyColorBackgroundColors);
				void					set_CaptionColor_highlighted							(ety::Color c_etyColorCaptionColor_highlighted);
				void					set_HoverSprite_Width									(float fHoverSprite_Width);
				void					set_HoverSprite_Height									(float fHoverSprite_Height);
				void					set_HoverSpriteColors									(ety::Color c_etyColorHoverSpriteColors);
				void					set_Background_SubRect									(sf::IntRect c_sfIntRectButtonSubRect, bool bUpdateSprite);
				void					set_HoverSprite_SubRect									(sf::IntRect c_sfIntRectHoverSpriteSubRect, bool bUpdateSprite);
		virtual void					set_Active												(bool bActive);
		virtual void					set_Visibility											(bool bVisibility);	
		virtual	void					set_RealPosition										(sf::Vector2f c_sfVector2fRealPosition);




				//Get-Methoden
				bool					get_AnimatedCaption										(void);
				bool					get_TextButton											(void);
				bool					get_HoverSprite_Visibility								(void);
										///////////////////////////////////////////////////////////////////////////////////
								/// \Beschreibung: 
								/// Gibt zurück ob der Mauszeiger über dem Schriftzug liegt
								///
								/// \parameter	void
								///
								/// \rückgabe	bool
								///////////////////////////////////////////////////////////////////////////////////
				bool					get_CaptionHighlighted									(void);
				float					get_HoverSprite_Width									(void);
				float					get_HoverSprite_Height									(void);
				sf::Vector2u			get_Charactersize_highlighted							(void);
				CLabel*	const			get_CaptionLabel										(void);
				CLabel*	const			get_TooltipLabel										(void);
				CPictureControl* const	get_TooltipBackground									(void);
				ety::Color				get_BackgroundColors									(void);
				ety::Color				get_CaptionColor_highlighted							(void);
				ety::Color				get_HoverSpriteColors									(void);
				sf::Sprite				get_BackgroundSprite									(void);
				sf::Sprite				get_HoverSprite											(void);
				sf::IntRect				get_Background_SubRect									(void);
				sf::IntRect				get_HoverSprite_SubRect									(void);
	};			
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CBUTTON.HPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////