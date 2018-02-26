#pragma once
#include "CTask.hpp"

namespace ety
{
	class CAttribute;

	class CAttributeTask :	public CTask
	{
	private:
	protected:
						CAttribute*		mp_c_etyAttribute;
	public:
										CAttributeTask			(void);
										~CAttributeTask			(void);

										CAttributeTask			( std::string strTaskID, bool bTaskActive );
										CAttributeTask			( std::string strTaskID, bool bTaskActive, CAttribute& c_etyAttribute );

						void			set_Attribute			( CAttribute& c_etyAttribute );

						CAttribute&		get_Attribute			( void );
	};
}
