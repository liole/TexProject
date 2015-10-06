#pragma once
#pragma region TexProject Includes
#include <TexProject/TexProject_Header.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Main.h>
#pragma endregion
#pragma region Includes
#include <list>
#include <iterator>
#pragma endregion


namespace TexProject
{
	namespace Helper
	{
		namespace Structure
		{
			template<typename T>
			class ClassList
			{
			protected:
				static std::list<T*>							list;
				typename std::list<T*>::iterator				iter;
			public:
				inline											ClassList();
				inline											~ClassList();
			};
		}
		namespace Logic
		{
			interface IPriority
			{
			public:
				inline						IPriority() = default;
				inline						IPriority(int32 priority_);
				inline						IPriority(const IPriority&) = default;
				inline						~IPriority() = default;

				inline IPriority&			operator = (const IPriority&) = default;

				inline void					SetPriority(int32 priority_);
				inline int32				GetPriority() const;
			};
			interface IColor4
			{
			public:
				inline						IColor4() = default;
				inline						IColor4(const vec4& color_);
				inline						IColor4(const IColor4&) = default;
				inline						~IColor4() = default;

				inline vec4					GetColor() const;
				inline void					SetColor(const vec4& color_);
			};

			struct Priority:
				public IPriority
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
				inline int32				GetPriority() const;
			};
			struct Color4:
				public IColor4
			{
			protected:
				vec4						color;

			public:

				inline						Color4() = default;
				inline						Color4(const vec4& color_);
				inline						Color4(const Color4&) = default;
				inline						~Color4() = default;

				inline vec4					GetColor() const;
				inline void					SetColor(const vec4& color_);
			};
		}
		namespace Transform					// Space Transformation
		{
			namespace D2					// Two Dimension
			{
				interface IPosition
				{
				public:
					inline					IPosition() = default;
					inline					IPosition(const vec2& pos_);
					inline					IPosition(const IPosition&) = default;
					inline					IPosition(IPosition&&) = delete;
					inline					~IPosition() = default;

					inline IPosition&		operator = (const IPosition&) = default;
					inline IPosition&		operator = (IPosition&&) = delete;

					inline void				SetPos(const vec2& pos_);
					inline vec2				GetPos() const;
					inline void				AddPos(const vec2& add_);
					inline void				MulPos(const vec2& mul_);
				};
				interface ISize
				{
				public:
					inline					ISize() = default;
					inline					ISize(vec2 pos_);
					inline					ISize(const ISize&) = default;
					inline					ISize(ISize&&) = delete;
					inline					~ISize() = default;

					inline ISize&			operator = (const ISize&) = default;
					inline ISize&			operator = (ISize&&) = delete;

					inline void				SetSize(const vec2& pos_);
					inline vec2				GetSize() const;
					inline void				AddSize(const vec2& add_);
					inline void				MulSize(const vec2& mul_);
				};

				struct Position: public IPosition				// Position
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

					inline void				SetPos(const vec2& pos_);
					inline vec2				GetPos() const;
					inline void				AddPos(const vec2& add_);
					inline void				MulPos(const vec2& mul_);
				};
				struct Size: public ISize						// Size
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

					inline void				SetSize(const vec2& pos_);
					inline vec2				GetSize() const;
					inline void				AddSize(const vec2& add_);
					inline void				MulSize(const vec2& mul_);
				};
			}
			namespace D3
			{
				namespace Projection
				{
					enum struct Type
					{
						Orthogonal,
						Perspective
					};
					struct Params
					{
						struct Orthogonal
						{
							float32			left,
							right,
							bottom,
							top,
							back,
							front;
							inline			Orthogonal() = default;
							inline			Orthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 back_,float32 front_):
								left(left_),
								right(right_),
								bottom(bottom_),
								top(top_),
								back(back_),
								front(front_)
							{
							}

							inline bool		operator != (const Orthogonal& source) const
							{
								return
									(
									left != source.left ||
									right != source.right ||
									bottom != source.bottom ||
									top != source.top ||
									back != source.back  ||
									front != source.front
									);
							}
						};
						struct Perspective
						{
							float32			fov,
							aspect,
							zNear,
							zFar;

							inline			Perspective() = default;
							inline			Perspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_):
								fov(fov_),
								aspect(aspect_),
								zNear(zNear_),
								zFar(zFar_)
							{
							}

							inline bool		operator != (const Perspective& source) const
							{
								return
									(
									fov != source.fov ||
									aspect != source.aspect ||
									zNear != source.zNear ||
									zFar != source.zFar
									);
							}
						};
					};
				}

				interface IPosition
				{
				public:
					inline					IPosition() = default;
					inline explicit			IPosition(const vec3& pos_);
					inline					IPosition(const IPosition&) = default;
					inline					IPosition(IPosition&&) = delete;
					inline					~IPosition() = default;

					inline IPosition&		operator = (const IPosition&) = default;
					inline IPosition&		operator = (IPosition&&) = delete;

					inline void				SetPos(const vec3& pos_);
					inline vec3				GetPos() const;
					inline void				AddPos(const vec3& add_);
					inline void				MulPos(const vec3& mul_);
				};
				interface IAngle
				{
				public:
					inline					IAngle() = default;
					inline explicit			IAngle(const vec3& ang_);
					inline					IAngle(const IAngle&) = default;
					inline					IAngle(IAngle&&) = delete;
					inline					~IAngle() = default;

					inline IAngle&			operator = (const IAngle&) = default;
					inline IAngle&			operator = (IAngle&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline vec3				GetAng() const;
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
				};
				interface IScale
				{
				public:
					inline					IScale() = default;
					inline explicit			IScale(vec3 scl_);
					inline					IScale(const IScale&) = default;
					inline					IScale(IScale&&) = delete;
					inline					~IScale() = default;

					inline IScale&			operator = (const IScale&) = default;
					inline IScale&			operator = (IScale&&) = delete;

					inline void				SetScale(const vec3& scl_);
					inline vec3				GetScale() const;
					inline void				AddScale(const vec3& add_);
					inline void				MulScale(const vec3& mul_);
				};
				interface ISize
				{
				public:
					inline					ISize() = default;
					inline explicit			ISize(vec3 pos_);
					inline					ISize(const ISize&) = default;
					inline					ISize(ISize&&) = delete;
					inline					~ISize() = default;

					inline ISize&			operator = (const ISize&) = default;
					inline ISize&			operator = (ISize&&) = delete;

					inline void				SetSize(const vec3& pos_);
					inline vec3				GetSize() const;
					inline void				AddSize(const vec3& add_);
					inline void				MulSize(const vec3& mul_);
				};
				interface IProjectionMatrix
				{
				public:
					inline					IProjectionMatrix() = default;
					inline explicit			IProjectionMatrix(const Projection::Type& type_);
					inline explicit			IProjectionMatrix(const Projection::Params::Orthogonal& source);
					inline explicit			IProjectionMatrix(const Projection::Params::Perspective& source);
					inline					IProjectionMatrix(const IProjectionMatrix&) = default;
					inline					IProjectionMatrix(IProjectionMatrix&&) = delete;
					inline					~IProjectionMatrix() = default;

					inline IProjectionMatrix&					operator = (const IProjectionMatrix&) = default;
					inline IProjectionMatrix&					operator = (IProjectionMatrix&&) = delete;

					inline Projection::Type	GetProjectionType() const;

					inline void				SetOrthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 zNear_,float32 zFar_);
					inline void				SetOrthogonal(const Projection::Params::Orthogonal& source = Projection::Params::Orthogonal(-50,50,-50,50,0,100));
					inline void				SetPerspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_);
					inline void				SetPerspective(const Projection::Params::Perspective& source = Projection::Params::Perspective(80.0f,1.0f,1.0f,100.0f));

					inline mat4				GetPMat() const;
					inline mat4				GetPIMat() const;
				};
				interface IRotateMatrix:
					public IAngle
				{
				public:
					inline					IRotateMatrix() = default;
					inline explicit			IRotateMatrix(const vec3& ang_);
					inline					IRotateMatrix(const IRotateMatrix&) = default;
					inline					IRotateMatrix(IRotateMatrix&&) = delete;
					inline					~IRotateMatrix() = default;

					inline IRotateMatrix&	operator = (const IRotateMatrix&) = default;
					inline IRotateMatrix&	operator = (IRotateMatrix&&) = delete;

					inline void				Rotate(const vec3& val_);	// Relative rotation

					inline mat3				GetRMat() const;
					inline mat3				GetRIMat() const;
				};
				interface IViewMatrix:
					public IPosition,
					public IRotateMatrix
				{
				public:
					inline					IViewMatrix() = default;
					inline					IViewMatrix(const vec3& pos_,const vec3& ang_);
					inline explicit			IViewMatrix(const IViewMatrix&) = default;
					inline					IViewMatrix(IViewMatrix&&) = delete;
					inline					~IViewMatrix() = default;

					inline IViewMatrix&		operator = (const IViewMatrix&) = default;
					inline IViewMatrix&		operator = (IViewMatrix&&) = delete;

					inline void				Move(const vec3& val_);		// Relative Move

					inline mat4				GetVMat() const;
					inline mat4				GetVIMat() const;
				};
				interface IViewProjectionMatrix :
					public IViewMatrix,
					public IProjectionMatrix
				{
				public:
					inline					IViewProjectionMatrix() = default;
					inline					IViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Orthogonal proj_);
					inline					IViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Perspective proj_);
					inline explicit			IViewProjectionMatrix(const IViewProjectionMatrix&) = default;
					inline					IViewProjectionMatrix(IViewProjectionMatrix&&) = delete;
					inline					~IViewProjectionMatrix() = default;

					inline IViewProjectionMatrix&				operator = (const IViewProjectionMatrix&) = default;
					inline IViewProjectionMatrix&				operator = (IViewProjectionMatrix&&) = delete;

					inline mat4				GetVPMat() const;
					inline mat4				GetVPIMat() const;
				};
				/*interface IViewProjectionMatrix:
					public IPosition,
					public IProjectionMatrix,
					public IRotateMatrix
				{
				public:
					inline					IViewProjectionMatrix() = default;
					inline explicit			IViewProjectionMatrix(const IViewProjectionMatrix&) = default;
					inline					IViewProjectionMatrix(IViewProjectionMatrix&&) = delete;
					inline					~IViewProjectionMatrix() = default;

					inline IViewProjectionMatrix&				operator = (const IViewProjectionMatrix&) = default;
					inline IViewProjectionMatrix&				operator = (IViewProjectionMatrix&&) = delete;

					inline void				Move(const vec3& val_);		// Relative Move

					inline mat4				GetVMat() const;
					inline mat4				GetVIMat() const;
					inline mat4				GetVPMat() const;
					inline mat4				GetVPIMat() const;
				};*/
				interface IModelMatrix:
					public IPosition,
					public IScale,
					public IRotateMatrix
				{
				public:
					inline					IModelMatrix() = default;
					inline explicit			IModelMatrix(const IModelMatrix&) = default;
					inline					IModelMatrix(IModelMatrix&&) = delete;
					inline					~IModelMatrix() = default;

					inline IModelMatrix&	operator = (const IModelMatrix&) = default;
					inline IModelMatrix&	operator = (IModelMatrix&&) = delete;

					inline void				Move(const vec3& val_);		// Relative Move

					inline mat4				GetMMat() const;
					inline mat4				GetMIMat() const;
				};

				struct Position:			// Position
					public IPosition
				{
				protected:
					vec3					pos;

				public:
					inline					Position() = default;
					inline explicit			Position(vec3 pos_);
					inline					Position(const Position&) = default;
					inline					Position(Position&&) = delete;
					inline					~Position() = default;

					inline Position&		operator = (const Position&) = default;
					inline Position&		operator = (Position&&) = delete;

					inline void				SetPos(const vec3& pos_);
					inline vec3				GetPos() const;
					inline void				AddPos(const vec3& add_);
					inline void				MulPos(const vec3& mul_);
				};
				struct Angle:				// Angle
					public IAngle
				{
				protected:
					vec3					ang;

				public:
					inline					Angle() = default;
					inline explicit			Angle(vec3 ang_);
					inline					Angle(const Angle&) = default;
					inline					Angle(Angle&&) = delete;
					inline					~Angle() = default;

					inline Angle&			operator = (const Angle&) = default;
					inline Angle&			operator = (Angle&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline vec3				GetAng() const;
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
				};
				struct Scale:
					public IScale
				{
				protected:
					vec3					scale;

				public:
					inline					Scale() = default;
					inline explicit			Scale(vec3 scl_);
					inline					Scale(const Scale&) = default;
					inline					Scale(Scale&&) = delete;
					inline					~Scale() = default;

					inline Scale&			operator = (const Scale&) = default;
					inline Scale&			operator = (Scale&&) = delete;

					inline void				SetScale(const vec3& scl_);
					inline vec3				GetScale() const;
					inline void				AddScale(const vec3& add_);
					inline void				MulScale(const vec3& mul_);
				};
				struct Size:				// Size
					public ISize
				{
				protected:
					vec3					size;

				public:
					inline					Size() = default;
					inline explicit			Size(vec3 pos_);
					inline					Size(const Size&) = default;
					inline					Size(Size&&) = delete;
					inline					~Size() = default;

					inline Size&			operator = (const Size&) = default;
					inline Size&			operator = (Size&&) = delete;

					inline void				SetSize(const vec3& pos_);
					inline vec3				GetSize() const;
					inline void				AddSize(const vec3& add_);
					inline void				MulSize(const vec3& mul_);
				};
				struct ProjectionMatrix:
					public IProjectionMatrix
				{
				protected:
					Projection::Type		type;
					Projection::Params::Orthogonal				paramsOrthogonal;
					Projection::Params::Perspective				paramsPerspective;
					mutable bool			pRebuild = true,
											piRebuild = true;
					mutable mat4			pMat,
											piMat;

				public:
					inline					ProjectionMatrix() = default;
					inline explicit			ProjectionMatrix(const Projection::Type& type_);
					inline explicit			ProjectionMatrix(const Projection::Params::Orthogonal& source);
					inline explicit			ProjectionMatrix(const Projection::Params::Perspective& source);
					inline					ProjectionMatrix(const ProjectionMatrix& source);
					inline					ProjectionMatrix(ProjectionMatrix&&) = delete;
					inline					~ProjectionMatrix() = default;

					inline ProjectionMatrix&					operator = (const ProjectionMatrix&);
					inline ProjectionMatrix&					operator = (ProjectionMatrix&&) = delete;

					inline Projection::Type	GetProjectionType() const;

					inline void				SetOrthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 zNear_,float32 zFar_);
					inline void				SetOrthogonal(const Projection::Params::Orthogonal& source = Projection::Params::Orthogonal(-50,50,-50,50,0,100));
					inline void				SetPerspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_);
					inline void				SetPerspective(const Projection::Params::Perspective& source = Projection::Params::Perspective(80.0f,1.0f,1.0f,100.0f));

					inline Projection::Params::Orthogonal		GetOrthogonal() const;
					inline Projection::Params::Perspective		GetPerspective() const;

					inline mat4				GetPMat() const;
					inline mat4				GetPIMat() const;
				};
				struct RotateMatrix:
					public IRotateMatrix,
					public Angle
				{
				protected:
					mutable bool			rRebuild = true,	// Flag to rebuild matrix on next 'get'
											riRebuild = true;
					mutable mat3			rMat,				// rotate matrix storage
											riMat;				// rotate inverse matrix storage

				public:
					inline					RotateMatrix() = default;
					inline explicit			RotateMatrix(const vec3& ang_);
					inline					RotateMatrix(const RotateMatrix& source);
					inline					RotateMatrix(RotateMatrix&&) = delete;
					inline					~RotateMatrix() = default;

					inline RotateMatrix&	operator = (const RotateMatrix& source);
					inline RotateMatrix&	operator = (RotateMatrix&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
					inline void				Rotate(const vec3& val_);
					inline vec3				GetAng() const;

					inline mat3				GetRMat() const;
					inline mat3				GetRIMat() const;
				};
				struct ViewMatrix:
					public IViewMatrix,
					public Position,
					public RotateMatrix
				{
				protected:
					mutable bool			vRebuild = true,	// Flag to rebuild matrix on next 'get'
											viRebuild = true;
					mutable mat4			vMat,				// view matrix storage
											viMat;				// view inverse matrix storage
				public:
					inline					ViewMatrix() = default;
					inline					ViewMatrix(const vec3& pos_, const vec3& ang_);
					inline explicit			ViewMatrix(const ViewMatrix&) = default;
					inline					ViewMatrix(ViewMatrix&&) = delete;
					inline					~ViewMatrix() = default;

					inline ViewMatrix&		operator = (const ViewMatrix&) = default;
					inline ViewMatrix&		operator = (ViewMatrix&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
					inline vec3				GetAng() const;
					inline void				Rotate(const vec3& val_);	// Relative rotation

					inline void				SetPos(const vec3& pos_);
					inline void				AddPos(const vec3& add_);
					inline void				MulPos(const vec3& mul_);
					inline vec3				GetPos() const;
					inline void				Move(const vec3& val_);		// Relative Move

					//inline void				SetOrthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 zNear_,float32 zFar_);
					//inline void				SetOrthogonal(const Projection::Params::Orthogonal& source = Projection::Params::Orthogonal(-50,50,-50,50,0,100));
					//inline void				SetPerspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_);
					//inline void				SetPerspective(const Projection::Params::Perspective& source = Projection::Params::Perspective(80.0f,1.0f,1.0f,100.0f));

					inline mat3				GetRMat() const;
					inline mat3				GetRIMat() const;
					inline mat4				GetVMat() const;
					inline mat4				GetVIMat() const;
				};
				struct ViewProjectionMatrix:
					public IViewProjectionMatrix,
					public ViewMatrix,
					public ProjectionMatrix
				{
				protected:
					mutable bool			vpRebuild = true,
											vpiRebuild = true;
					mutable mat4			vpMat,
											vpiMat;
				public:
					inline					ViewProjectionMatrix() = default;
					inline					ViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Orthogonal proj_);
					inline					ViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Perspective proj_);
					inline explicit			ViewProjectionMatrix(const ViewProjectionMatrix&) = default;
					inline					ViewProjectionMatrix(ViewProjectionMatrix&&) = delete;
					inline					~ViewProjectionMatrix() = default;

					inline ViewProjectionMatrix&				operator = (const ViewProjectionMatrix&) = default;
					inline ViewProjectionMatrix&				operator = (ViewProjectionMatrix&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
					inline vec3				GetAng() const;
					inline void				Rotate(const vec3& val_);	// Relative rotation

					inline void				SetPos(const vec3& pos_);
					inline void				AddPos(const vec3& add_);
					inline void				MulPos(const vec3& mul_);
					inline vec3				GetPos() const;
					inline void				Move(const vec3& val_);		// Relative Move

					inline void				SetOrthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 zNear_,float32 zFar_);
					inline void				SetOrthogonal(const Projection::Params::Orthogonal& source = Projection::Params::Orthogonal(-50,50,-50,50,0,100));
					inline void				SetPerspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_);
					inline void				SetPerspective(const Projection::Params::Perspective& source = Projection::Params::Perspective(80.0f,1.0f,1.0f,100.0f));

					inline mat3				GetRMat() const;
					inline mat3				GetRIMat() const;
					inline mat4				GetVMat() const;
					inline mat4				GetVIMat() const;
					inline mat4				GetPMat() const;
					inline mat4				GetPIMat() const;
					inline mat4				GetVPMat() const;
					inline mat4				GetVPIMat() const;
				};
				struct ModelMatrix :
					public IModelMatrix,
					public Position,
					public Scale,
					public RotateMatrix
				{
				protected:
					mutable bool			mRebuild = true,
						miRebuild = true;
					mutable mat4			mMat,
						miMat;

				public:
					inline					ModelMatrix() = default;
					inline explicit			ModelMatrix(const ModelMatrix&);
					inline					ModelMatrix(const vec3& pos_,const vec3& ang_,const vec3& scl_);
					inline					ModelMatrix(ModelMatrix&&) = delete;
					inline					~ModelMatrix() = default;

					inline ModelMatrix&		operator = (const ModelMatrix&) = default;
					inline ModelMatrix&		operator = (ModelMatrix&&) = delete;

					inline void				SetAng(const vec3& ang_);
					inline vec3				GetAng() const;
					inline void				AddAng(const vec3& add_);
					inline void				MulAng(const vec3& mul_);
					inline void				SetScale(const vec3& scl_);
					inline vec3				GetScale() const;
					inline void				AddScale(const vec3& add_);
					inline void				MulScale(const vec3& mul_);
					inline void				SetPos(const vec3& pos_);
					inline vec3				GetPos() const;
					inline void				AddPos(const vec3& add_);
					inline void				MulPos(const vec3& mul_);
					inline void				Rotate(const vec3& val_);
					inline void				Move(const vec3& val_);

					inline mat3				GetRMat() const;
					inline mat3				GetRIMat() const;
					inline mat4				GetMMat() const;
					inline mat4				GetMIMat() const;
				};
			}
		}

		typedef Logic::IPriority								IPrio;
		typedef Logic::IColor4									IColor4;
		typedef Logic::Priority									Prio;
		typedef Logic::Color4									Color4;

		typedef Transform::D2::IPosition						IPos2;
		typedef Transform::D2::ISize							ISize2;
		typedef Transform::D2::Position							Pos2;
		typedef Transform::D2::Size								Size2;

		typedef Transform::D3::Projection::Params				PParams;
		typedef Transform::D3::IPosition						IPos3;
		typedef Transform::D3::IAngle							IAng3;
		typedef Transform::D3::ISize							ISize3;
		typedef Transform::D3::IProjectionMatrix				IPMat;
		typedef Transform::D3::IRotateMatrix					IRMat;
		typedef Transform::D3::IViewMatrix						IVMat;
		typedef Transform::D3::IModelMatrix						IMMat;
		typedef Transform::D3::Position							Pos3;
		typedef Transform::D3::Angle							Ang3;
		typedef Transform::D3::Size								Size3;
		typedef Transform::D3::ProjectionMatrix					PMat;
		typedef Transform::D3::RotateMatrix						RMat;
		typedef Transform::D3::ViewMatrix						VMat;
		typedef Transform::D3::ViewProjectionMatrix				VPMat;
		typedef Transform::D3::ModelMatrix						MMat;
	}
}
#pragma region
#pragma endregion


#pragma region Structure
#pragma region ClassList
template<typename T>
std::list<T*>													TexProject::Helper::Structure::ClassList<T>::list;
template<typename T>
inline															TexProject::Helper::Structure::ClassList<T>::ClassList():
	iter(list.insert(list.begin(),(T*)this))
{
}
template<typename T>
inline															TexProject::Helper::Structure::ClassList<T>::~ClassList()
{
	list.erase(iter);
}
#pragma endregion
#pragma endregion
#pragma region Logic
#pragma region Priority
inline TexProject::Helper::Logic::Priority::Priority(int32 priority_):
	priority(priority_)
{
}
inline void									TexProject::Helper::Logic::Priority::SetPriority(int32 priority_)
{
	priority = priority_;
}
inline TexProject::int32					TexProject::Helper::Logic::Priority::GetPriority() const
{
	return priority;
}
#pragma endregion
#pragma region Color
inline TexProject::Helper::Logic::Color4::Color4(const vec4& color_):
	color(color_)
{
}
inline TexProject::vec4						TexProject::Helper::Logic::Color4::GetColor() const
{
	return color;
}
inline void									TexProject::Helper::Logic::Color4::SetColor(const vec4& color_)
{
	color = color_;
}
#pragma endregion
#pragma endregion
#pragma region Transform
#pragma region D2
#pragma region Position
inline TexProject::Helper::Transform::D2::Position::Position(vec2 pos_):
	pos(pos_)
{
}
inline void									TexProject::Helper::Transform::D2::Position::SetPos(const vec2& pos_)
{
	pos = pos_;
}
inline TexProject::vec2						TexProject::Helper::Transform::D2::Position::GetPos() const
{
	return pos;
}
inline void									TexProject::Helper::Transform::D2::Position::AddPos(const vec2& add_)
{
	pos += add_;
}
inline void									TexProject::Helper::Transform::D2::Position::MulPos(const vec2& mul_)
{
	pos *= mul_;
}
#pragma endregion
#pragma region Size
inline TexProject::Helper::Transform::D2::Size::Size(vec2 size_):
	size(size_)
{
}
inline void									TexProject::Helper::Transform::D2::Size::SetSize(const vec2& size_)
{
	size = size_;
}
inline TexProject::vec2						TexProject::Helper::Transform::D2::Size::GetSize() const
{
	return size;
}
inline void									TexProject::Helper::Transform::D2::Size::AddSize(const vec2& add_)
{
	size += add_;
}
inline void									TexProject::Helper::Transform::D2::Size::MulSize(const vec2& mul_)
{
	size *= mul_;
}
#pragma endregion
#pragma endregion
#pragma region D3
#pragma region Position
inline TexProject::Helper::Transform::D3::Position::Position(vec3 pos_):
	pos(pos_)
{
}
inline void									TexProject::Helper::Transform::D3::Position::SetPos(const vec3& pos_)
{
	pos = pos_;
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::Position::GetPos() const
{
	return pos;
}
inline void									TexProject::Helper::Transform::D3::Position::AddPos(const vec3& add_)
{
	pos += add_;
}
inline void									TexProject::Helper::Transform::D3::Position::MulPos(const vec3& mul_)
{
	pos *= mul_;
}
#pragma endregion
#pragma region Angle
inline TexProject::Helper::Transform::D3::Angle::Angle(vec3 ang_):
	ang(ang_)
{
}
inline void									TexProject::Helper::Transform::D3::Angle::SetAng(const vec3& ang_)
{
	ang = ang_;
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::Angle::GetAng() const
{
	return ang;
}
inline void									TexProject::Helper::Transform::D3::Angle::AddAng(const vec3& add_)
{
	ang += add_;
}
inline void									TexProject::Helper::Transform::D3::Angle::MulAng(const vec3& mul_)
{
	ang *= mul_;
}
#pragma endregion
#pragma region Scale
inline TexProject::Helper::Transform::D3::Scale::Scale(vec3 scl_):
	scale(scl_)
{
}
inline void									TexProject::Helper::Transform::D3::Scale::SetScale(const vec3& scl_)
{
	scale = scl_;
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::Scale::GetScale() const
{
	return scale;
}
inline void									TexProject::Helper::Transform::D3::Scale::AddScale(const vec3& add_)
{
	scale += add_;
}
inline void									TexProject::Helper::Transform::D3::Scale::MulScale(const vec3& mul_)
{
	scale *= mul_;
}
#pragma endregion
#pragma region Size
inline TexProject::Helper::Transform::D3::Size::Size(vec3 size_):
	size(size_)
{
}
inline void									TexProject::Helper::Transform::D3::Size::SetSize(const vec3& size_)
{
	size = size_;
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::Size::GetSize() const
{
	return size;
}
inline void									TexProject::Helper::Transform::D3::Size::AddSize(const vec3& add_)
{
	size += add_;
}
inline void									TexProject::Helper::Transform::D3::Size::MulSize(const vec3& mul_)
{
	size *= mul_;
}
#pragma endregion
#pragma region ProjectionMatrix
inline TexProject::Helper::Transform::D3::ProjectionMatrix::ProjectionMatrix(const Projection::Type& type_)
{
	type = type_;
}
inline TexProject::Helper::Transform::D3::ProjectionMatrix::ProjectionMatrix(const Projection::Params::Orthogonal& source):
type(Projection::Type::Orthogonal)
{
	if(paramsOrthogonal != source)
	{
		pRebuild = true;
		piRebuild = true;
		paramsOrthogonal = source;
	}
}
inline TexProject::Helper::Transform::D3::ProjectionMatrix::ProjectionMatrix(const Projection::Params::Perspective& source):
type(Projection::Type::Perspective)
{
	if(paramsPerspective != source)
	{
		pRebuild = true;
		piRebuild = true;
		paramsPerspective = source;
	}
}
inline TexProject::Helper::Transform::D3::ProjectionMatrix::ProjectionMatrix(const ProjectionMatrix& source):
type(source.type)
{
	switch(source.GetProjectionType())
	{
	case Projection::Type::Orthogonal:
	{
		if(paramsOrthogonal != source.paramsOrthogonal)
		{
			pRebuild = true;
			piRebuild = true;
			paramsOrthogonal = source.paramsOrthogonal;
		}
		break;
	}
	case Projection::Type::Perspective:
	{
		if(paramsPerspective != source.paramsPerspective)
		{
			pRebuild = true;
			piRebuild = true;
			paramsPerspective = source.paramsPerspective;
		}
		break;
	}
	default: throw Exception("Forbidden projection type.");
	}
}
inline TexProject::Helper::Transform::D3::ProjectionMatrix&	TexProject::Helper::Transform::D3::ProjectionMatrix::operator = (const ProjectionMatrix& source)
{
	switch(source.GetProjectionType())
	{
	case Projection::Type::Orthogonal:
	{
		SetOrthogonal(source.paramsOrthogonal);
		break;
	}
	case Projection::Type::Perspective:
	{
		SetPerspective(source.paramsPerspective);
		break;
	}
	default: throw Exception("Forbidden projection type.");
	}
	return *this;
}
inline TexProject::Helper::Transform::D3::Projection::Type		TexProject::Helper::Transform::D3::ProjectionMatrix::GetProjectionType() const
{
	return type;
}
inline void									TexProject::Helper::Transform::D3::ProjectionMatrix::SetOrthogonal(float32 left_,float32 right_,float32 bottom_,float32 top_,float32 back_,float32 front_)
{
	type = Projection::Type::Orthogonal;
	if(paramsOrthogonal.left != left_ || paramsOrthogonal.right != right_ || paramsOrthogonal.bottom != bottom_ || paramsOrthogonal.top != top_ || paramsOrthogonal.back != back_ || paramsOrthogonal.front != front_)
	{
		pRebuild = true;
		piRebuild = true;
		paramsOrthogonal.left = left_;
		paramsOrthogonal.right = right_;
		paramsOrthogonal.bottom = bottom_;
		paramsOrthogonal.top = top_;
		paramsOrthogonal.back = back_ ;
		paramsOrthogonal.front = front_;
	}
}
inline void									TexProject::Helper::Transform::D3::ProjectionMatrix::SetOrthogonal(const Projection::Params::Orthogonal& source)
{
	type = Projection::Type::Orthogonal;
	if(paramsOrthogonal != source)
	{
		pRebuild = true;
		piRebuild = true;
		paramsOrthogonal = source;
	}
}
inline void									TexProject::Helper::Transform::D3::ProjectionMatrix::SetPerspective(float32 fov_,float32 aspect_,float32 zNear_,float32 zFar_)
{
	type = Projection::Type::Perspective;
	if(paramsPerspective.fov != fov_ || paramsPerspective.aspect != aspect_ || paramsPerspective.zNear != zNear_ || paramsPerspective.zFar != zFar_)
	{
		pRebuild = true;
		piRebuild = true;
		paramsPerspective.fov = fov_;
		paramsPerspective.aspect = aspect_;
		paramsPerspective.zNear = zNear_;
		paramsPerspective.zFar = zFar_;
	}
}
inline void									TexProject::Helper::Transform::D3::ProjectionMatrix::SetPerspective(const Projection::Params::Perspective& source)
{
	type = Projection::Type::Perspective;
	if(paramsPerspective != source)
	{
		pRebuild = true;
		piRebuild = true;
		paramsPerspective = source;
	}
}
inline TexProject::Helper::Transform::D3::Projection::Params::Orthogonal			TexProject::Helper::Transform::D3::ProjectionMatrix::GetOrthogonal() const
{
	return paramsOrthogonal;
}
inline TexProject::Helper::Transform::D3::Projection::Params::Perspective			TexProject::Helper::Transform::D3::ProjectionMatrix::GetPerspective() const
{
	return paramsPerspective;
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ProjectionMatrix::GetPMat() const
{
	if(pRebuild)
	{
		pRebuild = false;
		switch(type)
		{
		case TexProject::Helper::Transform::D3::Projection::Type::Orthogonal:
			pMat.makeProjectionOrthogonal(paramsOrthogonal.left,paramsOrthogonal.right,paramsOrthogonal.bottom,paramsOrthogonal.top,paramsOrthogonal.back,paramsOrthogonal.front);
			break;
		case TexProject::Helper::Transform::D3::Projection::Type::Perspective:
			pMat.makeProjectionPerspective(paramsPerspective.fov,paramsPerspective.aspect,paramsPerspective.zNear,paramsPerspective.zFar);
			break;
		default:
			throw("Unknown projection type.");
			break;
		}
	}
	return pMat;
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ProjectionMatrix::GetPIMat() const
{
	if(piRebuild)
	{
		piRebuild = false;
		switch(type)
		{
		case TexProject::Helper::Transform::D3::Projection::Type::Orthogonal:
			piMat.makeProjectionOrthogonalInverse(paramsOrthogonal.left,paramsOrthogonal.right,paramsOrthogonal.bottom,paramsOrthogonal.top,paramsOrthogonal.back,paramsOrthogonal.front);
			break;
		case TexProject::Helper::Transform::D3::Projection::Type::Perspective:
			piMat.makeProjectionPerspectiveInverse(paramsPerspective.fov,paramsPerspective.aspect,paramsPerspective.zNear,paramsPerspective.zFar);
			break;
		default:
			throw("Unknown projection type.");
			break;
		}
	}
	return piMat;
}
#pragma endregion
#pragma region RotateMatrix
inline TexProject::Helper::Transform::D3::RotateMatrix::RotateMatrix(const vec3& ang_):
	Angle(ang_)
{
}
inline TexProject::Helper::Transform::D3::RotateMatrix::RotateMatrix(const RotateMatrix& source):
	Angle(source.ang)
{
}
inline TexProject::Helper::Transform::D3::RotateMatrix&	TexProject::Helper::Transform::D3::RotateMatrix::operator = (const RotateMatrix& source)
{
	if(ang.x != source.ang.x || ang.y != source.ang.y || ang.z != source.ang.z)
	{
		rRebuild = true;
		riRebuild = true;
		ang = source.ang;
	}
	return *this;
}
inline void									TexProject::Helper::Transform::D3::RotateMatrix::SetAng(const vec3& ang_)
{
	if(ang.x != ang_.x || ang.y != ang_.y || ang.z != ang_.z)
	{
		rRebuild = true;
		riRebuild = true;
		ang = ang_;
	}
}
inline void									TexProject::Helper::Transform::D3::RotateMatrix::AddAng(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		rRebuild = true;
		riRebuild = true;
		ang += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::RotateMatrix::MulAng(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		rRebuild = true;
		riRebuild = true;
		ang *= mul_;
	}
}
inline void									TexProject::Helper::Transform::D3::RotateMatrix::Rotate(const vec3& val_)
{
	if(val_.x != _0f || val_.y != _0f || val_.z != _0f)
	{
		rMat = mat3::rotateZXY(val_) * GetRMat();
		ang = getAng(rMat);
		riRebuild = true;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::RotateMatrix::GetAng() const
{
	return Angle::GetAng();
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::RotateMatrix::GetRMat() const
{
	if(rRebuild)
	{
		rMat.makeRotateZXY(ang);
		rRebuild = false;
	}
	return rMat;
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::RotateMatrix::GetRIMat() const
{
	if(riRebuild)
	{
		riMat.makeRotateYXZ(-ang);
		riRebuild = false;
	}
	return riMat;
}
#pragma endregion
#pragma region ViewMatrix
inline										TexProject::Helper::Transform::D3::ViewMatrix::ViewMatrix(const vec3& pos_, const vec3& ang_):
	Position(pos_),
	RotateMatrix(ang_),
	vRebuild(true), viRebuild(true)
{
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::SetAng(const vec3& ang_)
{
	if(ang.x != ang_.x || ang.y != ang_.y || ang.z != ang_.z)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang = ang_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::AddAng(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::MulAng(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang *= mul_;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ViewMatrix::GetAng() const
{
	return RotateMatrix::GetAng();
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::SetPos(const vec3& pos_)
{
	if(pos.x != pos_.x || pos.y != pos_.y || pos.z != pos_.z)
	{
		vRebuild = true;
		viRebuild = true;
		pos = pos_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::AddPos(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		vRebuild = true;
		viRebuild = true;
		pos += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::MulPos(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		vRebuild = true;
		viRebuild = true;
		pos *= mul_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::Rotate(const vec3& val_)
{
	if(val_.x != _0f || val_.y != _0f || val_.z != _0f)
	{
		rMat = mat3::rotateZXY(val_) * rMat;
		ang = getAng(rMat);
		//rRebuild = true;
		riRebuild = true;
		vRebuild = true;
		viRebuild = true;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewMatrix::Move(const vec3& val_)
{
	AddPos(GetRMat() * val_);
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ViewMatrix::GetPos() const
{
	return Position::GetPos();
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ViewMatrix::GetRMat() const
{
	return RotateMatrix::GetRMat();
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ViewMatrix::GetRIMat() const
{
	return RotateMatrix::GetRIMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewMatrix::GetVMat() const
{
	if(vRebuild)
	{
		vMat = mat4::move(-pos) * mat4(GetRIMat());
		vRebuild = false;
	}
	return vMat;
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewMatrix::GetVIMat() const
{
	if(viRebuild)
	{
		//viMat = mat4::move(-pos) * mat4(GetRIMat());
		viMat = mat4(GetRMat()) * mat4::move(pos);
		viRebuild = false;
	}
	return viMat;
}
#pragma endregion
#pragma region ViewProjectionMatrix
inline										TexProject::Helper::Transform::D3::ViewProjectionMatrix::ViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Orthogonal proj_):
	ViewMatrix(pos_,ang_),
	ProjectionMatrix(proj_),
	vpRebuild(true), vpiRebuild(true)
{
}
inline										TexProject::Helper::Transform::D3::ViewProjectionMatrix::ViewProjectionMatrix(const vec3& pos_, const vec3& ang_, const Projection::Params::Perspective proj_):
	ViewMatrix(pos_,ang_),
	ProjectionMatrix(proj_),
	vpRebuild(true), vpiRebuild(true)
{
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetAng(const vec3& ang_)
{
	if (ang.x != ang_.x || ang.y != ang_.y || ang.z != ang_.z)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		ang = ang_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::AddAng(const vec3& add_)
{
	if (add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		ang += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::MulAng(const vec3& mul_)
{
	if (mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		vRebuild = true;
		viRebuild = true;
		rRebuild = true;
		riRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		ang *= mul_;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetAng() const
{
	return ViewMatrix::GetAng();
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetPos(const vec3& pos_)
{
	if (pos.x != pos_.x || pos.y != pos_.y || pos.z != pos_.z)
	{
		vRebuild = true;
		viRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		pos = pos_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::AddPos(const vec3& add_)
{
	if (add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		vRebuild = true;
		viRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		pos += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::MulPos(const vec3& mul_)
{
	if (mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		vRebuild = true;
		viRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		pos *= mul_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::Rotate(const vec3& val_)
{
	if (val_.x != _0f || val_.y != _0f || val_.z != _0f)
	{
		rMat = mat3::rotateZXY(val_) * rMat;
		ang = getAng(rMat);
		//rRebuild = true;
		riRebuild = true;
		vRebuild = true;
		viRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::Move(const vec3& val_)
{
	AddPos(GetRMat() * val_);
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetPos() const
{
	return Position::GetPos();
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetOrthogonal(float32 left_, float32 right_, float32 bottom_, float32 top_, float32 back_, float32 front_)
{
	//ProjectionMatrix::SetOrthogonal(left_, right_, bottom_, top_, back_, front_);
	type = Projection::Type::Orthogonal;
	if (paramsOrthogonal.left != left_ || paramsOrthogonal.right != right_ || paramsOrthogonal.bottom != bottom_ || paramsOrthogonal.top != top_ || paramsOrthogonal.back != back_ || paramsOrthogonal.front != front_)
	{
		pRebuild = true;
		piRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		paramsOrthogonal.left = left_;
		paramsOrthogonal.right = right_;
		paramsOrthogonal.bottom = bottom_;
		paramsOrthogonal.top = top_;
		paramsOrthogonal.back = back_;
		paramsOrthogonal.front = front_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetOrthogonal(const Projection::Params::Orthogonal& source)
{
	//ProjectionMatrix::SetOrthogonal(source);
	type = Projection::Type::Orthogonal;
	if (paramsOrthogonal != source)
	{
		pRebuild = true;
		piRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		paramsOrthogonal = source;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetPerspective(float32 fov_, float32 aspect_, float32 zNear_, float32 zFar_)
{
	//ProjectionMatrix::SetPerspective(fov_, aspect_, zNear_, zFar_);
	type = Projection::Type::Perspective;
	if (paramsPerspective.fov != fov_ || paramsPerspective.aspect != aspect_ || paramsPerspective.zNear != zNear_ || paramsPerspective.zFar != zFar_)
	{
		pRebuild = true;
		piRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		paramsPerspective.fov = fov_;
		paramsPerspective.aspect = aspect_;
		paramsPerspective.zNear = zNear_;
		paramsPerspective.zFar = zFar_;
	}
}
inline void									TexProject::Helper::Transform::D3::ViewProjectionMatrix::SetPerspective(const Projection::Params::Perspective& source)
{
	//ProjectionMatrix::SetPerspective(source);
	type = Projection::Type::Perspective;
	if (paramsPerspective != source)
	{
		pRebuild = true;
		piRebuild = true;
		vpRebuild = true;
		vpiRebuild = true;
		paramsPerspective = source;
	}
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetRMat() const
{
	return ViewMatrix::GetRMat();
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetRIMat() const
{
	return ViewMatrix::GetRIMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetVMat() const
{
	return ViewMatrix::GetVMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetVIMat() const
{
	return ViewMatrix::GetVIMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetPMat() const
{
	return ProjectionMatrix::GetPMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetPIMat() const
{
	return ProjectionMatrix::GetPIMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetVPMat() const
{
	if (vpRebuild)
	{
		vpRebuild = false;
		vpMat = GetVMat() * mat4::scale(vec3(1.0f, 1.0f, -1.0f)) * GetPMat();
	}
	return vpMat;
	//return GetVMat() * mat4::scale(vec3(1.0f, 1.0f, -1.0f)) * GetPMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ViewProjectionMatrix::GetVPIMat() const
{
	if (vpiRebuild)
	{
		vpiRebuild = false;
		vpiMat = GetPIMat() * mat4::scale(vec3(1.0f, 1.0f, -1.0f)) * GetVIMat();
	}
	return vpiMat;
	//return GetPIMat() * mat4::scale(vec3(1.0f, 1.0f, -1.0f)) * GetVIMat();
}
#pragma endregion
#pragma region ModelMatrix
inline TexProject::Helper::Transform::D3::ModelMatrix::ModelMatrix(const vec3& pos_,const vec3& ang_,const vec3& scl_):
	RotateMatrix(ang_),
	Position(pos_),
	Scale(scl_)
{
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::SetAng(const vec3& ang_)
{
	if(ang.x != ang_.x || ang.y != ang_.y || ang.z != ang_.z)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang = ang_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::AddAng(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::MulAng(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		ang *= mul_;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ModelMatrix::GetAng() const
{
	return RotateMatrix::GetAng();
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::SetScale(const vec3& scale_)
{
	if(scale.x != scale_.x || scale.y != scale_.y || scale.z != scale_.z)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		scale = scale_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::AddScale(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		scale += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::MulScale(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		mRebuild = true;
		miRebuild = true;
		rRebuild = true;
		riRebuild = true;
		scale *= mul_;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ModelMatrix::GetScale() const
{
	return Scale::GetScale();
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::SetPos(const vec3& pos_)
{
	if(pos.x != pos_.x || pos.y != pos_.y || pos.z != pos_.z)
	{
		mRebuild = true;
		miRebuild = true;
		pos = pos_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::AddPos(const vec3& add_)
{
	if(add_.x != _0f || add_.y != _0f || add_.z != _0f)
	{
		mRebuild = true;
		miRebuild = true;
		pos += add_;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::MulPos(const vec3& mul_)
{
	if(mul_.x != _1f || mul_.y != _1f || mul_.z != _1f)
	{
		mRebuild = true;
		miRebuild = true;
		pos *= mul_;
	}
}
inline TexProject::vec3						TexProject::Helper::Transform::D3::ModelMatrix::GetPos() const
{
	return Position::GetPos();
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::Rotate(const vec3& val_)
{
	if(val_.x != _0f || val_.y != _0f || val_.z != _0f)
	{
		rMat = mat3::rotateZXY(val_) * GetRMat();
		ang = getAng(rMat);
		rRebuild = true;
		riRebuild = true;
		mRebuild = true;
		miRebuild = true;
	}
}
inline void									TexProject::Helper::Transform::D3::ModelMatrix::Move(const vec3& val_)
{
	AddPos(GetRMat() * val_);
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ModelMatrix::GetRMat() const
{
	return RotateMatrix::GetRMat();
}
inline TexProject::mat3						TexProject::Helper::Transform::D3::ModelMatrix::GetRIMat() const
{
	return RotateMatrix::GetRIMat();
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ModelMatrix::GetMMat() const
{
	if(mRebuild)
	{
		mRebuild = false;
		mMat = mat4::scale(scale) * mat4(GetRMat()) * mat4::move(pos);
	}
	return mMat;
}
inline TexProject::mat4						TexProject::Helper::Transform::D3::ModelMatrix::GetMIMat() const
{
	if(miRebuild)
	{
		miRebuild = false;
		miMat = mat4::move(-pos) * mat4(GetRIMat()) * mat4::scale(1.0f / scale);
	}
	return miMat;
}
#pragma endregion
#pragma endregion
#pragma endregion

















