#include "CKillTask.hpp"


						ety::CKillTask::CKillTask					( void )
						:m_iKillCounter								( -1 )
{
}


						ety::CKillTask::~CKillTask					( void )
{
}

						ety::CKillTask::CKillTask					( std::string strTaskID, bool bTaskActive, int iKillCounter )
						:m_iKillCounter								(iKillCounter)
{
	m_bTaskActive		=	bTaskActive;
	m_strTaskID			=	strTaskID;
	m_bTaskCompleted	=	false;
}

		void			ety::CKillTask::decrease_KillCounter		( void )
{
	m_iKillCounter--;
}
		void			ety::CKillTask::increase_KillCounter		( void )
{
	m_iKillCounter++;
}

		void			ety::CKillTask::set_KillCounter				( int iKillCounter )
{
	m_iKillCounter	=	iKillCounter;
}

const	int&			ety::CKillTask::get_KillCounter				( void )
{
	return	m_iKillCounter;
}
