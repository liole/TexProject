/*
Всеможливі допоміжні типи
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>


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
		namespace Logic
		{
			struct Priority
			{
			protected:
				int32						priority;

			public:
				inline						Priority() = default;
				inline						Priority(int32 priority_);
				inline						Priority(const Priority&) = default;
				inline						Priority(Priority&&) = delete;
				inline						~Priority() = default;

				inline Priority&			operator = (const Priority&) = default;
				inline Priority&			operator = (Priority&&) = delete;

				inline void					SetPriority(int32 priority_);
				inline int32				GetPriority();
			};
		}
		namespace Transform					// Space Transformation
		{
			namespace D2					// Two Dimension
			{
				struct Position				// Position
				{
				protected:
					vec2					pos;

				public:
					inline					Position() = default;
					inline					Position(vec2 pos_);
					inline					Position(const Position&) = default;
					inline					Position(Position&&) = delete;
					inline					~Position() = default;

					inline Position&		operator = (const Position&) = default;
					inline Position&		operator = (Position&&) = delete;

					inline void				SetPos(vec2 pos_);
					inline vec2				GetPos();
					inline void				AddPos(vec2 add_);
					inline void				MulPos(vec2 mul_);
				};
				struct Size					// Size
				{
				protected:
					vec2					size;

				public:
					inline					Size() = default;
					inline					Size(vec2 pos_);
					inline					Size(const Size&) = default;
					inline					Size(Size&&) = delete;
					inline					~Size() = default;

					inline Size&			operator = (const Size&) = default;
					inline Size&			operator = (Size&&) = delete;

					inline void				SetSize(vec2 pos_);
					inline vec2				GetSize();
					inline void				AddSize(vec2 add_);
					inline void				MulSize(vec2 mul_);
				};
			}
		}

		typedef Logic::Priority				Prio;
		typedef Transform::D2::Position		Pos2;
		typedef Transform::D2::Size			Size2;
	}
}


// Structure::IndirectClassArray
template<typename T,bool autoAdd,bool autoRemove>
typename T**							TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::array_ = nullptr;
template<typename T,bool autoAdd,bool autoRemove>
TexProject::uint32						TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::count_ = 0;
template<typename T,bool autoAdd,bool autoRemove>
TexProject::uint32						TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::capacity_ = 0;

template<typename T,bool autoAdd,bool autoRemove>
inline TexProject::uint32				TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::GetCount()
{
	return count_;
}
template<typename T,bool autoAdd,bool autoRemove>
inline typename T*						TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::Get(uint32 i)
{
#ifdef __TEXPROJECT_DEBUG__
	if( i < count_ )
	{
		return array_[i];
	}
	else
	{
		throw ErrorException("[TexProject::Helper::Structure::IndirectClassArray]\nOut of array.");
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
void									TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::AddToArray()
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
void									TexProject::Helper::Structure::IndirectClassArray<T,autoAdd,autoRemove>::RemoveFromArray()
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




// Logic::Priority
TexProject::Helper::Logic::Priority::Priority(int32 priority_):
	priority(priority_)
{
}
void										TexProject::Helper::Logic::Priority::SetPriority(int32 priority_)
{
	priority = priority_;
}
TexProject::int32							TexProject::Helper::Logic::Priority::GetPriority()
{
	return priority;
}


// Transform::D2::Position
TexProject::Helper::Transform::D2::Position::Position(vec2 pos_):
	pos(pos_)
{
}
void										TexProject::Helper::Transform::D2::Position::SetPos(vec2 pos_)
{
	pos = pos_;
}
TexProject::vec2							TexProject::Helper::Transform::D2::Position::GetPos()
{
	return pos;
}
void										TexProject::Helper::Transform::D2::Position::AddPos(vec2 add_)
{
	pos += add_;
}
void										TexProject::Helper::Transform::D2::Position::MulPos(vec2 mul_)
{
	pos *= mul_;
}


// Transform::D2::Size
TexProject::Helper::Transform::D2::Size::Size(vec2 size_):
	size(size_)
{
}
void										TexProject::Helper::Transform::D2::Size::SetSize(vec2 size_)
{
	size = size_;
}
TexProject::vec2							TexProject::Helper::Transform::D2::Size::GetSize()
{
	return size;
}
void										TexProject::Helper::Transform::D2::Size::AddSize(vec2 add_)
{
	size += add_;
}
void										TexProject::Helper::Transform::D2::Size::MulSize(vec2 mul_)
{
	size *= mul_;
}












