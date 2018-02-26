///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CEDITCONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"



namespace ety
{
	class CLabel;
	class CPictureControl;

	//Dieses Dialogitem ist ein Eingabefeld und dient ausschließlich dazu
	//Eingaben anzunehmen und zu speichern
	class CEditControl :	  public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann


	protected:
				bool								m_bDeleteContentbyFirstFocus;
				bool								m_bFocused;
				int									m_iTextCursorPosition;
				CLabel*								mp_c_etyLabelText;
				CPictureControl*					mp_c_etyPictureControlBackground;
				VariableType::en_etyVariableType	m_en_etyVariableTypePossibleInputType;
					
				

	public:

													//Kon- und Destruktor
													CEditControl									(void); 
													~CEditControl									(void);
																
								
													//Überladene Konstruktoren
													CEditControl									(
																									  std::string strCustomID, const sf::Texture& c_sfTextureBackgroundSprite, 
																									  bool bDeleteContentbyFirstFocus, float fWidth, float fHeight, 
																									  sf::Vector2f c_sfVector2fPosition, sf::IntRect c_sfIntRectSubRect, 
																									  std::string strContent, float fCharactersize, ety::Color c_etyColorTextcolor, 
																									  CDialogitem* p_c_etyDialogitemParent, CDialog* p_c_etyDialogParentDialog
																									);



		virtual	void								adjust_SizeToResolution							( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool								check_MouseCoordinates							(void);
		virtual	bool								draw_Dialogitem									(sf::RenderTexture* p_c_sfRenderTextureScene);

				void								handle_InputEvents								(sf::Event sfEventLastEvent);

		virtual void								modificate_Colorfilter							(sf::Vector3f c_sfVector3fFactors);

		virtual void								reset_FocusedDialogitem							(void);

		virtual	void								update_Dialogitem								(const sf::Uint32& uiFrameTime);


				//Set-Methoden
				void								set_DeleteContentbyFirstFocus					(bool bDeleteContentbyFirstFocus);
				void								set_TextCursorPosition							(int iTextCursorPosition);
				void								set_EditControlContent							(std::string strEditControlContent);
				void								set_InputType									(enum VariableType::en_etyVariableType en_etyVariableType);
		virtual	void								set_Focus										(bool bFocus);



				//Get-Methoden
				bool								get_DeleteContentbyFirstFocus					(void);
				int									get_TextCursorPosition							(void);
				std::string							get_EditControlContent							(void);
				CLabel*								get_Text										(void);
				CPictureControl*					get_Background									(void);
				VariableType::en_etyVariableType	get_InputType									(void);
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CEDITCONTROL.HPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////