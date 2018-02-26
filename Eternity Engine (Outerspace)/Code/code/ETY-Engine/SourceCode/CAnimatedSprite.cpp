#include "CAnimatedSprite.hpp"


		ety::CAnimatedSprite::CAnimatedSprite		( void )
			: m_bPlayAnimation				( false	)
			, m_bRepeatAnimation			( false	)
			, m_fAnimationDuration			( 0.f )
			, m_fCurrentPhaseDuration		( 0.f )
			, m_uintAnimationPhases			( 0 )
			, m_uintAnimationPhaseWidth		( 0 )
			, m_uintAnimationPhaseHeight	( 0 )
			, m_uintAnimationStartPhase		( 0 )
			, m_uintAnimationEndPhase		( 0 )
{
}
		ety::CAnimatedSprite::~CAnimatedSprite		( void )
{
}

void	ety::CAnimatedSprite::start_Animation		( const unsigned int uintAnimationStartPhase, const unsigned int uintAnimationEndPhase, const bool bRepeatAnimation, const float fAnimationDuration )
{
	m_bPlayAnimation			= true;
	m_bRepeatAnimation			= bRepeatAnimation;
	m_fAnimationDuration		= fAnimationDuration;
	m_uintAnimationStartPhase	= uintAnimationStartPhase;
	m_uintAnimationEndPhase		= uintAnimationEndPhase;
	m_uintCurrentPhase			= uintAnimationStartPhase;

	if( m_uintAnimationStartPhase > m_uintAnimationPhases )
	{
		m_uintAnimationStartPhase = m_uintAnimationPhases;
	}
	if( m_uintAnimationEndPhase > m_uintAnimationPhases )
	{
		m_uintAnimationEndPhase = m_uintAnimationPhases;
	}

	if( m_uintAnimationStartPhase < m_uintAnimationEndPhase )
	{
		m_fMaxPhaseDuration = m_fAnimationDuration / m_uintAnimationEndPhase - m_uintAnimationStartPhase;
	}
	else 
	{
		m_fMaxPhaseDuration = m_fAnimationDuration / m_uintAnimationStartPhase - m_uintAnimationEndPhase;
	}

	m_uintAnimationPhasesInColumn	= this->getTexture()->getSize().x / m_uintAnimationPhaseWidth;
	m_uintAnimationPhasesInRow		= this->getTexture()->getSize().y / m_uintAnimationPhaseHeight;

	unsigned int uintColumn = int(  m_uintAnimationStartPhase % m_uintAnimationPhasesInColumn	);
	unsigned int uintRow	= int(  m_uintAnimationStartPhase / m_uintAnimationPhasesInColumn	);

//	this->SetSubRect( sf::Rect<int>( uintColumn * m_uintAnimationPhaseWidth, uintRow * m_uintAnimationPhaseHeight, m_uintAnimationPhaseWidth, m_uintAnimationPhaseHeight ) );
}

void	ety::CAnimatedSprite::stop_Animation		( void )
{
	m_bPlayAnimation			= false;
}

void	ety::CAnimatedSprite::update_Sprite			( const sf::Uint32& uiFrameTime )
{
	if(  m_uintAnimationStartPhase != m_uintAnimationEndPhase  )
	{
		if( m_bPlayAnimation == true )
		{
			m_fCurrentPhaseDuration += uiFrameTime;

			if( m_fCurrentPhaseDuration >= m_fMaxPhaseDuration )
			{
				unsigned int uintColumn = int(  m_uintCurrentPhase % m_uintAnimationPhasesInColumn	);
				unsigned int uintRow	= int(  m_uintCurrentPhase / m_uintAnimationPhasesInColumn	);

//				this->SetSubRect( sf::Rect<int>( uintColumn * m_uintAnimationPhaseWidth, uintRow * m_uintAnimationPhaseHeight, m_uintAnimationPhaseWidth, m_uintAnimationPhaseHeight ) );

				m_fCurrentPhaseDuration = 0.f;

				if( m_uintCurrentPhase == m_uintAnimationEndPhase && m_bRepeatAnimation == false )
				{
					stop_Animation();
				}
				else if( m_uintCurrentPhase == m_uintAnimationEndPhase && m_bRepeatAnimation == true )
				{
					m_uintCurrentPhase = m_uintAnimationStartPhase;

					return ;
				}

				if( m_uintAnimationStartPhase < m_uintAnimationEndPhase )
				{
					m_uintCurrentPhase++;
				}
				else if( m_uintAnimationStartPhase > m_uintAnimationEndPhase )
				{
					m_uintCurrentPhase--;
				}
			}
		}
	}
}

void	ety::CAnimatedSprite::set_Sprite			( const sf::Texture& c_sfTexture, const unsigned int uintAnimationPhases, const unsigned int uintAnimationPhaseWidth, const unsigned int uintAnimationPhaseHeight )
{
	this->setTexture( c_sfTexture );

	m_uintAnimationPhases		= uintAnimationPhases;
	m_uintAnimationPhaseWidth	= uintAnimationPhaseWidth;
	m_uintAnimationPhaseHeight	= uintAnimationPhaseHeight;

//	this->SetSubRect( sf::Rect<int>( 0, 0, uintAnimationPhaseWidth, uintAnimationPhaseHeight ) );
}

