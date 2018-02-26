#include "CAttributeTask.hpp"
#include "CAttribute.hpp"


						ety::CAttributeTask::CAttributeTask			( void )
						:mp_c_etyAttribute							( NULL )
{
}


						ety::CAttributeTask::~CAttributeTask		( void )
{
	if(mp_c_etyAttribute != NULL)
	{
		delete mp_c_etyAttribute;
		mp_c_etyAttribute = NULL;
	}
}

						ety::CAttributeTask::CAttributeTask			( std::string strTaskID, bool bTaskActive )
{
	mp_c_etyAttribute	=	new CAttribute();
	m_bTaskActive		=	bTaskActive;
	m_strTaskID			=	strTaskID;
	m_bTaskCompleted	=	false;
}
						ety::CAttributeTask::CAttributeTask			( std::string strTaskID, bool bTaskActive, CAttribute& c_etyAttribute )
{
	mp_c_etyAttribute	=	new CAttribute(c_etyAttribute);
	m_bTaskActive		=	bTaskActive;
	m_strTaskID			=	strTaskID;
	m_bTaskCompleted	=	false;
}

void					ety::CAttributeTask::set_Attribute			( CAttribute& c_etyAttribute )
{
	if(mp_c_etyAttribute == NULL)
	{
		mp_c_etyAttribute = new CAttribute(c_etyAttribute);
	}
	else
	{
		*mp_c_etyAttribute	=	c_etyAttribute;
	}
}

ety::CAttribute&		ety::CAttributeTask::get_Attribute			( void )
{
	return	*mp_c_etyAttribute;
}
