#pragma once
#include <string>
#include <list>

namespace ety
{
	class CTask;

	class CMission
	{
	private:
	protected:
				bool				m_bActive;
				bool				m_bMainMission;
				bool				m_bMissionCompleted;
				bool				m_bMissionDiscovered;
				std::list<CTask*>	m_listTasks;
				std::string			m_strMissionID;
	public:
									CMission					( void );
									~CMission					( void );

									CMission					( std::string strMissionID, bool bMainMission, bool bActive, bool bMissionDiscovered);

				void				add_Task					( CTask* const p_c_etyTask );

				void				set_MissionCompleted		( bool bMissionCompleted );
				void				set_MissionDiscovered		( bool bMissionDiscovered );

		const	bool&				get_MainMission				( void );
		const	bool&				get_MissionCompleted		( void );
		const	bool&				get_MissionDiscovered		( void );
		const	std::string&		get_MissionID				( void );

				template										<typename typeTaskType>	
				typeTaskType 		get_TaskByID				( const std::string& strTaskID)
				{
					for(std::list<CTask*>::iterator itTask = m_listTasks.begin(); itTask != m_listTasks.end(); itTask++)
					{
						//Es wird die CustomID des Dialogitems überprüft und wenn sie überein stimmt wird das Dialogitem zurückgegeben
						if((*itTask)->get_TaskID() == strTaskID)
						{
							typeTaskType typeTask = reinterpret_cast<typeTaskType>((*itTask));
							return typeTask;
						}
					}
					return NULL;
				}
	};
}

