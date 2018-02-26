#pragma once
#include "CDialogitem.hpp"

namespace ety
{
	class CPictureControl;
	class CButton;

	class CRadioButtonBox :	public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, von der Klasse abzuleiten

	protected:

		bool								m_bLocalization;
		float								m_fOrigin_Width;
		float								m_fOrigin_Height;
		unsigned int						m_uiCurrentSelectedButton;
		unsigned int						m_uiTextCharactersize;
		ety::Color							m_c_etyColorShapeColors;
		ety::Color							m_c_etyColorCaptionTextcolor;
		ety::Color							m_c_etyColorCaptionTextcolor_highlighted;
		CGamesettings*						mp_c_etyGamesettingsManager;
		CPictureControl*					mp_c_etyPictureControlBackground;
		sf::Texture							m_c_sfTextureRadioButtonBoxSet;
		sf::Vector2i						m_c_sfVector2iRadioButtonBoxTexturesSubRect_Position;
		sf::Vector2i						m_c_sfVector2iRadioButtonBoxTexturesSubRect_Size;
		std::list<CButton*>					m_listRadioButtons;


	public:
											CRadioButtonBox							(void);
											~CRadioButtonBox						(void);



											CRadioButtonBox							(
																					  std::string strCustomID, unsigned int uiCurrentSelectedEntrie, unsigned int uiCurrentSelectedButton, 
																					  const sf::Texture& c_sfTextureRadioButtonBoxSetTexture, unsigned int uiDrawPosition, 
																					  Affinity::en_etyAffinity en_etyAffinity, bool bVisibility, bool bActive, 
																					  ety::Color c_etyColorShapeColors,float fWidth, float fHeight, 
																					  enum Anchor::en_etyAnchor en_etyAnchor, bool bAnchorCentered, sf::Vector2f c_sfVector2fPosition, 
																					  bool bRealPosition, sf::Vector2i c_sfVector2iRadioButtonBoxTextureSubRect_Position, 
																					  sf::Vector2i c_sfVector2iRadioButtonBoxTextureSubRect_Size, ety::Color c_etyColorTextcolor, 
																					  ety::Color c_etyColorTextcolor_Highlighted, unsigned int uiTextCharactersize, bool bStandardSounds,
																					  CDialogitem* p_c_etyDialogitemParentDialogitem, CDialogitem* p_c_etyDialogitemAnchorOrientation, 
																					  enum AttachedType::en_etyAttachedType en_etyAttachedType, CDialog* p_c_etyDialogParentDialog, 
																					  const sf::VideoMode& c_sfCurrentVideoMode, std::list<std::string>* p_listBoxEntries,
																					  bool bLocalization, CGamesettings* const p_c_etyGamesettingsManager
																					);
											
																					//ety::Color c_etyColorTextcolor
																					//ety::Color c_etyColorTextcolor_Highlighted, 
																					//unsigned int uiTextCharactersize


				bool						add_ListEntry							( std::string strEntry, unsigned int uiPosition );
		virtual	void						adjust_SizeToResolution					( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool						check_MouseCoordinates					( void );

		virtual	bool						draw_Dialogitem							( sf::RenderTexture* p_c_sfRenderTextureScene );

		virtual	void						handle_InternEvents						( const sf::Event& c_sfEvent );

		virtual void						modificate_Colorfilter					( sf::Vector3f c_sfVector3fFactors );

		virtual	void						update_Dialogitem						( const sf::Uint32& uiFrameTime );



		//Set-Methoden
				void						set_CurrentSelectedEntry				( unsigned int uiNewSelectedEntrie, bool bFocusSelectedEntry );
				void						set_ShapeColors							( ety::Color c_etyColorShapeColors );

		//Get-Methoden
				ety::Color					get_ShapeColors							( void );
				CPictureControl*	const	get_Background							( void );
	};
}

