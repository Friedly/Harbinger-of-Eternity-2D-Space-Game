#include "CIngameState.hpp"
#include "CGameStateManager.hpp"
#include "CUserInterface.hpp"
#include "CCameraComponent.hpp"
#include "CWorld.hpp"

#include "CDialogitem.hpp"
#include "CButton.hpp"

#include <string>
#include "CProfile.hpp"
#include "CShield.hpp"

															ety::CIngameState::CIngameState					( const std::string& strStateName )
															: CDialogGameState		( strStateName )
															, m_bGamePaused			( false )
															, mp_c_etyUserInterface	( NULL )
															{
															}
															ety::CIngameState::~CIngameState				( void )
															{
																/*if(mp_c_etyUserInterface != NULL)
																{
																	delete mp_c_etyUserInterface;
																	mp_c_etyUserInterface = NULL;
																}*/
															}

		void												ety::CIngameState::on_Enter						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			ety::CMouse::set_CustomCursorSprite( p_c_etyCurrentRessourceManager->get_Texture( "Crosshair.png" ),true );

			gp_c_etyWorld->set_ItemManagement	( get_GameStatemanager()->m_c_etyAttributes.get_Attribute<ety::CItemManagement>("p_c_etyCurrentItemManagement") )
						 ->set_Gamesettings		( p_c_etyCurrentGamesettingManager )
						 ->set_RessourceManager	( p_c_etyCurrentRessourceManager );

			gp_c_etyWorld->load_World( *get_GameStatemanager()->m_c_etyAttributes.get_Attribute<ety::CETYProfile>("p_c_etyCurrentProfile")->m_c_etyAttributes.get_Attribute<std::string>("strCurrentWorld") , "Initialisation/Worlds/" );

			CLua* const p_c_etyLuaScript = get_GameStatemanager()->get_LuaScript();

			p_c_etyLuaScript->init_Lua();

			ety::CWorld::register_ClassToLuabind( p_c_etyLuaScript );

							luabind::globals( p_c_etyLuaScript->get_LuaState() )["c_etyWorld"]	= gp_c_etyWorld;
				luabind::globals( p_c_etyLuaScript->get_LuaState() )["c_etyEntitymanager"]		= gp_c_etyWorld->get_Entitymanager();

			p_c_etyLuaScript->start_Script( "Initialisation/Worlds/" + gp_c_etyWorld->get_Name() + ".lua" );

			p_c_etyLuaScript->close_Lua();

			if(mp_c_etyUserInterface == NULL)
			{
				mp_c_etyUserInterface	=	new CUserInterface(this);
				mp_c_etyUserInterface->init_UserInterface(p_c_etyCurrentRessourceManager, p_c_etyCurrentGamesettingManager);
				mp_c_etyUserInterface->update_UserInterface(0);
				//ShieldTest
				static_cast<CShield*>(gp_c_etyWorld->get_Entitymanager()->get_Entity("Player")->get_Component<CItemModulesComponent>("ItemModulesComponent")->get_EquipmentFromModule(ModuleType::enSHIELD))->set_CurrentAbsorbedDamage(0.f);
			}
		}
		void												ety::CIngameState::on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			ety::CMouse::set_CustomCursorSprite( p_c_etyCurrentRessourceManager->get_Texture( "Cursor.png" ), false );

			gp_c_etyWorld->delete_Singleton();

			if(mp_c_etyUserInterface != NULL)
			{
				delete mp_c_etyUserInterface;
				mp_c_etyUserInterface = NULL;
			}
		}

		void												ety::CIngameState::init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			
		}

		void												ety::CIngameState::update_GameState				( const sf::Uint32& uiFrameTime )
		{
			if(m_bGamePaused == false)
			{
				gp_c_etyWorld->update_World( uiFrameTime );
			}
			if(mp_c_etyUserInterface != NULL)
			{
				//Nur Shield und Armor test
				CShield* p_c_etyShield	=	static_cast<CShield*>(gp_c_etyWorld->get_Entitymanager()->get_Entity("Player")->get_Component<CItemModulesComponent>("ItemModulesComponent")->get_EquipmentFromModule(ModuleType::enSHIELD));
				if(p_c_etyShield->get_ShieldStatus() == 0)
				{
					float value	=	float(*gp_c_etyWorld->get_Entitymanager()->get_Entity("Player")->get_Component<CAttributeComponent>("AttributeComponent")->m_c_etyAttributes.get_Attribute<unsigned int>("uiStructureStability"));

					if(value >= 1)
					{
						value--;
						gp_c_etyWorld->get_Entitymanager()->get_Entity("Player")->get_Component<CAttributeComponent>("AttributeComponent")->m_c_etyAttributes.change_Attribute<unsigned int>("uiStructureStability", unsigned int(value));
					}
				}
				else
				{
					p_c_etyShield->set_CurrentAbsorbedDamage(p_c_etyShield->get_CurrentAbsorbedDamage() + 0.25f);
				}
				
				mp_c_etyUserInterface->update_UserInterface(uiFrameTime);
			}

			CDialogGameState::update_GameState( uiFrameTime );
		}

		void												ety::CIngameState::render_GameState				( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			gp_c_etyWorld->render_World( p_c_sfRenderTextureGameScene );

			CDialogGameState::render_GameState( p_c_sfRenderTextureGameScene );
		}

		void												ety::CIngameState::set_GamePaused				( const bool& bGamePaused )
		{
			m_bGamePaused	=	bGamePaused;
		}

		ety::CUserInterface* const							ety::CIngameState::get_UserInterface			( void )
		{
			return mp_c_etyUserInterface;
		}


const	ety::GameStateRunning::en_etyGameStateRunning		ety::CIngameState::handle_GameStateEvents		( const sf::Event& sfEventLastEvent  )
		{
			CDialogitem* p_c_etyDialogitemEvent = mp_c_etyDialogManager->get_MouseEventDialogitem();

			//Kollisions-Kreise anzeigen
			if( sfEventLastEvent.type == sf::Event::KeyReleased && sfEventLastEvent.key.code == sf::Keyboard::F2 )
			{
				gp_c_etyWorld->set_CollisionRenderStatus( !gp_c_etyWorld->get_CollisionRenderStatus() );
			}

			if(sfEventLastEvent.type == sf::Event::KeyReleased)
			{
				if(sfEventLastEvent.key.code == sf::Keyboard::Escape)
				{
					if(m_bGamePaused == false)
					{
						//IngameMenu anzeigen und Spiel pausieren
						m_bGamePaused = true;
						mp_c_etyUserInterface->event_openIngameMenu(1, mp_c_etyDialogManager);
					}
					else
					{
						//IngameMenu schließen und Spiel fortsetzen
						m_bGamePaused = false;
						mp_c_etyUserInterface->event_closeIngameMenu(1, mp_c_etyDialogManager);
					}
				}
			}
			
			sf::Event c_sfEvent = sfEventLastEvent;
			mp_c_etyDialogManager->handle_Events(c_sfEvent);
	
			if(p_c_etyDialogitemEvent != NULL)
			{
				p_Function p_FunctionEvent = get_EventFunction(p_c_etyDialogitemEvent->get_CustomID(), c_sfEvent);

				if(p_FunctionEvent != NULL)
				{
					std::string strCustomID = p_c_etyDialogitemEvent->get_CustomID();

					return p_FunctionEvent(2, mp_c_etyDialogManager, new std::string(strCustomID));
				}
			}

			return ety::GameStateRunning::enTRUE;
		}

		ety::GameStateRunning::en_etyGameStateRunning		ety::CIngameState::event_exitIngame				( int iAmount, ... )
		{
			va_ArgumentList va_ALParameter;
			va_OpenArgumentList(va_ALParameter, iAmount);

			CDialogManager* p_c_etyDialogManager	=	static_cast<CDialogManager*>(va_getArgument(va_ALParameter, void*));  
			CIngameState*	p_c_etyIngameState		=	static_cast<CIngameState*>(p_c_etyDialogManager->get_ParentGameState());
			va_CloseArgumentList(va_ALParameter);

			ety::CButton* p_c_etyButtonEventButton	=	static_cast< ety::CButton* >(p_c_etyDialogManager->get_MouseEventDialogitem());

			if( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK) != NULL)
			{
				while( p_c_etyButtonEventButton->get_EventSound(ety::SoundType::enCLICK)->getStatus() == sf::Sound::Playing )
				{
				}
			}

			//Ingame verlassen und in den Hangar zurückkehren
			p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->pushback_GameState( "SpaceStationState" );
			p_c_etyDialogManager->get_ParentGameState()->get_GameStatemanager()->pushback_GameState( "SpaceStationHangarState", ety::GamestateStatus::enBACKGROUND );

			p_c_etyIngameState->set_GamePaused(false);

			return ety::GameStateRunning::enFALSE;
		}

