#include "CTask.hpp"


						ety::CTask::CTask				(void)
{
}


						ety::CTask::~CTask				(void)
{
}

						ety::CTask::CTask				( std::string strTaskID, bool bTaskActive )
						:m_bTaskActive					(bTaskActive)
						,m_strTaskID					(strTaskID)
						,m_bTaskCompleted				(false)
{
}

		void			ety::CTask::set_TaskActive		( bool bTaskActive )
{
	m_bTaskActive	=	bTaskActive;
}
		void			ety::CTask::set_TaskCompleted	( bool bTaskCompleted )
{
	m_bTaskCompleted	=	bTaskCompleted;
}

const	bool&			ety::CTask::get_TaskActive		( void )
{
	return m_bTaskActive;
}
const	bool&			ety::CTask::get_TaskCompleted	( void )
{
	return m_bTaskCompleted;
}
const	std::string&	ety::CTask::get_TaskID			( void )
{
	return m_strTaskID;
}
