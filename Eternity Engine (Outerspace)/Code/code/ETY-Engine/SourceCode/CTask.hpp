#pragma once
#include <string>

namespace ety
{
	class CTask
	{
	private:
	protected:
				bool					m_bTaskActive;
				bool					m_bTaskCompleted;
				std::string				m_strTaskID;

	public:
										CTask				( void );
										~CTask				( void );

										CTask				( std::string strTaskID, bool bTaskActive );

		virtual			void			set_TaskActive		( bool bTaskActive );
		virtual			void			set_TaskCompleted	( bool bTaskCompleted );

		virtual	const	bool&			get_TaskActive		( void );
		virtual	const	bool&			get_TaskCompleted	( void );
		virtual	const	std::string&	get_TaskID			( void );
	};
}

