#ifndef _WING_CORE_SMART_PTR_H_
#define _WING_CORE_SMART_PTR_H_

namespace WingCore
{
	template<class T>
	class SmartPtr
	{
	public:

		SmartPtr()
			:mPtr(nullptr)
		{
		}

		SmartPtr(T* ptr)
			:mPtr(nullptr)
		{
			setPtr(ptr);
		}

		SmartPtr(const SmartPtr<T> &sPtr)
			:mPtr(nullptr)
		{
			setPtr(sPtr);
		}

		~SmartPtr()
		{
			if (mPtr && mPtr->release() == 0)
				delete mPtr;

			mPtr = nullptr;
		}

		inline SmartPtr<T> &operator =(T* ptr)
		{
			if (mPtr != ptr)
				setPtr(ptr);
			return *this;
		}

		inline SmartPtr<T> &operator =(const SmartPtr<T> &sPtr)
		{
			if (mPtr != sPtr.getPtr())
				setPtr(sPtr.getPtr());

			return *this;
		}

		inline T* operator ->() const
		{
			return mPtr;
		}

		inline operator T*() const
		{
			return mPtr;
		}

		inline bool operator !() const
		{
			return (mPtr == nullptr);
		}

		inline bool operator ==(T* ptr) const
		{
			return (mPtr == ptr);
		}

		inline bool operator ==(SmartPtr<T> sPtr) const
		{
			return (mPtr == sPtr.getPtr());
		}

		inline bool operator !=(T* ptr) const
		{
			return (mPtr != ptr);
		}

		inline bool operator !=(SmartPtr<T> sPtr) const
		{
			return (mPtr != sPtr.getPtr());
		}

		inline void setPtr(T* ptr)
		{
			if (ptr)
				ptr->addReference();
			mPtr = ptr;
		}

		inline T* getPtr() const
		{
			return mPtr;
		}

	private:
		T*	mPtr;
	};


}

#endif