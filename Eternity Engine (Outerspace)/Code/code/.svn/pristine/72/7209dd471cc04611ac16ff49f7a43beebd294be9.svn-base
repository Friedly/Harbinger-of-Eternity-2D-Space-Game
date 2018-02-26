///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCHECKBOX.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"

namespace ety
{
	//Eine "standardmäßige" Checkbox
	class CCheckbox :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann

	protected:
				//Ob die Checkbox "markiert" ist
				bool			m_bStatus_checked;
				ety::Color		m_c_etyColorCheckboxSpriteColors;
				sf::Sprite		m_c_sfSpriteCheckboxSprite;
				sf::IntRect		m_c_sfIntRectCheckboxSubRect;


	public:

								//Kon- und Destruktor
								CCheckbox											(void);
								~CCheckbox											(void);

								//Überladener Konstruktor
								CCheckbox											(
																					  std::string strCustomID, const sf::Texture& c_sfTextureCheckboxSet,  
																					  bool bStatus_checked, float fWidth, float fHeight, sf::Vector2f c_sfVector2fPosition, 
																					  sf::IntRect c_sfIntRectCheckbocSubRect, CDialogitem* p_c_etyDialogitemParent,
																					  CDialog* p_c_etyDialogParentDialog
																					);


																					

		virtual	void			adjust_SizeToResolution								( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool			check_MouseCoordinates								(void);
		virtual	bool			draw_Dialogitem										(sf::RenderTexture* p_c_sfRenderTextureScene);
		virtual void			handle_InternEvents									(const sf::Event& c_sfEvent);
		virtual void			modificate_Colorfilter								(sf::Vector3f c_sfVector3fFactors);
		virtual	void			update_Dialogitem									(const sf::Uint32& uiFrameTime);
								


				void			set_Status											(bool bStatus_checked);
				void			set_CheckboxSpriteColors							(ety::Color c_etyColorCheckboxSpriteColors);
				void			set_CheckboxSprite									(const sf::Sprite& c_sfSpriteCheckboxSprite, bool bUpdateSubRect);
				void			set_CheckboxSprite									(const sf::Texture& sfTextureCheckboxSprite, bool bUpdateSubRect);
				void			set_SubRect											(sf::IntRect m_c_sfIntRectSubRect, bool bUpdateSprite);



				bool			get_Status											(void);
				ety::Color		get_CheckboxSpriteColors							(void);
		const	sf::Sprite&		get_CheckboxSprite									(void);
				sf::IntRect		get_SubRect											(void);		
	};	
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CCHECKBOX.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////