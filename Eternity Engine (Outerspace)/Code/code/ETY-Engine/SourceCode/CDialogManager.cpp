///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGMANAGER.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////

#include "CLua.hpp"

#include "CDialogManager.hpp"
#include "CDialogitem.hpp"
#include "CGameState.hpp"
#include "CGameStateManager.hpp"
#include "CGamesettings.hpp"

#include "CComboBox.hpp"
#include "CEditControl.hpp"
#include "CScrollbar.hpp"

#include <iostream>



																				ety::CDialogManager::CDialogManager						( void )
																				: m_bModalDialog										( false )
																				, mp_c_etyDialogitemFocusedDialogitem					( NULL )
																				,mp_c_etyGameStateParentState							( NULL )
																				,mp_c_etyGamesettingsManager							( NULL )
																				,mp_c_etyDialogitemMouseEvent							( NULL )
																				,mp_c_etyDialogModal									( NULL )
																				,mp_c_etyDialogitemDoubleClickEvent						( NULL )
																				,mp_c_etyDialogitemMouseNoFocusRelease					( NULL )
																				,m_sfUint32ElapsedFrameTime								( 0 )
																				,mp_c_sfTextureStandardTooltip							( NULL )
{
}


																				ety::CDialogManager::~CDialogManager					( void )
{
	m_listDialogs.clear();
}


																				ety::CDialogManager::CDialogManager						(ety::CGameState* const p_c_etyGameStateParentState)
																				: m_bModalDialog										( false )
																				, mp_c_etyDialogitemFocusedDialogitem					( NULL )
																				,mp_c_etyDialogitemMouseEvent							( NULL )
																				,mp_c_etyGameStateParentState							( p_c_etyGameStateParentState )
																				,mp_c_etyGamesettingsManager							( NULL )
																				,mp_c_etyDialogModal									( NULL )
																				,mp_c_etyDialogitemDoubleClickEvent						( NULL )
																				,mp_c_etyDialogitemMouseNoFocusRelease					( NULL )
																				,mp_c_sfTextureStandardTooltip							( NULL )
																				,m_sfUint32ElapsedFrameTime								( 0 )
{
}


		//..........
const	bool																	ety::CDialogManager::add_Dialog							( ety::CDialog* const p_c_etyDialogNewDialog )
{
	//Gleiches Prinzip wie bei den Dialogitems (Zur genauen Info siehe Dialog.cpp/add_Dialogitem
	//Sollte nur die DrawPosition oder die Affinity geändert worden sein, muss darauf geachtet werden, dass der Dialog nicht doppelt in die Liste geschrieben wird!
	

	//An dieser Stelle wird der Dialog herausgefiltert und aus der Liste entfernt, damit es beim erneuten Einfügen nicht doppelt in der Liste steht
	for(std::list<CDialog*>::iterator itDialogs = m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++)
	{
		if( (*itDialogs) == p_c_etyDialogNewDialog )
		{
			m_listDialogs.erase( itDialogs );
			break;
		}
	}


	//Bei einer leeren Liste kann der Dialog sofort eingefügt werden
	if( m_listDialogs.empty() == true )
	{
		m_listDialogs.push_front( p_c_etyDialogNewDialog );

		if( p_c_etyDialogNewDialog->get_DialogManager() != this )
		{
			p_c_etyDialogNewDialog->set_Dialogmanager(this);
		}

		return true;
	}

	//Einfügen in den Backgroundbereich
	if(p_c_etyDialogNewDialog->get_Affinity() == Affinity::enBACKGROUND)
	{
		std::list<CDialog*>::iterator itDialogs = m_listDialogs.begin();

		for(itDialogs ; itDialogs != m_listDialogs.end() ; itDialogs++)
		{
			if((*itDialogs)->get_Affinity() == Affinity::enBACKGROUND && (*itDialogs)->get_DrawPosition() >= p_c_etyDialogNewDialog->get_DrawPosition())
			{
				m_listDialogs.insert(itDialogs, p_c_etyDialogNewDialog);

				if( p_c_etyDialogNewDialog->get_DialogManager() != this )
				{
					p_c_etyDialogNewDialog->set_Dialogmanager(this);
				}

				return true;
			}
			else if((*itDialogs)->get_Affinity() != Affinity::enBACKGROUND)
			{
				m_listDialogs.insert(itDialogs, p_c_etyDialogNewDialog);

				if( p_c_etyDialogNewDialog->get_DialogManager() != this )
				{
					p_c_etyDialogNewDialog->set_Dialogmanager(this);
				}

				return true;
			}
		}

		m_listDialogs.push_back(p_c_etyDialogNewDialog);
		return true;
	}
	//Einfügen in den Foregroundbereich
	else if(p_c_etyDialogNewDialog->get_Affinity() == Affinity::enFOREGROUND)
	{
		std::list<CDialog*>::iterator itDialogs = m_listDialogs.end();

		while(1)
		{
			itDialogs--;

			if((*itDialogs)->get_Affinity() == Affinity::enFOREGROUND && (*itDialogs)->get_DrawPosition() > p_c_etyDialogNewDialog->get_DrawPosition())
			{
				itDialogs++;
				if(itDialogs != m_listDialogs.end())
				{
					m_listDialogs.insert( itDialogs, p_c_etyDialogNewDialog );

					if( p_c_etyDialogNewDialog->get_DialogManager() != this )
					{
						p_c_etyDialogNewDialog->set_Dialogmanager(this);
					}

					return true;
				}
				else
				{
					m_listDialogs.push_back(p_c_etyDialogNewDialog);

					if( p_c_etyDialogNewDialog->get_DialogManager() != this )
					{
						p_c_etyDialogNewDialog->set_Dialogmanager(this);
					}

					return true;
				}		
			}
			else if((*itDialogs)->get_Affinity() != Affinity::enFOREGROUND)
			{
				itDialogs++;
				if(itDialogs != m_listDialogs.end())
				{
					m_listDialogs.insert( itDialogs, p_c_etyDialogNewDialog );
					if( p_c_etyDialogNewDialog->get_DialogManager() != this )
					{
						p_c_etyDialogNewDialog->set_Dialogmanager(this);
					}
					return true;
				}
				else
				{
					m_listDialogs.push_back(p_c_etyDialogNewDialog);
					if( p_c_etyDialogNewDialog->get_DialogManager() != this )
					{
						p_c_etyDialogNewDialog->set_Dialogmanager(this);
					}
					return true;
				}
			}

			if(itDialogs == m_listDialogs.begin())
			{
				m_listDialogs.push_front(p_c_etyDialogNewDialog);
				if( p_c_etyDialogNewDialog->get_DialogManager() != this )
				{
					p_c_etyDialogNewDialog->set_Dialogmanager(this);
				}
				return true;
			}
		}
	}
	//Einfügen in den Standardbereich
	else if(p_c_etyDialogNewDialog->get_Affinity() == Affinity::enSTANDARD)
	{
		std::list<CDialog*>::iterator itDialogs = m_listDialogs.begin();

		while((*itDialogs)->get_Affinity() == Affinity::enBACKGROUND)
		{
			itDialogs++;
			if(itDialogs == m_listDialogs.end())
			{
				m_listDialogs.push_back(p_c_etyDialogNewDialog);
				if( p_c_etyDialogNewDialog->get_DialogManager() != this )
				{
					p_c_etyDialogNewDialog->set_Dialogmanager(this);
				}
				return true;
			}
		}

		while((*itDialogs)->get_DrawPosition() < p_c_etyDialogNewDialog->get_DrawPosition() && (*itDialogs)->get_Affinity() != Affinity::enFOREGROUND)
		{
			itDialogs++;
			if(itDialogs == m_listDialogs.end())
			{
				m_listDialogs.push_back(p_c_etyDialogNewDialog);
				if( p_c_etyDialogNewDialog->get_DialogManager() != this )
				{
					p_c_etyDialogNewDialog->set_Dialogmanager(this);
				}
				return true;
			}
		}

		m_listDialogs.insert(itDialogs, p_c_etyDialogNewDialog);
		if( p_c_etyDialogNewDialog->get_DialogManager() != this )
		{
			p_c_etyDialogNewDialog->set_Dialogmanager(this);
		}
		return true;
	}

	return false;

}		
		//..........

		void																	ety::CDialogManager::change_FocusedDialogitem			( ety::CDialogitem* const p_c_etyDialogitemNewFocusedDialogitem)
{
	if(mp_c_etyDialogitemFocusedDialogitem != NULL && mp_c_etyDialogitemFocusedDialogitem != p_c_etyDialogitemNewFocusedDialogitem)
	{
		CDialogitem* mp_c_etyDialogitemOldFocusedDialogitem = mp_c_etyDialogitemFocusedDialogitem;
		mp_c_etyDialogitemFocusedDialogitem					=	p_c_etyDialogitemNewFocusedDialogitem;

		mp_c_etyDialogitemOldFocusedDialogitem->reset_FocusedDialogitem();
	}
	else 
	{
		mp_c_etyDialogitemFocusedDialogitem					=	p_c_etyDialogitemNewFocusedDialogitem;
	}
}
		//..........
		void																	ety::CDialogManager::change_ModalDialog					( bool bDialogModal, CDialog* p_c_etyDialogModalDialog, sf::Vector3f c_sfVector3fFactors )
{
	m_bModalDialog	=	false;

	for(std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++)
	{
		if((*itDialogs) != p_c_etyDialogModalDialog)
		{
			(*itDialogs)->reset_Modal();
			(*itDialogs)->modificate_ColorFilter(c_sfVector3fFactors);
		}
		else if(bDialogModal == true)
		{
			m_bModalDialog = true;
			mp_c_etyDialogModal = p_c_etyDialogModalDialog;
		}
	}
}
		//..........
		bool																	ety::CDialogManager::check_IsDialogitemActive			( CDialogitem* const p_c_etyDialogitem )
{
	if(p_c_etyDialogitem->get_ParentDialog()->get_Modal() == true  && p_c_etyDialogitem->get_ParentDialog()->get_Visibility() == true 
		&& mp_c_etyGameStateParentState->get_GameStateStatus() == ety::GamestateStatus::enACTIVE
		|| m_bModalDialog == false && p_c_etyDialogitem->get_ParentDialog()->get_Visibility() == true 
		&& mp_c_etyGameStateParentState->get_GameStateStatus() == ety::GamestateStatus::enACTIVE)
	{
		return true;
	}

	return false;
}
		//..........
		void																	ety::CDialogManager::cleanup_Dialogs					( void )
{
	m_listDialogs.clear();
}


		const bool																ety::CDialogManager::delete_Dialog						( ety::CDialog* const p_c_etyDialog )
		{
			for(std::list<CDialog*>::iterator itDialogs = m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++)
			{
				if( (*itDialogs) == p_c_etyDialog )
				{
					m_listDialogs.erase( itDialogs );
					return true;
				}
			}

			return false;
		}
		void																	ety::CDialogManager::draw_Dialogs						( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
{
	std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin();

	//Diese Schleife zeichnet alle Dialoge des States in das RenderTexture
	for( itDialogs; itDialogs != m_listDialogs.end(); itDialogs++)
	{
		if((*itDialogs)->get_Visibility() == true)
		{
			//Zeichnen des Dialoghintergrundes
			p_c_sfRenderTextureGameScene->draw((*itDialogs)->get_BackgroundSprite());
			//und seiner Dialogitems
			(*itDialogs)->draw_Dialogitems(p_c_sfRenderTextureGameScene);
		}
	}
}

		void																	ety::CDialogManager::handle_Events						( sf::Event& c_sfEvent )
{
	if(c_sfEvent.type == sf::Event::MouseWheelMoved)
	{
		if(mp_c_etyDialogitemFocusedDialogitem != NULL)
		{
			if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enCOMBOBOX)
			{
				CComboBox* p_c_etyComboBoxTmp = dynamic_cast<CComboBox*>(mp_c_etyDialogitemFocusedDialogitem);
				if(p_c_etyComboBoxTmp->get_Unfolded() == true && p_c_etyComboBoxTmp->get_Scrollbar() != NULL)
				{
					if(p_c_etyComboBoxTmp->get_Scrollbar()->get_Active() == true)
					{
						p_c_etyComboBoxTmp->get_Scrollbar()->set_CurrentBlock(p_c_etyComboBoxTmp->get_Scrollbar()->get_CurrentBlock() - c_sfEvent.mouseWheel.delta);
					}	
				}				
			}
			else if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enLISTBOX)
			{
				CComboBox* p_c_etyComboBoxTmp = dynamic_cast<CComboBox*>(mp_c_etyDialogitemFocusedDialogitem);

				if(p_c_etyComboBoxTmp->get_Scrollbar() != NULL)
				{
					if(p_c_etyComboBoxTmp->get_Scrollbar()->get_Active() == true)
					{
						p_c_etyComboBoxTmp->get_Scrollbar()->set_CurrentBlock(p_c_etyComboBoxTmp->get_Scrollbar()->get_CurrentBlock() - c_sfEvent.mouseWheel.delta);
					}
				}	
			}
			else 
			{
				CDialogitem* p_c_etyDialogitemTmp = dynamic_cast<CDialogitem*>(mp_c_etyDialogitemFocusedDialogitem);
				if(p_c_etyDialogitemTmp->get_DialogitemType() == DialogitemType::enBUTTON && p_c_etyDialogitemTmp->get_AttachedType() == AttachedType::enCHILDREN 
					&& p_c_etyDialogitemTmp->get_ParentDialogitem()->get_DialogitemType() == DialogitemType::enSCROLLBAR 
					&& p_c_etyDialogitemTmp->get_ParentDialogitem()->get_Active() == true)
				{
					CComboBox* p_c_etyComboBoxTmp = dynamic_cast<CComboBox*>(p_c_etyDialogitemTmp->get_ParentDialogitem()->get_ParentDialogitem());
					p_c_etyComboBoxTmp->get_Scrollbar()->set_CurrentBlock(p_c_etyComboBoxTmp->get_Scrollbar()->get_CurrentBlock() - c_sfEvent.mouseWheel.delta);
				}
				else if(p_c_etyDialogitemTmp->get_DialogitemType() == DialogitemType::enBUTTON && p_c_etyDialogitemTmp->get_AttachedType() == AttachedType::enCHILDREN 
					&& p_c_etyDialogitemTmp->get_ParentDialogitem()->get_DialogitemType() == DialogitemType::enLISTBOX)
				{
					CComboBox* p_c_etyComboBoxTmp = dynamic_cast<CComboBox*>(p_c_etyDialogitemTmp->get_ParentDialogitem());
					if(p_c_etyComboBoxTmp->get_Scrollbar() != NULL)
					{
						if(p_c_etyComboBoxTmp->get_Scrollbar()->get_Active() == true)
						{
							p_c_etyComboBoxTmp->get_Scrollbar()->set_CurrentBlock(p_c_etyComboBoxTmp->get_Scrollbar()->get_CurrentBlock() - c_sfEvent.mouseWheel.delta);
						}
					}
				}
			}
		}
	}
	else if(c_sfEvent.type == sf::Event::TextEntered)
	{
		if(mp_c_etyDialogitemFocusedDialogitem != NULL)
		{
			if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enEDITCONTROL)
			{
				//Bei Texteingaben wird das Event sofort an das entsprechende EditControl, sofern vorhanden, weiter geleitet
				CEditControl* p_c_etyEditControlTmpPointer = static_cast < CEditControl* > (mp_c_etyDialogitemFocusedDialogitem);
				p_c_etyEditControlTmpPointer->handle_InputEvents(c_sfEvent);
			}
		}
	}
	else if(c_sfEvent.type == sf::Event::KeyPressed)
	{
		if(c_sfEvent.key.code == sf::Keyboard::Delete || c_sfEvent.key.code == sf::Keyboard::Left || c_sfEvent.key.code == sf::Keyboard::Right)
		{
			//Beim Drücken gewisser Tasten wird das Event auch sofort an das entsprechende EditControl weitergeleitet
			if(mp_c_etyDialogitemFocusedDialogitem != NULL)
			{
				if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enEDITCONTROL)
				{
					CEditControl* p_c_etyEditControlTmpPointer = static_cast < CEditControl* > (mp_c_etyDialogitemFocusedDialogitem);
					p_c_etyEditControlTmpPointer->handle_InputEvents(c_sfEvent);
				}
			}
		}
	}
	else if(c_sfEvent.type == sf::Event::KeyReleased)
	{
		if(c_sfEvent.key.code == sf::Keyboard::Home || c_sfEvent.key.code == sf::Keyboard::End)
		{
			//Das Gleiche gilt auch für das Loslassen mancher Tasten
			if(mp_c_etyDialogitemFocusedDialogitem != NULL)
			{
				if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enEDITCONTROL)
				{
					CEditControl* p_c_etyEditControlTmpPointer = static_cast < CEditControl* > (mp_c_etyDialogitemFocusedDialogitem);
					p_c_etyEditControlTmpPointer->handle_InputEvents(c_sfEvent);
				}
			}
		}
		else if(c_sfEvent.key.code == sf::Keyboard::Escape)
		{
			//Beim Drücken der Escape-Taste wird einfach das aktuell gefocuste EditControl abgewählt
			if(mp_c_etyDialogitemFocusedDialogitem != NULL)
			{
				if(mp_c_etyDialogitemFocusedDialogitem->get_DialogitemType() == DialogitemType::enEDITCONTROL)
				{
					change_FocusedDialogitem(NULL);
				}
			}
		}
	}
	else if(c_sfEvent.type == sf::Event::MouseButtonPressed)
	{
		if(mp_c_etyDialogitemMouseEvent != NULL)
		{
			mp_c_etyDialogitemMouseEvent->set_Focus(true);

			if(mp_c_etyDialogitemMouseEvent->get_DialogitemType() == DialogitemType::enSLIDECONTROL)
			{
				mp_c_etyDialogitemMouseNoFocusRelease = mp_c_etyDialogitemMouseEvent;
			}
			else if(mp_c_etyDialogitemMouseEvent->get_DialogitemType() == DialogitemType::enBUTTON && mp_c_etyDialogitemMouseEvent->get_ParentDialogitem() != NULL &&
				mp_c_etyDialogitemMouseEvent->get_AttachedType() == AttachedType::enCHILDREN)
			{
				if(mp_c_etyDialogitemMouseEvent->get_ParentDialogitem()->get_DialogitemType() == DialogitemType::enSCROLLBAR)
				{
					mp_c_etyDialogitemMouseNoFocusRelease = mp_c_etyDialogitemMouseEvent;
				}
			}
		}
	}
	else if(c_sfEvent.type == sf::Event::MouseButtonReleased)
	{
		if(mp_c_etyDialogitemDoubleClickEvent == mp_c_etyDialogitemMouseEvent)
		{
			m_sfUint32ElapsedFrameTime = 0;
			c_sfEvent.type = sf::Event::MouseButtonDoubleClick;
		}

		mp_c_etyDialogitemDoubleClickEvent = mp_c_etyDialogitemMouseEvent;
		
		if(mp_c_etyDialogitemMouseNoFocusRelease != NULL)
		{
			c_sfEvent.type = sf::Event::MouseButtonNoFocusReleased;

			mp_c_etyDialogitemMouseNoFocusRelease->handle_InternEvents(c_sfEvent);
			mp_c_etyDialogitemMouseNoFocusRelease = NULL;

			return ;
		}	
	}

	if(mp_c_etyDialogitemMouseEvent != NULL)
	{
		mp_c_etyDialogitemMouseEvent->handle_InternEvents(c_sfEvent);
	}
}

		void																	ety::CDialogManager::reinit_Dialogs						( const sf::VideoMode& c_sfNewVideoMode )
{
	for( std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++ )
	{
		(*itDialogs)->adjust_SizeToResolution( c_sfNewVideoMode );
	}
}

		void																	ety::CDialogManager::update_Dialogs						( const sf::Uint32& uiFrameTime )
{
	if(mp_c_etyDialogitemDoubleClickEvent != NULL && m_sfUint32ElapsedFrameTime < 500)
	{
		m_sfUint32ElapsedFrameTime += uiFrameTime;
	}
	else
	{
		m_sfUint32ElapsedFrameTime = 0;
		mp_c_etyDialogitemDoubleClickEvent = NULL;
	}


	mp_c_etyDialogitemMouseEvent = NULL;
	CDialogitem* p_c_etyDialogitemTmp = NULL;

	for( std::list<ety::CDialog*>::iterator itDialogs =	m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++)
	{
		p_c_etyDialogitemTmp = (*itDialogs)->update_Dialog( uiFrameTime );
		if(p_c_etyDialogitemTmp != NULL)
		{
			mp_c_etyDialogitemMouseEvent = p_c_etyDialogitemTmp;
		}
	}
}

		void																	ety::CDialogManager::update_Language					( const std::string strNewLanguage, CLua* const mp_c_etyLuaScript )
{
	for( std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin(); itDialogs != m_listDialogs.end(); itDialogs++ )
	{
		(*itDialogs)->update_Language( strNewLanguage, mp_c_etyLuaScript );
	}
}


		void																	ety::CDialogManager::set_ModalDialog					( bool bModalDialog )
{
	m_bModalDialog	=	bModalDialog;
}
		void																	ety::CDialogManager::set_StandardFont					( const sf::Font& c_sfFontStandardFont )
{
	m_c_sfFontStandardFont	= c_sfFontStandardFont;
}
		void																	ety::CDialogManager::set_StandardTooltipTexture			( const	sf::Texture& c_sfTextureStandardTooltip, sf::IntRect c_sfIntRectStandardSubRect )
{
	mp_c_sfTextureStandardTooltip		=	&c_sfTextureStandardTooltip;
	m_c_sfIntRectTooltipStandardSubRect	=	c_sfIntRectStandardSubRect;
}
		void																	ety::CDialogManager::set_GamesettingsManager			( ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
{
	mp_c_etyGamesettingsManager = p_c_etyCurrentGamesettingManager;
}
		void																	ety::CDialogManager::set_ElapsedFrameTime				( const sf::Uint32& uiFrameTime )
{
	m_sfUint32ElapsedFrameTime = uiFrameTime;
}

const	bool																	ety::CDialogManager::get_ModalDialog					( void )
{
	return m_bModalDialog;
}
		std::list<ety::CDialog*>												ety::CDialogManager::get_Dialogs						( void )
{
	std::list<CDialog*> listAllDialogs;

	for( std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin() ; itDialogs != m_listDialogs.end() ; itDialogs++)
	{
		listAllDialogs.push_back((*itDialogs));
	}

	return listAllDialogs;
}
const	std::string																ety::CDialogManager::get_Language						( void )
{
	if(mp_c_etyGamesettingsManager == NULL)
	{
		return "NULL";
	}

	return mp_c_etyGamesettingsManager->get_Language();
}
const	sf::Font&																ety::CDialogManager::get_StandardFont					( void )
{
	return m_c_sfFontStandardFont;
}
const	sf::Texture*															ety::CDialogManager::get_StandardTooltipTexture			( void )
{
	return mp_c_sfTextureStandardTooltip;
}
const	sf::IntRect&															ety::CDialogManager::get_StandardTooltipSubRect			( void )
{
	return m_c_sfIntRectTooltipStandardSubRect;
}
		ety::CDialog*												 const		ety::CDialogManager::get_DialogbyCustomID				( std::string strCustomID )
{
	for(std::list<ety::CDialog*>::iterator itDialogs = m_listDialogs.begin() ; itDialogs != m_listDialogs.end() ; itDialogs++)
	{
		if((*itDialogs)->get_DialogID() == strCustomID)
		{
			return (*itDialogs);
		}
	}

	return NULL;
}
		ety::CDialogitem*											 const		ety::CDialogManager::get_MouseEventDialogitem			( void )
{
	return mp_c_etyDialogitemMouseEvent;
}
		ety::CDialogitem*											 const		ety::CDialogManager::get_MouseNoFocusEventDialogitem	( void )
{
	return mp_c_etyDialogitemMouseNoFocusRelease;
}
		ety::CDialogitem*											 const		ety::CDialogManager::get_FocusedDialogitem				( void )
{
			return mp_c_etyDialogitemFocusedDialogitem;
}
		ety::CGameState*											 const		ety::CDialogManager::get_ParentGameState				( void )
{
	return mp_c_etyGameStateParentState;
}
		ety::CLua*													 const		ety::CDialogManager::get_LuaScript						( void )
{
	return mp_c_etyGameStateParentState->get_GameStatemanager()->get_LuaScript();
}
const	ety::mapSoundTypeSounds													ety::CDialogManager::get_StandardSounds					( DialogitemType::en_etyDialogitemType en_etyDialogitemType )
{
	return	mp_c_etyGameStateParentState->get_GameStatemanager()->get_Filemanagement()->get_StandardSounds( mp_c_etyGameStateParentState->get_GameStateName(), en_etyDialogitemType );
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////								CDIALOGMANAGER.CPP							///////////
///////////////////////////////////////////////////////////////////////////////////////////////