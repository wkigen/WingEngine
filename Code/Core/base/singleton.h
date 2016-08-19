#ifndef _WING_CORE_SINGLETON_H_
#define _WING_CORE_SINGLETON_H_

#include "common\defines.h"

namespace WingCore
{

	template<class T>
	class Singleton
	{
	public :

		static inline T* getInstance();


	protected:

		Singleton();
		~Singleton();

	private:
		static T* mInstance;
	};


	//--------------------------------------

	//--------------------------------------
	template <class T> T* Singleton<T>::mInstance = nullptr;

	template<class T>
	Singleton<T>::Singleton()
	{

	}


	template<class T>
	Singleton<T>::~Singleton()
	{

	}

	template<class T>
	inline T* Singleton<T>::getInstance()
	{
		if (mInstance == nullptr)
			mInstance = new T();
		return mInstance;
	}
}

#endif