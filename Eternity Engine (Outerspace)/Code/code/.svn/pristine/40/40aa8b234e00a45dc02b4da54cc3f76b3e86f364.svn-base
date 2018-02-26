#pragma once
#include "CDialogitem.hpp"

namespace ety
{
	class CLabel;
	class CPictureControl;
	class CScrollbar;

	class CTextBox :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann

	protected:


		std::string							m_strOriginContent;
		ety::CLabel*						mp_c_etyLabelText;
		ety::CPictureControl*				mp_c_etyPictureControlBackground;
		ety::CScrollbar*					mp_c_etyScrollbar;

	public:
											CTextBox												(void);
											~CTextBox												(void);

											CTextBox												( 
																									std::string strCustomID, bool bScrollbar, 
																									const sf::Texture& c_sfTextureTextBoxTexture, float fScrollbarSizePercent, 
																									int uiDrawPosition, Affinity::en_etyAffinity en_etyAffinity, bool bVisibility, 
																									bool bActive, ety::Color c_etyColorTextBoxColorFilter,float fWidth, float fHeight, 
																									enum Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, 
																									sf::Vector2f c_sfVector2fPosition, bool bRealPosition,
																									sf::Vector2i c_sfVector2iTextBoxTexturesSubRect_Position,
																									sf::Vector2i c_sfVector2iTextBoxTexturesSubRect_Size,
																									sf::Vector2i c_sfVector2iScrollbarSubRect_Size, std::string strContent,
																									ety::Color c_etyColorTextcolor, unsigned int uiTextCharactersize,
																									enum Anchor::en_etyAnchor en_etyTextAnchor, bool bTextAnchorCentered, 
																									sf::Vector2f c_sfVector2fTextPosition,
																									bool bStandardSounds, CDialogitem* p_c_etyDialogitemParentDialogitem, 
																									CDialogitem* p_c_etyDialogitemAnchorOrientation, 
																									enum AttachedType::en_etyAttachedType en_etyAttachedType,
																									CDialog* p_c_etyDialogParentDialog, const sf::VideoMode& c_sfCurrentVideoMode
																									);


				void						adjust_TextBorders										(void);
		virtual	void						adjust_SizeToResolution									( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );
					
		virtual	bool						check_MouseCoordinates									(void);

		virtual	bool						draw_Dialogitem											(sf::RenderTexture* p_c_sfRenderTextureScene);

		virtual void						handle_InternEvents										(const sf::Event& c_sfEvent);

		virtual void						modificate_Colorfilter									(sf::Vector3f c_sfVector3fFactors);

		virtual	void						update_Dialogitem										(const sf::Uint32& uiFrameTime);


		//Set-Methoden
				void						set_Content												(std::string strNewContent);
		virtual	void						set_Active												(bool bActive);

		//Get-Methoden
				CLabel*				const	get_TextLabel											(void);
				CPictureControl*	const	get_Background											(void);
				CScrollbar*			const	get_Scrollbar											(void);
	};
}


