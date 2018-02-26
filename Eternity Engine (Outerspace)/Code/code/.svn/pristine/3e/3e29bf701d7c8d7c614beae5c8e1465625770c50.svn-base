#pragma once

#include "CIniFile.hpp"
#include "CMathConvertClasses.hpp"
#include "CAttribute.hpp"

#include <map>
#include <vector>
#include <list>

#include <iostream>

typedef std::map<std::string, std::string>			mapItemByModule;
typedef std::map<std::string, mapItemByModule>		mapItemsBySpaceship;

namespace ety
{
	class CProfile
	{
	private:
	protected:
		unsigned int						m_uiID;

		std::string							m_strFilename;
		std::string							m_strDirectory;

	public:
				ety::CAttribute				m_c_etyAttributes;
		//Konstruktor/Destruktor
											CProfile			( const std::string& strFilename, const std::string& strDirectory, const unsigned int uiID );
											~CProfile			( void );

		void								set_ID				( const unsigned int uiID );

		const	std::string&				get_Filename		( void );
		const	std::string&				get_Directory		( void );
		const	unsigned int				get_ID				( void );

	};

	class CETYProfile : public CProfile
	{
	private:
	protected:
	public:
				CETYProfile		( const std::string& strFilename, const std::string& strDirectory, const unsigned int uiID );
				~CETYProfile	( void );
	};
}