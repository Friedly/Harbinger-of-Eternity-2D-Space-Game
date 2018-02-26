#pragma once
#include "CTask.hpp"

namespace ety
{
	class CKillTask :	public CTask
	{
	private:
	protected:
					int				m_iKillCounter;
	public:
									CKillTask					( void );
									~CKillTask					( void );

									CKillTask					( std::string strTaskID, bool bTaskActive, int iKillCounter );

					void			decrease_KillCounter		( void );
					void			increase_KillCounter		( void );

					void			set_KillCounter				( int iKillCounter );

			const	int&			get_KillCounter				( void );
	};
}

