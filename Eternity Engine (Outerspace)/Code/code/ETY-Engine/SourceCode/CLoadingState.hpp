#pragma once
#pragma warning( disable : 4355 )

#include "CDialogGameState.hpp"

#include <vector>

#include <SFML\System\Thread.hpp>
#include <SFML\System\Mutex.hpp>

namespace ety
{
	class CProgressbar
	{
	private:
					bool			m_bFinished;

					float			m_fBarGrow;

					sf::Sprite		m_c_sfSpriteLayout;
					sf::Sprite		m_c_sfSpriteBar;

			const	sf::VideoMode*	mp_c_sfVideomode;

					unsigned int	m_uiRessourceCount;
					unsigned int	m_uiRessourcesLoaded;
	protected:
	public:
									CProgressbar						( void )
											: m_bFinished				( false )
											, m_fBarGrow				( 0.f	)
									{
									}

					void			init_Progressbar					( const sf::Texture& c_sfSpriteLayout, const unsigned int uiRessourceCount, const sf::VideoMode& c_sfCurrentVideoMode )
					{
						
						m_c_sfSpriteLayout	.setTexture			( c_sfSpriteLayout );
						m_c_sfSpriteBar		.setTexture			( c_sfSpriteLayout );

						m_c_sfSpriteBar		.setTextureRect		( sf::IntRect( 0, static_cast<int>(m_c_sfSpriteBar.getGlobalBounds().height/2.f), static_cast<int>(m_c_sfSpriteBar.getGlobalBounds().width), static_cast<int>(m_c_sfSpriteBar.getGlobalBounds().height/2.f) ) );
						m_c_sfSpriteLayout	.setTextureRect		( sf::IntRect( 0, 0	 , static_cast<int>(m_c_sfSpriteLayout.getGlobalBounds().width), static_cast<int>(m_c_sfSpriteLayout.getGlobalBounds().height/2.f) ) );

						m_c_sfSpriteLayout	.setScale			( static_cast<float>( c_sfCurrentVideoMode.width )/1680.f , static_cast<float>( c_sfCurrentVideoMode.height )/1050.f );
						m_c_sfSpriteBar		.setScale			( static_cast<float>( c_sfCurrentVideoMode.width )/1680.f , static_cast<float>( c_sfCurrentVideoMode.height )/1050.f );

						m_fBarGrow				=		static_cast<float>( m_c_sfSpriteBar.getTexture()->getSize().x ) / static_cast<float>( uiRessourceCount );

						m_uiRessourceCount		=		uiRessourceCount;
						m_uiRessourcesLoaded	=		0;

						mp_c_sfVideomode		=		&c_sfCurrentVideoMode;
					}

					void			render_Progressbar					( sf::RenderTexture* const p_c_sfRenderTexture )
					{
						p_c_sfRenderTexture->draw( m_c_sfSpriteLayout	);
						p_c_sfRenderTexture->draw( m_c_sfSpriteBar		);
					}

					void			reset_Progressbar					( void )
					{
						m_uiRessourceCount		= 0;
						m_uiRessourcesLoaded	= 0;
						m_bFinished				= false;
						m_fBarGrow				= 0.f;
					}

					void			update_Progressbar					( void )
					{
						float fBarWidth = m_fBarGrow * float( (m_uiRessourcesLoaded) );

						if( fBarWidth <= m_c_sfSpriteBar.getTexture()->getSize().x )
						{
							m_c_sfSpriteBar.setTextureRect( sf::IntRect( m_c_sfSpriteBar.getTextureRect().left, m_c_sfSpriteBar.getTextureRect().top, static_cast<int>( fBarWidth ), static_cast<int>( m_c_sfSpriteBar.getLocalBounds().height ) ) );
						}

						if( (m_uiRessourcesLoaded) == m_uiRessourceCount )
						{
							m_bFinished = true;
						}
					}

					void			add_Progress						( void )
					{
						m_uiRessourcesLoaded++;
					}

					void			set_ProgressbarPosition				( const sf::Vector2f c_sfVectorPosition )
					{
						m_c_sfSpriteLayout.setOrigin	( float( m_c_sfSpriteLayout.getTextureRect().width )/2.f, float( m_c_sfSpriteLayout.getTextureRect().height )/2.f );
						m_c_sfSpriteLayout.setPosition	( c_sfVectorPosition.x, c_sfVectorPosition.y );

						m_c_sfSpriteBar.setOrigin		( float( m_c_sfSpriteBar.getTextureRect().width )/2.f, float( m_c_sfSpriteBar.getTextureRect().height )/2.f );
						m_c_sfSpriteBar.setPosition		( c_sfVectorPosition.x, c_sfVectorPosition.y );
					}

		const		bool			get_Finished						( void )
					{
						return m_bFinished;
					}
	};

	class CLoadingState : public CDialogGameState
	{
	private:
					bool												m_bStartLoadingThread;

					unsigned int										m_uiRessourcesLoaded;

					std::vector<std::string>							m_vecGamestatesToLoad;

					sf::Thread											m_c_sfLoadingThread;

					ety::CRessourceManager*								mp_c_etyCurrentRessourceManager;
					ety::CGamesettings*									mp_c_etyCurrentGamesettings;
					ety::CFilemanagement*								mp_c_etyCurrentFilemanagement;

					ety::CProgressbar									m_c_etyProgressbar;

					
	public:
																		CLoadingState					( const std::string& strGameStateName, ety::CFilemanagement* const p_c_etyFilemanagement );

																		~CLoadingState					( void );

					void												load_RessourcesThread			( void );

					void												on_Enter						( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );
					void												on_Exit							( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

		//Funktionen, welche Ressourcen initialisieren und ihn wieder freigeben,
		//sowie z.B alle Objekte aktualisieren und zeichnen.
					void												init_GameState					( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

					void												update_GameState				( const sf::Uint32& uiFrameTime );

					void												render_GameState				( sf::RenderTexture* const p_c_sfRenderTextureGameScene );

		const		ety::GameStateRunning::en_etyGameStateRunning		handle_GameStateEvents			( const sf::Event& sfEventLastEvent  );

					void												add_GamestateToLoad				( const std::string& strGamestateToLoad );
	};
}