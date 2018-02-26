///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSLIDECONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"


namespace ety
{
	class CLabel;
	class CPictureControl;

	class CSlideControl  :	  public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann

	protected:

		bool									m_bAmountBarActive;
		bool									m_bPercent;
		bool									m_bShowFloat;
		bool									m_bShowValueDisplay;
		float									m_fCurrentValue;
		ety::Color								m_c_etyColorFilter;
		sf::Vector2f							m_c_sfVector2fValueRange;
		sf::IntRect								m_c_sfIntRectAmountBarSubRect;
		CLabel*									mp_c_etyLabelValueDisplay;
		CPictureControl*						mp_c_etyPictureControlBackground;
		CPictureControl*						mp_c_etyPictureControlAmountBar;

	public:

		//Kon- und Destruktor
												CSlideControl						(void);
												~CSlideControl						(void);
		

		//Überladene Konstruktoren
												CSlideControl						(
																					  std::string strCustomID, const sf::Texture& c_sfTextureBackgroundTexture, float fWidth, 
																					  float fHeight, sf::Vector2f c_sfVector2fPosition,sf::Vector2f c_sfVector2fValueRange, 
																					  float fStartValue, sf::IntRect c_sfIntRectBackgroundSubRect, 
																					  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																					);



		virtual	void							adjust_SizeToResolution				( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool							check_MouseCoordinates				( void );

				bool							create_ValueDisplay					( bool bShowFloat, bool bPercent, float fCharactersize, ety::Color c_etyColorTextColor, 
																					  enum Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, sf::Vector2f c_sfVector2fPosition);

		virtual	bool							draw_Dialogitem						( sf::RenderTexture* p_c_sfRenderTextureScene );

		virtual void							handle_InternEvents					( const sf::Event& c_sfEvent );

		virtual void							modificate_Colorfilter				( sf::Vector3f c_sfVector3fFactors );
			
		virtual	void							update_Dialogitem					( const sf::Uint32& uiFrameTime );


		//Set-Methoden
				void							set_AmountBarActive					( bool bAmountBarActive );
				void							set_Percent							( bool bPercent);
				void							set_ShowFloat						( bool bShowFloat);
				void							set_ShowValueDisplay				( bool bShowValueDisplay );
				void							set_CurrentValue					( float fCurrentValue );
				void							set_ColorFilter						( ety::Color c_etyColorFilter );
				void							set_ValueRange						( sf::Vector2f c_sfVector2fValueRange );
				void							set_AmountBarStandardSubRect		( sf::IntRect c_sfIntRectAmountBarSubRect );
				

		//Get-Methoden
				bool							get_AmountBarActive					( void );
				bool							get_Percent							( void );
				bool							get_ShowFloat						( void );
				bool							get_ShowValueDisplay				( void );
				float							get_CurrentValue					( void );
				ety::Color&						get_ColorFilter						( void );
				sf::Vector2f					get_ValueRange						( void );
				sf::IntRect						get_AmountBarSubRect				( void );
				CLabel*				const		get_ValueDisplay					( void );
				CPictureControl*	const		get_Background						( void );
				CPictureControl*	const		get_AmountBar						( void );
	};
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CSLIDECONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////
