#pragma once
#include <SFML\Graphics.hpp>
#include <map>
#include <string>

namespace ety
{
	class CDialog;
	class CSpaceStationHangarState;
	class CRessourceManager;
	class CGamesettings;
	class CEntity;

	class CShop
	{
	private:
	protected:
				std::map<std::string, CDialog*>		m_mapDialogs;
				CSpaceStationHangarState*			mp_c_etySpaceStationHangarState;
				CEntity*							mp_c_etyEntityPlayer;
	public:
													CShop					( void );
													~CShop					( void );

													CShop					( CSpaceStationHangarState* const p_c_etySpaceStationHangarState );

				void								add_Dialog				( CDialog* const p_c_etyDialog );

				void								init_Shop				( ety::CRessourceManager* const p_c_etyCurrentRessourceManager, 
																			  ety::CGamesettings* const p_c_etyCurrentGamesettingManager );

				void								update_Shop				( const sf::Uint32& uiFrameTime );

				void								show_ButtonTooltip		( std::string strButtonID );
				
				CDialog*	const					get_DialogByID			( std::string strDialogID );
	};
}


