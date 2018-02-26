///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSCROLLBAR.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"


namespace ety
{
	class CPictureControl;
	class CButton;
	//Diese Klasse hat die Funktion einer konventionellen Scrollbar! Die Scrollbar besteht aus einem Background (PictureControl) sowie einem Schieber ("Slider" (Button)).
	//Die Scrollbar kann in mehrere Blöcke unterteilt werden in die der Slider beweget werden kann.
	//Die komplette Event- und Anpassungsverwaltung über nimmt immer der übergeordnete Context bzw. Dialogitem.
	class CScrollbar :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann

	protected:

				//Gibt die Anzahl der Blocks an in die die Scrollbar unterteilt ist
				unsigned int				m_uiAvailableBlocks;
				//Gibt den Block an in dem sich der Slider momentan befindet
				unsigned int				m_uiCurrentBlock;
				//Der Schieber bzw. Slider
				CButton*					mp_c_etyButtonSlider;
				//Der Background
				CPictureControl*			mp_c_etyPictureControlBackground;
				//Der Farbfilter
				ety::Color					m_c_etyColorShapeColors;

				//Die Position und Größe auf dem Texture-Set
				sf::IntRect					m_c_sfIntRectScrollbarSubRect;


	public:
											//Kon- und Destruktor
											CScrollbar								(void);
											~CScrollbar								(void);

											//Überladene Konstruktoren
											CScrollbar								(
																					  std::string strCustomID, const sf::Texture& p_c_sfTextureScrollbarSprite, float fWidth, 
																					  float fHeight, sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectScrollbarSubRect,
																					  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																					);



		virtual	void						adjust_SizeToResolution					( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool						check_MouseCoordinates					(void);

		virtual	bool						draw_Dialogitem							(sf::RenderTexture* p_c_sfRenderTextureScene);

		virtual	void						handle_InternEvents						(const sf::Event& c_sfEvent);

		virtual void						modificate_Colorfilter					(sf::Vector3f c_sfVector3fFactors);

		virtual	void						update_Dialogitem						(const sf::Uint32& uiFrameTime);
				bool						update_SliderPosition					(void);

		//Set-Methoden
				void						set_AvailableBlocks						(unsigned int uiAvailableBlocks);
				bool						set_CurrentBlock						(unsigned int uiCurrentBlock);
				void						set_ShapeColors							(ety::Color c_etyColorShapeColors);
		virtual	void						set_Active								(bool bActive);
		virtual void						set_Height								(float fHeight);
		virtual void						set_Width								(float fWidth);
		virtual void						set_Visibility							(bool bVisibility);


		//Get-Methoden
				unsigned int				get_AvailableBlocks						(void);
				unsigned int				get_CurrentBlock						(void);
				CButton* const				get_Slider								(void);
				CPictureControl* const		get_Background							(void);
				ety::Color					get_ShapeColors							(void);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSCROLLBAR.HPP								///////////
///////////////////////////////////////////////////////////////////////////////////////////////