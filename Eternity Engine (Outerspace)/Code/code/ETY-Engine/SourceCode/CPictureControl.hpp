///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CPICTURECONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"


namespace ety
{
	//Dieses Dialogitem ist nur dazu da ein Sprite/"Bild" anzuzeigen, wie es der Name auch sagt (Verwaltet ein Bild)
	class CPictureControl :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann


	protected:
				
				float			m_fRotationAngle;
				ety::Color		m_c_etyColorFilter;
				sf::Sprite		m_c_sfSpritePicture;
				//Da sich z.B. alle Bilder der Steuerelemente auf einem sf::Texture befinden,
				//muss man herausfiltern, welches man "Subbild" davon man letztlich als z.B.
				//PictureSprite festlegen möchte.
				//SubRect_Size darin steht die Größe des Steuerelements auf dem Bild
				sf::IntRect		m_c_sfIntRectSubRect;



	public:
				
				
								//Kon- und Destruktor
								CPictureControl									(void);
								~CPictureControl								(void);

								//Überladene Konstruktoren
								CPictureControl									(
																				  std::string strCustomID, const sf::Texture& c_sfTexturePictureSprite,  float fWidth, float fHeight, 
																				  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectPictureSubRect, 
																				  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog 
																				);


																				
																				



		virtual	void			adjust_SizeToResolution							( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool			check_MouseCoordinates							(void);

		virtual	bool			draw_Dialogitem									(sf::RenderTexture* p_c_sfRenderTextureScene);

		virtual void			modificate_Colorfilter							(sf::Vector3f c_sfVector3fFactors);

		virtual	void			update_Dialogitem								(const sf::Uint32& uiFrameTime);



				//Set-Methoden
				void			set_RotationAngle								(float fRotationAngle);
				void			set_ColorFilter									(ety::Color c_etyColorFilter);
				void			set_PictureSprite								(const sf::Texture& c_sfTexturePicture, bool bUpdateSubRect);
				void			set_PictureSprite								(const sf::Sprite& c_sfSpriteHoverSprite, bool bUpdateSubRect);
				void			set_SubRect										(sf::IntRect c_sfIntRectSubRect, bool bUpdateSprite);
		virtual	void			set_RealPosition								(sf::Vector2f c_sfVector2fRealPosition);



				//Get-Methoden
				float			get_RotationAngle								(void);
				ety::Color		get_ColorFilter									(void);
				sf::Sprite&		get_PictureSprite								(void);
				sf::IntRect		get_SubRect										(void);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CPICTURECONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////