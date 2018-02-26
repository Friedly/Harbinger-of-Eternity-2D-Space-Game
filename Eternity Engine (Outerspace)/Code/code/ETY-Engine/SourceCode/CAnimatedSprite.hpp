#pragma once

//Sfml Includes
#include <SFML\Graphics.hpp>

//Compiler Includes
#include <iostream>

namespace ety
{
	class CAnimatedSprite : public sf::Sprite
	{
	private:
		bool			m_bPlayAnimation;
		bool			m_bRepeatAnimation;

		float			m_fAnimationDuration;
		float			m_fCurrentPhaseDuration;
		float			m_fMaxPhaseDuration;

		unsigned int	m_uintAnimationPhases;
		unsigned int	m_uintAnimationPhaseWidth;
		unsigned int	m_uintAnimationPhaseHeight;
		unsigned int	m_uintAnimationStartPhase;
		unsigned int	m_uintAnimationEndPhase;
		unsigned int	m_uintAnimationPhasesInRow;
		unsigned int	m_uintAnimationPhasesInColumn;
		unsigned int	m_uintCurrentPhase;
		

	protected:
		//Wird nicht abgeleitet.

	public:
				explicit		CAnimatedSprite		( void );
								~CAnimatedSprite	( void );

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Startet eine Animation angefangen bei einer Startphase und endet bei einer Endphase in der angegeben Zeit,
		/// wenn nötig kann man die Animation in Dauerschleife wiederholen lassen.
		/// \parameter	unsigned int, unsigned int, bool, float - Startphase, Endphase, Dauerschleife, Animationdauer
		/// \rückgabe	keinen
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void					start_Animation		( const unsigned int uintAnimationStartPhase = 0, const unsigned int uintAnimationEndPhase = 0, const bool bRepeatAnimation = false, const float fAnimationDuration = 0.f );

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Stoppt die Animation, die letzte Animationsphase wird beibehalten und angezeigt.
		/// \parameter	keinen
		/// \rückgabe	keinen
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void					stop_Animation		( void );

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Aktualisiert über die Frametime das Sprite und setzt die neue Animationsphase wenn nötig.
		/// \parameter	float	- Frametime
		/// \rückgabe	keinen
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void					update_Sprite		( const sf::Uint32& uiFrameTime );

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \Beschreibung: 
		/// Initialisiert für die Animation des Objektes die "Bildtabelle", sowie die Anzahl der Animationsphasen,
		/// die Breite und Höhe einer einzelnen Animationsphase.
		/// \parameter	const sf::Texture&, unsigned int,		- Bildtabelle, Anzahl Animationsphasen,
		///				unsigned int, unsigned int			  Breite einer Phase, Höhe einer Phase													 
		/// \rückgabe	keinen
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void					set_Sprite			( const sf::Texture& c_sfTexture, const unsigned int uintAnimationPhases, const unsigned int uintAnimationPhaseWidth, const unsigned int uintAnimationPhaseHeight );
	};
}

