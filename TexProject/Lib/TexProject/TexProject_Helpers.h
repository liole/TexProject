/*
Всеможливі допоміжні типи
*/
#pragma once
#include <TexProject/TexProject_Header.h>


namespace TexProject
{
	namespace Helper
	{
		namespace Structure
		{
			template<typename T,bool autoAdd,bool autoRemove>
			struct IndirectClassArray
			{
			protected:
				static const uint32			uninitID = 0xFFFFFFFF;

				static T**					array_;
				static uint32				count_;
				static uint32				capacity_;

			public:

				/*Повертає кількість екземплярів класу*/
				static inline uint32		GetCount();
				/*Повертає вказівник на і-й екземпляр класу*/
				static inline T*			Get(uint32 i);


				uint32						id_;

											IndirectClassArray();
											~IndirectClassArray();

				void						AddToArray();
				void						RemoveFromArray();
			};
		}
	}

}


// Structure::IndirectClassArray
template<typename T,bool autoAdd,bool autoRemove>
typename T**					TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::array_ = nullptr;
template<typename T,bool autoAdd,bool autoRemove>
TexProject::uint32				TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::count_ = 0;
template<typename T,bool autoAdd,bool autoRemove>
TexProject::uint32				TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::capacity_ = 0;

template<typename T,bool autoAdd,bool autoRemove>
inline TexProject::uint32		TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::GetCount()
{
	return count_;
}
template<typename T,bool autoAdd,bool autoRemove>
inline typename T*				TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::Get(uint32 i)
{
#ifdef __TEXPROJECT_DEBUG__
	if( i < count_ )
	{
		return array_[i];
	}
	else
	{
		Error("[TexProject::Helper::Structure::IndirectClassArray]\nOut of array.");
	}
#else
	return array_[i];
#endif
}

template<typename T,bool autoAdd,bool autoRemove>
TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::IndirectClassArray():
	id_(uninitID)
{
	if(autoAdd) AddToArray();
}
template<typename T,bool autoAdd,bool autoRemove>
TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::~IndirectClassArray()
{
	if(autoRemove) RemoveFromArray();
}
template<typename T,bool autoAdd,bool autoRemove>
void							TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::AddToArray()
{
	if(id_ == uninitID)
	{
		if( count_ + 1 > capacity_ )
		{
			capacity_ = std::max<uint32>(32,capacity_*2);
			array_ = (T**)realloc(array_,sizeof(T*)*capacity_);
		}
		array_[count_] = (T*)this;
		id_ = count_;
		++count_;
	}
}
template<typename T,bool autoAdd,bool autoRemove>
void							TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::RemoveFromArray()
{
	if(id_ != uninitID)
	{
#ifdef __TEXPROJECT_DEBUG__
		if(count_ == 0) Error("[TexProject::Helper::Structure::IndirectClassArray]\nRemoving element from empty array.");
#endif
		--count_;

		if(id_ != count_)
		{
			array_[id_] = array_[count_];
			array_[id_]->id_ = id_;
		}

		if(count_ >= 32 && count_ < capacity_/4)
		{
			capacity_ /= 2;
			array_ = (T**)realloc(array_,sizeof(T*)*capacity_);
		}
	}
}

















