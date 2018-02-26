#pragma once

#define NULL 0

namespace ety
{
	template <class T>
	class CSingleton
	{
	private:

	protected:
		static		T*		mp_c_etySingleton;

	public:
							CSingleton			( void ){};
		virtual				~CSingleton			( void ){};

		static		void	delete_Singleton	( void )
		{
			if( mp_c_etySingleton != NULL )
			{
				delete mp_c_etySingleton;
				mp_c_etySingleton = NULL;
			}
		}

		static		T*		get_Singleton		( void )
		{
			if( mp_c_etySingleton == NULL )
			{
				mp_c_etySingleton = new T;
			}

			return mp_c_etySingleton;
		}
	};

	template <class T> T*	ety::CSingleton<T>::mp_c_etySingleton = NULL;
}

