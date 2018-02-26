#pragma once

#include <string>

#include <SFML\System\Time.hpp>

#include "CLua.hpp"

namespace ety
{
	class CEntity;

	class CComponent
	{
	private:
	protected:
								bool					m_bActive;
								ety::CEntity*			mp_c_Owner;

	public:
														CComponent					( void );
		virtual											~CComponent					( void );

		virtual					void					update_Component			( const sf::Uint32& uiFrameTime ) = 0;

								void					set_Owner					( ety::CEntity* const p_c_Owner );

								ety::CEntity*	const	get_Owner					( void );

		virtual		const		std::string				get_FamilyID				( void ) = 0;
		virtual		const		std::string				get_ComponentID				( void ) = 0;
					const		bool					get_Active					( void );
	};
}

