///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CLABEL.HPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

//Eternity-Includes
#include "CDialogitem.hpp"

namespace ety
{
	//Ein Label ist ein ein Text der angezeigt wird
	//Er kann auch in verschiedenen Varianten ausgeschrieben (animiert) werden
	class CLabel :	  public CDialogitem
	{
	private:

		//Es soll die Möglichkeit gelassen werden, dass man andere Klassen von diesem Dialogitem ableiten kann


	protected:

				//Ob der Text ausgeschrieben/animiert werden soll
				bool												m_bTextwriteout;
				float												m_fTextwriteoutDuration;
				//Schriftgröße
				//Die Größe des Labels definiert sich über seine Schrifftgröße
				sf::Vector2u										m_c_sfVector2uCharactersize;
				//Die unteren beiden Variablen werden zum animieren des Textes benötigt
				//Jeh nach "Animations-art", kann die Bedeutung/Verwendung der Variablen
				//leicht variieren
				int													m_iDrawnCharacter;
				int													m_iPastFrametime;
				int													m_iPastFrames;
				//Dieser Zeiger wird auch zum animieren des Textes benötigt
				int*												mp_iAllocatedIndices;
				ety::Color											m_c_etyColorTextcolor;
				//Dies ist das eigentliche Objekt, was auch später gezeichnet wird
				sf::Text											m_c_sfTextLabelText;
				std::string											m_strContent;
		enum	TextwriteoutStyle::en_etyTextwriteoutStyle			m_en_etyTextwriteoutStyle;
				

		

	public:
		
			
																	CLabel							(void);
																	~CLabel							(void);
	

																	CLabel							(
																									  std::string strCustomID, std::string strContent, float fCharactersize, 
																									  ety::Color c_etyColorTextcolor, sf::Vector2f c_sfVector2fPosition, 
																									  CDialogitem* p_c_etyDialogitemParent, 
																									  CDialog* p_c_etyDialogParentDialog
																									);

																									
														
				
		virtual	void												adjust_SizeToResolution			( const sf::VideoMode& c_sfVideoModeNewSettings, const sf::VideoMode& c_sfVideoModeOldSettings );

		virtual	bool												check_MouseCoordinates			(void);

		virtual	bool												draw_Dialogitem					(sf::RenderTexture* p_c_sfRenderTextureScene);

		virtual void												modificate_Colorfilter			(sf::Vector3f c_sfVector3fFactors);

		virtual	void												update_Dialogitem				(const sf::Uint32& uiFrameTime);	

				///////////////////////////////////////////////////////////////////////////////////
				/// \Beschreibung: 
				/// Animiert den Text, damit das gewünschte Textwriteout richtig angezeigt wird
				///
				/// \parameter	void
				///
				/// \rückgabe	void
				///////////////////////////////////////////////////////////////////////////////////
				void												write_Text						(const sf::Uint32& uiFrameTime);
				
				
				
				//Set-Methoden
				void												set_Textwriteout				(bool bTextwriteout);
				void												set_TextwriteoutDuration		(float fDuration);
				///////////////////////////////////////////////////////////////////////////////////
				/// \Beschreibung: 
				/// Diese Methode wird für den COD-Textwriteout gebraucht, denn jeh nach Größe des
				///	Contents, wird ein Array angelegt und mit zufälligen Integerwerten belegt.
				///	Genaueres zur Funktionsweise des COD-Textwriteouts in der write_Text-Funktion
				///
				/// \parameter	void
				///
				/// \rückgabe	void
				///////////////////////////////////////////////////////////////////////////////////
				void												set_AllocatedIndices			(void);
				void												set_Charactersize				(sf::Vector2u c_sfVector2uCharactersize);
				void												set_Textcolor					(ety::Color c_sfColorTextcolor);
				void												set_Textfont					(sf::Font c_sfFontTextfont);
				///////////////////////////////////////////////////////////////////////////////////
				/// \parameter 
				/// 0	=	Regular
				///	1	=	Bold
				///	2	=	Italic
				///	3	=	Bold&Italic
				///	4	=	Underlined
				///	5	=	Bold&Underlined
				///	6	=	Italic&Underlined
				///	7	=	Bold&Italic&Underlined
				///////////////////////////////////////////////////////////////////////////////////
				void												set_TextStyle					(sf::Uint32 sf_Uint32Textstyle);
				void												set_sfTextObject				(sf::Text c_sfTextContent);
				void												set_sfTextObjectContent			(std::string strTextContent);
				void												set_TextwriteoutStyle			(enum TextwriteoutStyle::en_etyTextwriteoutStyle en_etyTextwriteoutStyle);
				void												set_Content						(std::string strContent);
		virtual	void												set_Transperancy				(sf::Uint8 sfUint8Transperancy);
		virtual	void												set_RealPosition				(sf::Vector2f c_sfVector2fRealPosition);
				
					

				//Get-Methoden
				bool												get_Textwriteout				(void);
				float												get_TextwriteoutDuration		(void);
				int*												get_AllocatedIndices			(void);
				sf::Vector2u										get_Charactersize				(void);
				ety::Color											get_Textcolor					(void);
				sf::Font											get_Textfont					(void);
				sf::Uint32											get_TextStyle					(void);
				sf::Text*	const									get_sfTextObject				(void);
				std::string											get_Content						(void);				
				TextwriteoutStyle::en_etyTextwriteoutStyle			get_TextwriteoutStyle			(void);		
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CLABEL.HPP									///////////
///////////////////////////////////////////////////////////////////////////////////////////////