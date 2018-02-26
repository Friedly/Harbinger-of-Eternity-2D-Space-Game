#include "CLoadingState.hpp"

#include "CFilemanagement.hpp"
#include "CGameStateManager.hpp"
#include "CLabel.hpp"
#include "CMouse.hpp"


															ety::CLoadingState::CLoadingState				( const std::string& strGameStateName, ety::CFilemanagement* const p_c_etyFilemanagement )
																: CDialogGameState						( strGameStateName )
																, m_c_sfLoadingThread					( &ety::CLoadingState::load_RessourcesThread, this )
																, m_bStartLoadingThread				( true )
																, mp_c_etyCurrentFilemanagement	( p_c_etyFilemanagement )
		{
		}

															ety::CLoadingState::~CLoadingState				( void )
		{
		}

		void												ety::CLoadingState::on_Enter					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}
		void												ety::CLoadingState::on_Exit						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
		}

		void												ety::CLoadingState::init_GameState				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager )
		{
			CLua* const p_c_etyLuaScript = get_GameStatemanager()->get_LuaScript();

			p_c_etyLuaScript->init_Lua();

			if( p_c_etyLuaScript->start_Script("Initialisation/Gamestates/Language.lua") == false )
			{
			}

			mp_c_etyCurrentFilemanagement->load_Ressources( m_strGameStateName, p_c_etyCurrentRessourceManager );

			mp_c_etyCurrentRessourceManager		= p_c_etyCurrentRessourceManager;
			mp_c_etyCurrentGamesettings			= p_c_etyCurrentGamesettingManager;

			//Festlegen der Font
			sf::Font sfFontStandardFont = p_c_etyCurrentRessourceManager->get_Font("Standard.ttf");
			mp_c_etyDialogManager->set_StandardFont(sfFontStandardFont);

			ety::CMouse::set_CustomCursorSprite( p_c_etyCurrentRessourceManager->get_Texture( "Cursor.png" ), false );

			//Background
			ety::CDialog* p_c_etyDialogBackground = new CDialog(
				"LoadingStateBackground", p_c_etyCurrentRessourceManager->get_Texture( "LoadingScreen.jpg" ), 1680.f, 1050.f, sf::Vector2f( 0.f, 0.f ), 
				sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(1920, 1200)), mp_c_etyDialogManager, p_c_etyCurrentGamesettingManager->get_Videomode()
				);

			mp_c_etyDialogManager->add_Dialog( p_c_etyDialogBackground );

			//Progressbar
			unsigned int uiRessourceCount = 0;
			unsigned int test = 0;

			for( std::vector<std::string>::iterator itGamestateToLoad = m_vecGamestatesToLoad.begin(); itGamestateToLoad != m_vecGamestatesToLoad.end(); itGamestateToLoad++ )
			{
				uiRessourceCount += mp_c_etyCurrentFilemanagement->get_RessourceCount( *itGamestateToLoad );
				uiRessourceCount += 2;
				test++;
			}

			m_c_etyProgressbar.init_Progressbar			(	p_c_etyCurrentRessourceManager->get_Texture( "IronProgressbar.png" )
														  , uiRessourceCount
														  , p_c_etyCurrentGamesettingManager->get_Videomode()						);

			m_c_etyProgressbar.set_ProgressbarPosition	(   sf::Vector2f( float(p_c_etyCurrentGamesettingManager->get_Videomode().width)/2.f, ( float( p_c_etyCurrentGamesettingManager->get_Videomode().height )/6.f )*5.f ) );

			p_c_etyLuaScript->close_Lua();
		}

		void												ety::CLoadingState::update_GameState			( const sf::Uint32& uiFrameTime )
		{
			CDialogGameState::update_GameState( uiFrameTime );

			if( m_bStartLoadingThread == true )
			{
				m_c_sfLoadingThread.launch();
				m_bStartLoadingThread = false;
			}

			m_c_etyProgressbar.update_Progressbar();
		}

		void												ety::CLoadingState::render_GameState			( sf::RenderTexture* const p_c_sfRenderTextureGameScene )
		{
			CDialogGameState::render_GameState( p_c_sfRenderTextureGameScene );

			m_c_etyProgressbar.render_Progressbar( p_c_sfRenderTextureGameScene );
		}

const	ety::GameStateRunning::en_etyGameStateRunning		ety::CLoadingState::handle_GameStateEvents		( const sf::Event& sfEventLastEvent  )
		{
			if( sfEventLastEvent.type == sf::Event::Closed  )
			{
				m_c_sfLoadingThread.wait();

				return ety::GameStateRunning::enFALSE;
			}

			if( m_c_etyProgressbar.get_Finished() == true )
			{
				m_c_sfLoadingThread.wait();

				m_bStartLoadingThread = true;

				m_c_etyProgressbar.reset_Progressbar();

				mp_c_etyGameStatemanager->popback_GameState();

				return ety::GameStateRunning::enFALSE;
			}

			return ety::GameStateRunning::enTRUE;
		}

		void												ety::CLoadingState::load_RessourcesThread		( void )
		{
			mp_c_etyCurrentFilemanagement->load_Ressources( &m_vecGamestatesToLoad, mp_c_etyCurrentRessourceManager, &m_c_etyProgressbar );

			for( std::vector<std::string>::iterator itGamestateToLoad = m_vecGamestatesToLoad.begin(); itGamestateToLoad != m_vecGamestatesToLoad.end(); itGamestateToLoad++ )
			{
				mp_c_etyCurrentFilemanagement->assign_StandardSounds( (*itGamestateToLoad), mp_c_etyCurrentRessourceManager );

				m_c_etyProgressbar.add_Progress();

				mp_c_etyGameStatemanager->get_GamestateByGamestateName<CGameState>((*itGamestateToLoad))->CGameState::init_GameState( mp_c_etyCurrentRessourceManager, mp_c_etyCurrentGamesettings );
				mp_c_etyGameStatemanager->get_GamestateByGamestateName<CGameState>((*itGamestateToLoad))->init_GameState			( mp_c_etyCurrentRessourceManager, mp_c_etyCurrentGamesettings );
				
				m_c_etyProgressbar.add_Progress();
			}
		}

		void												ety::CLoadingState::add_GamestateToLoad			( const std::string& strGamestateToLoad )
		{
			m_vecGamestatesToLoad.push_back( strGamestateToLoad );
		}